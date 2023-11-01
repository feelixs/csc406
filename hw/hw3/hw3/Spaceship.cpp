//
//  Spaceship.cpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#include "Spaceship.hpp"
#include <math.h>

const float BLINK_DUR = 0.1;
const float RAD_TO_DEG = M_PI / 180;

bool Spaceship::blinkIsVisible_ = true;
float Spaceship::blinkTimer_ = 0;
float Spaceship::returnFromInvulnerabilityAfter_ = 0;
float Spaceship::boundingBoxXmin_ = 0;
float Spaceship::boundingBoxXmax_ = 0;
float Spaceship::boundingBoxYmin_ = 0;
float Spaceship::boundingBoxYmax_ = 0;


Spaceship::Spaceship(float x, float y, int life)
:   Object(x, y, 0.f),
    GraphicObject(x, y, 0.f),
    AnimatedObject(x, y, 0.f, 0.f, 0.f, 0.f),
    red_(0.f),
    green_(1.f),
    blue_(1.f),
    isAccelerating_(0),
    accel_(0.f),
    life_(life),
    absBoundingBox_(std::make_unique<AbsBoundingBox>(-0.5, 0.5, -0.5, 0.5, ColorIndex::RED)),
    egocentric_(false),
    invulnerable_(false)
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
    if (!blinkIsVisible_)  // if spaceship is currently blinking, don't draw it
        return;
    
    
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
    if (invulnerable_) {
        glColor3f(1.f, 1.f, 1.f);
    } else {
        glColor3f(red_, green_, blue_);
    }
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.2f, -0.3f);
    glVertex2f(-0.2f, -0.3f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
    
    absBoundingBox_->draw();
}


bool Spaceship::isInside(const WorldPoint& pt)
{
    if (!absBoundingBox_->isInside(pt.x, pt.y)) {
        // if pt is not inside my collision box, we don't need to do any calculations
        return false;
    }
    
    // it's inside the collisionbox, but is it inside the spaceship?
    float h = sqrt(3) / 4;
    // spaceship triangle vertices
    WorldPoint A = WorldPoint{0, -h};
    WorldPoint B = WorldPoint{-0.5, h};
    WorldPoint C = WorldPoint{0.5, h};
    
    // prepare pt transformations
    float dx = pt.x - getX(), dy = pt.y - getY();
    float ca = cosf(-getAngle()), sa = sinf(-getAngle());
    float lx = ca * dx + sa * dy;
    float ly = -sa * dx + ca * dy;
    
    // barycentric coordinates
    float detT = (B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y);
    float alpha = ((B.y - C.y) * (lx - C.x) + (C.x - B.x) * (ly - C.y)) / detT;
    float beta = ((C.y - A.y) * (lx - C.x) + (A.x - C.x) * (ly - C.y)) / detT;
    float gamma = 1.0f - alpha - beta;

    return (alpha >= 0) && (beta >= 0) && (gamma >= 0);
}


void Spaceship::update(float dt) {
    // after going invulnerable, a timer (returnFromInvulnerabilityAfter_) is set.
    // this code handles returning from invulnerability after the timer expires
    if (invulnerable_) {
        if (returnFromInvulnerabilityAfter_ > 0) {
            returnFromInvulnerabilityAfter_ -= dt;
        } else {
            returnFromInvulnerabilityAfter_ = 0;
            invulnerable_ = false;
            blinkIsVisible_ = true;
        }
        
        // handle blinking in and out
        if (blinkTimer_ <= 0) {
            blinkIsVisible_ = !blinkIsVisible_;
            blinkTimer_ = BLINK_DUR;
        } else {
            blinkTimer_ -= dt;
        }
    }
    
    
    // set x & y velocities to trig components of the spaceship's acceleration
    setVx(getVx() + cosf(getAngle() * RAD_TO_DEG) * dt * getAccel());
    setVy(getVy() + sinf(getAngle() * RAD_TO_DEG) * dt * getAccel());
    
    // move bounding box to where the spaceship is onscreen
    absBoundingBox_->setDimensions(getX() + boundingBoxXmin_, getX() + boundingBoxXmax_, getY() + boundingBoxYmin_, getY() + boundingBoxYmax_);
    
    // if not egocentric, move the player around the screen
    if (!egocentric_) {
        if (getVx() != 0.f)
            setX(getX() + getVx()*dt);
        if (getVy() != 0.f)
            setY(getY() + getVy()*dt);
    }
    
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
