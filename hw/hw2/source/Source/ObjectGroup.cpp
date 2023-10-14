//
//  ObjectGroup.cpp
//  hw2
//
//  Created by Michael Felix on 10/10/23.
//

#include "ObjectGroup.hpp"
#include <iostream>

float** ObjectGroup::headPoints_;


ObjectGroup::ObjectGroup(GroupType type, GroupSize size, int num, float x, float y):
    GraphicObject(x, y, 0),
    type_(type),
    size_(size),
    num_(num),
    spin_(0),
    speedX_(0),
    speedY_(0)
{
    _init_();
}

ObjectGroup::ObjectGroup(GroupType type, GroupSize size, int num, Point at):
    GraphicObject(at.x, at.y, 0),
    type_(type),
    size_(size),
    num_(num),
    spin_(0),
    speedX_(0),
    speedY_(0)
{
    _init_();
}


void ObjectGroup::_init_() {
    headPoints_ = new float*[num_];
    for (int k=0; k<num_; k++)
        headPoints_[k] = new float[2];
        
    float angleStep = 2.f*M_PI/num_;
    for (int k=0; k<num_; k++)
    {
        float theta = k*angleStep;
        headPoints_[k][0] = cosf(theta) + getX();
        headPoints_[k][1] = sinf(theta) + getY();
    }
    
    if (size_ == LARGE) {
        pixelSize_ = 1.f;
    } else if (size_ == MEDIUM) {
        pixelSize_ = 0.75f;
    } else {
        pixelSize_ = 0.5f;
    }
    
    float rotateBy;
    
    
    if (type_ == HEADS_ON_WHEELS) {
        rotateBy = 360/num_; // for example: six heads would be 360d/6 = 60d
    } else {
        rotateBy = 0;
        std::cout << "An invalid GroupType was used when creating an ObjectGroup!" << std::endl;
    }
    
    for (int i = 0; i < num_; i++) {
        groupHeads_.push_back(std::make_shared<Animal>(Point{headPoints_[i][0], headPoints_[i][1]}, rotateBy * (i-1), pixelSize_, 0.f, 1.f, 1.f));
    }
}


void ObjectGroup::setColor(float r, float g, float b) {
    for (auto head : groupHeads_) {
        head -> setColor(r, g, b);
    }
}


void ObjectGroup::draw() const {
    for (int i = 0; i < num_; i++) {
        groupHeads_.at(i)->draw();
    }
}


void ObjectGroup::update(float dt) {
    if (animationEnabled_) {
        setX(getX() + speedX_ * dt);
        setY(getY() + speedY_ * dt);
        for (auto a : groupHeads_) {
            if (speedX_ != 0.f)
                a->setX(a->getX() + speedX_ * dt);
            if (speedY_ != 0.f)
                a->setY(a->getY() + speedY_ * dt);
            if (spin_ != 0.f)
                a->setAngle(a->getAngle() + spin_ * dt);
            a->update(dt);
        }
    }
}


void ObjectGroup::togglePlay() {
    if (animationEnabled_) {
        animationEnabled_ = false;
    } else {
        animationEnabled_ = true;
    }
}
