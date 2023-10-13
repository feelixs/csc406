//
//  PolyCustom.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyHalfCircle.hpp"
#include "glPlatform.h"
#include <fstream>
#include <iostream>
#include <string>

int PolyHalfCircle::_numLoadedPnts = 0;
const int PolyHalfCircle::_maxLoadedPnts = 25;
float** PolyHalfCircle::_loadedShapePnts;


PolyHalfCircle::PolyHalfCircle(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue):
    PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue)
{
    initFromPolygon();
}

PolyHalfCircle::PolyHalfCircle(Point centerPoint, float angle, float scaleX, float scaleY, float red, float green, float blue, Point offset, float angleOffset):
    PolyShape(centerPoint, angle, scaleX, scaleY, red, green, blue, offset, angleOffset)
{
    initFromPolygon();
}


PolyHalfCircle::~PolyHalfCircle() {
   
}


void PolyHalfCircle::initFromPolygon() {
    /// hard coded values for the shape
    _numLoadedPnts = 10;
    
    _loadedShapePnts = new float*[_numLoadedPnts];
    for (int i = 0; i < _numLoadedPnts; i++) {
        _loadedShapePnts[i] = new float[2];
    }
    // these are the coords for a half-circle
    _loadedShapePnts[0][0] = 1.0;
    _loadedShapePnts[0][1] = 0.0;
    _loadedShapePnts[1][0] = 0.9510565162951535;
    _loadedShapePnts[1][1] = 0.3090169943749474;
    _loadedShapePnts[2][0] = 0.8090169943749475;
    _loadedShapePnts[2][1] = 0.5877852522924731;
    _loadedShapePnts[3][0] = 0.5877852522924731;
    _loadedShapePnts[3][1] = 0.8090169943749475;
    _loadedShapePnts[4][0] = 0.30901699437494745;
    _loadedShapePnts[4][1] = 0.9510565162951535;
    _loadedShapePnts[5][0] = 6.123233995736766e-17;
    _loadedShapePnts[5][1] = 1.0;
    _loadedShapePnts[6][0] = -0.30901699437494734;
    _loadedShapePnts[6][1] = 0.9510565162951536;
    _loadedShapePnts[7][0] = -0.587785252292473;
    _loadedShapePnts[7][1] = 0.8090169943749475;
    _loadedShapePnts[8][0] = -0.8090169943749473;
    _loadedShapePnts[8][1] = 0.5877852522924732;
    _loadedShapePnts[9][0] = -0.9510565162951535;
    _loadedShapePnts[9][1] = 0.3090169943749475;
    
    vertexList = glGenLists(1);
    glNewList(vertexList, GL_COMPILE);
    glBegin(GL_POLYGON);
    for (int k=0; k<PolyHalfCircle::_maxLoadedPnts; k++) {
        if (k >= PolyHalfCircle::_numLoadedPnts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        glVertex2f(PolyHalfCircle::_loadedShapePnts[k][0], PolyHalfCircle::_loadedShapePnts[k][1]);
    }
    glEnd();
    glEndList();
}
