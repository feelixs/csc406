/*----------------------------------------------------------------------------------+
 |																					|
 |	Vehicle6.cpp	Trajectory generation by linear interpolation with				|
 |					slope-continuity-preserving parabolic connections about			|
 |					the waypoints													|
 |																					|
 |	The options for this program are												|
 |		o to generate a trajectory for few or many waypoints.  This is done by		|
 |			setting LONG_PATH to 0 or 1												|
 |																					|
 |	Author:		Jean-Yves Hervé,	University of Rhode Island						|
 |									Dept. of Com[puter Science and Statistics		|
 |									3D Group for Interactive Visualization			|
 |	Fall 2010, rev  Fall 2021														|
 +---------------------------------------------------------------------------------*/
 
#define LONG_PATH   0

#include <iostream>
#include <math.h>
//
#include "Vehicle6.h"

using namespace std;

//-----------------------------------------------------
//  Linear interpolation
//-----------------------------------------------------

//  I use this to slow/speed up the display.  Normally, I would not need to do this as I
//  would use "real" time in my waypoints array and then normalized (to the range [0,1]
//  time for my interpolation calculations.
const float TIME_FACTOR = 0.05f;

//  The array of way points stores for each point {x, y, theta, time}, with t in [0, 1]
//  and increasing. 
//  I hard-code these here so that they are easier to see.  In a real application, the
//  waypoint array would be allocated dynamically and probably passed as a parameter
//  to the constructor.
#if LONG_PATH
    const int   NB_WAY_PTS = 8;
#else
    const int   NB_WAY_PTS = 5;
#endif

const float WAY_POINT[NB_WAY_PTS][4] = {{.1f, .1f, 90.f, 0.f}, 
#if LONG_PATH
                                        {.2f, .7f, 0.f, 0.25f}, 
#endif
                                        {.5f, .3f, 0.f, .3f}, 
#if LONG_PATH
                                        {.5f, .9f, 90.f, .4f}, 
#endif
                                        {0.7f, 0.5f, 60.f, .6f}, 
                                        {0.8f, 0.9f, 170.f, 0.8f}, 
#if LONG_PATH
                                        {0.9f, 0.1f, 270.f, .9f},
#endif
                                        {0.2f, 0.3f, 270.f, 1.f}};


const int NB_PARABOLIC_SEGMENTS = NB_WAY_PTS - 2;

//  The parabolic segment will start DT before the time set for the waypoint and end DT after the
//  time set for the waypoint.  The duration of a parabolic connection is therefore 2 DT.
//  Alternatively, I could have set a maximum (absolute) value for the x, y, theta accelerations,
//  and computed a value of DT so that the acceleration along x, y, theta does not exceed this
//  max acceleration.  
//  Reminder: we are transitioning in 2DT from a linear segment of slope m1 to a segment of
//  slope m2, so the acceleration is a = |m2-m1|/2DT
const float DT = 0.01f; 


Vehicle6::Vehicle6(void)
	:	_x(WAY_POINT[0][0]),
		_y(WAY_POINT[0][1]),
		_angle(WAY_POINT[0][2]),
		_ut(0.f),
		_a(NULL),		
		_path(NULL),
		_recordPath(true)
{
    _ut = 0;
    
    //  allocate the array of parabolic segment coefficients
    _a = new GLfloat**[NB_PARABOLIC_SEGMENTS];
    
    for (int i=0; i<NB_PARABOLIC_SEGMENTS; i++) 
    {
        //  parabolic segment i connects the segments [m(i), m(i+1)] and [m(i+1), m(i+2)]
        _a[i] = new GLfloat*[3];        //  3 coefficients per parabola
        for (int j=0; j<3; j++)
            _a[i][j] = new GLfloat[3];   //  x, y, theta;
            
        //  compute the slope on both sides of the waypoint
        float vx1 = (WAY_POINT[i+1][0] - WAY_POINT[i][0])/(WAY_POINT[i+1][3] - WAY_POINT[i][3]);
        float vx2 = (WAY_POINT[i+2][0] - WAY_POINT[i+1][0])/(WAY_POINT[i+2][3] - WAY_POINT[i+1][3]);
        float vy1 = (WAY_POINT[i+1][1] - WAY_POINT[i][1])/(WAY_POINT[i+1][3] - WAY_POINT[i][3]);
        float vy2 = (WAY_POINT[i+2][1] - WAY_POINT[i+1][1])/(WAY_POINT[i+2][3] - WAY_POINT[i+1][3]);
        float vtheta1 = (WAY_POINT[i+1][2] - WAY_POINT[i][2])/(WAY_POINT[i+1][3] - WAY_POINT[i][3]);
        float vtheta2 = (WAY_POINT[i+2][2] - WAY_POINT[i+1][2])/(WAY_POINT[i+2][3] - WAY_POINT[i+1][3]);
        //
        //  The parabolic eq is at time t = tk + tau and -DT ≤ tau ≤ DT (tk is a way point time)
        //              x(t) = a[2]*tau^2 + a[1]*tau + a[0],  
        //  a[2] is 1/2 the acceleration
        //  a[1] is computed so that dx/dt(tk-DT) = vx1 (tangent to linear segment)
        //  a[0] is computed so that x(-DT) = Xk - vx1*DT (continuous at junction)
        _a[i][2][0] = (vx2-vx1)/(4*DT);
        _a[i][1][0] = vx1 + 2*_a[i][2][0]*DT;
        _a[i][0][0] = WAY_POINT[i+1][0] - _a[i][2][0]*DT*DT + (_a[i][1][0]-vx1)*DT;
        //
        _a[i][2][1] = (vy2-vy1)/(4*DT);
        _a[i][1][1] = vy1 + 2*_a[i][2][1]*DT;
        _a[i][0][1] = WAY_POINT[i+1][1] - _a[i][2][1]*DT*DT + (_a[i][1][1]-vy1)*DT;
        //
        _a[i][2][2] = (vtheta2-vtheta1)/(4*DT);
        _a[i][1][2] = vtheta1 + 2*_a[i][2][2]*DT;
        _a[i][0][2] = WAY_POINT[i+1][2] - _a[i][2][2]*DT*DT + (_a[i][1][2]-vtheta1)*DT;
    }
    
#if 0
printf("{");
for (int i=0; i<NB_PARABOLIC_SEGMENTS; i++)
{
	printf("{");
	for(int j=0; j<3; j++)
	{
		printf("{%f,%f,%f}", _a[i][j][0], _a[i][j][1], _a[i][j][2]);
		if (j<2)
			printf(",");
	}
	printf("}");
	if (i<NB_PARABOLIC_SEGMENTS-2)
		printf(",");
}
printf("}");

#endif

    _recordPath = true;
    setPosition(WAY_POINT[0][0], WAY_POINT[0][1]);
    setOrientation(WAY_POINT[0][2]);
}
        
