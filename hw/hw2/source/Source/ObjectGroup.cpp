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
    num_(num)
{
    _init_();
}

ObjectGroup::ObjectGroup(GroupType type, GroupSize size, int num, Point at):
    GraphicObject(at.x, at.y, 0),
    type_(type),
    size_(size),
    num_(num)
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
    
    switch (size_) {
        case LARGE:
            pixelSize_ = 1.f;
        case MEDIUM:
            pixelSize_ = 0.75f;
        case SMALL:
            pixelSize_ = 0.5f;
        default:
            pixelSize_ = 0.75f;
    }
    
    float rotateBy;
    
    
    if (type_ == HEADS_ON_STICK) {
        rotateBy = 0;
    }
    else if (type_ == HEADS_ON_WHEELS) {
        rotateBy = 360/num_; // for example: six heads would be 360d/6 = 60d
    } else {
        rotateBy = 0;
        std::cout << "An invalid GroupType was used when creating an ObjectGroup!" << std::endl;
    }
    
    Point createAt;
    for (int i = 0; i < num_; i++) {
        groupHeads_.push_back(std::make_shared<Animal>(Point{headPoints_[i][0], headPoints_[i][1]}, rotateBy * i, pixelSize_, 0.f, 1.f, 1.f));
    }
}


void ObjectGroup::draw() const {
    for (int i = 0; i < num_; i++) {
        groupHeads_.at(i)->draw();
    }
}


void ObjectGroup::update(float dt) {
    
}
