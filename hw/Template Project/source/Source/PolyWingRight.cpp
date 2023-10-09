//
//  PolyEarRight.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyWingRight.hpp"
#include "glPlatform.h"
#include <fstream>
#include <iostream>
#include <string>

int PolyWingRight::_numLoadedPnts = 0;
const int PolyWingRight::_maxLoadedPnts = 25;
float** PolyWingRight::_loadedShapePnts;


PolyWingRight::PolyWingRight(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue):
    PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue)
{
    initFromPolygon();
}


PolyWingRight::~PolyWingRight() {
   // std::cout << "Custom polygon at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
    //PolyShape::~PolyShape();
}


void PolyWingRight::draw() const {
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
    for (int k=0; k<PolyWingRight::_maxLoadedPnts; k++) {
        if (k >= PolyWingRight::_numLoadedPnts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        glVertex2f(PolyWingRight::_loadedShapePnts[k][0], PolyWingRight::_loadedShapePnts[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

void PolyWingRight::initFromPolygon() {
    /// hard coded values for the shape
    _numLoadedPnts = 5;
    
    _loadedShapePnts = new float*[_numLoadedPnts];
    for (int i = 0; i < _numLoadedPnts; i++) {
        _loadedShapePnts[i] = new float[2];
    }
    
    PolyWingRight::_loadedShapePnts[0][0] = 0.76;
    PolyWingRight::_loadedShapePnts[0][1] = 0.38;
    PolyWingRight::_loadedShapePnts[1][0] = 0.66;
    PolyWingRight::_loadedShapePnts[1][1] = 0.1;
    PolyWingRight::_loadedShapePnts[2][0] = 0.65;
    PolyWingRight::_loadedShapePnts[2][1] = 0;
    PolyWingRight::_loadedShapePnts[3][0] = 0.83;
    PolyWingRight::_loadedShapePnts[3][1] = 0;
    PolyWingRight::_loadedShapePnts[4][0] = 0.9;
    PolyWingRight::_loadedShapePnts[4][1] = -0.2;
}

void PolyWingRight::setCenterPoint(Point newCenter) {
    setX(newCenter.x);
    setY(newCenter.y);
}
