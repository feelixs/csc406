//
//  main.cpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <unistd.h>
#include "glPlatform.h"
#include "dolphin.hpp"

using namespace std;

void myDisplay(void);
void myInit(void);
void myIdle(void);
void mouseHandler(int b, int s, int x, int y);
void keyHandler(unsigned char c, int x, int y);
void menuHandler(int value);
void submenuHandler(int colorIndex);
void timerBg(int val);
void resizeFunc(int w, int h);
void drawDolphin(float centerX, float centerY, float angle, float radiusX, float radiusY, float r, float g, float b);


const int QUIT = 0, ESC = 27;
const int RENDER_EVERY = 10;  // how many ms to wait between renders?

const int INIT_WIN_X = 100, INIT_WIN_Y = 40;


int DISPLAY_WIDTH = 1000, DISPLAY_HEIGHT = 1000;
const char* DISPLAY_TITLE = "CSC406 Homework 1";


const int numCirclePts = 24;
float circlePts[numCirclePts][2];

const int numShapePoints = 3;
float* shapePntBuff[numShapePoints];

void drawDolphin(float centerX, float centerY, float angle, float radiusX, float radiusY, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.f);
    
    
    glRotatef(angle, 0.f, 0.f, 1.f);
    
    glScalef(radiusX, radiusY, 1.f);
    
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
           for (int k=0; k<numShapePoints; k++)
               glVertex2f(shapePntBuff[k][0],
                          shapePntBuff[k][1]);
    
    glEnd();
    glPopMatrix();
}


//    This is the function that does the actual scene drawing
//    Typically, you shold almost never have to call this function directly yourself.
//    It will be called automatically by glut, the way in Java the JRE invokes the paint
//    method of a frame.  Simply, because there is no inheritance/overriding mechanism, we
//    need to set up this function as a "callback function."  In this demo I do it in the
//    main function.  A plus side of this way of doing is that the function can be named any way
//    we want, and that in fact we can have different display functions and change during
//    the execution of the program the current display function used by glut.
//
void myDisplay(void)
{
   //    This clears the buffer(s) we draw into.  We will see later this
   //    semester what this really means
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //    There are two "matrix modes" in OpenGL: "projection", which sets up the
   //    camera, and "model view" which we have to be in to do any drawing
   glMatrixMode(GL_MODELVIEW);
   
   //    This says that we start from the lower-left corner of the screen
   glLoadIdentity();

   //--------------------------
   //    basic drawing code
   //--------------------------

    drawDolphin(400, 400, 12, 200, 100, 0.f, 1.f, 1.f);
    
   //    We were drawing into the back buffer, now it should be brought
   //    to the forefront.
   glutSwapBuffers();
}


//    This callback function is called when the window is resized
//    (generally by the user of the application).
//    It is also called when the window is created, why I placed there the
//    code to set up the virtual camera for this application.
//
void resizeFunc(int w, int h)
{
   //    This calls says that I want to use the entire dimension of the window for my drawing.
   glViewport(0, 0, w, h);
   DISPLAY_WIDTH = w;
   DISPLAY_HEIGHT = h;
   
   //    Here I create my virtual camera.  We are going to do 2D drawing for a while, so what this
   //    does is define the dimensions (origin and units) of the "virtual world that my viewport
   //    maps to.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   //    Here I define the dimensions of the "virtual world" that my
   //    window maps to
   gluOrtho2D(0.f, DISPLAY_WIDTH, 0.f, DISPLAY_HEIGHT);

   //    When it's done, request a refresh of the display
   glutPostRedisplay();
}


//    This function is called when a mouse event occurs.  This event, of type s
//    (up, down, dragged, etc.), occurs on a particular button of the mouse.
//
void mouseHandler(int button, int state, int x, int y)
{
   // silence the warning
   (void) x;
   (void) y;
   
   switch (button)
   {
       case GLUT_LEFT_BUTTON:
           if (state == GLUT_DOWN)
           {
               //    do something
           }
           else if (state == GLUT_UP)
           {
               exit(0);
           }
           break;
           
       default:
           break;
   }
}

//    This callback function is called when a keyboard event occurs
//
void keyHandler(unsigned char c, int x, int y)
{
   // silence warning
   (void) x;
   (void) y;
   
   switch (c)
   {
       case 'q':
           exit(0);
           break;
           
       default:
           break;
   }
}


void myIdle(void)
{
   //  possibly I do something to update the scene
   
   //    And finally I perform the rendering
   glutPostRedisplay();
}

void timerBg(int value)
{
   static int frameIndex=0;
    
    // call the timer again after 1 ms
   glutTimerFunc(1, timerBg, value);

   // TODO do background physics here
   
   //  Perform rendering every few calls of this fnc
   if (frameIndex++ % RENDER_EVERY == 0)
       glutPostRedisplay();
       
}

void menuHandler(int choice)
{
   switch (choice)
   {
       case ESC:
       case QUIT:
           exit(0);
           break;
       default:
           break;
   }
}

void submenuHandler(int choice)
{
   switch (choice)
   {
       default:
           break;
   }
}

void myInit(void)
{
   // Create Menus
   int myMenu;
   myMenu = glutCreateMenu(menuHandler);
   glutAddMenuEntry("Quit", QUIT);

   glutAttachMenu(GLUT_RIGHT_BUTTON);

   //    Initialize the array of coordinates of the disk or radius 1 centered at (0, 0)
   float angleStep = 2.f*M_PI/numCirclePts;
   for (int k=0; k<numCirclePts; k++)
   {
       float theta = k*angleStep;
       circlePts[k][0] = cosf(theta);
       circlePts[k][1] = sinf(theta);
   }
    
    initShape(shapePntBuff);
}


int main(int argc, char** argv)
{
   //    Initialize glut and create a new window
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

   glutInitWindowSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
   glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
   glutCreateWindow(DISPLAY_TITLE);
   
   //    set up the callbacks
   glutDisplayFunc(myDisplay);
   glutReshapeFunc(resizeFunc);
   glutMouseFunc(mouseHandler);
   glutKeyboardFunc(keyHandler);
   glutIdleFunc(myIdle);
   glutTimerFunc(10,    timerBg,        0);
   //              time        name of        value to pass
   //              in ms        function    to the func
   
   //    Now we can do application-level
   myInit();

   //    Now we enter the main loop of the program and to a large extend
   //    "lose control" over its execution.  The callback functions that
   //    we set up earlier will be called when the corresponding event
   //    occurs
   glutMainLoop();
   
   //    This will never be executed (the exit point will be in one of the
   //    callback functions).
   return 0;
}
