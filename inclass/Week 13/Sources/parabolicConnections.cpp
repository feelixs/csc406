/*----------------------------------------------------------------------------------+
 |																					|
 |	cubicSplines.cpp	Trajectory generation by linear interpolation segments		|
 |						with parabolic connections (does not pass through the		|
 |						waypoints													|
 |																					|
 |	Execution:	 Hit the space bar to execute the trajectory						|
 |																					|
 |	Author:		Jean-Yves Hervé,	University of Rhode Island						|
 |									Dept. of Com[puter Science and Statistics		|
 |									3D Group for Interactive Visualization			|
 |	Fall 2010, rev  Fall 2021														|
 +---------------------------------------------------------------------------------*/
 
#include <stdlib.h>
#include <stdio.h>
//
#include "glPlatform.h"
#include "Vehicle6.h"

void myDisplay(void);
void myResize(int w, int h);
void myMouse(int b, int s, int x, int y);
void myKeyboard(unsigned char c, int x, int y);
void myTimeOut(int id);
void myInit(void);


Vehicle6* myVehicle = NULL;
bool gAnimate = false;
const float gTimeIncr = 0.001f;
const int   msecs = 20;

//	This is the function that does the actual scene drawing
//
void myDisplay(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (myVehicle != NULL)
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
    if (gAnimate)
        myVehicle->update(gTimeIncr * msecs);

	glutPostRedisplay();	

	//	Set up next timer event
	glutTimerFunc(msecs, myTimeOut, 0);

}


void myInit(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
		
	myVehicle = new Vehicle6();
	
	myDisplay();
}


int main(int argc, char** argv)
{
	//	Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
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
