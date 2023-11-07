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
#include <iomanip>
#include <sstream>
//
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "glPlatform.h"
#include "World.h"
#include "Spaceship.hpp"
#include "Healthbar.hpp"
#include "LivesDisplay.hpp"

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
const int NUM_STARTING_ASTEROIDS = 1;

float curScore = 0;
float curPlayerAccel = 0;

vector<shared_ptr<Bullet>> allBullets;
vector<shared_ptr<Asteroid>> allAsteroids;

const WorldPoint LIVES_COUNTER_POS = WorldPoint{-29.5, 8.75};
const int PLAYER_STARTING_LIVES = 3;
const WorldPoint INTEGRITY_BAR_POS = WorldPoint{-15, 4.75};
const int PLAYER_STARTING_INTEGRITY = 5;
const float INTEGRITY_BAR_SCALE = 1;
const float BULLET_LIFE_SECS = 1.0;
const int BULLET_VEL = 10;
const float PLAYER_ROTATION_RATE = 180;

const int STARTING_PLAYER_ACCEL = 5;


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

//--------------------------------------
#if 0
#pragma mark Function prototypes
#endif
//--------------------------------------
void displayTextualInfo(const string& infoStr, int textRow);
void displayTextualInfo(const char* infoStr, int textRow);
void myDisplayFunc(void);
void myResizeFunc(int w, int h);
void myMouseHandler(int b, int s, int x, int y);
void myMouseMotionHandler(int x, int y);
void myMousePassiveMotionHandler(int x, int y);
void myEntryHandler(int state);
void myKeyHandler(unsigned char c, int x, int y);
void myKeyUpHandler(unsigned char c, int x, int y);
void mySpecialKeyHandler(int key, int x, int y);
void mySpecialKeyUpHandler(int key, int x, int y);
void myMenuHandler(int value);
void mySubmenuHandler(int colorIndex);
void myTimerFunc(int val);
void applicationInit();

void setEgocentricGlobal(bool val);
void correctForEgocentric();
void detectCollisions();
void eraseAsteroid(shared_ptr<Asteroid> ast);
void clearAsteroids();
void eraseBullet(shared_ptr<Bullet> b);
//--------------------------------------
#if 0
#pragma mark Constants
#endif
//--------------------------------------
const int INIT_WIN_X = 10, INIT_WIN_Y = 32;

shared_ptr<Spaceship> player;

const float World::X_MIN = -10.f;
const float World::X_MAX = +10.f;
const float World::Y_MIN = -10.f;
const float World::Y_MAX = +10.f;
const float World::WIDTH = World::X_MAX - World::X_MIN;
const float World::HEIGHT = World::Y_MAX - World::Y_MIN;

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
uniform_real_distribution<float> World::randomWidth(0.5f, 2.5f);
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

bool GAME_PAUSED = false;
bool GAME_OVER = false;

bool pointerInWindow = false;
GLint lastX = -1, lastY = -1;

const GLfloat* textColor = TEXT_COLOR[0];
const GLfloat* bgndColor = BGND_COLOR[0];

vector<shared_ptr<GraphicObject> > objectList;
list<shared_ptr<AnimatedObject> > animatedObjectList;

WorldType World::worldType = WorldType::CYLINDER_WORLD;

//--------------------------------------
#if 0
#pragma mark -
#pragma mark Callback functions
#endif
//--------------------------------------

