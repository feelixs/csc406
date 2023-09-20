/*-------------------------------------------------------------------------+
|    Very simple basic OpenGL/glut demo.                                        |
|                                                                            |
|    This application simply creates a glut window and displays some 2D        |
|    shapes in that window.  Sets up callback functions to handle menu,        |
|    mouse and keyboard events.                                                |
+-------------------------------------------------------------------------*/

// "pure" C++ headers
#include <string>
#include <vector>
// C++ wrappers around C headers
#include <cstdlib>
#include <cmath>
#include <cstdio>    //     cstdio.h       stdio.h
//                                        C header
// C system headers
#include <unistd.h>
//    User headers
#include "glPlatform.h"


using namespace std;

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
void myIdle(void);
void myTimerFunc(int val);
void drawDisk(float centerX, float centerY, float radius, float r, float g, float b);
void drawEllipse(float centerX, float centerY, float angle, float radiusX, float radiusY, float r, float g, float b);

//--------------------------------------
//  Interface constants
//--------------------------------------

//    I like to setup my meny item indices as enmerated values, but really
//    regular int constants would do the job just fine.

enum MenuItemID {    SEPARATOR = -1,
                   //
                   QUIT_MENU = 0,
                   OTHER_MENU_ITEM,
                   SOME_ITEM = 10
};

const string MAIN_MENU_ITEM_STR[] = {    "Quit",            //    QUIT_MENU
                                       "Something"        //    OTHER_MENU_ITEM
};

enum FirstSubmenuItemID {    FIRST_SUBMENU_ITEM = 11,
                           SECOND_SUBMENU_ITEM = 12
};


const int   INIT_WIN_X = 100,
           INIT_WIN_Y = 40;


//--------------------------------------
//  File-level global variables
//--------------------------------------

int winWidth = 800,
   winHeight = 800;

int numVerts = 4;
const float vertArray[][2] = {{400.f, 100.f},
                             {400.f, 200.f},
                             {300.f, 200.f},
                             {200.f, 150.f}};
const int numCirclePts = 24;
float circlePts[numCirclePts][2];


void drawDisk(float centerX, float centerY, float radius, float r, float g, float b)
{
    //first save the current coord orientation (origin, axis, scale)
    glPushMatrix();
    
    glTranslatef(centerX, centerY, 0.f);  // change the origin by however much x, y, z
    glScalef(radius, radius, 1.f); // scale the coord graph by the specified x y z
   glColor3f(r, g, b);
   glBegin(GL_POLYGON);
           for (int k=0; k<numCirclePts; k++)
               glVertex2f(circlePts[k][0],
                          circlePts[k][1]);
    
   glEnd();

    // restore original pushed matrix
    glPopMatrix();
}

void drawEllipse(float centerX, float centerY, float angle, float radiusX, float radiusY, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.f);
    
    
    glRotatef(angle, 0.f, 0.f, 1.f);
    
    glScalef(radiusX, radiusY, 1.f);
    
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
           for (int k=0; k<numCirclePts; k++)
               glVertex2f(circlePts[k][0],
                          circlePts[k][1]);
    
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


   //    Draw a red disk of center (x=600, y=500), radius = 150
   //    Version 4
    
    drawEllipse(400, 400, 12, 200, 100, 0.f, 1.f, 1.f);
    
   drawDisk(600, 500, 150, 1.f, 0.f, 0.f);
   
   drawDisk(200, 700, 50, 0.f, 0.f, 1.f);

   drawDisk(700, 200, 50, 1.f, 1.f, 1.f);
    
    

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
   
   //    Here I create my virtual camera.  We are going to do 2D drawing for a while, so what this
   //    does is define the dimensions (origin and units) of the "virtual world that my viewport
   //    maps to.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   //    Here I define the dimensions of the "virtual world" that my
   //    window maps to
   gluOrtho2D(0.f, winWidth, 0.f, winHeight);

   //    When it's done, request a refresh of the display
   glutPostRedisplay();
}


//    This function is called when a mouse event occurs.  This event, of type s
//    (up, down, dragged, etc.), occurs on a particular button of the mouse.
//
void myMouseHandler(int button, int state, int x, int y)
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
void myKeyHandler(unsigned char c, int x, int y)
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

void myTimerFunc(int value)
{
   static int frameIndex=0;
   //    "re-prime the timer"
   glutTimerFunc(1, myTimerFunc, value);

   //     do something (e.g. update the state of some objects)
   
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
   int myMenu, mySubmenu;
   
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

   //    Initialize the array of coordinates of the disk or radius 1 centered at (0, 0)
   float angleStep = 2.f*M_PI/numCirclePts;
   for (int k=0; k<numCirclePts; k++)
   {
       float theta = k*angleStep;
       circlePts[k][0] = cosf(theta);
       circlePts[k][1] = sinf(theta);
   }

   
   
//    myDisplayFunc();
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
