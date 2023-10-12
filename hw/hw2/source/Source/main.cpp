//
//  main.cpp
//  Display Text
//	The main purpose of this project is to show how to
//	display textual information in OpenGL.
//	I use as basis an elementary program working with "world units"
//	to display a simple scene.
//
//	Very basic interface with limited keyboard action:
//		- 'q' or ESC exits the app,
//		- 'm' toggles on/off mouse motion tracking (button pressed)
//		- 'p' toggles on/off passive mouse motion tracking (no button pressed)
//		- 'e' toggles on/off mouse exit/enter
//		- 't' toggles on/off text overlay display
//		- 'i' activates the input of a second text string
//			(input from the terminal)
//	Initial aspect ratio of the window is preserved when the window
//	is resized.
//
//  Created by Jean-Yves Hervé on 2023-10-04.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "ObjectGroup.hpp"
#include "Animal.hpp"
#include "glPlatform.h"
#include "World.h"
#include "Ellipse.h"

using namespace std;

//--------------------------------------
#if 0
#pragma mark Custom data types
#endif
//--------------------------------------

//	I like to setup my meny item indices as enmerated values, but really
//	regular int constants would do the job just fine.
enum MenuItemID {	SEPARATOR = -1,
					//
					QUIT_MENU = 0,
					OTHER_MENU_ITEM,
					SOME_ITEM = 10
};

enum FirstSubmenuItemID {	FIRST_SUBMENU_ITEM = 11,
							SECOND_SUBMENU_ITEM = 12
};

//--------------------------------------
#if 0
#pragma mark Function prototypes
#endif
//--------------------------------------
//void displayTextualInfo(const char* infoStr, int x, int y, FontSize isLarge);
void myDisplayFunc(void);
void myResizeFunc(int w, int h);
void myMouseHandler(int b, int s, int x, int y);
void myMouseMotionHandler(int x, int y);
void myMousePassiveMotionHandler(int x, int y);
void myEntryHandler(int state);
void myKeyHandler(unsigned char c, int x, int y);
void myMenuHandler(int value);
void mySubmenuHandler(int colorIndex);
void myTimerFunc(int val);
void applicationInit();

//--------------------------------------
#if 0
#pragma mark Constants
#endif
//--------------------------------------
const int INIT_WIN_X = 10, INIT_WIN_Y = 32;
const float X_MIN = -10.f, X_MAX = +10.f;
const float Y_MIN = -10.f, Y_MAX = +10.f;

#define SMALL_DISPLAY_FONT    GLUT_BITMAP_HELVETICA_10
#define MEDIUM_DISPLAY_FONT   GLUT_BITMAP_HELVETICA_12
#define LARGE_DISPLAY_FONT    GLUT_BITMAP_HELVETICA_18
//const int TEXT_PADDING = 0;
//const float TEXT_COLOR[4] = {1.f, 1.f, 1.f, 1.f};
//const float PARTITION_COLOR[4] = {0.6f, 0.6f, 0.6f, 1.f};

//--------------------------------------
#if 0
#pragma mark Global variables
#endif
//--------------------------------------

int winWidth = 800,
    winHeight = 800;
bool trackMousePointer = false;
bool trackPassiveMousePointer = false;
bool trackEntry = false;
bool displayText = false;
string stringLine = "";

vector<shared_ptr<GraphicObject> > objectList;


//--------------------------------------
#if 0
#pragma mark -
#pragma mark Callback functions
#endif
//--------------------------------------

void myDisplayFunc(void)
{
	//	This clears the buffer(s) we draw into.  We will see later this
	//	semester what this really means
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	There are two "matrix modes" in OpenGL: "projection", which sets up the
	//	camera, and "model view" which we have to be in to do any drawing
	glMatrixMode(GL_MODELVIEW);
	
	//	This says that we start from the lower-left corner of the screen
	glLoadIdentity();
	glPushMatrix();
	
	//--------------------------
	//	Draw stuff
	//--------------------------
	glColor3f(1.f, 0.5f, 0.f);
	glBegin(GL_POLYGON);
		glVertex2f(1.5f, -5.0f);
		glVertex2f(4.f, 1.0f);
		glVertex2f(-1.f, 3.f);
	glEnd();

	for (auto obj : objectList)
	{
		if (obj != nullptr)
			obj->draw();
	}

	glPopMatrix();

	//	Display textual info
//		displayTextualInfo(	message[k],
//							LEFT_MARGIN,
//							3*STATE_PANE_HEIGHT/4 - k*V_PAD,
//							LARGE_FONT_SIZE);

	//	We were drawing into the back buffer, now it should be brought
	//	to the forefront.
	glutSwapBuffers();
}

