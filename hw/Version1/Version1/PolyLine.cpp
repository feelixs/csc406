//
//  PolyLine.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyLine.hpp"
#include "PolyShape.hpp"
#include "glPlatform.h"
#include <iostream>


float** PolyLine::_straightLinePoints;
const int numLinePts = 4;

PolyLine::PolyLine(float centerX, float centerY, float angle, float length, float width, float r, float g, float b): PolyShape(centerX, centerY, angle, length, width, r, g, b) {
    _straightLinePoints = new float*[4]; // only need 2 points for a line, but we also want to give it width
    for (int i = 0; i < numLinePts; i++)
        _straightLinePoints[i] = new float[2];
    
    // scaleX_ = length
    // scaleY_ = width
    _straightLinePoints[0][0] = 0;
    _straightLinePoints[0][1] = - (scaleX_/2.f);
    
    _straightLinePoints[1][0] = 0;
    _straightLinePoints[1][1] = - (scaleX_/2.f) + scaleY_;
    
    _straightLinePoints[2][0] = scaleY_;
    _straightLinePoints[2][1] = (scaleX_/2.f) + scaleY_;
    
    _straightLinePoints[3][0] = scaleY_;
    _straightLinePoints[3][1] = (scaleX_/2.f);
}


PolyLine::~PolyLine() {
    //for (int i = 0; i < 2; i++) {
    //    delete[] _straightLinePoints[i];
    //}
    //delete[] _straightLinePoints;
    std::cout << "Line at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
    //PolyShape::~PolyShape();
}


void PolyLine::draw() const {
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
    for (int k=0; k<numLinePts; k++) {
        glVertex2f(_straightLinePoints[k][0], _straightLinePoints[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}
