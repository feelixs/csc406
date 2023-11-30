/*----------------------------------------------------------------------------------+
 |																					|
 |	linearInterpolation.cpp		Trajectory generation by linear interpolation		|
 |								between hard-coded waypoints						|
 |																					|
 |	Execution:	 Hit the space bar to execute the trajectory						|
 |																					|
 |	Author:		Jean-Yves Hervé,	University of Rhode Island						|
 |									Dept. of Com[puter Science and Statistics		|
 |									3D Group for Interactive Visualization			|
 |	Fall 2010, rev  Fall 2021														|
 +---------------------------------------------------------------------------------*/
 
#include <memory>
#include <cstdlib>
#include <cstdio>
//
#include "glPlatform.h"
#include "LinearInterpolator.h"
#include "Vehicle.h"

using namespace std;

void myDisplay(void);
void myResize(int w, int h);
void myMouse(int b, int s, int x, int y);
void myKeyboard(unsigned char c, int x, int y);
void myTimeOut(int id);
void myInit(void);
vector<vector<float> > initKeyframes();

const vector<vector<float> > WAY_POINT_LIST = initKeyframes();
const unsigned int NB_WAY_PTS = static_cast<unsigned int>(WAY_POINT_LIST.size());
const unsigned int DIM_STATE_VECT = static_cast<unsigned int>(WAY_POINT_LIST[0].size());

Vehicle* myVehicle = nullptr;
bool gAnimate = false;
const float gTimeIncr = 0.001f;
const int   msecs = 10;

//	This is the function that does the actual scene drawing
//
void myDisplay(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (myVehicle != nullptr)
        myVehicle->draw();
        
	//	We were drawing into the back buffer, now it should be brought
	//	to the forefront.
	glutSwapBuffers();
}

//	This callback function is called when the window is resized
//	(generally by the user of the application).
//
void myResize(int w, int h)
{
	//	update projection transformations
	glViewport(0, 0, w, h);
	
	//	When it's done, request a refresh of the display
	glutPostRedisplay();
}


//	This function is called when a mouse event occurs.  This event, of type s
//	(up, down, dragged, etc.), occurs on a particular button of the mouse.
//
void myMouse(int b, int s, int x, int y)
{
	switch (b)
	{
		case GLUT_LEFT_BUTTON:
			if (s == GLUT_DOWN)
			{
				//	do something
			}
			else if (s == GLUT_UP)
			{
				// do something else
			}
			break;
			
		default:
			break;
	}
}

//	This callback function is called when a keyboard event occurs
//
void myKeyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
		case 27:
			exit(0);
			break;
			
		case ' ':
		    gAnimate=!gAnimate;
		    break;
		    
		default:
			break;
	}
}


//	This function is called after (at least) the specified time has ellapsed
//	since it was last "primed" (pushed back on the queue).
//
void myTimeOut(int id)
{
	//	Set up next timer event
	glutTimerFunc(msecs, myTimeOut, 0);

    if (gAnimate)
        myVehicle->update(gTimeIncr * msecs);

	glutPostRedisplay();
}


void myInit(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	
	shared_ptr<KeyframeAnimator> anim = make_shared<LinearInterpolator>(WAY_POINT_LIST);
	myVehicle = new Vehicle(anim, true, true);
}

vector<vector<float> > initKeyframes()
{
	vector<vector<float> > frames;

//					  x_i  y_i  θ_i   t_i
	vector<float> f0{.1f, .1f, 90.f, 0.f};
	frames.push_back(f0);

	#if LONG_PATH
		vector<float> f1{.2f, .7f, 0.f, 2.f}
		frames.push_back(f1);
	#endif

	vector<float> f2{.5f, .3f, 0.f, 3.f};
	frames.push_back(f2);

	#if LONG_PATH
		vector<float> f3{.5f, .9f, 90.f, 4.f}
		frames.push_back(f3);
	#endif

	vector<float> f4{0.7f, 0.5f, 60.f, 6.f};
	frames.push_back(f4);
	vector<float> f5{0.8f, 0.9f, 170.f, 8.f};
	frames.push_back(f5);

	#if LONG_PATH
		vector<float> f6{0.9f, 0.1f, 270.f, 9.f};
		frames.push_back(f6);
	#endif
	
	vector<float> f7{0.2f, 0.3f, 270.f, 10.f};
	frames.push_back(f7);

	return frames;
}

int main(int argc, char** argv)
{
	//	Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 40);
	glutCreateWindow(argv[0]);
	
	//	set up the callbacks
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myResize);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
	glutTimerFunc(msecs, myTimeOut, 0);
	
	//	Now we can do application-level
	myInit();

	//	Now we enter the main loop of theprogram and to a large extend
	//	"loose control" over its execution.  The callback functions that 
	//	we set up earlier will be called when the corresponding event
	//	occurs
	glutMainLoop();
	
	//	This will never be executed (the exit point will be in one of the
	//	call back functions).
	return 0;
}
