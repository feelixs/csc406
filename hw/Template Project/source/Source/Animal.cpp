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
    Point thisShapeCenter = Point{getX(), getY()}; // stores the animal's absolute center
    Point translation = Point{0.f, 0.f}; // this stores the translation away from the shape's centerpoint, and will be rotated by this->angle
    
    // right wing
    translation = Point{getX() + (scaleX_/10.f), getY() + (scaleY_/1.6f)};
    translation.rotateAround(&thisShapeCenter, angle_);
    _myShapes.push_back(std::make_shared<PolyWingRight>(translation, angle_ - 10.f, scaleX_, scaleY_, red_, green_, blue_));
    // left wing
    translation = Point{getX() - (scaleX_/10.f), getY() + (scaleY_/1.6f)};
    translation.rotateAround(&thisShapeCenter, angle_);
    _myShapes.push_back(std::make_shared<PolyWingLeft>(translation.x, translation.y, angle_ + 10.f, scaleX_, scaleY_, red_, green_, blue_));
    
    // two half-circles at different angles (face/body)
    translation = Point{getX(), getY()};
    translation.rotateAround(&thisShapeCenter, angle_);
    _myShapes.push_back(std::make_shared<PolyHalfCircle>(translation.x, translation.y, angle_+4.f, scaleX_, scaleY_, red_, green_, blue_));
    translation = Point{getX(), getY()};
    translation.rotateAround(&thisShapeCenter, angle_);
    _myShapes.push_back(std::make_shared<PolyHalfCircle>(translation.x, translation.y, angle_+14.f, scaleX_, scaleY_, red_, green_, blue_));
    
    // left eye
    translation = Point{getX() + (-scaleX_/2.4f), getY() + (scaleY_/1.9f)};
    translation.rotateAround(&thisShapeCenter, angle_);
    _myShapes.push_back(std::make_shared<PolyCircle>(translation.x, translation.y, angle_, scaleX_/8.f, scaleY_/8.f, 0.f, 0.f, 0.f));
    translation = Point{getX() + (-scaleX_/2.5f), getY() + (scaleY_/1.8f)};
    translation.rotateAround(&thisShapeCenter, angle_);
    _myShapes.push_back(std::make_shared<PolyCircle>(translation.x, translation.y, angle_, scaleX_/28.f, scaleY_/28.f, 1.f, 1.f, 1.f));
    
    // right eye
    translation = Point{getX() + (scaleX_/2.4f), getY() + (scaleY_/1.9f)};
    translation.rotateAround(&thisShapeCenter, angle_);
    _myShapes.push_back(std::make_shared<PolyCircle>(translation.x, translation.y, angle_, scaleX_/8.f, scaleY_/8.f, 0.f, 0.f, 0.f));

    translation = Point{getX() + (scaleX_/2.3f), getY() + (scaleY_/1.8f)};
    translation.rotateAround(&thisShapeCenter, angle_);
    _myShapes.push_back(std::make_shared<PolyCircle>(translation.x, translation.y, angle_, scaleX_/28.f, scaleY_/28.f, 1.f, 1.f, 1.f));
    
    // nose
    translation = Point{getX(), getY() + (scaleY_/4.f)};
    translation.rotateAround(&thisShapeCenter, angle_);
    _myShapes.push_back(std::make_shared<PolyTriangle>(translation.x, translation.y, angle_+180.f, scaleX_/40.f, scaleY_/20.f, 1.f, 1.f, 1.f));
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
