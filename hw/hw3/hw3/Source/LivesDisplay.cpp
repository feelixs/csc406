//
//  LivesDisplay.cpp
//  hw3
//
//  Displays the Player's remaining Lives as a Graphic object
//
//  Created by Michael Felix on 11/5/23.
//

#include "LivesDisplay.hpp"

float LivesDisplay::totalLives_ = 0;
float LivesDisplay::remainingLives_ = 0;

LivesDisplay::LivesDisplay(const WorldPoint &pt, std::shared_ptr<Spaceship> obj, float posOffset, float scale):
    Object(pt.x, pt.y, 0.f),
    GraphicObject(pt.x, pt.y, 0.f),
    AnimatedObject(pt.x, pt.y, 0.f, 0.f, 0.f, 0.f),
    obj_(obj),
    spacing_(posOffset),
    scale_(scale)
{
    totalLives_ = remainingLives_ = obj_->getLives();    
}


bool LivesDisplay::isInside(const WorldPoint& pt) {
    return false;
}

void LivesDisplay::draw() const {
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
    
    // apply rotation
    glRotatef(getAngle(), 0.f, 0.f, 1.f); // the spaceship model is drawn wrong by 90 degrees
    
    //    apply the radius as a scale
    glScalef(scale_, scale_, 1.f);
    
    
    // spaceship model
    glColor3f(0.f, 1.f, 1.f);
    for (int i = 0; i < remainingLives_; i++) {
        glBegin(GL_LINE_LOOP);
        glVertex2f(i * spacing_, 0.5f);
        glVertex2f(i * spacing_ + 0.5f, -0.5f);
        glVertex2f(i * spacing_ + 0.2f, -0.3f);
        glVertex2f(i * spacing_ - 0.2f, -0.3f);
        glVertex2f(i * spacing_ - 0.5f, -0.5f);
        glEnd();
    }
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

void LivesDisplay::update(float dt) {
    remainingLives_ = obj_->getLives();
}
