//
//  PolyCircle.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyCircle.hpp"
#include "PolyShape.hpp"
#include <iostream>
#include <math.h>


PolyCircle::PolyCircle(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue): PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue) {
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
    PolyShape::~PolyShape();
    for (int i = 0; i < _numCirPoints; i++) {
        delete[] _circlePoints[i];
    }
    delete[] _circlePoints;
    std::cout << "Cicle at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
}
