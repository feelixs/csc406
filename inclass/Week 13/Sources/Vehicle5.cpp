/*----------------------------------------------------------------------------------+
 |																					|
 |	Vehicle5.cpp	Trajectory generation by cubic spline fitting					|
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
 |	Fall 2010, rev  Fall 2021														|
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
    #include <jama_svd.h>
#endif
//
#include "Vehicle5.h"

using namespace std;

TNT::Array2D<double> transpose(const TNT::Array2D<double>& mat);
TNT::Array2D<double> product(const TNT::Array2D<double>& matA, const TNT::Array2D<double>& matB);
TNT::Array1D<double> product(const TNT::Array2D<double>& mat, const TNT::Array1D<double>& vect);

//  I use this to slow/speed up the display.  Normally, I would not need to do this as I
//  would use "real" time in my waypoints array and then normalized (to the range [0,1]
//  time for my interpolation calculations.
const float TIME_FACTOR = 0.04f;

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

const int   NB_SEGMENTS = NB_WAY_PTS-1;

Vehicle5::Vehicle5(void)
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
	TNT::Array2D<double>A(4*NB_SEGMENTS, 4*NB_SEGMENTS, 0.0);  
    // right-side term matrix.  Its terms are xi, yi, thetai for all waypoints
	TNT::Array2D<double>B(4*NB_SEGMENTS, 3); 
	// solution of the SLE: the coefficients of the x, y, theta polynomials  
	TNT::Array2D<double> X(4*NB_SEGMENTS, 3); 

    //  initialize the first two and last two rows of the matrix.  These correspond to the
    //  conditions at the path's endpoints.
    A[0][0] = 1; 
    B[0][0] = WAY_POINT[0][0]; B[0][1] = WAY_POINT[0][1]; B[0][2] = WAY_POINT[0][2];
    //
    A[1][1] = 1;
//    B[1][0] = B[1][1] = B[1][2] = 1.0;
    B[1][0] = B[1][1] = B[1][2] = 0.0;
    //
    A[4*NB_SEGMENTS-2][4*NB_SEGMENTS-4] = A[4*NB_SEGMENTS-2][4*NB_SEGMENTS-3]
                                        = A[4*NB_SEGMENTS-2][4*NB_SEGMENTS-2]
                                        = A[4*NB_SEGMENTS-2][4*NB_SEGMENTS-1]
                                        = A[4*NB_SEGMENTS-1][4*NB_SEGMENTS-3] = 1.0;
    B[4*NB_SEGMENTS-2][0] = WAY_POINT[NB_WAY_PTS-1][0]; 
    B[4*NB_SEGMENTS-2][1] = WAY_POINT[NB_WAY_PTS-1][1]; 
    B[4*NB_SEGMENTS-2][2] = WAY_POINT[NB_WAY_PTS-1][2];
    A[4*NB_SEGMENTS-1][4*NB_SEGMENTS-2] = 2.0;
    A[4*NB_SEGMENTS-1][4*NB_SEGMENTS-1] = 3.0;
    B[4*NB_SEGMENTS-1][0] = B[4*NB_SEGMENTS-1][1] = B[4*NB_SEGMENTS-1][2] = 0.0;
    //
    //  Now fill in the values for the connections at interior points                                
    for (int i=1; i<NB_WAY_PTS-1; i++)
    {
        int k = 4*(i-1)+2;
        int l = 4*(i-1);
        //
        A[k][l] = A[k][l+1] = A[k][l+2] = A[k][l+3] = 1;
        B[k][0] = WAY_POINT[i][0];
        B[k][1] = WAY_POINT[i][1];
        B[k][2] = WAY_POINT[i][2];
        //
        A[k+1][l+1] = 1.0;
        A[k+1][l+2] = 2.0;
        A[k+1][l+3] = 3.0;
        A[k+1][l+5] = -1.0;
        B[k+1][0] = B[k+1][1] = B[k+1][2] = 0.0;
        //
        A[k+2][l+2] = 2.0;
        A[k+2][l+3] = 6.0;
        A[k+2][l+6] = -2.0;
        B[k+2][0] = B[k+2][1] = B[k+2][2] = 0.0;
        //
        A[k+3][l+4] = 1;
        B[k+3][0] = WAY_POINT[i][0];
        B[k+3][1] = WAY_POINT[i][1];
        B[k+3][2] = WAY_POINT[i][2];
    }
    
    //----------------------------------------------------
    //  2. Solve the SLE
    //----------------------------------------------------
    #if LU_VERSION   
        JAMA::LU<double> * aLU =  new JAMA::LU<double>(A);
        X = aLU->solve(B);
    #else
        JAMA::SVD<double> aSVD = JAMA::SVD<double>(A);
        TNT::Array2D<double>U, V;
        TNT::Array1D<double>S;
        aSVD.getU(U);
        aSVD.getV(V);
        aSVD.getSingularValues(S);

		TNT::Array2D<double> Ut = transpose(U);

		TNT::Array2D<double> tempArray =  product(Ut, B);
		
		// scale by sigma elements
		for (int i=0; i<A.dim1(); i++) {
			for (int j=0; j<3; j++) {
				tempArray[i][j] /= S[i];
			}
		}
		
		X = product(V, tempArray);

    #endif
    
    //----------------------------------------------------
    //  3. Copy the results in my instance variables
    //----------------------------------------------------
    _a = new GLfloat**[NB_SEGMENTS];
    for (int i=0; i<NB_SEGMENTS; i++)
    {
        _a[i] = new GLfloat*[4];        //  a0, a1, a2, a3
        for (int j=0; j<4; j++)
        {
            _a[i][j] = new GLfloat[3];  //  x, y, theta
            
            for (int k=0; k<3; k++)
                _a[i][j][k] = static_cast<float>(X[4*i+j][k]);

        }
    }
}
        
Vehicle5::~Vehicle5(void)
{
    for (int i=0; i<(int)_path.size(); i++)
        delete []_path[i];
    _path.clear();
}
        
void Vehicle5::update(float dt)
{
    if (_ut < 1.f)
    {
        _ut += TIME_FACTOR * dt;

        //  which interval do we fall into?
        for (int i=0; i<NB_WAY_PTS; i++)
        {
            if (WAY_POINT[i][3] >= _ut)
            {
                int j = i-1;
                //we fall in the interval [j, j+1] --> segment Sj
                
                //  compute scaled time along segment 0 ≤ tau ≤ 1
                float   tau = (_ut - WAY_POINT[j][3]) / (WAY_POINT[j+1][3] - WAY_POINT[j][3]);
                float   tau2 = tau*tau,
						tau3 = tau*tau2;
                        
                //  compute position and angle using cubic equation
                float x  = _a[j][3][0]*tau3 + _a[j][2][0]*tau2 + _a[j][1][0]*tau + _a[j][0][0];
                float y  = _a[j][3][1]*tau3 + _a[j][2][1]*tau2 + _a[j][1][1]*tau + _a[j][0][1];
                float angle  = _a[j][3][2]*tau3 + _a[j][2][2]*tau2 + _a[j][1][2]*tau + _a[j][0][2];
                
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


void Vehicle5::draw(void)
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

void Vehicle5::setPosition(GLfloat theX, GLfloat theY)
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

void Vehicle5::setOrientation(GLfloat theAngle)
{
    _angle = theAngle;
}

TNT::Array2D<double> transpose(const TNT::Array2D<double>& mat)
{
	int m = mat.dim1(),
		n = mat.dim2();
	TNT::Array2D<double> transpMat(n, m);
	
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
			transpMat[j][i] = mat[i][j];
		
	return transpMat;
}

TNT::Array2D<double> product(const TNT::Array2D<double>& matA, const TNT::Array2D<double>& matB)
{
	int m = matA.dim1(),
		n = matA.dim2(),
		p = matB.dim2();
		
	if (matB.dim1() != n)
	{
		cout << "Matrix dimensions don't match in product function." << endl;
		exit(1);
	}
	TNT::Array2D<double> prod(m, p);
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<p; i++)
		{
			prod[i][j] = 0.f;
			for (int k=0; j<p; i++)
			{
				prod[i][j] += matA[i][k]*matB[k][j];
			}
		}
	}

	return prod;
}

TNT::Array1D<double> product(const TNT::Array2D<double>& mat, const TNT::Array1D<double>& vect)
{
	int m = mat.dim1(),
		n = mat.dim2();
		
	if (vect.dim() != n)
	{
		cout << "Matrix and vector dimensions don't match in product function." << endl;
		exit(1);
	}
	TNT::Array1D<double> prod(m);
	for (int i=0; i<m; i++)
	{
		prod[i] = 0.f;
		for (int j=0; j<n; j++)
		{
			prod[i] += mat[i][j]*vect[j];
		}
	}

	return prod;
}