void setEgocentricGlobal(bool val) {
    if (val) {
        player->setEgocentric(true);
        curPlayerAccel = player->getAccel(); // we will not be using the player->accel_ variable to deternmine the asteroids' movemnt
        player->setAccel(0); // because we need to set it to 0 in egocentric mode so the player doesn't move
        
        // if we just switched to egocentric mode, the player might not be in the center of the screen
        // so we need to move all asteroids by the player's offset to account for when we move the player to the center
        for (auto ast : allAsteroids) {
            if (ast != nullptr) {
                if (player->getX() != 0) {
                    ast->setX(ast->getX() - player->getX());
                }
                if (player->getY() != 0) {
                    ast->setY(ast->getY() - player->getY());
                }
                ast->setEgocentric(true);
            }
        }
        // also need to relocate bullets
        for (auto b : allBullets) {
            if (b != nullptr) {
                if (player->getX() != 0) {
                    b->setX(b->getX() - player->getX());
                }
                if (player->getY() != 0) {
                    b->setY(b->getY() - player->getY());
                }
            }
        }
        // now center the player on the screen
        if (player->getX() != 0) {
            player->setX(0);
        }
        if (player->getY() != 0) {
            player->setY(0);
        }
        
    } else {
        player->setEgocentric(false);
        player->setAccel(curPlayerAccel);
        curPlayerAccel = 0;
        
        // egocentric mode has been disabled
        for (auto ast : allAsteroids) {
            if (ast != nullptr) {
                // reset each asteroid velocity to its default value
                ast->setVx(ast->getInitVx());
                ast->setVy(ast->getInitVy());
                ast->setEgocentric(false);
            }
        }
    }
    
    
}

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

    if (!player->isEgocentric()) { // if we're egocentric, we don't want objects to wrap around
        if (World::worldType == WorldType::CYLINDER_WORLD)
        {
            // draw x offscreen
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
            
            // recenter
            glTranslatef(-World::WIDTH, 0, 0);
            
            // now draw y
            glTranslatef(0, -World::HEIGHT,  0);
            for (auto obj : objectList)
            {
                if (obj != nullptr)
                    obj->draw();
            }
            glTranslatef(0, 2*World::HEIGHT,  0);
            for (auto obj : objectList)
            {
                if (obj != nullptr)
                    obj->draw();
            }
        }
    }

	glPopMatrix();
    
    glTranslatef(World::X_MIN, World::Y_MAX, 0.f);
    glScalef(World::drawInPixelScale, -World::drawInPixelScale, 1.f);
    
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << curScore; // only display 2 decimal points after score
    if (player->getLives() > 0) {
        displayTextualInfo(stream.str(), 0);
    } else {
        // we're putting 'game over detection' in the draw function
        //so that the life count is drawn 1 last time (with no lives remaining) before pausing everything
        GAME_PAUSED = true;
        GAME_OVER = true;
        displayTextualInfo("GAME OVER: PRESS 'R' TO RESTART     " + stream.str(), 0);
    }

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
				// left mouse down
			}
			else if (state == GLUT_UP)
            {
                // left mouse up
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
	
}

void myMousePassiveMotionHandler(int ix, int iy)
{
    /*
	lastX = ix;
	lastY = iy;
	pointerInWindow = (ix >= 0 && ix < winWidth && iy >= 0 && iy < winHeight);

	if (trackPassiveMousePointer)
	{
		cout << "Passive mouse at (" << ix << ", " << iy << ")" << endl;
	}
     */

}

void myEntryHandler(int state)
{
    /*
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
     */
    
}


void mySpecialKeyHandler(int key, int x, int y) {
    switch (key)
    {
        case GLUT_KEY_RIGHT:
            player->setSpin(-PLAYER_ROTATION_RATE);
            break;
        case GLUT_KEY_LEFT:
            player->setSpin(PLAYER_ROTATION_RATE);
            break;
        case GLUT_KEY_UP:
            curPlayerAccel = player->getAccelRate();
            player->setAccel(curPlayerAccel);
            player->setIsAccelerating(true);
            break;
        default:
            break;
    }
}

void mySpecialKeyUpHandler(int key, int x, int y) {
    switch (key)
    {
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_LEFT:
            player->setSpin(0);
            break;
        case GLUT_KEY_UP:
            player->setIsAccelerating(false);
            curPlayerAccel = 0;
            player->setAccel(0);
            break;
        default:
            break;
    }
}


