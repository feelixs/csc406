//
//  main.cpp
//  hw2
//
//  Created by Michael Felix on 10/12/23.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <memory>
#include "EllipseReticle.hpp"
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
void displayTextualInfo(string infoStr, Point pos);
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
const int TEXT_PADDING = 0;
const float TEXT_COLOR[4] = {1.f, 1.f, 1.f, 1.f};
const float PARTITION_COLOR[4] = {0.6f, 0.6f, 0.6f, 1.f};


const float ANGLE_CHNG_STEP = -10; // i set up the angle changing login backwards
const float SPD_CHNG_STEP = 1;

//--------------------------------------
#if 0
#pragma mark Global variables
#endif
//--------------------------------------

int winWidth = 800,
    winHeight = 800;

vector<shared_ptr<ObjectGroup>> allObjectGroups;

bool creationModeEnabled = false;
GroupType creationModeType = HEADS_ON_STICK; // chosen GroupType
GroupSize creationModeSize = SMALL; // chosen GroupSize
int creationModeNum = 6; // number of heads
shared_ptr<Animal> creationModePreview;
shared_ptr<EllipseReticle> creationModeReticle;

bool velocityModeEnabled = false;
bool velocityToChange = 0; // 0 means +/- keys will change x, 1 means y
shared_ptr<PolyShape> velocityModePreview;

bool rotationModeEnabled = false;

bool animationModeEnabled = false;
shared_ptr<PolyShape> animationModePlayingIcon;
shared_ptr<PolyShape> animationModePausedIcon;

int groupEditIndex = -1; // represents the groupobject thats currently selected by the user

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
    
    if (creationModeEnabled) {
        creationModeReticle->draw();
    }
    
	for (auto obj : allObjectGroups)
	{
		if (obj != nullptr)
			obj->draw();
	}
     
    creationModePreview->draw();
    velocityModePreview->draw();
    
    if (animationModeEnabled) {
        animationModePlayingIcon->draw();
    } else {
        animationModePausedIcon->draw();
    }


	glPopMatrix();

	//	Display textual info
    if (groupEditIndex > -1) {
        displayTextualInfo(to_string(groupEditIndex), Point{-9, -9});
    }


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

				/*cout << "Click at: (" << ix << ", " << iy << ")" << endl;
				Point wPt = pixelToWorld(ix, iy);
				cout << "Corresponding world point: (" << wPt.x << ", " <<
						wPt.y << ")" << endl;
				Point pPt = worldToPixel(wPt.x, wPt.y);
				cout << "Back to pixels: (" << pPt.x << ", " <<
						pPt.y << ")" << endl;
                 */
			}
			else if (state == GLUT_UP)
			{
                if (creationModeEnabled) {
                    // create an objectgroup at the mouse pointer
                    allObjectGroups.push_back(make_shared<ObjectGroup>(creationModeType, creationModeSize, creationModeNum, pixelToWorld(ix, iy)));
                }
                
			}
			break;
			
		default:
			break;
	}
}

void myMouseMotionHandler(int ix, int iy)
{
	// track active mouse motion
}
void myMousePassiveMotionHandler(int ix, int iy)
{
    Point mousePos = pixelToWorld(ix, iy);
    creationModeReticle->setX(mousePos.x);
    creationModeReticle->setY(mousePos.y);
}
void myEntryHandler(int state)
{
	// track when mouse enters/leaves
}


