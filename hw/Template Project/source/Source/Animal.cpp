//
//  Animal.cpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#include "Animal.hpp"
#include "World.h"
#include "GraphicObject.h"
#include "PolyRect.hpp"
#include "PolyHalfCircle.hpp"
#include "PolyTriangle.hpp"
#include "PolyCircle.hpp"
#include "PolyWingRight.hpp"
#include "PolyWingLeft.hpp"
#include <iostream>
#include <string>
#include "glPlatform.h"


std::vector<std::shared_ptr<GraphicObject>> Animal::_myShapes;
float** Animal::_loadedShapePnts;
float** Animal::_circlePoints;


Animal::Animal(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue)
    :   GraphicObject(centerX, centerY, angle),
        angle_(angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue)
{
    // this is where we programatically draw the animal
    
    Point tempPoint = Point{0.f, 0.f}; // we will use this point to apply trig functions for angle rotations
    
    // wings
    tempPoint.x = getX()+(scaleX_/10.f);
    tempPoint.y = getY()+(scaleY_/1.6);
    tempPoint.rotateBy(angle_);
    _myShapes.push_back(std::make_shared<PolyWingRight>(tempPoint.x, tempPoint.y, angle_-10, scaleX_, scaleY_, red_, green_, blue_));
    
    tempPoint.x = getX()-(scaleX_/10.f);
    tempPoint.y = getY()+(scaleY_/1.6);
    tempPoint.rotateBy(angle_);
    _myShapes.push_back(std::make_shared<PolyWingLeft>(tempPoint.x, tempPoint.y, angle_+10, scaleX_, scaleY_, red_, green_, blue_));
    
    // two half-circles at different angles (face/body)
    tempPoint.x = getX();
    tempPoint.y = getY();
    tempPoint.rotateBy(angle_);
    _myShapes.push_back(std::make_shared<PolyHalfCircle>(tempPoint.x, tempPoint.y, angle_+4.f, scaleX_, scaleY_, red_, green_, blue_));
    
    tempPoint.x = getX();
    tempPoint.y = getY();
    tempPoint.rotateBy(angle_);
    _myShapes.push_back(std::make_shared<PolyHalfCircle>(tempPoint.x, tempPoint.y, angle_+14.f, scaleX_, scaleY_, red_, green_, blue_));
    // left eye
    
    tempPoint.x = getX()-(scaleX_/2.4);
    tempPoint.y = getY()+(scaleY_/1.9);
    tempPoint.rotateBy(angle_);
    _myShapes.push_back(std::make_shared<PolyCircle>(tempPoint.x, tempPoint.y, angle_, scaleX_/8.f, scaleY_/8.f, 0.f, 0.f, 0.f));
    
    tempPoint.x = getX()-(scaleX_/2.5);
    tempPoint.y = getY()+(scaleY_/1.8);
    tempPoint.rotateBy(angle_);
    _myShapes.push_back(std::make_shared<PolyCircle>(tempPoint.x, tempPoint.y, angle_, scaleX_/28.f, scaleY_/28.f, 1.f, 1.f, 1.f));
    // right eye
    
    tempPoint.x = getX()+(scaleX_/2.4);
    tempPoint.y = getY()+(scaleY_/1.9);
    tempPoint.rotateBy(angle_);
    _myShapes.push_back(std::make_shared<PolyCircle>(tempPoint.x, tempPoint.y, angle_, scaleX_/8.f, scaleY_/8.f, 0.f, 0.f, 0.f));
    
    tempPoint.x = getX()+(scaleX_/2.3);
    tempPoint.y = getY()+(scaleY_/1.8);
    tempPoint.rotateBy(angle_);
    _myShapes.push_back(std::make_shared<PolyCircle>(tempPoint.x, tempPoint.y, angle_, scaleX_/28.f, scaleY_/28.f, 1.f, 1.f, 1.f));
    // nose
    
    tempPoint.x = getX();
    tempPoint.y = getY()+(scaleY_/4.f);
    tempPoint.rotateBy(angle_);
    _myShapes.push_back(std::make_shared<PolyTriangle>(tempPoint.x, tempPoint.y, angle_+180.f, scaleX_/40.f, scaleY_/20.f, 1.f, 1.f, 1.f));
    std::cout << "Animal was created at " << getX() << ", " << getY() << std::endl;
}

Animal::~Animal() {
    std::cout << "Animal at " << getX() << ", " << getY() << " was deleted" << std::endl;
}

void Animal::draw() const {
    for (int i=0; i<_myShapes.size(); i++) {
        _myShapes.at(i)->draw();
    }
}
