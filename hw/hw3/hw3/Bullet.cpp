//
//  Bullet.cpp
//  hw3
//
//  Created by Michael Felix on 10/27/23.
//

#include "Bullet.hpp"
#include <math.h>

Bullet::Bullet(float x, float y, float angle, float vel) 
    : Object(x, y, angle),
    GraphicObject(x, y, angle),
    AnimatedObject(x, y, angle, 0, 0, 0), // we will calculate vx and vy in the init
    vel_(vel)
{
    initVel_();
}


Bullet::Bullet(WorldPoint& xy, float angle, float vel)
    : Object(xy.x, xy.y, angle),
    GraphicObject(xy.x, xy.y, angle),
    AnimatedObject(xy.x, xy.y, angle, 0, 0, 0), // we will calculate vx and vy in the init
    vel_(vel)
{
    initVel_();
}

void Bullet::initVel_() {
    // set vx and vy relative to my angle and constant vel
    setVx(getVx() + cosf(getAngle() * M_PI / 180) * vel_);
    setVy(getVy() + sinf(getAngle() * M_PI / 180) * vel_);
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



