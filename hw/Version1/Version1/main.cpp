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
#include <random>
#include <unistd.h>
#include <iostream>
#include "glPlatform.h"
#include "PolyShape.hpp"
#include "Animal.hpp"

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


vector<shared_ptr<Animal>> shapeList;

const int QUIT = 0, ESC = 27;
const int RENDER_EVERY = 10;  // how many ms to wait between renders?

const int INIT_WIN_X = 100, INIT_WIN_Y = 40;


int DISPLAY_WIDTH = 1000, DISPLAY_HEIGHT = 1000;
const char* DISPLAY_TITLE = "CSC406 Homework 1";


const int numCirclePts = 24;
float circlePts[numCirclePts][2];


// create a random float number generator
static int clickCount = 0;
static std::random_device seed;
static std::mt19937 gen(seed());
std::uniform_real_distribution<float> colorValGen(0.0f, 1.0f); // set the range of the random color generator from 0-1

// set the range of possible locations, but subtract 100 because we don't want them too far offscreen
std::uniform_real_distribution<float> coordValGenX(0.0f, DISPLAY_WIDTH-100.f);
std::uniform_real_distribution<float> coordValGenY(0.0f, DISPLAY_HEIGHT-100.f);
std::uniform_real_distribution<float> scaleValGen(80.f, 200.f);

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

   //    There are two "matrix modes" in OpenGL: "projection", which sets up the
   //    camera, and "model view" which we have to be in to do any drawing
   glMatrixMode(GL_MODELVIEW);
   
   //    This says that we start from the lower-left corner of the screen
   glLoadIdentity();

   //--------------------------
   //    basic drawing code
   //--------------------------

    for (auto obj : shapeList)
    {
        if (obj != nullptr)
            obj->draw();
    }
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
void mouseHandler(int button, int state, int x, int y)
{
   // silence the warning
   (void) x;
   (void) y;
   
   switch (button)
   {
       case GLUT_LEFT_BUTTON:
           if (state == GLUT_UP)
           {
               float randScale = scaleValGen(seed);
               shapeList.push_back(make_shared<Animal>(x, DISPLAY_HEIGHT-y, 0, randScale, randScale, colorValGen(seed), colorValGen(seed), colorValGen(seed)));
               if (clickCount < 4)
                   shapeList[clickCount++] = nullptr;
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int myMenu;
    myMenu = glutCreateMenu(menuHandler);
    glutAddMenuEntry("Quit", QUIT);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    // initialize some animals
    shapeList.push_back(make_shared<Animal>(coordValGenX(seed), coordValGenY(seed), 0, 100, 100, colorValGen(seed), colorValGen(seed), colorValGen(seed)));
    shapeList.push_back(make_shared<Animal>(coordValGenX(seed), coordValGenY(seed), 0, 80, 80, colorValGen(seed), colorValGen(seed), colorValGen(seed)));
    shapeList.push_back(make_shared<Animal>(coordValGenX(seed), coordValGenY(seed), 0, 200, 200, colorValGen(seed), colorValGen(seed), colorValGen(seed)));
    shapeList.push_back(make_shared<Animal>(coordValGenX(seed), coordValGenY(seed), 0, 50, 50, colorValGen(seed), colorValGen(seed), colorValGen(seed)));
    shapeList.push_back(make_shared<Animal>(coordValGenX(seed), coordValGenY(seed), 0, 150, 150, colorValGen(seed), colorValGen(seed), colorValGen(seed)));
    shapeList.push_back(make_shared<Animal>(coordValGenX(seed), coordValGenY(seed), 0, 70, 70, colorValGen(seed), colorValGen(seed), colorValGen(seed)));
    shapeList.push_back(make_shared<Animal>(coordValGenX(seed), coordValGenY(seed), 0, 55, 55, colorValGen(seed), colorValGen(seed), colorValGen(seed)));
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
