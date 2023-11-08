/*-------------------------------------------------------------------------+
|    Very simple basic OpenGL/glut demo.                                        |
|                                                                            |
|    This application simply creates a glut window and displays some 2D        |
|    shapes in that window.  Sets up callback functions to handle menu,        |
|    mouse and keyboard events.                                                |
+-------------------------------------------------------------------------*/

// "pure" C++ headers
#include <string>
#include <algorithm>
#include <vector>
#include <memory>
#include <iostream>
// C++ wrappers around C headers
#include <cstdlib>
#include <cmath>
#include <cstdio>    //     cstdio.h       stdio.h
//                                        C header
// C system headers
#include <unistd.h>
//    User headers
#include "glPlatform.h"

#include "Ellipse.hpp"

using namespace std;

//--------------------------------------
//  Custom data types
//--------------------------------------

//    I like to setup my meny item indices as enmerated values, but really
//    regular int constants would do the job just fine.

enum MenuItemID {    SEPARATOR = -1,
                   //
                   QUIT_MENU = 0,
                   OTHER_MENU_ITEM,
                   SOME_ITEM = 10
};


enum FirstSubmenuItemID {    FIRST_SUBMENU_ITEM = 11,
                           SECOND_SUBMENU_ITEM = 12
};

struct Point
{
   float x;
   float y;
};


//--------------------------------------
//  Function prototypes
//--------------------------------------
void myDisplayFunc(void);
void myResizeFunc(int w, int h);
void myMouseHandler(int b, int s, int x, int y);
void myKeyHandler(unsigned char c, int x, int y);
void myMenuHandler(int value);
void mySubmenuHandler(int colorIndex);
void myInit(void);
void myTimerFunc(int val);
Point pixelToWorld(float ix, float iy);


//--------------------------------------
//  Interface constants
//--------------------------------------

const string MAIN_MENU_ITEM_STR[] = {    "Quit",            //    QUIT_MENU
                                       "Something"        //    OTHER_MENU_ITEM
};

const int   INIT_WIN_X = 100,
           INIT_WIN_Y = 40;


float X_MIN = -10.f, X_MAX = +10.f;
float Y_MIN = -10.f, Y_MAX = +10.f;
const float WORLD_WIDTH = X_MAX-X_MIN;
const float WORLD_HEIGHT = Y_MAX-Y_MIN;

const float diskRad = WORLD_WIDTH/20.f;

//--------------------------------------
//  File-level global variables
//--------------------------------------

int winWidth = 800,
   winHeight = 800;

int numVerts = 4;
const float vertArray[][2] = {{-4.f, -1.00f},
                             {-4.f, -2.00f},
                             {-3.f, -2.f},
                             {-2.f, -1.5f}};

vector<shared_ptr<Ellipse>> ellipseList;

// first rough expression
float pixelToWorldScale = max(WORLD_WIDTH / winWidth, WORLD_HEIGHT/winHeight);
float worldToPixel = 1.f / pixelToWorldScale;

