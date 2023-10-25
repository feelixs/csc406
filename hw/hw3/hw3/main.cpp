//
//  main.cpp
//
//	This project summarizes all the basic OpenGL + glut stuff
//	and graphic class material that we have discussed so far.
//	And then it adds a few things:
//		o For class hierarchy, look at comments about virtual
//			functions and destructors.
//		o mouse motion and mouse passive motion callback functions
//		o display of textual information in OpenGL + glut
//
//	Very basic interface with limited keyboard action:
//		- 'q' or ESC exits the app,
//		- 'c' switches between "creation" and "test" modes for mouse clicks
//		- 'm' toggles on/off mouse motion tracking (button pressed)
//		- 'p' toggles on/off passive mouse motion tracking (no button pressed)
//		- 'e' toggles on/off mouse exit/enter
//		- 't' toggles on/off text overlay display
//		- 'b' toggles on/off text background display
//		- 'i' activates the input of a second text string
//			(input from the terminal)
//		- clicking the mouse anywhere in the window will print out
//			pixel location of the click, conversion in world coordinates, and
//			conversion back to pixels (for verification).
//
//	Initial aspect ratio of the window is preserved when the window
//	is resized.
//	Pay attention to what I do there for the radius random generator.
//
//  Created by Jean-Yves Hervé on 2023-10-04.
//
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <random>
#include <chrono>
#include <ctime>
//
#include "Asteroid.hpp"
#include "glPlatform.h"
#include "World.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Face.h"
#include "SmilingFace.h"
#include "AnimatedEllipse.h"
#include "AnimatedRectangle.h"

using namespace std;
using namespace earshooter;

//--------------------------------------
#if 0
#pragma mark Custom data types
#endif
//--------------------------------------

//	I like to setup my meny item indices as enmerated values, but really
//	regular int constants would do the job just fine.
//	Note that in modern C++, it's generally advised to use "scoped enums", which
//	are declared as "enum class NameOfType".  I agree and do so in general, but
//	here these are meant to be used with my glut interface, and it's really
//	bothersome to do the casting to int each each time.

const char* WIN_TITLE = "Asteroids (Homework 3)";

enum MenuItemID {	SEPARATOR = -1,
					//
					QUIT_MENU = 0,
					OTHER_MENU_ITEM,
					SOME_ITEM = 10
};

enum TextColorSubmenuItemID {	FIRST_TEXT = 11,
								RED_TEXT = 11,
								GREEN_TEXT,
								WHITE_TEXT,
								MAGENTA_TEXT,
								//
								MAX_COUNT_TEXT
};
const int NUM_TEXT_COLORS = MAX_COUNT_TEXT - FIRST_TEXT;

enum BackgroundColorSubmenuItemID {	FIRST_BGND = 21,
									LIGHT_GREY_BGND = 21,
									DARK_GREY_BGND,
									GREEN_BGND,
									BLUE_BGND,
									BROWN_BGND,
									//
									MAX_COUNT_BGND
};
const int NUM_BGND_COLORS = MAX_COUNT_BGND - FIRST_BGND;

enum FontSize {
					SMALL_FONT_SIZE = 0,
					MEDIUM_FONT_SIZE,
					LARGE_FONT_SIZE,
					//
					NUM_FONT_SIZES
};

enum AppMode {
				CREATION_MODE = 0,
				TEST_MODE
};

//--------------------------------------
#if 0
#pragma mark Function prototypes
#endif
//--------------------------------------
void printMatrix(const GLfloat* m);
void displayTextualInfo(const string& infoStr, int textRow);
void displayTextualInfo(const char* infoStr, int textRow);
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

const float World::X_MIN = -10.f;
const float World::X_MAX = +10.f;
const float World::Y_MIN = -10.f;
const float World::Y_MAX = +10.f;
const float World::WIDTH = World::X_MAX - World::X_MIN;
const float World::HEIGHT = World::Y_MAX - World::Y_MIN;
//
//	I set my speed range in terms of the time it takes to go across the window
const float MIN_SPEED = World::WIDTH/20.f;
const float MAX_SPEED = World::WIDTH/5.f;

#define SMALL_DISPLAY_FONT    GLUT_BITMAP_HELVETICA_10
#define MEDIUM_DISPLAY_FONT   GLUT_BITMAP_HELVETICA_12
#define LARGE_DISPLAY_FONT    GLUT_BITMAP_HELVETICA_18
const int H_PAD = 10;
const int V_PAD = 5;

