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


void AnimatedObject::update(float dt)
{
	if (vx_ != 0.f)
		setX(getX() + vx_*dt);
	if (vy_ != 0.f)
		setY(getY() + vy_*dt);
	if (spin_ != 0.f)
		setAngle(getAngle() + spin_*dt);
    
	if (getX() < World::X_MIN || getX() > World::X_MAX ||
		getY() < World::Y_MIN || getY() > World::Y_MAX)
	{
        if (getX() < World::X_MIN)
            setX(getX() + World::WIDTH);
        else if (getX() > World::X_MAX)
            setX(getX() - World::WIDTH);
        if (getY() < World::Y_MIN || getY() > World::Y_MAX){
            if (getY() < World::Y_MIN)
                setY(-World::Y_MIN);
            else
                setY(-World::Y_MAX);
            //vy_ = -vy_;
        }
	}
}