void myResizeFunc(int w, int h)
{
	winWidth = w;
    winHeight = h;
	
	World::setWorldBounds(X_MIN, X_MAX, Y_MIN, Y_MAX, winWidth, winHeight);
	if (winWidth != w || winHeight != h)
	{
		glutReshapeWindow(winWidth, winHeight);
	}
	
	//	This calls says that I want to use the entire dimension of the window for my drawing.
	glViewport(0, 0, winWidth, winHeight);

	//	Here I create my virtual camera.  We are going to do 2D drawing for a while, so what this
	//	does is define the dimensions (origin and units) of the "virtual world that my viewport
	//	maps to.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//	Here I define the dimensions of the "virtual world" that my
	//	window maps to
	gluOrtho2D(X_MIN, X_MAX, Y_MIN, Y_MAX);

	//	When it's done, request a refresh of the display
	glutPostRedisplay();
}

void myMenuHandler(int choice)
{
	switch (choice)
	{
		//	Exit/Quit
		case QUIT_MENU:
			exit(0);
			break;
		
		//	Do something
		case OTHER_MENU_ITEM:
			break;
		
		default:	//	this should not happen
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

//	This function is called when a mouse event occurs.  This event, of type s
//	(up, down, dragged, etc.), occurs on a particular button of the mouse.
//
void myMouseHandler(int button, int state, int ix, int iy)
{
//	static int clickCount = 0;

	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				//	do something

				cout << "Click at: (" << ix << ", " << iy << ")" << endl;
				Point wPt = pixelToWorld(ix, iy);
				cout << "Corresponding world point: (" << wPt.x << ", " <<
						wPt.y << ")" << endl;
				Point pPt = worldToPixel(wPt.x, wPt.y);
				cout << "Back to pixels: (" << pPt.x << ", " <<
						pPt.y << ")" << endl;
			}
			else if (state == GLUT_UP)
			{
              //  objectList.push_back(make_shared<Ellipse>(4, 4, 30, 2, 1, 0.f, 1.f, 1.f));
                
               // objectList.push_back(make_shared<Animal>(pixelToWorld(ix, iy), 90.f, 1, 0.f, 1.f, 1.f));
                
                objectList.push_back(make_shared<ObjectGroup>(HEADS_ON_WHEELS, LARGE, 4, pixelToWorld(ix, iy)));
			}
			break;
			
		default:
			break;
	}
}

void myMouseMotionHandler(int ix, int iy)
{
	if (trackMousePointer)
	{
		cout << "Active mouse at (" << ix << ", " << iy << ")" << endl;
	}
}
void myMousePassiveMotionHandler(int ix, int iy)
{
	if (trackPassiveMousePointer)
	{
		cout << "Passive mouse at (" << ix << ", " << iy << ")" << endl;
	}

}
void myEntryHandler(int state)
{
	if (trackEntry)
	{
		if (state == GLUT_ENTERED)
		{
			cout << "===> Pointer entered" << endl;
		}
		else	// GLUT_LEFT
		{
			cout << "<=== Pointer exited" << endl;
		}
	}
}


//	This callback function is called when a keyboard event occurs
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
		
		case 'm':
			trackMousePointer = !trackMousePointer;
			break;

		case 'p':
			trackPassiveMousePointer = !trackPassiveMousePointer;
			break;
			
		case 'e':
			trackEntry = !trackEntry;
			break;
			
		case 'i':
			cout << "Enter a new line of text: ";
			cin >> stringLine;
			break;
			
		case 't':
			displayText = !displayText;
			
		default:
			break;
	}
}


void myTimerFunc(int value)
{
	static int frameIndex=0;

	//	"re-prime the timer"
	glutTimerFunc(1, myTimerFunc, value);

	//	 do something (e.g. update the state of some objects)
	
	//	And finally I perform the rendering
	if (frameIndex++ % 10 == 0)
	{
		glutPostRedisplay();
	}
}

//--------------------------------------
#if 0
#pragma mark -
#pragma mark Application init and main
#endif
//--------------------------------------