//	This callback function is called when a keyboard event occurs
//
void myKeyHandler(unsigned char c, int x, int y)
{
    
   // cout << c << endl;
	// silence warning
    
	(void) x;
	(void) y;
    	
	switch (c)
    {
        case 'q':
        case 'Q':
        case 27:
            exit(0);
            break;
        
        case 'g':
        case 'G':
            setEgocentricGlobal(false);
            break;
        case 'e':
        case 'E':
            setEgocentricGlobal(true);
            break;
            
            // TODO add arrow keys
        case 'd':
        case 'D':
            player->setSpin(-PLAYER_ROTATION_RATE);
            break;
        case 'a':
        case 'A':
            player->setSpin(PLAYER_ROTATION_RATE);
            break;
        case 'w':
        case 'W':
            curPlayerAccel = player->getAccelRate();
            player->setAccel(curPlayerAccel);
            player->setIsAccelerating(true);
            break;
        case 's':
        case 'S':
            /*
             
             // pdf said no 'slow down' control
            if (player->getVx() != 0.f)
                player->setVx(player->getVx() * DECREASE_SPEED_CONST);
            if (player->getVy() != 0.f)
                player->setVy(player->getVy() * DECREASE_SPEED_CONST);
            */
            break;
        case 'r':
            if (GAME_OVER) {
                clearAsteroids(); // on game restart, remove all asteroids that were spawned last game
                
                curScore = 0;
                player->setX(0);
                player->setY(0);
                player->setAccel(0);
                player->setAngle(0);
                player->setVx(0);
                player->setVy(0);
                player->setLives(PLAYER_STARTING_LIVES);
                player->setIntegtrity(PLAYER_STARTING_INTEGRITY);
                player->setAccelRate(STARTING_PLAYER_ACCEL);
                GAME_OVER = false;
                GAME_PAUSED = false;
            }
            break;
            
        case ' ': { // space -> shoot a bullet from the player
            WorldPoint p = WorldPoint{player->getX(), player->getY()};
            shared_ptr<Bullet> b = make_shared<Bullet>(p, player->getAngle(), BULLET_VEL, BULLET_LIFE_SECS);
            allBullets.push_back(b);
            objectList.push_back(b);
            break;
        }
        
        default:
            break;
	}
}

void myKeyUpHandler(unsigned char c, int x, int y)
{
    // silence warning
    (void) x;
    (void) y;

    switch (c) {
        case 'w':
        case 'W':
            player->setIsAccelerating(false);
            curPlayerAccel = 0;
            player->setAccel(0);
            break;
        case 'a':
        case 'A':
        case 'd':
        case 'D':
            player->setSpin(0);
            break;
    }
}

void correctForEgocentric() {
    if (player->isEgocentric()) {
        // is the game in egocentric mode?
        for (auto ast : allAsteroids) {
            if (ast != nullptr) {
                // if so, change each asteroid's velocity by negative the player's
                ast->setVx(ast->getInitVx() - player->getVx());
                ast->setVy(ast->getInitVy() - player->getVy());
            }
        }
    }
}


/// @param ast the asteroid from the allAsteroids vector to erase from allAsteroids and objectList
void eraseAsteroid(shared_ptr<Asteroid> ast) {
    allAsteroids.erase(std::remove(allAsteroids.begin(), allAsteroids.end(), ast), allAsteroids.end());
    objectList.erase(std::remove(objectList.begin(), objectList.end(), ast), objectList.end());
}

void clearAsteroids() {
    // first remove all asteroids from objectlist
    bool erased;
    for (int i = 0; i < objectList.size(); /* we will manually increment */) {
        erased = false;
        for (auto ast: allAsteroids) {
            if (objectList.at(i) == ast) {
                objectList.erase(objectList.begin() + i);
                erased = true;
                break;
            }
        }
        if (!erased) { // only increment if we haven't deleted from objectlist in this iteration
            i++;
        }
    }
    
    allAsteroids.clear(); // then clear asteroid list
}

/// @param b the bullet from the allBullets vector to erase from allBullets and objectList
void eraseBullet(shared_ptr<Bullet> b) {
    // erase 'b' from allBullets & objectList
    allBullets.erase(std::remove(allBullets.begin(), allBullets.end(), b), allBullets.end());
    objectList.erase(std::remove(objectList.begin(), objectList.end(), b), objectList.end());
}



