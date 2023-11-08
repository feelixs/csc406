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
        initVel_(Velocity{vx, vy}),
        halfWidth_(width/2),
        halfHeight_(height/2),
        gameIsEgocentric_(false)
{
    initBoundingBox_();
}

Asteroid::Asteroid(const WorldPoint& pt, float angle, float spin, float width, float height, const Velocity& vel)
    :    Object(pt, angle),
        GraphicObject(pt, angle),
        AnimatedObject(pt.x, pt.y, angle, vel.vx, vel.vy, spin),
        //
        width_(width),
        height_(height),
        initVel_(vel),
        halfWidth_(width/2),
        halfHeight_(height/2),
        gameIsEgocentric_(false)
{
    initBoundingBox_();
}

void Asteroid::initBoundingBox_() {
    //create an absolute collision box with height & width set to the MAXIMUM possible hitbox of object
    // (when the object is rotated by 45 degrees)
    //
    // this way, the game can first check if collisions occur within this box
    // and then do a trig calc for the object collision ONLY IF this bounding box has a collision
    setAbsoluteBox(std::make_shared<AbsBoundingBox>(-1, 1, -1, 1, ColorIndex::RED));
    setRelativeBox(std::make_shared<RelBoundingBox>(-0.5, 0.5, -0.5, 0.5, 0, ColorIndex::RED));
    float corners[4][2] = {
        {-halfWidth_, halfHeight_},
        {halfWidth_, halfHeight_},
        {halfWidth_, -halfHeight_},
        {-halfWidth_, -halfHeight_}
    };
    
    float cosTheta = cosf(M_PI / 4); // 45 degrees = rotation with most extreme size for bounding box
    float sinTheta = sinf(M_PI / 4);

    for (int i = 0; i < 4; i++) {
        float xRot = corners[i][0] * cosTheta - corners[i][1] * sinTheta;
        float yRot = corners[i][0] * sinTheta + corners[i][1] * cosTheta;
        // after rotating this corner, is it lower (for min) or higher (for max) than the unrotated corner?
        // if so, replace the min/max coords
        absoluteBoxMinX_ = fmin(absoluteBoxMinX_, xRot);
        absoluteBoxMaxX_ = fmax(absoluteBoxMaxX_, xRot);
        absoluteBoxMinY_ = fmin(absoluteBoxMinY_, yRot);
        absoluteBoxMaxY_ = fmax(absoluteBoxMaxY_, yRot);
    }
    
    getAbsoluteBox()->setDimensions(getX()+absoluteBoxMinX_, getX()+absoluteBoxMaxX_, getY()+absoluteBoxMinY_, getY()+absoluteBoxMaxY_);
    getRelativeBox()->setDimensions(getX()-halfWidth_, getX()+halfWidth_, getY()-halfHeight_, getY()+halfHeight_, getAngle());
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
    
    getRelativeBox()->draw();
    getAbsoluteBox()->draw();
    
}

void Asteroid::update(float dt) {
    if (getVx() != 0.f)
        setX(getX() + getVx()*dt);
    if (getVy() != 0.f)
        setY(getY() + getVy()*dt);
    if (getSpin() != 0.f)
        setAngle(getAngle() + getSpin()*dt);
    
    if (!gameIsEgocentric_) {
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
    
    getAbsoluteBox()->setDimensions(getX()+absoluteBoxMinX_, getX()+absoluteBoxMaxX_, getY()+absoluteBoxMinY_, getY()+absoluteBoxMaxY_);
    getRelativeBox()->setDimensions(getX()-halfWidth_, getX()+halfWidth_, getY()-halfHeight_, getY()+halfHeight_, getAngle());
}


bool Asteroid::isInside(const WorldPoint& pt)
{
    if (!getAbsoluteBox()->isInside(pt.x, pt.y)) {
        // if pt is not inside Absolute Boundingbox, we don't need to do any calculations
        return false;
    }
    
    // it's inside the absolute box, but is it inside the asteroid?
    // the relative box's area is same as the asteroid's
    return getRelativeBox()->isInside(pt.x, pt.y);
}


bool Asteroid::collidesWith(std::shared_ptr<GraphicObject> other) {
    if (!getAbsoluteBox()->overlaps((*other->getAbsoluteBox()))) {
        // if not overlapping the Absolute Boundingbox, we don't need to do any calculations
        return false;
    }
    
    // it's inside the absolute box, meaning we must check if it's also inside the inner Relative box
    return getRelativeBox()->overlaps((*other->getRelativeBox()));
}
