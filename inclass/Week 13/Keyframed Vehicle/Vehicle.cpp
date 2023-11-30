/*----------------------------------------------------------------------------------+
 |																					|
 |	Vehicle.h	Class for general vehicle objects controled by a keyframe animator	|									|
 |																					|
 |	Author:		Jean-Yves Hervé,	University of Rhode Island						|
 |									Dept. of Computer Science and Statistics		|
 |									3D Group for Interactive Visualization			|
 |	Fall 2023																		|
 +---------------------------------------------------------------------------------*/
 
#define LONG_PATH   0

#include <iostream>
#include <cmath>
//
#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(shared_ptr<KeyframeAnimator> anim, bool recordPath, bool drawWaypoints)
	:	animator_(anim),
		ut_(0.f),
		_path(vector<GLfloat*>()),
		recordPath_(recordPath),
		drawWaypoints_(drawWaypoints)
{
	x_ = animator_->getKeyframeElement(0, 0);
	y_ = animator_->getKeyframeElement(0, 1);
	angle_ = animator_->getKeyframeElement(0, 2);
}

Vehicle::Vehicle(float x, float y, float angle, bool recordPath, bool drawWaypoints)
	:	animator_(nullptr),
		x_(x),
		y_(y),
		angle_(angle),
		ut_(0.f),
		_path(vector<GLfloat*>()),
		recordPath_(recordPath),
		drawWaypoints_(drawWaypoints)
{
}


Vehicle::~Vehicle(void)
{
    for (int i=0; i< (int) _path.size(); i++)
        delete []_path[i];
    _path.clear();
}
        
void Vehicle::update(float dt)
{
	if (animator_ != nullptr)
	{
		ut_ += dt;
		if (ut_ > animator_->getLastKeyFrameTime())
		{
			ut_ = animator_->getLastKeyFrameTime();
			recordPath_ = false;
		}

		vector<float> stateVect = animator_->getStateVector(ut_);
		setPosition(stateVect[0], stateVect[1]);
		setOrientation(stateVect[2]);
	}
}


void Vehicle::draw(void) const
{
    glPushMatrix();

	if (drawWaypoints_)
	{
		//  display the way points in green
		glColor4f(0.f, 1.f, 0.f, 1.f);
		for (unsigned int i=0; i<animator_->getNumFrames(); i++)
		{
			glPushMatrix();
			glTranslatef(animator_->getKeyframeElement(i, 0),
						 animator_->getKeyframeElement(i, 1),
						 0.f);
			glRotatef(animator_->getKeyframeElement(i, 2), 0.f, 0.f, 1.f);
			glBegin(GL_POLYGON);
				glVertex2f(0.04f, 0.f);
				glVertex2f(-0.03f, 0.01f);
				glVertex2f(-0.03f, -0.01f);
			glEnd();
			glPopMatrix();
		}
	}
	
    //  display the path so far in blue
    if (_path.size()>1) 
    {
        glBegin(GL_LINE_STRIP);
        glColor4f(0.f, 0.f, 1.f, 1.f);
        for (int i=0; i< (int)(_path.size()); i++)
            glVertex2fv(_path[i]);
        glEnd();
    }
    
    //  then display the vehicle's current location in red
    glTranslatef(x_, y_, 0.f);
    glRotatef(angle_, 0.f, 0.f, 1.f);
    glColor4f(1.f, 0.f, 0.f, 1.f);
    glBegin(GL_POLYGON);
        glVertex2f(0.04f, 0.f);
        glVertex2f(-0.03f, 0.01f);
        glVertex2f(-0.03f, -0.01f);
    glEnd();

    glPopMatrix();
}

void Vehicle::setPosition(GLfloat theX, GLfloat theY)
{
    x_ = theX;
    y_ = theY;
    
    if (recordPath_)
    {
        GLfloat *pt = new GLfloat[2];
        pt[0] = x_;
        pt[1] = y_;
        _path.push_back(pt);
    }
}

void Vehicle::setOrientation(GLfloat theAngle)
{
    angle_ = theAngle;
}