const string TEXT_COLOR_STR[NUM_TEXT_COLORS] = {"white",		//	WHITE_TEXT
												"red",			//	RED_TEXT
												"green",		//	GREEN_TEXT
												"magenta"};		//	MAGENTA_TEXT
							
const string BGND_COLOR_STR[NUM_BGND_COLORS] = {"light gray",	//	LIGHT_GREY_BGND
												"dark gray",	//	DARK_GREY_BGND
												"green",		//	GREEN_BGND
												"blue",			//	BLUE_BGND
												"brown"};		//	BROWN_BGND

const GLfloat TEXT_COLOR[NUM_TEXT_COLORS][3] = { {1.f, 1.f, 1.f},	//	WHITE_TEXT
												 {1.f, 0.f, 0.f},	//	RED_TEXT
												 {0.f, .8f, 0.f},	//	GREEN_TEXT
												 {1.f, 0.f, 1.f}};	//	MAGENTA_TEXT
							
const GLfloat BGND_COLOR[NUM_BGND_COLORS][3] = { {.5f, .5f, .5f},	//	LIGHT_GREY_BGND
												 {.3f, .3f, .3f},	//	DARK_GREY_BGND
												 {0.f, .4f, 0.f},	//	GREEN_BGND
												 {0.f, 0.f, .4f},	//	BLUE_BGND
												 {.4f, .2f, 0.f}};	//	BROWN_BGND

const bool displayTextOnLeft = false;
const bool displayTextOnTop = true;
const FontSize fontSize = LARGE_FONT_SIZE;

//--------------------------------------
#if 0
#pragma mark Global variables
#endif
//--------------------------------------

time_t startTime = -1;
int winWidth = 800,
    winHeight = 800;

random_device World::randDev;
default_random_engine World::randEngine(World::randDev());
uniform_real_distribution<float> World::wxDist = uniform_real_distribution<float>(World::X_MIN, World::X_MAX);
uniform_real_distribution<float> World::wyDist = uniform_real_distribution<float>(World::Y_MIN, World::Y_MAX);
uniform_real_distribution<float> World::objectScaleDist = uniform_real_distribution<float>(World::WIDTH/20, World::WIDTH/10);
uniform_real_distribution<float> World::colorDist(0.f, 1.f);
uniform_real_distribution<float> World::normalDist(0.f, 1.f);
uniform_real_distribution<float> World::angleDegDist(0.f, 360.f);
uniform_real_distribution<float> World::angleRadDist(0.f, 2.f*M_PI);
//	In non-simulation contexts, I like to specify velocities in terms of the time it goes
//	to go cross the world (in seconds).  For simulations, the problem dictates speed.
// re-initialized when the window is resized
uniform_real_distribution<float> World::spinDegDist(360.f/15.f, 360.f/5.f);
// 8 chance out of 10 for an ellipse generated by click to be animated
bernoulli_distribution World::animatedChoiceDist(8.0/10.0f);
bernoulli_distribution World::headsOrTailsDist(0.5f);

// re-initialized when the window is resized
uniform_real_distribution<float> World::radiusDist;

float World::pixelToWorldRatio;
float World::worldToPixelRatio;
float World::drawInPixelScale;

bool trackEntry = false;
bool trackMousePointer = false;
bool trackPassiveMousePointer = false;
bool pointerInWindow = false;
GLint lastX = -1, lastY = -1;

bool displayText = false;
bool displayBgnd = false;
string stringLine = "";
const GLfloat* textColor = TEXT_COLOR[0];
const GLfloat* bgndColor = BGND_COLOR[0];

list<shared_ptr<GraphicObject> > objectList;
list<shared_ptr<AnimatedObject> > animatedObjectList;

WorldType World::worldType = WorldType::CYLINDER_WORLD;
AppMode appMode = AppMode::CREATION_MODE;

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
	
	//	This says that we start from the origin of the camera, whose coordinates
	//	(in the 2D case) coincide with that of the world's orogin.
	glLoadIdentity();
	glPushMatrix();

	for (auto obj : objectList)
	{
		if (obj != nullptr)
			obj->draw();
	}

	if (World::worldType == WorldType::CYLINDER_WORLD)
	{
		glTranslatef(-World::WIDTH, 0, 0);
		for (auto obj : objectList)
			{
				if (obj != nullptr)
					obj->draw();
			}
		glTranslatef(2*World::WIDTH, 0, 0);
		for (auto obj : objectList)
			{
				if (obj != nullptr)
					obj->draw();
			}
		
	
	}

	glPopMatrix();
	glutSwapBuffers();
}

