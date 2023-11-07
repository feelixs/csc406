//
//  AnimatedObject.cpp
//  Template Project
//
//  Created by Jean-Yves Hervé on 2023-10-17.
//

#include "World.h"
#include "AnimatedObject.h"

using namespace earshooter;

AnimatedObject::AnimatedObject(float x, float y, float angle,
								 float vx, float vy, float spin)
	:	Object(x, y, angle),
		//
		vx_(vx),
		vy_(vy),
		spin_(spin)
{
}

AnimatedObject::AnimatedObject(const WorldPoint& pt, float angle, const Velocity& vel, float spin)
	:	Object(pt, angle),
		//
		vx_(vel.vx),
		vy_(vel.vy),
		spin_(spin)
{
}


void AnimatedObject::update(float dt) {
}
