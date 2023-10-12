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
    _init_();
}

PolyRect::PolyRect(Point centerPoint, float angle, float length, float width, float r, float g, float b): PolyShape(centerPoint, angle, length, width, r, g, b), width_(width), length_(length) {
    _init_();
}

void PolyRect::_init_() {
    _rectPoints = new float*[numRectPts]; // only need 2 points for a line, but we also want to give it width
    for (int i = 0; i < numRectPts; i++)
        _rectPoints[i] = new float[2];
    
    _rectPoints[0][0] = -length_ / 2.f;
    _rectPoints[0][1] = -width_ / 2.f;
    
    _rectPoints[1][0] = -length_ / 2.f;
    _rectPoints[1][1] = width_ / 2.f;
    
    _rectPoints[2][0] = length_ / 2.f;
    _rectPoints[2][1] = width_ / 2.f;

    _rectPoints[3][0] = length_ / 2.f;
    _rectPoints[3][1] = -width_ / 2.f;
    
    vertexList = glGenLists(1);
    glNewList(vertexList, GL_COMPILE);
    glBegin(GL_POLYGON);
    for (int k=0; k<numRectPts; k++) {
        glVertex2f(_rectPoints[k][0], _rectPoints[k][1]);
    }
    glEnd();
    glEndList();
}

PolyRect::~PolyRect() {
    
}