void myResizeFunc(int w, int h)
{
	winWidth = w;
    winHeight = h;
	
	World::setScalingRatios(winWidth, winHeight);
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
	gluOrtho2D(World::X_MIN, World::X_MAX, World::Y_MIN, World::Y_MAX);

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
		case RED_TEXT:
		case GREEN_TEXT:
		case WHITE_TEXT:
		case MAGENTA_TEXT:
			textColor = TEXT_COLOR[choice - FIRST_TEXT];
			break;
			
		case LIGHT_GREY_BGND:
		case DARK_GREY_BGND:
		case GREEN_BGND:
		case BLUE_BGND:
		case BROWN_BGND:
			bgndColor = BGND_COLOR[choice - FIRST_BGND];
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
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				//	do something
				cout << "Click at: (" << ix << ", " << iy << ")" << endl;
				WorldPoint wPt = pixelToWorld(ix, iy);
				cout << "Corresponding world point: (" << wPt.x << ", " <<
						wPt.y << ")" << endl;
				PixelPoint pPt = worldToPixel(wPt.x, wPt.y);
				cout << "Back to pixels: (" << pPt.x << ", " <<
						pPt.y << ")" << endl;
				
			}
			else if (state == GLUT_UP)
			{
				WorldPoint clickPt = pixelToWorld(ix, iy);
				
				if (appMode == AppMode::TEST_MODE)
				{
					for (auto obj : objectList)
					{
						if (obj->isInside(clickPt)) {
							cout << "Clicked inside object" << endl;
							// check if the object was animated
//							vector<shared_ptr<AnimatedObject> >::iterator iter = find(animatedObjectList.begin(),
//																		 animatedObjectList.end(),
//																		 obj);
//							if (iter != animatedObjectList.end())
//								*iter = nullptr;
//							objectList.remove(obj);
						}
					}
				}
				//	Creation mode
				else
				{
					//----------------
					//	ellipse
					//----------------
					if (headsOrTails())
					{
						//	create a randomly-colored ellipse centered at the click location
						WorldPoint clickPt = pixelToWorld(ix, iy);
						if (isAnimated())
						{
							shared_ptr<AnimatedEllipse> ell  = make_shared<AnimatedEllipse>(
									clickPt,								//	{x, y}
									randomAngleDeg(),						//	angle
									randomObjectScale()*0.5f,				//	h radius
									randomObjectScale()*0.5f,				//	v radius
									randomVelocity(MIN_SPEED, MAX_SPEED),	//	{vx, vy}
									randomSpinDeg(),						//	spin
									randomColor(),							//	red
									randomColor(),							//	green
									randomColor());							//	blue
							animatedObjectList.push_back(ell);
							objectList.push_back(ell);
						}
						else
						{
							objectList.push_back(make_shared<Ellipse>(
									clickPt,								//	{x, y}
									randomAngleDeg(),						//	angle
									randomObjectScale()*0.5f,				//	h radius
									randomObjectScale()*0.5f,				//	v radius
									randomColor(),							//	red
									randomColor(),							//	green
									randomColor()));						//	blue
						}
					}
					//----------------
					//	Rectangle
					//----------------
					else
					{
						//	create a randomly-colored ellipse centered at the click location
						WorldPoint clickPt = pixelToWorld(ix, iy);
						if (isAnimated())
						{
							shared_ptr<AnimatedRectangle> rect = make_shared<AnimatedRectangle>(
									clickPt,								//	{x, y}
									randomAngleDeg(),						//	angle
									randomObjectScale(),					//	width
									randomObjectScale(),					//	height
									randomVelocity(MIN_SPEED, MAX_SPEED),	//	{vx, vy}
									randomSpinDeg(),						//	spin
									randomColor(),							//	red
									randomColor(),							//	green
									randomColor());							//	blue
							animatedObjectList.push_back(rect);
							objectList.push_back(rect);
						}
						else
						{
							objectList.push_back(make_shared<Rectangle>(
									clickPt,								//	{x, y}
									randomAngleDeg(),						//	angle
									randomObjectScale(),					//	width
									randomObjectScale(),					//	height
									randomColor(),							//	red
									randomColor(),							//	green
									randomColor()));						//	blue
						}
						
					}
				
				}
			}
		break;
		
		case GLUT_RIGHT_BUTTON:
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
	lastX = ix;
	lastY = iy;
	pointerInWindow = (ix >= 0 && ix < winWidth && iy >= 0 && iy < winHeight);

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
			pointerInWindow = true;
			cout << "===> Pointer entered" << endl;
		}
		else	// GLUT_LEFT
		{
			pointerInWindow = false;
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
			getline(cin, stringLine);
			break;
			
		case 't':
			displayText = !displayText;
			
		case 'b':
			displayBgnd = !displayBgnd;
			break;
		
		case 'c':
			if (appMode == AppMode::CREATION_MODE)
				appMode = AppMode::TEST_MODE;
			else
				appMode = AppMode::CREATION_MODE;
			
			break;

		default:
			break;
	}
}


