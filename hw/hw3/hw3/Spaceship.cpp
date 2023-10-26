//
//  Spaceship.cpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#include "Spaceship.hpp"


Spaceship::Spaceship(float x, float y)
:   Object(x, y, 0.f),
    GraphicObject(x, y, 0.f),
    AnimatedObject(x, y, 0.f, 0.f, 0.f, 0.f),
    vel_(0.f),
    headingDeg_(0.f),
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


void Spaceship::update(float dt) {
    if (getVx() != 0.f)
        setX(getX() + getVx()*dt);
    if (getVy() != 0.f)
        setY(getY() + getVy()*dt);
    if (getSpin() != 0.f)
        setAngle(getAngle() + getSpin()*dt);
        
    //    Temporary stuff:  Freeze motion if the object's origin reaches the edges
    //    of the world
    if (getX() < World::X_MIN || getX() > World::X_MAX ||
        getY() < World::Y_MIN || getY() > World::Y_MAX)
    {
        switch (World::worldType)
        {
            case WorldType::BOX_WORLD:
            if (getX() < World::X_MIN || getX() > World::X_MAX){
                if (getX() < World::X_MIN)
                    setX(World::X_MIN);
                else
                    setX(World::X_MAX);
                setX(-getVx());
            }
            if (getY() < World::Y_MIN || getY() > World::Y_MAX){
                if (getY() < World::Y_MIN)
                    setY(World::Y_MIN);
                else
                    setY(World::Y_MAX);
                setVy(-getVy());
            }
            break;
            
            case WorldType::CYLINDER_WORLD:
                if (getX() < World::X_MIN)
                    setX(getX() + World::WIDTH);
                else if (getX() > World::X_MAX)
                    setX(getX() - World::WIDTH);
            if (getY() < World::Y_MIN || getY() > World::Y_MAX){
                if (getY() < World::Y_MIN)
                    setY(-World::Y_MIN);
                else
                    setY(-World::Y_MAX);
                //getVy() = -getVy();
            }
            break;
                
            default:
            break;
        }
    }
}
