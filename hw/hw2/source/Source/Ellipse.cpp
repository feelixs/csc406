//
//  Ellipse.cpp
//  Prog 02
//
//  Created by Jean-Yves Hervé on 2023-09-14.
//

#include <cmath>
#include <iostream>
#include "glPlatform.h"
#include "Ellipse.h"


const int Ellipse::numCirclePts_ = 24;
float** Ellipse::circlePts_;

bool ellipseInitialized = initEllipseFunc();

Ellipse::Ellipse(float centerX, float centerY, float angle, float radiusX, float radiusY,
				float red, float green, float blue)
	:	GraphicObject(centerX, centerY, angle),
		//
		radiusX_(radiusX),
		radiusY_(radiusY),
		red_(red),
		green_(green),
		blue_(blue)
{
}
Ellipse::Ellipse(float centerX, float centerY, float radius,
				float red, float green, float blue)
	:	GraphicObject(centerX, centerY, 0.f),
		//	
		radiusX_(radius),
		radiusY_(radius),
		red_(red),
		green_(green),
		blue_(blue)
{
}

Ellipse::~Ellipse() {
}

void Ellipse::draw() const
{
	//	save the current coordinate system (origin, axes, scale)
	glPushMatrix();
	
	//	move to the center of the disk
	glTranslatef(getX(), getY(), 0.f);
		
	// apply rotation
	glRotatef(getAngle(), 0.f, 0.f, 1.f);
	
	//	apply the radius as a scale
	glScalef(radiusX_, radiusY_, 1.f);
	
	glColor3f(red_, green_, blue_);
	glBegin(GL_POLYGON);
			for (int k=0; k<numCirclePts_; k++)
				glVertex2f(circlePts_[k][0],
						   circlePts_[k][1]);
	glEnd();
	
	//	restore the original coordinate system (origin, axes, scale)
	glPopMatrix();
}

// I want this code to run only once
bool initEllipseFunc()
{
	Ellipse::circlePts_ = new float*[Ellipse::numCirclePts_];
	for (int k=0; k<Ellipse::numCirclePts_; k++)
		Ellipse::circlePts_[k] = new float[2];
		
	//	Initialize the array of coordinates of the disk or radius 1 centered at (0, 0)
	float angleStep = 2.f*M_PI/Ellipse::numCirclePts_;
	for (int k=0; k<Ellipse::numCirclePts_; k++)
	{
		float theta = k*angleStep;
		Ellipse::circlePts_[k][0] = cosf(theta);
		Ellipse::circlePts_[k][1] = sinf(theta);
	}
	return true;
}
