//
//  Bullet.cpp
//  hw3
//
//  Created by Michael Felix on 10/27/23.
//

#include "Bullet.hpp"
#include <math.h>
#include <iostream>

const float RAD_TO_DEG = M_PI / 180;

Bullet::Bullet(float x, float y, float angle, float vel, float lifetime)
    : Object(x, y, angle),
    GraphicObject(x, y, angle),
    AnimatedObject(x, y, angle, 0, 0, 0), // we will calculate vx and vy in the init
    vel_(vel),
    lifetime_(lifetime),
    age_(0)
{
    initVel_();
}


Bullet::Bullet(WorldPoint& xy, float angle, float vel, float lifetime)
    : Object(xy.x, xy.y, angle),
    GraphicObject(xy.x, xy.y, angle),
    AnimatedObject(xy.x, xy.y, angle, 0, 0, 0), // we will calculate vx and vy in the init
    vel_(vel),
    lifetime_(lifetime),
    age_(0)
{
    initVel_();
}

void Bullet::initVel_() {
    // set vx and vy relative to my angle and constant vel
    setVx(getVx() + cosf(getAngle() * RAD_TO_DEG) * vel_);
    setVy(getVy() + sinf(getAngle() * RAD_TO_DEG) * vel_);
}

bool Bullet::isInside(const WorldPoint& pt) {
    return (pt.x == getX() && pt.y == getY());
}

void Bullet::draw() const {
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
        
    // apply rotation
    glRotatef(getAngle(), 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(1.f, 1.f, 1.f);
    
    glColor3f(0.5f, 0.5f, 1.f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, -0.05f);
        glVertex2f(+0.05f, -0.05f);
        glVertex2f(+0.05f, +0.05f);
        glVertex2f(-0.05f, +0.05f);
    glEnd();
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}


void Bullet::update(float dt) {
    age_ += dt;
    //std::cout << age_ << std::endl;
    if (getVx() != 0.f)
        setX(getX() + getVx()*dt);
    if (getVy() != 0.f)
        setY(getY() + getVy()*dt);
    if (getSpin() != 0.f)
        setAngle(getAngle() + getSpin()*dt);
    
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
        }
    }
}


