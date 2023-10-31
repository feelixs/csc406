//
//  Asteroid.cpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#include "Asteroid.hpp"


Asteroid::Asteroid(float centerX, float centerY, float angle, float spin, float width, float height, float vx, float vy)
    :    Object(centerX, centerY, angle),
        GraphicObject(centerX, centerY, angle),
        AnimatedObject(centerX, centerY, angle, vx, vy, spin),
        width_(width),
        height_(height),
        collisionBox_(std::make_unique<BoundingBox>(-1, 1, -1, 1, ColorIndex::RED)),
        initVel_(Velocity{vx, vy})
{
    initBoundingBox_(width/2, height/2);
}

Asteroid::Asteroid(const WorldPoint& pt, float angle, float spin, float width, float height, const Velocity& vel)
    :    Object(pt, angle),
        GraphicObject(pt, angle),
        AnimatedObject(pt.x, pt.y, angle, vel.vx, vel.vy, spin),
        //
        width_(width),
        height_(height),
        collisionBox_(std::make_unique<BoundingBox>(-1, 1, -1, 1, ColorIndex::RED)),
        initVel_(vel)
{
    initBoundingBox_(width/2, height/2);
}

void Asteroid::initBoundingBox_(float halfWidth, float halfHeight) {
    //create an absolute collision box with height & width set to the MAXIMUM possible hitbox of object
    // (when the object is rotated by 45 degrees)
    //
    // this way, the game can first check if collisions occur within this box
    // and then do a trig calc for the object collision ONLY IF this bounding box has a collision

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

void Asteroid::draw() const
{
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
        
    // apply rotation
    glRotatef(getAngle(), 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(width_, height_, 1.f);
    
    glColor3f(1.f, 1.f, 1.f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(+0.5f, -0.5f);
        glVertex2f(+0.5f, +0.5f);
        glVertex2f(-0.5f, +0.5f);
    glEnd();
    
    
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
    
    collisionBox_->draw();
}

void Asteroid::update(float dt) {
    
    collisionBox_->setDimensions(getX()+boundingBoxXmin_, getX()+boundingBoxXmax_, getY()+boundingBoxYmin_, getY()+boundingBoxYmax_);
    
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
    if (!collisionBox_->isInside(pt.x, pt.y)) {
        // if pt is not inside my collision box, we don't need to do any calculations
        return false;
    }
    
    // it's inside the collisionbox, but is it inside the asteroid (rectangle)
    float dx = pt.x - getX(), dy = pt.y - getY();
    if (getAngle() != 0.f)
    {
        float ca = cosf(getAngle()), sa = sinf(getAngle());
        float rdx = ca * dx + sa*dy;
        float rdy = -sa *dx + ca*dy;
    
        return (rdx >= -width_/2 ) && (rdx <= width_/2 ) &&
               (rdy >= -height_/2 ) && (rdy <= +height_/2 );
    
    }
    else
        return (pt.x >= getX() - width_/2 ) && (pt.x <= getX() + width_/2 ) &&
               (pt.y >= getY() - height_/2 ) && (pt.y <= getY() + height_/2 );
}
