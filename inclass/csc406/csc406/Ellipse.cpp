//
//  Ellipse.cpp
//  CSC406-inclass
//
//  Created by Michael Felix on 9/14/23.
//

#include "Ellipse.hpp"
#include <cmath>
#include <cstdio>
#include "glPlatform.h"

const int Ellipse::_numCirclePts = 24;
float** Ellipse::_circlePts;

bool ellipseInitialized = ellipseInit();


Ellipse::Ellipse(float centerX, float centerY, float angle, float radiusX, float radiusY, float r, float g, float b)
    :_centerX(centerX),
    _centerY(centerY),
    _angle(angle),
    _radiusX(radiusX),
    _radiusY(radiusY),
    _red(r),
    _green(g),
    _blue(b)
{
    this->_centerX = centerX;
    this->_centerY = centerY;
    this->_radiusX = radiusX;
    this->_radiusY = radiusY;
    this->_angle = angle;
    this->_red = r;
    this->_green = g;
    this->_blue = b;
}

void Ellipse::draw() const {
    glPushMatrix();
    glTranslatef(_centerX, _centerY, 0.f);
    
    
    glRotatef(_angle, 0.f, 0.f, 1.f);
    
    glScalef(_radiusX, _radiusY, 1.f);
    
    glColor3f(_red, _green, _blue);
    glBegin(GL_POLYGON);
           for (int k=0; k<_numCirclePts; k++)
               glVertex2f(_circlePts[k][0],
                          _circlePts[k][1]);
    
    glEnd();
    glPopMatrix();
}

Ellipse::~Ellipse() {
    std::cout << "Ellipse at " << _centerX << ", " << _centerY << " deleted" << std::endl;
}

bool ellipseInit() {
    Ellipse::_circlePts = new float*[Ellipse::_numCirclePts];
    for (int k=0; k<Ellipse::_numCirclePts; k++)
        Ellipse::_circlePts[k] = new float[2];
        
    //    Initialize the array of coordinates of the disk or radius 1 centered at (0, 0)
    float angleStep = 2.f*M_PI/Ellipse::_numCirclePts;
    for (int k=0; k<Ellipse::_numCirclePts; k++)
    {
        float theta = k*angleStep;
        Ellipse::_circlePts[k][0] = cosf(theta);
        Ellipse::_circlePts[k][1] = sinf(theta);
    }
    return true;
}
