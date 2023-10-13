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


PolyWingRight::PolyWingRight(Point centerPoint, float angle, float scaleX, float scaleY, float red, float green, float blue, Point offset):
    PolyShape(centerPoint, angle, scaleX, scaleY, red, green, blue, offset)
{
    initFromPolygon();
}


PolyWingRight::~PolyWingRight() {
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
    
    vertexList = glGenLists(1);
    glNewList(vertexList, GL_COMPILE);
    glBegin(GL_POLYGON);
    for (int k=0; k<PolyWingRight::_maxLoadedPnts; k++) {
        if (k >= PolyWingRight::_numLoadedPnts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        glVertex2f(PolyWingRight::_loadedShapePnts[k][0], PolyWingRight::_loadedShapePnts[k][1]);
    }
    glEnd();
    glEndList();
}
