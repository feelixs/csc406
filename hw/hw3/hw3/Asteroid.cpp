//
//  Asteroid.cpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#include "Asteroid.hpp"

using namespace earshooter;

Asteroid::Asteroid(float centerX, float centerY, float angle, float width, float height, float vx, float vy)
    :    Object(centerX, centerY, angle),
        GraphicObject(centerX, centerY, angle),
        AnimatedObject(centerX, centerY, angle, vx, vy, 0.f),
        //
        scaleX_(width),
        scaleY_(height)
{
}

Asteroid::Asteroid(const WorldPoint& pt, float angle, float spin, float width, float height, const Velocity& vel)
    :    Object(pt, angle),
        GraphicObject(pt, angle),
        AnimatedObject(pt.x, pt.y, angle, vel.vx, vel.vy, spin),
        //
        scaleX_(width),
        scaleY_(height)
{
}

void Asteroid::draw() const
{
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
        
    // apply rotation
    glRotatef(getAngle(), 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(scaleX_, scaleY_, 1.f);
    
//    glColor3f(red_, green_, blue_);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(+0.5f, -0.5f);
        glVertex2f(+0.5f, +0.5f);
        glVertex2f(-0.5f, +0.5f);
    glEnd();
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

bool Asteroid::isInside(const WorldPoint& pt)
{
    return false;
}
