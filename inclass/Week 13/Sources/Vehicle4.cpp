/*----------------------------------------------------------------------------------+
 |																					|
 |	Vehicle4.cpp	Trajectory generation by polynomial fitting						|
 |																					|
 |	The options for this program are												|
 |		o to use LU factorization or SVD decomposition to solve the system of		|
 |			linear equations. This is done by setting LU_VERSION to 1 or 0			|
 |		o to generate a trajectory for few or many waypoints.  This is done by		|
 |			setting LONG_PATH to 0 or 1												|
 |																					|
 |	Author:		Jean-Yves Hervé,	University of Rhode Island						|
 |									Dept. of Com[puter Science and Statistics		|
 |									3D Group for Interactive Visualization			|
 |	Fall 2010, rev  Fall 2022														|
 +---------------------------------------------------------------------------------*/
 
#define LU_VERSION  1
#define LONG_PATH   1

#include <iostream>
#include <math.h>
//
#include <tnt.h>
#include <tnt_cmat.h>
#include <tnt_vec.h>
#if LU_VERSION
    #include<jama_lu.h>
#else
    #include <jama_svdMod.h>
#endif
//
#include "Vehicle4.h"

using namespace std;

//-----------------------------------------------------
//  Polynomial fit
//-----------------------------------------------------

//  I use this to slow/speed up the display.  Normally, I would not need to do this as I
//  would use "real" time in my waypoints array and then normalized (to the range [0,1]
//  time for my interpolation calculations.
const float TIME_FACTOR = 0.09f;

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


Vehicle4::Vehicle4(void)
	:	_x(WAY_POINT[0][0]),
		_y(WAY_POINT[0][1]),
		_angle(WAY_POINT[0][2]),
		_ut(0.f),
		_path(NULL),
		_recordPath(true),
		_a(NULL)		
{
    //----------------------------------------------------
    //  1. Initialize the TNT matrices of the SLE
    //----------------------------------------------------
    //  (Vandermonde) matrix of the system. Its terms are  1, ti, ti^2, ti^3... for row i
	TNT::Array2D<double>A(NB_WAY_PTS, NB_WAY_PTS);  
    // right-side term matrix.  Its terms are xi, yi, thetai for all waypoints
	TNT::Array2D<double>B(NB_WAY_PTS, 3); 
	// solution of the SLE: the coefficients of the x, y, theta polynomials  
	TNT::Array2D<double> X(NB_WAY_PTS, 3); 

    for (int i=0; i<NB_WAY_PTS; i++)
    {
        double tPowj = 1.;
        
        for (int j=0; j<NB_WAY_PTS; j++)
        {
            A[i][j] = tPowj;
            tPowj *= WAY_POINT[i][3];
        }

        for (int k=0; k<3; k++)
            B[i][k] = WAY_POINT[i][k];
        
    }
    
    //----------------------------------------------------
    //  2. Solve the SLE
    //----------------------------------------------------
    #if LU_VERSION   
        JAMA::LU<double> * aLU =  new JAMA::LU<double>(A);
        X = aLU->solve(B);
    #else
        JAMA::SVD<double> * aSVD =  new JAMA::SVD<double>(A);
        TNT::Array2D<double>U, V;
        TNT::Array1D<double>S;
        aSVD->getU(U);
        aSVD->getV(V);
        aSVD->getSingularValues(S);
    #endif    
    
    //----------------------------------------------------
    //  3. Copy the results in my instance variables
    //----------------------------------------------------
    _a = new GLfloat*[NB_WAY_PTS];
    for (int i=0; i<NB_WAY_PTS; i++)
    {
        _a[i] = new GLfloat[3];
        for (int k=0; k<3; k++)
            _a[i][k] = static_cast<float>(X[i][k]);
    }
}
        
Vehicle4::~Vehicle4(void)
{
    for (int i=0; i< (int)_path.size(); i++)
        delete []_path[i];
    _path.clear();
}
        
void Vehicle4::update(float dt)
{
    if (_ut < 1.f)
    {
        _ut += TIME_FACTOR * dt;
        
        GLfloat x =0, y=0, theta=0;
        GLfloat tPowj=1;
        for (int j=0; j<NB_WAY_PTS; j++)
        {
            x += _a[j][0] * tPowj;
            y += _a[j][1] * tPowj;
            theta += _a[j][2] * tPowj;
            tPowj *= _ut;
        }
        setPosition(x, y);
        setOrientation(theta);
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


void Vehicle4::draw(void)
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

void Vehicle4::setPosition(GLfloat theX, GLfloat theY)
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

void Vehicle4::setOrientation(GLfloat theAngle)
{
    _angle = theAngle;
}


