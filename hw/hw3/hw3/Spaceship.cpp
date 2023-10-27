//
//  Spaceship.cpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#include "Spaceship.hpp"
#include <math.h>

float Spaceship::boundingBoxXmin_ = 0;
float Spaceship::boundingBoxXmax_ = 0;
float Spaceship::boundingBoxYmin_ = 0;
float Spaceship::boundingBoxYmax_ = 0;


Spaceship::Spaceship(float x, float y)
:   Object(x, y, 0.f),
    GraphicObject(x, y, 0.f),
    AnimatedObject(x, y, 0.f, 0.f, 0.f, 0.f),
    red_(0.5f),
    green_(0.5f),
    blue_(1.f),
    isAccelerating_(0),
    accel_(0.f),
    collisionBox_(std::make_unique<BoundingBox>(-0.5, 0.5, -0.5, 0.5, ColorIndex::RED))
{
    //create an absolute collision box with height & width set to the MAXIMUM possible hitbox of object
    // (when the object is rotated by 45 degrees)
    //
    // this way, the game can first check if collisions occur within this box
    // and then do a trig calc for the object collision ONLY IF this bounding box has a collision
    float halfWidth = 0.5;
    float halfHeight = 0.5;

    float corners[4][2] = {
        {-halfWidth, halfHeight},
        {halfWidth, halfHeight},
        {halfWidth, -halfHeight},
        {-halfWidth, -halfHeight}
    };
    
    float cosTheta = cosf(M_PI / 4); // 45 degrees = rotation with most extreme size for bounding box
    float sinTheta = sinf(M_PI / 4);

    boundingBoxXmin_ = boundingBoxXmax_ = corners[0][0] * cosTheta - corners[0][1] * sinTheta;
    boundingBoxYmin_ = boundingBoxYmax_ = corners[0][0] * sinTheta + corners[0][1] * cosTheta;

    for (int i = 1; i < 4; i++) {
        float xRot = corners[i][0] * cosTheta - corners[i][1] * sinTheta;
        float yRot = corners[i][0] * sinTheta + corners[i][1] * cosTheta;

        boundingBoxXmin_ = fmin(boundingBoxXmin_, xRot);
        boundingBoxXmax_ = fmax(boundingBoxXmax_, xRot);
        boundingBoxYmin_ = fmin(boundingBoxYmin_, yRot);
        boundingBoxYmax_ = fmax(boundingBoxYmax_, yRot);
    }
}


void Spaceship::draw() const {
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
    
    // apply rotation
    glRotatef(getAngle() - 90, 0.f, 0.f, 1.f); // the spaceship model is drawn wrong by 90 degrees
    
    //    apply the radius as a scale
    glScalef(1.f, 1.f, 1.f);
    
    
    if (isAccelerating_) {
        // thrust flame
        glColor3f(1.0f, 0.5f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0.0f, -0.7f);
        glVertex2f(0.2f, -0.3f);
        glVertex2f(-0.2f, -0.3f);
        glEnd();
    }
    // spaceship model
    glColor3f(red_, green_, blue_);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.2f, -0.3f);
    glVertex2f(-0.2f, -0.3f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
    
    collisionBox_->draw();
}


bool Spaceship::isInside(const WorldPoint& pt)
{
    return false;
}


void Spaceship::update(float dt) {
    
    setVx(getVx() + cosf(getAngle() * M_PI / 180) * dt * getAccel());
    setVy(getVy() + sinf(getAngle() * M_PI / 180) * dt * getAccel());
    
    collisionBox_->setDimensions(getX() + boundingBoxXmin_, getX() + boundingBoxXmax_, getY() + boundingBoxYmin_, getY() + boundingBoxYmax_);
  
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
