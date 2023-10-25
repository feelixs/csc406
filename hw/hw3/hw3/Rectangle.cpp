//
//  Rectangle.cpp
//
//  Created by Jean-Yves Hervé on 2023-09-14.
//

#include <cmath>
#include <iostream>
#include "glPlatform.h"
#include "Rectangle.h"

using namespace std;
using namespace earshooter;

Rectangle::Rectangle(float centerX, float centerY, float angle, float width, float height,
				float red, float green, float blue)
	:	Object(centerX, centerY, angle),
		GraphicObject(centerX, centerY, angle),
		//
		width_(width),
		height_(height),
		red_(red),
		green_(green),
		blue_(blue)
{
}

Rectangle::Rectangle(const WorldPoint& pt, float angle, float width, float height,
				float red, float green, float blue)
	:	Object(pt, angle),
		GraphicObject(pt, angle),
		//
		width_(width),
		height_(height),
		red_(red),
		green_(green),
		blue_(blue)
{
}

void Rectangle::draw() const
{
	//	save the current coordinate system (origin, axes, scale)
	glPushMatrix();
	
	//	move to the center of the disk
	glTranslatef(getX(), getY(), 0.f);
		
	// apply rotation
	glRotatef(getAngle(), 0.f, 0.f, 1.f);
	
	//	apply the radius as a scale
	glScalef(width_, height_, 1.f);
	
	glColor3f(red_, green_, blue_);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(+0.5f, -0.5f);
		glVertex2f(+0.5f, +0.5f);
		glVertex2f(-0.5f, +0.5f);
	glEnd();
	
	//	restore the original coordinate system (origin, axes, scale)
	glPopMatrix();
}

bool Rectangle::isInside(const WorldPoint& pt)
{
	return false;
}
