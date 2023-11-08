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
float Spaceship::absoluteBoxMinX_ = 0;
float Spaceship::absoluteBoxMax_ = 0;
float Spaceship::absoluteBoxMinY_ = 0;
float Spaceship::absoluteBoxMaxY_ = 0;
float Spaceship::startingAccelRate_ = 0;


float Spaceship::invulnerableSecs_ = 0.5f; // in seconds - amound of time to be invulnerable after taking dmg

Spaceship::Spaceship(float x, float y, int integtrity, int accel_rate, int lives)
:   Object(x, y, 0.f),
    GraphicObject(x, y, 0.f),
    AnimatedObject(x, y, 0.f, 0.f, 0.f, 0.f),
    red_(0.f),
    green_(1.f),
    blue_(1.f),
    isAccelerating_(0),
    accel_(0.f),
    accelRate_(accel_rate),
    integrity_(integtrity),
    startingIntegrity_(integtrity),
    lives_(lives),
    egocentric_(false),
    invulnerable_(false)
{
    ColorIndex boundingColor = ColorIndex::NO_COLOR;
    setAbsoluteBox(std::make_shared<AbsBoundingBox>(-0.5, 0.5, -0.5, 0.5, boundingColor));
    setRelativeBox(std::make_shared<RelBoundingBox>(-0.5, 0.5, -0.5, 0.5, 0, boundingColor));
    
    startingAccelRate_ = accelRate_;
    
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

    for (int i = 0; i < 4; i++) {
        float xRot = corners[i][0] * cosTheta - corners[i][1] * sinTheta;
        float yRot = corners[i][0] * sinTheta + corners[i][1] * cosTheta;
        // after rotating this corner, is it lower (for min) or higher (for max) than the unrotated corner?
        // if so, replace the min/max coords
        absoluteBoxMinX_ = fmin(absoluteBoxMinX_, xRot);
        absoluteBoxMax_ = fmax(absoluteBoxMax_, xRot);
        absoluteBoxMinY_ = fmin(absoluteBoxMinY_, yRot);
        absoluteBoxMaxY_ = fmax(absoluteBoxMaxY_, yRot);
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
    
    // thrust flame
    if (isAccelerating_) {
        switch (lives_) {
            case 3:
                // full thrust
                glColor3f(1.0f, 0.5f, 0.0f);
                glBegin(GL_POLYGON);
                glVertex2f(0.0f, -0.7f);
                glVertex2f(0.2f, -0.3f);
                glVertex2f(-0.2f, -0.3f);
                glEnd();
                break;
            case 2:
                // half thrust
                glColor3f(1.0f, 0.5f, 0.0f);
                glBegin(GL_POLYGON);
                glVertex2f(0.0f, -0.5f);
                glVertex2f(0.15f, -0.3f);
                glVertex2f(-0.15f, -0.3f);
                glEnd();
                break;
            default:
                // lives <2 means spaceship is so damaged that its engines are non-functional
                // here we assume that lives will never go higher than 3, which is impossible unless we manually set it
                break;
        }
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
    
    getRelativeBox()->draw();
    getAbsoluteBox()->draw();
}

void Spaceship::takeHits(float dmg) {
//    cout << "player takes damage and goes invulnerable for " << invulnerableSecs_ << " secs\n";
    setIntegtrity(integrity_ - dmg);
    goInvulnerableFor(invulnerableSecs_);
    if (integrity_ <= 0) {
        lives_--;
        if (lives_ > 0) {
            integrity_ = startingIntegrity_;
        }
    }
}

bool Spaceship::isInside(const WorldPoint& pt)
{
    if (!getAbsoluteBox()->isInside(pt.x, pt.y)) {
        // if pt is not inside my collision box, we don't need to do any calculations
        return false;
    }
    if (!getRelativeBox()->isInside(pt.x, pt.y)) {
        return false;
    }
    
    // it's inside the collisionboxes, but is it inside the spaceship?
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
        }
        
        // handle blinking in and out
        if (blinkTimer_ <= 0) {
            blinkIsVisible_ = !blinkIsVisible_;
            blinkTimer_ = BLINK_DUR;
        } else {
            blinkTimer_ -= dt;
        }
    } else {
        blinkIsVisible_ = true;
    }
    
    
    // set x & y velocities to trig components of the spaceship's acceleration
    setVx(getVx() + cosf(getAngle() * RAD_TO_DEG) * dt * getAccel());
    setVy(getVy() + sinf(getAngle() * RAD_TO_DEG) * dt * getAccel());
    
    // move bounding box to where the spaceship is onscreen
    
    getAbsoluteBox()->setDimensions(getX() + absoluteBoxMinX_, getX() + absoluteBoxMax_, getY() + absoluteBoxMinY_, getY() + absoluteBoxMaxY_);
    getRelativeBox()->setDimensions(getX() - 0.5, getX() + 0.5, getY() - 0.5, getY() + 0.5, getAngle());
    
    // set player acceleration based on remaining lives
    // >2 lives -> normal acceleration
    // 2 lives -> half acceleration
    // 1 lives -> no acceleration
    // 0 lives -> ship destroyed (game over)
    switch (lives_) {
        case 2:
            accelRate_ = startingAccelRate_ / 2;
            break;
        case 1:
            accelRate_ = 0;
            break;
        default:
            break;
    }
    
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


bool Spaceship::collidesWith(std::shared_ptr<GraphicObject> other) {
    return getRelativeBox()->overlaps((*other->getRelativeBox())); //TODO add hierarchical bounding box checking
}
