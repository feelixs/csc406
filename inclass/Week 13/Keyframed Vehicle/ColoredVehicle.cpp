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
#include "ColoredVehicle.h"

using namespace std;

ColoredVehicle::ColoredVehicle(shared_ptr<KeyframeAnimator> anim, bool recordPath, bool drawWaypoints)
	:	animator_(anim),
		ut_(0.f),
		_path(vector<GLfloat*>()),
		recordPath_(recordPath),
		drawWaypoints_(drawWaypoints)
{
	x_ = animator_->getKeyframeElement(0, 0);
	y_ = animator_->getKeyframeElement(0, 1);
	angle_ = animator_->getKeyframeElement(0, 2);
	scale_ = animator_->getKeyframeElement(0, 3);
	r_ = animator_->getKeyframeElement(0, 4);
	g_ = animator_->getKeyframeElement(0, 5);
	b_ = animator_->getKeyframeElement(0, 6);
}


ColoredVehicle::~ColoredVehicle(void)
{
    for (int i=0; i< (int) _path.size(); i++)
        delete []_path[i];
    _path.clear();
}
        
void ColoredVehicle::update(float dt)
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
		scale_  = stateVect[3];
		r_  = stateVect[4];
		g_  = stateVect[5];
		b_  = stateVect[6];
	}
}


void ColoredVehicle::draw(void) const
{
    glPushMatrix();

	if (drawWaypoints_)
	{
		//  display the way points in green
		for (unsigned int i=0; i<animator_->getNumFrames(); i++)
		{
			glPushMatrix();
			glTranslatef(animator_->getKeyframeElement(i, 0),
						 animator_->getKeyframeElement(i, 1),
						 0.f);
			glRotatef(animator_->getKeyframeElement(i, 2), 0.f, 0.f, 1.f);
			glScalef(animator_->getKeyframeElement(i, 3),
					  animator_->getKeyframeElement(i, 3),
					  1.f);
			glColor4f(animator_->getKeyframeElement(i, 4),
					  animator_->getKeyframeElement(i, 5),
					  animator_->getKeyframeElement(i, 6), 1.f);
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
    glScalef(scale_, scale_, 1.f);
    glColor4f(r_, g_, b_, 1.f);
    glBegin(GL_POLYGON);
        glVertex2f(0.04f, 0.f);
        glVertex2f(-0.03f, 0.01f);
        glVertex2f(-0.03f, -0.01f);
    glEnd();

    glPopMatrix();
}

void ColoredVehicle::setPosition(GLfloat theX, GLfloat theY)
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

void ColoredVehicle::setOrientation(GLfloat theAngle)
{
    angle_ = theAngle;
}

