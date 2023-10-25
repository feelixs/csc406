//
//  Object.cpp
//  Template Project
//
//  Created by Jean-Yves Hervé on 2023-10-17.
//

#include "Object.h"

using namespace earshooter;

Object::Object(float x, float y, float angle)
	:	x_(x),
		y_(y),
		angle_(angle)
{}

Object::Object(const WorldPoint& pt, float angle)
	:	x_(pt.x),
		y_(pt.y),
		angle_(angle)
{}