void myTimerFunc(int value)
{
	static int frameIndex=0;
	static chrono::high_resolution_clock::time_point lastTime = chrono::high_resolution_clock::now();

	//	"re-prime the timer"
	glutTimerFunc(1, myTimerFunc, value);

	//	 do something (e.g. update the state of animated objects)
	chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
	float dt = chrono::duration_cast<chrono::duration<float> >(currentTime - lastTime).count();
	for (auto obj : animatedObjectList)
	{
		if (obj != nullptr)
			obj->update(dt);
	}
	lastTime = currentTime;
	//	And finally I perform the rendering
	if (frameIndex++ % 10 == 0)
	{
		glutPostRedisplay();
	}
}

//--------------------------------------
#if 0
#pragma mark -
#pragma mark Utilities
#endif
//--------------------------------------

void displayTextualInfo(const string& infoStr, int textRow){
	displayTextualInfo(infoStr.c_str(), textRow);
}

void displayTextualInfo(const char* infoStr, int textRow)
{
    //-----------------------------------------------
    //  0.  Build the string to display <-- parameter
    //-----------------------------------------------
    int infoLn = static_cast<int> (strlen(infoStr));

    //-----------------------------------------------
    //  1.  Determine the string's length (in pixels)
    //-----------------------------------------------
    int textWidth = 0, fontHeight=-1;
	switch(fontSize)
	{
		case SMALL_FONT_SIZE:
			fontHeight = 10;
			for (int k=0; k<infoLn; k++)
			{
				textWidth += glutBitmapWidth(SMALL_DISPLAY_FONT, infoStr[k]);
			}
			break;
		
		case MEDIUM_FONT_SIZE:
			fontHeight = 12;
			for (int k=0; k<infoLn; k++)
			{
				textWidth += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr[k]);
			}
			break;
		
		case LARGE_FONT_SIZE:
			fontHeight = 16;
			for (int k=0; k<infoLn; k++)
			{
				textWidth += glutBitmapWidth(LARGE_DISPLAY_FONT, infoStr[k]);
			}
			break;
			
		default:
			break;
	}

    //-----------------------------------------------
    //  2.  get current material properties
    //-----------------------------------------------
    float oldAmb[4], oldDif[4], oldSpec[4], oldShiny;
    glGetMaterialfv(GL_FRONT, GL_AMBIENT, oldAmb);
    glGetMaterialfv(GL_FRONT, GL_DIFFUSE, oldDif);
    glGetMaterialfv(GL_FRONT, GL_SPECULAR, oldSpec);
    glGetMaterialfv(GL_FRONT, GL_SHININESS, &oldShiny);

    glPushMatrix();
	if (displayTextOnTop)
    {
		glTranslatef(0.f, textRow*(fontHeight+2*V_PAD), 0.f);
    }
	else
    {
		glTranslatef(0.f, winHeight - (textRow+1)*(fontHeight+2*V_PAD),0.f);
	}

    //-----------------------------------------------
    //  3.  Clear background rectangle if required
    //-----------------------------------------------
    if (displayBgnd)
    {
		glColor3fv(bgndColor);
		glBegin(GL_POLYGON);
			glVertex2i(0, 0);
			glVertex2i(0, fontHeight + 2*V_PAD);
			glVertex2i(winWidth, fontHeight + 2*V_PAD);
			glVertex2i(winWidth, 0);
		glEnd();
	}
	
	//	Move "up" from current plane, to make sure that we overwrite
	glTranslatef(0.f, 0.f, 0.1f);

    //-----------------------------------------------
    //  4.  Draw the string
    //-----------------------------------------------    
    //	Where do we start drawing from
    int xPos = displayTextOnLeft ? H_PAD : winWidth - textWidth - H_PAD;
    int yPos = fontHeight + V_PAD;

    glColor3fv(textColor);
    int x = xPos;
	switch(fontSize)
	{
		case SMALL_FONT_SIZE:
			for (int k=0; k<infoLn; k++)
			{
				glRasterPos2i(x, yPos);
				glutBitmapCharacter(SMALL_DISPLAY_FONT, infoStr[k]);
				x += glutBitmapWidth(SMALL_DISPLAY_FONT, infoStr[k]);
			}
			break;
		
		case MEDIUM_FONT_SIZE:
			for (int k=0; k<infoLn; k++)
			{
				glRasterPos2i(x, yPos);
				glutBitmapCharacter(MEDIUM_DISPLAY_FONT, infoStr[k]);
				x += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr[k]);
			}
			break;
		
		case LARGE_FONT_SIZE:
			for (int k=0; k<infoLn; k++)
			{
				glRasterPos2i(x, yPos);
				glutBitmapCharacter(LARGE_DISPLAY_FONT, infoStr[k]);
				x += glutBitmapWidth(LARGE_DISPLAY_FONT, infoStr[k]);
			}
			break;
			
		default:
			break;
	}

    //-----------------------------------------------
    //  5.  Restore old material properties
    //-----------------------------------------------
	glMaterialfv(GL_FRONT, GL_AMBIENT, oldAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, oldDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, oldSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, oldShiny);  
    
    //-----------------------------------------------
    //  6.  Restore reference frame
    //-----------------------------------------------
    glPopMatrix();
}

