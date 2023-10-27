//
//  Asteroid.cpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#include "Asteroid.hpp"


Asteroid::Asteroid(float centerX, float centerY, float angle, float width, float height, float vx, float vy)
    :    Object(centerX, centerY, angle),
        GraphicObject(centerX, centerY, angle),
        AnimatedObject(centerX, centerY, angle, vx, vy, 0.f),
        scaleX_(width),
        scaleY_(height),
        collisionBox_(std::make_unique<BoundingBox>(centerX-(width/2), centerX+(width/2), centerY-(height/2), centerY+(height/2), 0.f, ColorIndex::RED))
{
}

Asteroid::Asteroid(const WorldPoint& pt, float angle, float spin, float width, float height, const Velocity& vel)
    :    Object(pt, angle),
        GraphicObject(pt, angle),
        AnimatedObject(pt.x, pt.y, angle, vel.vx, vel.vy, spin),
        //
        scaleX_(width),
        scaleY_(height),
        collisionBox_(std::make_unique<BoundingBox>(pt.x-(width/2), pt.x+(width/2), pt.y-(height/2), pt.y+(height/2), 0.f, ColorIndex::RED))
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
    
    glColor3f(1.f, 1.f, 1.f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(+0.5f, -0.5f);
        glVertex2f(+0.5f, +0.5f);
        glVertex2f(-0.5f, +0.5f);
    glEnd();
    
    
    collisionBox_->draw();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

void Asteroid::update(float dt) {
    
  //  collisionBox_->setDimensions(getX()-(getScaleX()/2), getX()+(getScaleX()/2), getY()-(getScaleY()/2), getY()+(getScaleY()/2), 0.f);
    
    if (getVx() != 0.f)
        setX(getX() + getVx()*dt);
    if (getVy() != 0.f)
        setY(getY() + getVy()*dt);
    if (getSpin() != 0.f)
        setAngle(getAngle() + getSpin()*dt);
        
    if (getX() < World::X_MIN || getX() > World::X_MAX || getY() < World::Y_MIN || getY() > World::Y_MAX) {
        // this is for cylinder world
        if (getX() < World::X_MIN) {
            setX(getX() + World::WIDTH);
        }
        else if (getX() > World::X_MAX) {
            setX(getX() - World::WIDTH);
        }
        if (getY() < World::Y_MIN || getY() > World::Y_MAX) {
            if (getY() < World::Y_MIN) {
                setY(-World::Y_MIN);
            }
            else {
                setY(-World::Y_MAX);
            }
        }
    }
}


bool Asteroid::isInside(const WorldPoint& pt)
{
    return false;
}
