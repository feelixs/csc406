//
//  GraphicObject.cpp
//  Template Project
//
//  Created by Jean-Yves Hervé on 2023-10-05.
//

#include <iostream>
#include "GraphicObject.h"

using namespace earshooter;

GraphicObject::GraphicObject(float x, float y, float angle)
	:	Object(x, y, angle),
		absoluteBox_(nullptr),
		relativeBox_(nullptr)
{}

GraphicObject::GraphicObject(const WorldPoint& pt, float angle)
	:	Object(pt, angle),
		absoluteBox_(nullptr),
		relativeBox_(nullptr)
{}