void printMatrix(const GLfloat* m) {
    cout << "((" << m[0] << "\t" << m[4] << "\t" << m[8] << "\t" << m[12] << ")" << endl;
    cout << " (" << m[1] << "\t" << m[5] << "\t" << m[9] << "\t" << m[13] << ")" << endl;
    cout << " (" << m[2] << "\t" << m[6] << "\t" << m[10] << "\t" << m[14] << ")" << endl;
    cout << " (" << m[3] << "\t" << m[7] << "\t" << m[11] << "\t" << m[15] << "))" << endl;
}

//--------------------------------------
#if 0
#pragma mark -
#pragma mark Application init and main
#endif
//--------------------------------------

void applicationInit()
{
	// Create Menus
	int myMenu;
	
	//	Submenu for changing keyboard handling function
	int myTextColorSubmenu = glutCreateMenu(mySubmenuHandler);
	for (int k=0, t=FIRST_TEXT; k<NUM_TEXT_COLORS; k++, t++)
		glutAddMenuEntry(TEXT_COLOR_STR[k].c_str(), t);
	int myBgndColorSubmenu = glutCreateMenu(mySubmenuHandler);
	for (int k=0, b=FIRST_BGND; k<NUM_BGND_COLORS; k++, b++)
		glutAddMenuEntry(BGND_COLOR_STR[k].c_str(), b);

	// Main menu that the submenus are connected to
	myMenu = glutCreateMenu(myMenuHandler);
	glutAddMenuEntry("Quit", MenuItemID::QUIT_MENU);
	//
	glutAddMenuEntry("-", MenuItemID::SEPARATOR);
	glutAddMenuEntry("Other stuff", MenuItemID::OTHER_MENU_ITEM);
	glutAddMenuEntry("New entry", 64);
	
	glutAddMenuEntry("-", MenuItemID::SEPARATOR);
	glutAddSubMenu("Text color:", myTextColorSubmenu);
	glutAddSubMenu("Background color:", myBgndColorSubmenu);
	glutAddMenuEntry("-", MenuItemID::SEPARATOR);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


    shared_ptr<Asteroid> face = make_shared<Asteroid>(0.f, 0.f, 0.f, 1.f, 1.f, 5.f, 5.f);
    //    and add it to both lists
    objectList.push_back(face);
    animatedObjectList.push_back(face);
	
	//	time really starts now
	startTime = time(nullptr);
}

int main(int argc, char * argv[])
{
	//	Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	glutCreateWindow(WIN_TITLE);
	
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
