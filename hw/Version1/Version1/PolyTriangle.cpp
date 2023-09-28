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
}

PolyTriangle::~PolyTriangle() {
    //for (int i = 0; i < _numLoadedPnts; i++) {
    //    delete[] _loadedShapePnts[i];
    //}
    //delete[] _loadedShapePnts;
 //   std::cout << "Triangle at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
}



void PolyTriangle::draw() const {
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(centerX_, centerY_, 0.f);
        
    // apply rotation
    glRotatef(angle_, 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(scaleX_, scaleY_, 1.f);
    
    glColor3f(red_, green_, blue_);
    
    glBegin(GL_POLYGON);
    for (int k=0; k<numTrianPts; k++) {
        glVertex2f(_trianPoints[k][0], _trianPoints[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}
