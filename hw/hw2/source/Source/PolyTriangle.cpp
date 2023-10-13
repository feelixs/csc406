//
//  PolyTriangle.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyTriangle.hpp"
#include <iostream>
#include <math.h>
#include "glPlatform.h"


float** PolyTriangle::_trianPoints;
const int numTrianPts = 3;

PolyTriangle::PolyTriangle(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue): PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue) {
    _init_();
}

PolyTriangle::PolyTriangle(Point centerPoint, float angle, float scaleX, float scaleY, float red, float green, float blue, Point offset, float angleOffset): PolyShape(centerPoint, angle, scaleX, scaleY, red, green, blue, offset, angleOffset) {
    _init_();
}

void PolyTriangle::_init_() {
    _trianPoints = new float*[numTrianPts];
    for (int i = 0; i < numTrianPts; i++) {
        _trianPoints[i] = new float[2];
    }
    
    // calc the points for an equilateral triangle
    float width = 5.f;
    float height = width * sqrt(3.f);

    // vertex 1
    _trianPoints[0][0] = 0;
    _trianPoints[0][1] = height / 2.f;
    // vertex 2
    _trianPoints[1][0] =  -width;
    _trianPoints[1][1] = -height / 2.f;
    // vertex 3
    _trianPoints[2][0] = width;
    _trianPoints[2][1] = -height / 2.f;
    
    vertexList = glGenLists(1);
    glNewList(vertexList, GL_COMPILE);
    glBegin(GL_POLYGON);
    for (int k=0; k<numTrianPts; k++) {
        glVertex2f(_trianPoints[k][0], _trianPoints[k][1]);
    }
    glEnd();
    glEndList();
}


PolyTriangle::~PolyTriangle() {
    
}
