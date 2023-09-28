//
//  PolyLine.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyRect.hpp"
#include "PolyShape.hpp"
#include "glPlatform.h"
#include <iostream>


float** PolyRect::_rectPoints;
const int numRectPts = 4;

PolyRect::PolyRect(float centerX, float centerY, float angle, float length, float width, float r, float g, float b): PolyShape(centerX, centerY, angle, length, width, r, g, b), width_(width), length_(length) {
    _rectPoints = new float*[numRectPts]; // only need 2 points for a line, but we also want to give it width
    for (int i = 0; i < numRectPts; i++)
        _rectPoints[i] = new float[2];
    
    _rectPoints[0][0] = -length / 2.f;
    _rectPoints[0][1] = -width / 2.f;
    
    _rectPoints[1][0] = -length / 2.f;
    _rectPoints[1][1] = width / 2.f;
    
    _rectPoints[2][0] = length / 2.f;
    _rectPoints[2][1] = width / 2.f;

    _rectPoints[3][0] = length / 2.f;
    _rectPoints[3][1] = -width / 2.f;
    
}


PolyRect::~PolyRect() {
    //for (int i = 0; i < 2; i++) {
    //    delete[] _straightLinePoints[i];
    //}
    //delete[] _straightLinePoints;
    std::cout << "Line at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
    //PolyShape::~PolyShape();
}


void PolyRect::draw() const {
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(centerX_, centerY_, 0.f);
        
    // apply rotation
    glRotatef(angle_, 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
   // glScalef(scaleX_, scaleY_, 1.f);
    
    glColor3f(red_, green_, blue_);
    
    glBegin(GL_POLYGON);
    for (int k=0; k<numRectPts; k++) {
        glVertex2f(_rectPoints[k][0], _rectPoints[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}
