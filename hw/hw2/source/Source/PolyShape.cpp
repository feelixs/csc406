//
//  PolyShape.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyShape.hpp"
#include <iostream>
#include "glPlatform.h"


PolyShape::PolyShape(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue)
:   GraphicObject(centerX, centerY, angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue)
{
}

PolyShape::PolyShape(Point centerPoint, float angle, float scaleX, float scaleY, float red, float green, float blue)
:   GraphicObject(centerPoint.x, centerPoint.y, angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue)
{
}

PolyShape::~PolyShape() {
}



void PolyShape::draw() const {
    // this will be overriden by the shape class's children
    // we will never call draw of the base shape class directly
}