void detectCollisions() {

    // asteroid / bullet collisions
    bool deletedObj = false;
    for (int a = 0; a < allAsteroids.size(); a ++) {
        shared_ptr<Asteroid> ast = allAsteroids.at(a);
        for (int b = 0; b < allBullets.size(); b++) {
            if (ast->isInside(allBullets.at(b)->getPos())) {
                eraseAsteroid(ast);
                eraseBullet(allBullets.at(b));
                deletedObj = true;
                break;
            }
        }
        if (deletedObj) {
            break;  // after erasing from the vector we're iterating tru, we need to break to prevent out_of_range exception
        }
        
        // player / asteroid collision
        if (!player->isInvulnerable()) {
            if (player->collidesWith(ast)) {
                player->takeHits(1);
            }
        }
    }
}


void myTimerFunc(int value)
{
    static int frameIndex=0;
    static chrono::high_resolution_clock::time_point lastTime = chrono::high_resolution_clock::now();

    //    "re-prime the timer"
    glutTimerFunc(1, myTimerFunc, value);
    
    if (!GAME_PAUSED) {

        //	 do something (e.g. update the state of animated objects)
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        float dt = chrono::duration_cast<chrono::duration<float> >(currentTime - lastTime).count();
        
        correctForEgocentric();
        detectCollisions();
        
        for (auto obj : animatedObjectList)
        {
            if (obj != nullptr)
                obj->update(dt);
        }
        
        // iterate over all active bullets, deleting all expired ones and updating active ones
        auto thisBullet = allBullets.begin();
        while (thisBullet != allBullets.end()) {
            if ((*thisBullet)->getLife() < (*thisBullet)->getAge()) {
                auto itToRemove = std::remove(objectList.begin(), objectList.end(), *thisBullet);
                // erase the "removed" elements from objectList
                objectList.erase(itToRemove, objectList.end());
                thisBullet = allBullets.erase(thisBullet);
                // no need to ++ as this element is removed, we're now on the next one already
            } else {
                (*thisBullet)->update(dt);
                ++thisBullet;
            }
        }
        
        curScore += dt;
        lastTime = currentTime;
    }
    
    //    And finally I perform the rendering
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

//--------------------------------------
#if 0
#pragma mark -
#pragma mark Application init and main
#endif
//--------------------------------------

void applicationInit()
{
    for (int i = 0; i < NUM_STARTING_ASTEROIDS; i++) {
        shared_ptr<Asteroid> new_ast = make_shared<Asteroid>(randomPos(), randomAngleDeg(), randomSpinDeg(), randWidth(), randWidth(), randomVelocity(-1.f, 1.f));
        //    and add it to both lists
        objectList.push_back(new_ast);
        animatedObjectList.push_back(new_ast);
        allAsteroids.push_back(new_ast);
    }
    
    player = make_shared<Spaceship>(0.f, 0.f, PLAYER_STARTING_INTEGRITY, STARTING_PLAYER_ACCEL, PLAYER_STARTING_LIVES);
    objectList.push_back(player);
    animatedObjectList.push_back(player);
    
    shared_ptr<Healthbar> integrity_bar = make_shared<Healthbar>(INTEGRITY_BAR_POS, player, INTEGRITY_BAR_SCALE, 0.5);
    animatedObjectList.push_back(integrity_bar);
    objectList.push_back(integrity_bar);
    
    shared_ptr<LivesDisplay> lives_counter = make_shared<LivesDisplay>(LIVES_COUNTER_POS, player, 1.2, 0.75);
    
    animatedObjectList.push_back(lives_counter);
    objectList.push_back(lives_counter);
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
    glutKeyboardUpFunc(myKeyUpHandler);
    glutSpecialFunc(mySpecialKeyHandler);
    glutSpecialUpFunc(mySpecialKeyUpHandler);
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
