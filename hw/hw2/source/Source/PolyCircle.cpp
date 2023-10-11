//
//  PolyCircle.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyCircle.hpp"
#include "PolyShape.hpp"
#include "glPlatform.h"
#include <iostream>
#include <math.h>

float** PolyCircle::_circlePoints;
const int PolyCircle::_numCirPoints = 12;


PolyCircle::PolyCircle(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue): PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue) {
    _init_();
}

PolyCircle::PolyCircle(Point centerPoint, float angle, float scaleX, float scaleY, float red, float green, float blue): PolyShape(centerPoint, angle, scaleX, scaleY, red, green, blue) {
    _init_();
}

void PolyCircle::_init_() {
    PolyCircle::_circlePoints = new float*[PolyCircle::_numCirPoints];
    for (int k=0; k<PolyCircle::_numCirPoints; k++) {
        PolyCircle::_circlePoints[k] = new float[2];
    }
    float angleStep = 2.f*M_PI/PolyCircle::_numCirPoints;
    float theta;
    for (int k=0; k<PolyCircle::_numCirPoints; k++) {
        theta = k*angleStep;
        PolyCircle::_circlePoints[k][0] = cosf(theta);
        PolyCircle::_circlePoints[k][1] = sinf(theta);
    }
}

PolyCircle::~PolyCircle() {
}



void PolyCircle::draw() const {
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
        
    // apply rotation
    glRotatef(getAngle(), 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(getScaleX(), getScaleY(), 1.f);
    
    glColor3f(getRed(), getGreen(), getBlue());
    
    glBegin(GL_POLYGON);
    for (int k=0; k<PolyCircle::_numCirPoints; k++) {
        glVertex2f(PolyCircle::_circlePoints[k][0], PolyCircle::_circlePoints[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

