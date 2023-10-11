//
//  PolyEarLeft.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyWingLeft.hpp"
#include "glPlatform.h"
#include <fstream>
#include <iostream>
#include <string>

int PolyWingLeft::_numLoadedPnts = 0;
const int PolyWingLeft::_maxLoadedPnts = 25;
float** PolyWingLeft::_loadedShapePnts;


PolyWingLeft::PolyWingLeft(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue):
    PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue)
{
    initFromPolygon();
}

PolyWingLeft::PolyWingLeft(Point centerPoint, float angle, float scaleX, float scaleY, float red, float green, float blue):
    PolyShape(centerPoint, angle, scaleX, scaleY, red, green, blue)
{
    initFromPolygon();
}


PolyWingLeft::~PolyWingLeft() {

}


void PolyWingLeft::draw() const {
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
    for (int k=0; k<PolyWingLeft::_maxLoadedPnts; k++) {
        if (k >= PolyWingLeft::_numLoadedPnts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        glVertex2f(PolyWingLeft::_loadedShapePnts[k][0], PolyWingLeft::_loadedShapePnts[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}


void PolyWingLeft::initFromPolygon() {
    /// hard coded values for the shape
    _numLoadedPnts = 5;
    
    _loadedShapePnts = new float*[_numLoadedPnts];
    for (int i = 0; i < _numLoadedPnts; i++) {
        _loadedShapePnts[i] = new float[2];
    }
    
    PolyWingLeft::_loadedShapePnts[0][0] = -0.76;
    PolyWingLeft::_loadedShapePnts[0][1] = 0.38;
    PolyWingLeft::_loadedShapePnts[1][0] = -0.66;
    PolyWingLeft::_loadedShapePnts[1][1] = 0.1;
    PolyWingLeft::_loadedShapePnts[2][0] = -0.65;
    PolyWingLeft::_loadedShapePnts[2][1] = 0;
    PolyWingLeft::_loadedShapePnts[3][0] = -0.83;
    PolyWingLeft::_loadedShapePnts[3][1] = 0;
    PolyWingLeft::_loadedShapePnts[4][0] = -0.9;
    PolyWingLeft::_loadedShapePnts[4][1] = -0.2;
}