//    This is the function that does the actual scene drawing
//    Typically, you shold almost never have to call this function directly yourself.
//    It will be called automatically by glut, the way in Java the JRE invokes the paint
//    method of a frame.  Simply, because there is no inheritance/overriding mechanism, we
//    need to set up this function as a "callback function."  In this demo I do it in the
//    main function.  A plus side of this way of doing is that the function can be named any way
//    we want, and that in fact we can have different display functions and change during
//    the execution of the program the current display function used by glut.
//
void myDisplayFunc(void)
{
   //    This clears the buffer(s) we draw into.  We will see later this
   //    semester what this really means
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //    There are two "matrix modes" in OpenGL: "projection", which sets up the
   //    camera, and "model view" which we have to be in to do any drawing
   glMatrixMode(GL_MODELVIEW);
   
   //    This says that we start from the lower-left corner of the screen
   glLoadIdentity();
   
   // scale to start using "wprld units"
   

   //--------------------------
   //    basic drawing code
   //--------------------------

   //    Set a color, say what kind of object you want to draw,
   //    and list the coordinates of the vertices that define that object
   glColor3f(1.f, 0.5f, 0.f);
   glBegin(GL_POLYGON);
           for (int k=0; k<numVerts; k++)
               glVertex2f(vertArray[k][0], vertArray[k][1]);
   glEnd();

   for (auto obj : ellipseList)
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
void myResizeFunc(int w, int h)
{
   //    This calls says that I want to use the entire dimension of the window for my drawing.
   glViewport(0, 0, w, h);
   winWidth = w;
   winHeight = h;
   
   pixelToWorldScale = max(WORLD_WIDTH / winWidth, WORLD_HEIGHT/winHeight);
   worldToPixel = 1.f / pixelToWorldScale;
   
   //    Here I create my virtual camera.  We are going to do 2D drawing for a while, so what this
   //    does is define the dimensions (origin and units) of the "virtual world that my viewport
   //    maps to.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   //    Here I define the dimensions of the "virtual world" that my
   //    window maps to
   gluOrtho2D(X_MIN, X_MAX, Y_MIN, Y_MAX);

   //    When it's done, request a refresh of the display
   glutPostRedisplay();
}


//    This function is called when a mouse event occurs.  This event, of type s
//    (up, down, dragged, etc.), occurs on a particular button of the mouse.
//
void myMouseHandler(int button, int state, int ix, int iy)
{
   static int clickCount = 0;

   switch (button)
   {
       case GLUT_LEFT_BUTTON:
           if (state == GLUT_DOWN)
           {
               for (auto obj : ellipseList) {
                   if (obj->isInside(ix, iy)) {
                       cout << "mouse inside!!!!\n";
                   }
               }
               //    do something
           }
           else if (state == GLUT_UP)
           {
               // create a new disk
               Point worldPt = pixelToWorld(ix, iy);
               ellipseList.push_back(make_shared<Ellipse>(worldPt.x, worldPt.y, diskRad, 1.f, 1.f, 0.f));
           }
           break;
           
       default:
           break;
   }
}

Point pixelToWorld(float ix, float iy) {
   return Point{    X_MIN + 1.f*ix/winWidth*WORLD_WIDTH,
                   Y_MAX - 1.f*iy/winHeight*WORLD_HEIGHT
               };
}


//    This callback function is called when a keyboard event occurs
//
void myKeyHandler(unsigned char c, int x, int y)
{
   // silence warning
   (void) x;
   (void) y;
   
   switch (c)
   {
       case 'q':
       case 27:
           exit(0);
           break;
           
       default:
           break;
   }
}


void myTimerFunc(int value)
{
   static int frameIndex=0;
   //    "re-prime the timer"
   glutTimerFunc(1, myTimerFunc, value);

   //     do something (e.g. update the state of some objects)
   for (auto obj : ellipseList)
   {
       if (obj != nullptr)
           obj->update();
   }
   
   //    And finally I perform the rendering
   if (frameIndex++ % 10 == 0)
       glutPostRedisplay();
       
}

void myMenuHandler(int choice)
{
   switch (choice)
   {
       //    Exit/Quit
       case QUIT_MENU:
           exit(0);
           break;
       
       //    Do something
       case OTHER_MENU_ITEM:
           break;
       
       default:    //    this should not happen
           break;
   
   }

   glutPostRedisplay();
}

//  in this example my submenu selection indicates the keyboard handling
//  function to use.
void mySubmenuHandler(int choice)
{
   switch (choice)
   {
       case FIRST_SUBMENU_ITEM:
           break;
       
       case SECOND_SUBMENU_ITEM:
           break;
           
       default:
           break;
   }
}

void myInit(void)
{
   // Create Menus
   int myMenu;
   
   //    Submenu for changing keyboard handling function
//    mySubmenu = glutCreateMenu(mySubmenuHandler);
//    glutAddMenuEntry("first entry", FIRST_SUBMENU_ITEM);
//    glutAddMenuEntry("second entry", SECOND_SUBMENU_ITEM);

   // Main menu that the submenus are connected to
   myMenu = glutCreateMenu(myMenuHandler);
   glutAddMenuEntry("Quit", QUIT_MENU);
   //
   glutAddMenuEntry("-", SEPARATOR);
   glutAddMenuEntry("Other stuff", OTHER_MENU_ITEM);
   glutAddMenuEntry("New entry", 64);
   
//    glutAddSubMenu("Submenu example", mySubmenu);
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   ellipseList.push_back(make_shared<Ellipse>(4, 4, 30, 2, 1, 0.f, 1.f, 1.f));
   ellipseList.push_back(make_shared<Ellipse>(7, 2, 0, .50, .50, 1.f, 1.f, 1.f));
   ellipseList.push_back(make_shared<Ellipse>(2, 7, 0, .50, .5, 0.f, 0.f, 1.f));
   ellipseList.push_back(make_shared<Ellipse>(6, 5, 0, 1.5, 1.5, 1.f, 0.f, 0.f));
}


int main(int argc, char** argv)
{
   //    Initialize glut and create a new window
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

   glutInitWindowSize(winWidth, winHeight);
   glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
   glutCreateWindow("demo CSC406");
   
   //    set up the callbacks
   glutDisplayFunc(myDisplayFunc);
   glutReshapeFunc(myResizeFunc);
   glutMouseFunc(myMouseHandler);
   glutKeyboardFunc(myKeyHandler);
//    glutIdleFunc(myIdle);
   glutTimerFunc(10,    myTimerFunc,        0);
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
