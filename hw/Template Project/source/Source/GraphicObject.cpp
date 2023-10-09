//
//  GraphicObject.cpp
//  Template Project
//
//  Created by Jean-Yves Hervé on 2023-10-05.
//

#include <iostream>
#include "GraphicObject.h"

GraphicObject::GraphicObject(float x, float y, float angle)
	:	x_(x),
		y_(y),
		angle_(angle)
{}


void GraphicObject::setCenterPoint(Point newCenter) {
    x_ = newCenter.x;
    y_ = newCenter.y;
}
