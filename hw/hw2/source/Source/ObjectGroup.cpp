//
//  ObjectGroup.cpp
//  hw2
//
//  Created by Michael Felix on 10/10/23.
//

#include "ObjectGroup.hpp"


float** ObjectGroup::headPoints_;


ObjectGroup::ObjectGroup(GroupType type, GroupSize size, int num, float x, float y):
    GraphicObject(x, y, 0),
    type_(type),
    size_(size),
    num_(num)
{
    headPoints_ = new float*[num_];
    for (int k=0; k<num_; k++)
        headPoints_[k] = new float[2];
        
    float angleStep = 2.f*M_PI/num_;
    for (int k=0; k<num_; k++)
    {
        float theta = k*angleStep;
        headPoints_[k][0] = cosf(theta);
        headPoints_[k][1] = sinf(theta);
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
    switch (type_) {
        case HEADS_ON_STICK:
            rotateBy = 0;
        case HEADS_ON_WHEELS:
            rotateBy = 360/num_; // for example: six heads would be 360d/6 = 60d
        default:
            // this should never be the case
            rotateBy = 0;
    }
    Point createAt;
    for (int i = 0; i < num_; i++) {
        createAt = Point{headPoints_[i][0], headPoints_[i][1]};
        groupHeads_.push_back(std::make_shared<Animal>(createAt, rotateBy * i, pixelSize_, 0.f, 1.f, 1.f));
    }
}


void ObjectGroup::draw() const {
    for (int i = 0; i < num_; i++) {
        groupHeads_.at(i)->draw();
    }
}


void ObjectGroup::update(float dt) {
    
}