//	This callback function is called when a keyboard event occurs
//
void myKeyHandler(unsigned char c, int x, int y)
{
	switch (c)
	{
		case 'q':
		case 27:
			exit(0);
			break;
        
        case '\\':
            // '\' key resets all modes
            creationModeEnabled = false;
            velocityModeEnabled = false;
            rotationModeEnabled = false;
            animationModeEnabled = false;
            groupEditIndex = -1;
            
            creationModePreview->setColor(1.f, 0.f, 0.f);
            velocityModePreview->setColor(1.f, 0.f, 0.f);
            velocityModePreview->setSpin(0);
            velocityModePreview->setAngle(0);
            break;
        case 'c':
            // toggle creation mode
            cout << "c pressed\n";
            if (creationModeEnabled) {
                cout << "disabled creation\n";
                creationModeEnabled = false;
                creationModePreview->setColor(1.f, 0.f, 0.f); // red if disabled
            } else {
                cout << "enabled creation\n";
                creationModeEnabled = true;
                creationModePreview->setColor(0.f, 1.f, 0.f); // green animal if creation is enabled
            }
            break;
        case 's':
            if (creationModeEnabled) {
                cout << "head on stci\n";
                creationModeType = HEADS_ON_STICK;
                creationModeReticle.reset(new EllipseReticle(pixelToWorld(x, y), 1, 1.f, 1.f, 1.f, 24));
            }
            break;
        case 'w':
            if (creationModeEnabled) {
                cout << "head on wheel\n";
                creationModeType = HEADS_ON_WHEELS;
                creationModeReticle.reset(new EllipseReticle(pixelToWorld(x, y), 1, 1.f, 1.f, 1.f, 6));
            }
            break;
            
        case 'v':
            // toggle velocity mode
            cout << "v pressed\n";
            if (velocityModeEnabled) {
                cout << "disabled velocity\n";
                velocityModeEnabled = false;
                velocityModePreview->setColor(1.f, 0.f, 0.f);
            } else {
                cout << "enabled velocity\n";
                velocityModeEnabled = true;
                velocityModePreview->setColor(0.f, 1.f, 0.f);
            }
            break;
        case 'x':
            if (velocityModeEnabled) {
                velocityToChange = 0;
            }
            break;
        case 'y':
            if (velocityModeEnabled) {
                velocityToChange = 1;
            }
            break;
            
        case 'r':
            // toggle rotation mode
            cout << "r pressed\n";
            if (rotationModeEnabled) {
                cout << "disabled rotation\n";
                rotationModeEnabled = false;
                velocityModePreview->setSpin(0);
                velocityModePreview->setAngle(0);
            } else {
                cout << "enabled rotation\n";
                rotationModeEnabled = true;
                velocityModePreview->setSpin(-50);
            }
            break;
        case 'a':
            cout << "a pressed\n";
            if (animationModeEnabled) {
                cout << "disabled animation\n";
                animationModeEnabled = false;
            } else {
                cout << "enabled animation\n";
                animationModeEnabled = true;
            }
            break;
        case ' ':
            if ((animationModeEnabled) & (groupEditIndex > -1)) {
                allObjectGroups.at(groupEditIndex)->togglePlay();
            }
            break;
            
        case '=':
        case '+':
            // +, =, are mapped to the same key
            if (creationModeEnabled) {
                if (creationModeSize == SMALL) { // there are only 3 possible sizes
                    creationModeSize = MEDIUM;
                    cout << "medium\n";
                } else if (creationModeSize == MEDIUM) {
                    creationModeSize = LARGE;
                    cout << "large\n";
                } else {
                    cout << "small\n";
                    creationModeSize = SMALL;
                }
            }
            if ((velocityModeEnabled) & (groupEditIndex > -1)) {
                if (velocityToChange) {
                    // 1 = change y
                    allObjectGroups.at(groupEditIndex)->setSpeedY(allObjectGroups.at(groupEditIndex)->getSpeedY() + SPD_CHNG_STEP);
                } else {
                    // 0 = change x
                    allObjectGroups.at(groupEditIndex)->setSpeedX(allObjectGroups.at(groupEditIndex)->getSpeedX() + SPD_CHNG_STEP);
                }
            }
            // these modes are not mutually exclusive, so it's possible to be in velocity & rotation mode at the same time, for example
            // and in such a case pressing +/- will change both settings simultaneously
            if ((rotationModeEnabled) & (groupEditIndex > -1)) {
                allObjectGroups.at(groupEditIndex)->setSpin(allObjectGroups.at(groupEditIndex)->getSpin() + ANGLE_CHNG_STEP);
            }
            break;
            
        case '_':
        case '-':
            // _, -, are mapped to the same key
            if (creationModeEnabled) {
                if (creationModeSize == SMALL) { // there are only 3 possible sizes
                    creationModeSize = LARGE;
                    cout << "large\n";
                } else if (creationModeSize == MEDIUM) {
                    creationModeSize = SMALL;
                    cout << "small\n";
                } else {
                    creationModeSize = MEDIUM;
                    cout << "=\n";
                }
            }
            if ((velocityModeEnabled) & (groupEditIndex > -1)) {
                if (velocityToChange) {
                    // 1 = change y
                    allObjectGroups.at(groupEditIndex)->setSpeedY(allObjectGroups.at(groupEditIndex)->getSpeedY() - SPD_CHNG_STEP);
                } else {
                    // 0 = change x
                    allObjectGroups.at(groupEditIndex)->setSpeedX(allObjectGroups.at(groupEditIndex)->getSpeedX() - SPD_CHNG_STEP);
                }
            }
            if ((rotationModeEnabled) & (groupEditIndex > -1)) {
                allObjectGroups.at(groupEditIndex)->setSpin(allObjectGroups.at(groupEditIndex)->getSpin() - ANGLE_CHNG_STEP);
            }
            break;
            
        case 'z':
            if ((velocityModeEnabled) & (groupEditIndex > -1)) {
                // reset velocity of all object groups
                allObjectGroups.at(groupEditIndex)->setSpeedX(0);
                allObjectGroups.at(groupEditIndex)->setSpeedY(0);
            }
            break;
        
            
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (animationModeEnabled) {
                groupEditIndex = c - '0';  // char of a num minus the key '0' = the number
            }
            if (creationModeEnabled) {
                creationModeNum = c - '0';
            }
            break;
        case '0':
        case '1':
        case '2':
            if (animationModeEnabled) {
                groupEditIndex = c - '0';
            }
            break;
            
        case '[':
            if (animationModeEnabled) {
                groupEditIndex --;
                if (groupEditIndex < 0) {
                    groupEditIndex = (int) allObjectGroups.size() - 1;
                }
            }
            break;
        case ']':
            if (animationModeEnabled) {
                groupEditIndex ++;
                if (groupEditIndex == (int) allObjectGroups.size()) {
                    groupEditIndex = 0;
                }
            }
            break;
        
		default:
            cout << "Unhandled choice: " << c << endl;
			break;
	}
}


