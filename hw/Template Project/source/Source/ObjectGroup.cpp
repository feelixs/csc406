//
//  ObjectGroup.cpp
//  hw2
//
//  Created by Michael Felix on 10/10/23.
//

#include "ObjectGroup.hpp"


ObjectGroup::ObjectGroup(GroupType type, GroupSize size, int num, float x, float y):
    GraphicObject(x, y, 0),
    type_(type),
    size_(size),
    num_(num)
{
    
}


void ObjectGroup::draw() const {
    
}


void ObjectGroup::update(float dt) {
    
}