//void displayTextualInfo(const char* infoStr, int xPos, int yPos, FontSize fontSize)
//{
//    //-----------------------------------------------
//    //  0.  get current material properties
//    //-----------------------------------------------
//    float oldAmb[4], oldDif[4], oldSpec[4], oldShiny;
//    glGetMaterialfv(GL_FRONT, GL_AMBIENT, oldAmb);
//    glGetMaterialfv(GL_FRONT, GL_DIFFUSE, oldDif);
//    glGetMaterialfv(GL_FRONT, GL_SPECULAR, oldSpec);
//    glGetMaterialfv(GL_FRONT, GL_SHININESS, &oldShiny);
//
//    glPushMatrix();
//
//    //-----------------------------------------------
//    //  1.  Build the string to display <-- parameter
//    //-----------------------------------------------
//    int infoLn = (int) strlen(infoStr);
//
//    //-----------------------------------------------
//    //  2.  Determine the string's length (in pixels)
//    //-----------------------------------------------
//    int textWidth = 0;
//	switch(fontSize)
//	{
//		case SMALL_FONT_SIZE:
//			for (int k=0; k<infoLn; k++)
//			{
//				textWidth += glutBitmapWidth(SMALL_DISPLAY_FONT, infoStr[k]);
//			}
//			break;
//		
//		case MEDIUM_FONT_SIZE:
//			for (int k=0; k<infoLn; k++)
//			{
//				textWidth += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr[k]);
//			}
//			break;
//		
//		case LARGE_FONT_SIZE:
//			for (int k=0; k<infoLn; k++)
//			{
//				textWidth += glutBitmapWidth(LARGE_DISPLAY_FONT, infoStr[k]);
//			}
//			break;
//			
//		default:
//			break;
//	}
//		
//	//  add a few pixels of padding
//    textWidth += 2*TEXT_PADDING;
//	
//    //-----------------------------------------------
//    //  4.  Draw the string
//    //-----------------------------------------------    
//    glColor4fv(TEXT_COLOR);
//    int x = xPos;
//	switch(fontSize)
//	{
//		case SMALL_FONT_SIZE:
//			for (int k=0; k<infoLn; k++)
//			{
//				glRasterPos2i(x, yPos);
//				glutBitmapCharacter(SMALL_DISPLAY_FONT, infoStr[k]);
//				x += glutBitmapWidth(SMALL_DISPLAY_FONT, infoStr[k]);
//			}
//			break;
//		
//		case MEDIUM_FONT_SIZE:
//			for (int k=0; k<infoLn; k++)
//			{
//				glRasterPos2i(x, yPos);
//				glutBitmapCharacter(MEDIUM_DISPLAY_FONT, infoStr[k]);
//				x += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr[k]);
//			}
//			break;
//		
//		case LARGE_FONT_SIZE:
//			for (int k=0; k<infoLn; k++)
//			{
//				glRasterPos2i(x, yPos);
//				glutBitmapCharacter(LARGE_DISPLAY_FONT, infoStr[k]);
//				x += glutBitmapWidth(LARGE_DISPLAY_FONT, infoStr[k]);
//			}
//			break;
//			
//		default:
//			break;
//	}
//
//    //-----------------------------------------------
//    //  5.  Restore old material properties
//    //-----------------------------------------------
//	glMaterialfv(GL_FRONT, GL_AMBIENT, oldAmb);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, oldDif);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, oldSpec);
//	glMaterialf(GL_FRONT, GL_SHININESS, oldShiny);  
//    
//    //-----------------------------------------------
//    //  6.  Restore reference frame
//    //-----------------------------------------------
//    glPopMatrix();
//}


void applicationInit()
{
	// Create Menus
	int myMenu;
	
	//	Submenu for changing keyboard handling function
	int mySubmenu = glutCreateMenu(mySubmenuHandler);
	glutAddMenuEntry("first entry", FirstSubmenuItemID::FIRST_SUBMENU_ITEM);
	glutAddMenuEntry("second entry", FirstSubmenuItemID::SECOND_SUBMENU_ITEM);

	// Main menu that the submenus are connected to
	myMenu = glutCreateMenu(myMenuHandler);
	glutAddMenuEntry("Quit", MenuItemID::QUIT_MENU);
	//
	glutAddMenuEntry("-", MenuItemID::SEPARATOR);
	glutAddMenuEntry("Other stuff", MenuItemID::OTHER_MENU_ITEM);
	glutAddMenuEntry("New entry", 64);
	
	glutAddMenuEntry("-", MenuItemID::SEPARATOR);
	glutAddSubMenu("Submenu example", mySubmenu);
	glutAddMenuEntry("-", MenuItemID::SEPARATOR);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	objectList.push_back(make_shared<Ellipse>(7, 2, 0, .50, .50, 1.f, 1.f, 1.f));
	objectList.push_back(make_shared<Ellipse>(2, 7, 0, .50, .5, 0.f, 0.f, 1.f));
	objectList.push_back(make_shared<Ellipse>(6, 5, 0, 1.5, 1.5, 1.f, 0.f, 0.f));
}

int main(int argc, char * argv[])
{
	//	Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	glutCreateWindow("demo CSC406");
	
	//	set up the callbacks
	glutDisplayFunc(myDisplayFunc);
	glutReshapeFunc(myResizeFunc);
	glutMouseFunc(myMouseHandler);
	glutMotionFunc(myMouseMotionHandler);
	glutPassiveMotionFunc(myMousePassiveMotionHandler);
	glutEntryFunc(myEntryHandler);
	glutKeyboardFunc(myKeyHandler);
	glutTimerFunc(1,	myTimerFunc,		0);
	//			  time	    name of		value to pass
	//			  in ms		function	to the func
	
	//	Now we can do application-level
	applicationInit();

	//	Now we enter the main loop of the program and to a large extend
	//	"lose control" over its execution.  The callback functions that
	//	we set up earlier will be called when the corresponding event
	//	occurs
	glutMainLoop();
	
	//	This will never be executed (the exit point will be in one of the
	//	callback functions).
	return 0;
}
