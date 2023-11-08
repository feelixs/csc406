//
//  Healthbar.cpp
//  hw3
//
//
//  Displays a healthbar of the Player's remaining hull integrity as a Graphic object
//
//  Created by Michael Felix on 10/31/23.
//

#include "Healthbar.hpp"

float Healthbar::totalHealth_ = 0;
float Healthbar::curHealth_ = 0;
float** Healthbar::displayLinePts_;

Healthbar::Healthbar(const WorldPoint &pt, std::shared_ptr<Spaceship> obj, float len, float width):
    Object(pt.x, pt.y, 0.f),
    GraphicObject(pt.x, pt.y, 0.f),
    AnimatedObject(pt.x, pt.y, 0.f, 0.f, 0.f, 0.f),
    len_(len),
    width_(width),
    red_(0.f),
    blue_(0.f),
    green_(1.f),
    obj_(obj)
{
    totalHealth_ = obj_->getIntegrity();
    curHealth_ = totalHealth_;
    displayLinePts_ = new float*[totalHealth_];
    for (int i = 0; i < totalHealth_; i++) {
        displayLinePts_[i] = new float[2];
        displayLinePts_[i][0] = getX() + (i * len_);
        displayLinePts_[i][1] = getY();
    }
}

bool Healthbar::isInside(const WorldPoint& pt) {
    return false;
}

void Healthbar::draw() const {
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
    
    // apply rotation
    glRotatef(getAngle(), 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(1.f, 1.f, 1.f);
    
    glColor3f(red_, green_, blue_);
    
    // make a rectangle using two for loops based on one line (displayLinePts_)
    glBegin(GL_POLYGON);
    for (int k=0; k<curHealth_; k++) {
        glVertex2f(displayLinePts_[k][0], displayLinePts_[k][1]);
    }
    for (int k=curHealth_-1; k>=0; k--) {
        glVertex2f(displayLinePts_[k][0], displayLinePts_[k][1]+width_);
    }
    glEnd();
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

void Healthbar::update(float dt) {
    curHealth_ = obj_->getIntegrity();
    float lifeRatio = curHealth_ / totalHealth_;
    // slowly interpolate from green to red based on current health (spaceship integtrity)
    red_ = 1.0f - lifeRatio;
    green_ = lifeRatio;
    blue_ = 0.0f;
}