void myTimerFunc(int value)
{
    static int frameIndex=0;
    static chrono::high_resolution_clock::time_point lastTime = chrono::high_resolution_clock::now();

    //    "re-prime the timer"
    glutTimerFunc(1, myTimerFunc, value);

    //     do something (e.g. update the state of animated objects)
    chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
    float dt = chrono::duration_cast<chrono::duration<float>>(currentTime - lastTime).count();

	//	 do something (e.g. update the state of some objects)
	
    
        
    for (int i = 0; i < allObjectGroups.size(); i++)
    {
        auto obj = allObjectGroups.at(i);
        
        // display the currently selected object
        if (i == groupEditIndex) {
            obj->setColor(0.f, 1.f, 0.f);
        } else {
            obj->setColor(0.f, 1.f, 1.f);
        }
        if (animationModeEnabled) {
            // only update the obj position if animation mode is on
            if (obj != nullptr) {
                obj->update(dt);
            }
        }
    }
    
    // update the status info objects regardless of animation mode
    creationModePreview->update(dt);
    velocityModePreview->update(dt);
    
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
#pragma mark Application init and main
#endif
//--------------------------------------


void displayTextualInfo(string infoStr, Point pos)
{
    //-----------------------------------------------
    //  0.  get current material properties
    //-----------------------------------------------
    float oldAmb[4], oldDif[4], oldSpec[4], oldShiny;
    glGetMaterialfv(GL_FRONT, GL_AMBIENT, oldAmb);
    glGetMaterialfv(GL_FRONT, GL_DIFFUSE, oldDif);
    glGetMaterialfv(GL_FRONT, GL_SPECULAR, oldSpec);
    glGetMaterialfv(GL_FRONT, GL_SHININESS, &oldShiny);

    glPushMatrix();

    //-----------------------------------------------
    //  1.  Build the string to display <-- parameter
    //-----------------------------------------------
    int infoLn = (int) infoStr.size();

    //-----------------------------------------------
    //  2.  Determine the string's length (in pixels)
    //-----------------------------------------------
    int textWidth = 0;

    for (int k=0; k<infoLn; k++)
    {
        textWidth += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr.at(k));
    }


		
	//  add a few pixels of padding
    textWidth += 2*TEXT_PADDING;
	
    //-----------------------------------------------
    //  4.  Draw the string
    //-----------------------------------------------
    glColor4fv(TEXT_COLOR);
    int x = pos.x;

    for (int k=0; k<infoLn; k++)
    {
        glRasterPos2i(x, pos.y);
        glutBitmapCharacter(MEDIUM_DISPLAY_FONT, infoStr.at(k));
        x += glutBitmapWidth(MEDIUM_DISPLAY_FONT, infoStr.at(k));
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

    creationModePreview = make_shared<Animal>(Point{-9, 8.3}, 0, 0.5, 1.f, 0.f, 0.f);
    creationModeReticle = make_shared<EllipseReticle>(Point{0, 0}, 1, 1.f, 1.f, 1.f, 12);
    
    float rlen = 1;
    float rwid = 0.5;
    static float velPrevPnts[4][2] = {{-rlen / 2.f, -rwid / 2.f}, {-rlen / 2.f, rwid / 2.f}, {rlen / 2.f, rwid / 2.f}, {rlen / 2.f, -rwid / 2.f}};
    GLuint velocityPrevList = glGenLists(1);
    glNewList(velocityPrevList, GL_COMPILE);
    glBegin(GL_POLYGON);
    // rectangle to display when velocity mode is on
    for (int r=0; r < 4; r++) {
        glVertex2f(velPrevPnts[r][0], velPrevPnts[r][1]);
    }
    glEnd();
    glEndList();
    velocityModePreview = make_shared<PolyShape>(Point{-7, 8.5}, 0, rlen, rwid, 1.f, 0.f, 0.f, velocityPrevList);
    
    rlen = 0.5;
    rwid = 0.5;
    // two parralel lines - pressing 'a' while this is active pauses animation mode
    static float pauseIconPnts[4][2] = {{-rlen / 2, -rwid / 2}, {-rlen / 2, rwid / 2}, {rlen / 2, rwid / 2}, {rlen / 2, -rwid / 2}};
    GLuint pauseIconList = glGenLists(1);
    glNewList(pauseIconList, GL_COMPILE);
    glLineWidth(2.0);  // Adjust the line width as needed
    glBegin(GL_LINES);
    for (int l = 0; l < 4; l++) {
        glVertex2f(pauseIconPnts[l][0], pauseIconPnts[l][1]);
    }
    glEnd();
    glEndList();
    animationModePlayingIcon = make_shared<PolyShape>(Point{-5, 8.5}, 0, 1, 1, 1.f, 0.f, 0.f, pauseIconList);
    
    
    rwid = 5.f;
    rlen = rwid * sqrt(3.f);
    static float playIconPnts[3][2] = {{0, rlen / 2.f}, {-rwid, -rlen / 2.f}, {rwid, -rlen / 2.f}};
    
    GLuint playIconList = glGenLists(1);
    glNewList(playIconList, GL_COMPILE);
    glBegin(GL_POLYGON);
    for (int k=0; k<3; k++) {
        glVertex2f(playIconPnts[k][0], playIconPnts[k][1]);
    }
    glEnd();
    glEndList();
    animationModePausedIcon = make_shared<PolyShape>(Point{-5.1, 8.6}, 30, 0.075, 0.075, 1.f, 0.f, 0.f, playIconList);
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
