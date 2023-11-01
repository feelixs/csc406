//
//  LifeCounter.cpp
//  hw3
//
//  Created by Michael Felix on 10/31/23.
//

#include "LifeCounter.hpp"

int LifeCounter::totalLife_ = 0;
int LifeCounter::curLife_ = 0;
float** LifeCounter::displayVertices_;

LifeCounter::LifeCounter(WorldPoint &pt, std::shared_ptr<Spaceship> obj, float len, float width):
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
    totalLife_ = obj_->getLife();
    curLife_ = totalLife_;
    displayVertices_ = new float*[totalLife_];
    for (int i = 0; i < totalLife_; i++) {
        displayVertices_[i] = new float[2];
        displayVertices_[i][0] = getX() + (i * len_);
        displayVertices_[i][1] = getY();
    }
    for (int i = totalLife_; i > 0; --i) {
        displayVertices_[i] = new float[2];
        displayVertices_[i][0] = getX() + (i * len_);
        displayVertices_[i][1] = getY()-width_;
    }
}

bool LifeCounter::isInside(const WorldPoint& pt) {
    return false;
}

void LifeCounter::draw() const {
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
    
    // apply rotation
    glRotatef(getAngle() - 90, 0.f, 0.f, 1.f); // the spaceship model is drawn wrong by 90 degrees
    
    //    apply the radius as a scale
    glScalef(1.f, 1.f, 1.f);
    
    glColor3f(red_, green_, blue_);

    glBegin(GL_LINE_LOOP);
    for (int k=0; k<curLife_; k++) {
        glVertex2f(displayVertices_[k][0], displayVertices_[k][1]);
    }
    glEnd();
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}


void LifeCounter::update(float dt) {
    
}
