//
//  Ellipse.cpp
//  Prog 02
//
//  Created by Jean-Yves Hervé on 2023-09-14.
//

#include <cmath>
#include <iostream>
#include "glPlatform.h"
#include "Ellipse.hpp"

using namespace std;

#define VERSION1    1
#define VERSION2    2

#define VERSION VERSION1

extern float X_MIN, X_MAX;
extern float Y_MIN, Y_MAX;


const int Ellipse::numCirclePts_ = 24;
float** Ellipse::circlePts_;
GLuint Ellipse::displayList_;

bool ellipseInitialized = initEllipseFunc();

Ellipse::Ellipse(float centerX, float centerY, float angle, float radiusX, float radiusY,
                float red, float green, float blue)
    :    centerX_(centerX),
        centerY_(centerY),
        angle_(angle),
        radiusX_(radiusX),
        radiusY_(radiusY),
        red_(red),
        green_(green),
        blue_(blue)
{
}
Ellipse::Ellipse(float centerX, float centerY, float radius,
                float red, float green, float blue)
    :    centerX_(centerX),
        centerY_(centerY),
        angle_(0.f),
        radiusX_(radius),
        radiusY_(radius),
        red_(red),
        green_(green),
        blue_(blue)
{
}

Ellipse::~Ellipse()
{
    cout << "Ellipse at " << centerX_ << ", " << centerY_ << " sating goodbye" << endl;
}

void Ellipse::draw() const
{
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(centerX_, centerY_, 0.f);
        
    // apply rotation
    glRotatef(angle_, 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(radiusX_, radiusY_, 1.f);
    
    glColor3f(red_, green_, blue_);
#if VERSION == VERSION1
    glBegin(GL_POLYGON);
            for (int k=0; k<numCirclePts_; k++)
                glVertex2f(circlePts_[k][0],
                           circlePts_[k][1]);
    glEnd();
#else
    glCallList(displayList_);
#endif

    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

void Ellipse::update()
{
    static float speed = 0.01f;
    centerX_ += speed;
    
    // stop when arrive at the edge of the world
    if (centerX_ >= X_MAX)
    {
        speed = 0;
    }
}


// I want this code to run only once
bool initEllipseFunc()
{
    Ellipse::circlePts_ = new float*[Ellipse::numCirclePts_];
    for (int k=0; k<Ellipse::numCirclePts_; k++)
        Ellipse::circlePts_[k] = new float[2];
        
    //    Initialize the array of coordinates of the disk or radius 1 centered at (0, 0)
    float angleStep = 2.f*M_PI/Ellipse::numCirclePts_;
    for (int k=0; k<Ellipse::numCirclePts_; k++)
    {
        float theta = k*angleStep;
        Ellipse::circlePts_[k][0] = cosf(theta);
        Ellipse::circlePts_[k][1] = sinf(theta);
    }
    
    // create display list
    
#if VERSION == VERSION2
    Ellipse::displayList_ = glGenLists(1);

    glNewList(Ellipse::displayList_, GL_COMPILE);
    glBegin(GL_POLYGON);
    for (int k=0; k<Ellipse::numCirclePts_; k++)
    {
        float theta = k*angleStep;
        glVertex2f(cosf(theta), sinf(theta));
    }
    glEnd();
    glEndList();
#endif
    return true;
}


bool Ellipse::isInside(float x, float y) {
    float dx = (x - getX())/getRadiusX();
    float dy = (y - getY())/getRadiusY();
    return dx*dx + dy*dy < 1.f;
}
