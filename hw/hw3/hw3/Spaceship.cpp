//
//  Spaceship.cpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#include "Spaceship.hpp"
#include <math.h>


Spaceship::Spaceship(float x, float y)
:   Object(x, y, 0.f),
    GraphicObject(x, y, 0.f),
    AnimatedObject(x, y, 0.f, 0.f, 0.f, 0.f),
    vel_(0.f),
    red_(0.5f),
    green_(0.5f),
    blue_(0.5f)
{
    
}


void Spaceship::draw() const {
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
    
    // apply rotation
    glRotatef(getAngle(), 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(1.f, 1.f, 1.f);
    
    glColor3f(red_, green_, blue_);
    glBegin(GL_POLYGON);
    // spaceship model
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.2f, -0.3f);
    glVertex2f(-0.2f, -0.3f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}


bool Spaceship::isInside(const WorldPoint& pt)
{
    return false;
}

void Spaceship::addVel(float dv) {
    setVel(getVel() + dv);
}

void Spaceship::update(float dt) {
    float v = getVel(), x = getX(), y = getY(), a = getAngle(), s = getSpin();
    if (v != 0.f) {
        setX(x + sinf(v) * dt);
        setY(y + cosf(v) * dt);
    }
    if (s != 0.f)
        setAngle(a + s * dt);
        
    if (x < World::X_MIN || x > World::X_MAX || y < World::Y_MIN || y > World::Y_MAX) {
        // this is for cylinder world
        if (x < World::X_MIN) {
            setX(x + World::WIDTH);
        }
        else if (x > World::X_MAX) {
            setX(x - World::WIDTH);
        }
        if (y < World::Y_MIN || y > World::Y_MAX) {
            if (y < World::Y_MIN) {
                setY(-World::Y_MIN);
            }
            else {
                setY(-World::Y_MAX);
            }
        }
    }
}