Vehicle6::~Vehicle6(void)
{
    for (int i=0; i<(int)_path.size(); i++)
        delete []_path[i];
    _path.clear();
}
        
void Vehicle6::update(float dt)
{
    if (_ut < 1.f)
    {
        _ut += TIME_FACTOR * dt;

        //  which interval do we fall into?
        for (int i=1; i<NB_WAY_PTS; i++)
        {
            if (WAY_POINT[i][3]+DT >= _ut)
            {
                float x, y, angle;

                //  if we fail in the linear segment [t_<i-1>, t_<i> - DT]
                //  or if this the last segment (no parabolic connection)
                if ((i==NB_WAY_PTS-1) || (WAY_POINT[i][3]-DT >= _ut))
                {
                
                    //  compute interpolation factor
                    float s = (_ut - WAY_POINT[i-1][3]) / (WAY_POINT[i][3] - WAY_POINT[i-1][3]);
                    
                    x  = WAY_POINT[i-1][0] + s* (WAY_POINT[i][0] - WAY_POINT[i-1][0]);
                    y  = WAY_POINT[i-1][1] + s* (WAY_POINT[i][1] - WAY_POINT[i-1][1]);
                    angle  = WAY_POINT[i-1][2] + s* (WAY_POINT[i][2] - WAY_POINT[i-1][2]);
                }
                //  if we fall in the parabolic segment at way point i --> segment i-1
                else
                {
                    float   tau = _ut - WAY_POINT[i][3],
                            tau2 = tau*tau;
                    
                    x = _a[i-1][2][0]*tau2 + _a[i-1][1][0]*tau + _a[i-1][0][0];
                    y = _a[i-1][2][1]*tau2 + _a[i-1][1][1]*tau + _a[i-1][0][1];
                    angle = _a[i-1][2][2]*tau2 + _a[i-1][1][2]*tau + _a[i-1][0][2];
                }
                                    
                setPosition(x, y);
                setOrientation(angle);
                
                break;
            }
        }
    }
    //  we have reached the last point and we stop recording
    else
    {
        setPosition(WAY_POINT[NB_WAY_PTS-1][0], WAY_POINT[NB_WAY_PTS-1][1]);
        setOrientation(WAY_POINT[NB_WAY_PTS-1][2]);
        _ut = 1.f;
        _recordPath = false;
    }        
}


void Vehicle6::draw(void)
{
    glPushMatrix();

    //  display the way points in green
    glColor4f(0.f, 1.f, 0.f, 1.f);
    for (int i=0; i<NB_WAY_PTS; i++)
    {
        glPushMatrix();
        glTranslatef(WAY_POINT[i][0], WAY_POINT[i][1], 0.f);
        glRotatef(WAY_POINT[i][2], 0.f, 0.f, 1.f);
        glBegin(GL_POLYGON);
            glVertex2f(0.04f, 0.f);
            glVertex2f(-0.03f, 0.01f);
            glVertex2f(-0.03f, -0.01f);
        glEnd();
        glPopMatrix();
    }    
    
    //  display the path so far in blue
    if (_path.size()>1) 
    {
        glBegin(GL_LINE_STRIP);
        glColor4f(0.f, 0.f, 1.f, 1.f);
        for (int i=0; i< (int)(_path.size()); i++)
            glVertex2fv(_path[i]);
        glEnd();
    }
    
    //  then display the vehicle's current location in red
    glTranslatef(_x, _y, 0.f);
    glRotatef(_angle, 0.f, 0.f, 1.f);
    glColor4f(1.f, 0.f, 0.f, 1.f);
    glBegin(GL_POLYGON);
        glVertex2f(0.04f, 0.f);
        glVertex2f(-0.03f, 0.01f);
        glVertex2f(-0.03f, -0.01f);
    glEnd();

    glPopMatrix();
}

void Vehicle6::setPosition(GLfloat theX, GLfloat theY)
{
    _x = theX;
    _y = theY;
    
    if (_recordPath)
    {
        GLfloat *pt = new GLfloat[2];
        pt[0] = _x;
        pt[1] = _y;
        _path.push_back(pt);
    }
}

void Vehicle6::setOrientation(GLfloat theAngle)
{
    _angle = theAngle;
}
