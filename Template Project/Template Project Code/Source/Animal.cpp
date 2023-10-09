//
//  Animal.cpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#include "Animal.hpp"
#include "World.h"
#include "PolyShape.hpp"
#include "PolyRect.hpp"
#include "PolyHalfCircle.hpp"
#include "PolyTriangle.hpp"
#include "PolyCircle.hpp"
#include "PolyWingRight.hpp"
#include "PolyWingLeft.hpp"
#include <iostream>
#include <string>
#include "glPlatform.h"


std::vector<std::shared_ptr<PolyShape>> Animal::_myShapes;
float** Animal::_loadedShapePnts;
float** Animal::_circlePoints;


Animal::Animal(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue)
    :    centerX_(centerX),
        centerY_(centerY),
        angle_(angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue)
{
    // this is where we programatically draw the animal
    
    
    // wings
    _myShapes.push_back(std::make_shared<PolyWingRight>(centerX_+(scaleX_/10.f), centerY_+(scaleY_/1.6), angle_-10, scaleX_, scaleY_, red_, green_, blue_));
    _myShapes.push_back(std::make_shared<PolyWingLeft>(centerX_-(scaleX_/10.f), centerY_+(scaleY_/1.6), angle_+10, scaleX_, scaleY_, red_, green_, blue_));
    // two half-circles at different angles (face/body)
    _myShapes.push_back(std::make_shared<PolyHalfCircle>(centerX_, centerY_, angle_+4.f, scaleX_, scaleY_, red_, green_, blue_));
    _myShapes.push_back(std::make_shared<PolyHalfCircle>(centerX_, centerY_, angle_+14.f, scaleX_, scaleY_, red_, green_, blue_));
    // left eye
    _myShapes.push_back(std::make_shared<PolyCircle>(centerX_-(scaleX_/2.4), centerY_+(scaleY_/1.9), angle_, scaleX_/8.f, scaleY_/8.f, 0.f, 0.f, 0.f));
    _myShapes.push_back(std::make_shared<PolyCircle>(centerX_-(scaleX_/2.5), centerY_+(scaleY_/1.8), angle_, scaleX_/28.f, scaleY_/28.f, 1.f, 1.f, 1.f));
    // right eye
    _myShapes.push_back(std::make_shared<PolyCircle>(centerX_+(scaleX_/2.4), centerY_+(scaleY_/1.9), angle_, scaleX_/8.f, scaleY_/8.f, 0.f, 0.f, 0.f));
    _myShapes.push_back(std::make_shared<PolyCircle>(centerX_+(scaleX_/2.3), centerY_+(scaleY_/1.8), angle_, scaleX_/28.f, scaleY_/28.f, 1.f, 1.f, 1.f));
    // nose
    _myShapes.push_back(std::make_shared<PolyTriangle>(centerX_, centerY_+(scaleY_/4.f), angle_+180.f, scaleX_/40.f, scaleY_/20.f, 1.f, 1.f, 1.f));
    std::cout << "Animal was created at " << centerX_ << ", " << centerY_ << std::endl;
}

Animal::~Animal() {
    std::cout << "Animal at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
}

void Animal::draw() const {
    for (int i=0; i<_myShapes.size(); i++) {
        _myShapes.at(i)->draw();
    }
}
