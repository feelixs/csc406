//
//  Ellipse.cpp
//  CSC406-inclass
//
//  Created by Michael Felix on 9/14/23.
//

#include "Ellipse.hpp"


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
    
}
