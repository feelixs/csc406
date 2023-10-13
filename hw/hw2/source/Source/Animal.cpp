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


std::vector<std::shared_ptr<PolyShape>> Animal::_myShapes;
float** Animal::_loadedShapePnts;
float** Animal::_circlePoints;


Animal::Animal(Point centerPoint, float angle, float scale, float red, float green, float blue)
:   GraphicObject(centerPoint.x, centerPoint.y, angle),
    scaleX_(scale),
    scaleY_(scale),
    red_(red),
    green_(green),
    blue_(blue)
{
    _init_();
}


Animal::Animal(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue)
// Animal _init_() will use World::Point to initialize its shapes, regardless of which constructor is used
    :   GraphicObject(centerX, centerY, angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue)
{
    _init_();
}

void Animal::draw() const {
    for (int i=0; i<_myShapes.size(); i++) {
        _myShapes.at(i)->draw();
    }
}


void Animal::_init_() {
    // this is where we programatically draw the animal
    Point thisShapeCenter = Point{getX(), getY()}; // stores the animal's absolute center
    Point translationPoint = Point{0.f, 0.f}; // this stores the translation away from the shape's centerpoint, and will be rotated by this->angle
    
    // right wing
    translationPoint = Point{getX() + (scaleX_/10.f), getY() + (scaleY_/1.6f)};
    translationPoint.rotateAround(&thisShapeCenter, getAngle());
    _myShapes.push_back(std::make_shared<PolyWingRight>(translationPoint, getAngle() - 10.f, scaleX_, scaleY_, red_, green_, blue_, Point{getX()+(scaleX_/10.f), getY()+(scaleY_/1.6f)}));
    // left wing
    translationPoint = Point{getX() - (scaleX_/10.f), getY() + (scaleY_/1.6f)};
    translationPoint.rotateAround(&thisShapeCenter, getAngle());
    _myShapes.push_back(std::make_shared<PolyWingLeft>(translationPoint, getAngle() + 10.f, scaleX_, scaleY_, red_, green_, blue_, Point{getX()-(scaleX_/10.f), getY()+(scaleY_/1.6f)}));
    
    // two half-circles at different angles (face/body)
    translationPoint = Point{getX(), getY()};
    translationPoint.rotateAround(&thisShapeCenter, getAngle());
    _myShapes.push_back(std::make_shared<PolyHalfCircle>(translationPoint, getAngle()+4.f, scaleX_, scaleY_, red_, green_, blue_, Point{getX(), getY()}));
    translationPoint = Point{getX(), getY()};
    translationPoint.rotateAround(&thisShapeCenter, getAngle());
    _myShapes.push_back(std::make_shared<PolyHalfCircle>(translationPoint, getAngle()+14.f, scaleX_, scaleY_, red_, green_, blue_, Point{getX(), getY()}));
    
    // left eye
    translationPoint = Point{getX() + (-scaleX_/2.4f), getY() + (scaleY_/1.9f)};
    translationPoint.rotateAround(&thisShapeCenter, getAngle());
    _myShapes.push_back(std::make_shared<PolyCircle>(translationPoint, getAngle(), scaleX_/8.f, scaleY_/8.f, 0.f, 0.f, 0.f, Point{getX() + (-scaleX_/2.4f), getY() + (scaleY_/1.9f)}));
    translationPoint = Point{getX() + (-scaleX_/2.5f), getY() + (scaleY_/1.8f)};
    translationPoint.rotateAround(&thisShapeCenter, getAngle());
    _myShapes.push_back(std::make_shared<PolyCircle>(translationPoint, getAngle(), scaleX_/28.f, scaleY_/28.f, 1.f, 1.f, 1.f, Point{getX() + (-scaleX_/2.5f), getY() + (scaleY_/1.8f)}));
    
    // right eye
    translationPoint = Point{getX() + (scaleX_/2.4f), getY() + (scaleY_/1.9f)};
    translationPoint.rotateAround(&thisShapeCenter, getAngle());
    _myShapes.push_back(std::make_shared<PolyCircle>(translationPoint, getAngle(), scaleX_/8.f, scaleY_/8.f, 0.f, 0.f, 0.f, Point{getX() + (scaleX_/2.4f), getY() + (scaleY_/1.9f)}));

    translationPoint = Point{getX() + (scaleX_/2.3f), getY() + (scaleY_/1.8f)};
    translationPoint.rotateAround(&thisShapeCenter, getAngle());
    _myShapes.push_back(std::make_shared<PolyCircle>(translationPoint, getAngle(), scaleX_/28.f, scaleY_/28.f, 1.f, 1.f, 1.f, Point{getX() + (scaleX_/2.3f), getY() + (scaleY_/1.8f)}));
    
    // nose
    translationPoint = Point{getX(), getY() + (scaleY_/4.f)};
    translationPoint.rotateAround(&thisShapeCenter, getAngle());
    _myShapes.push_back(std::make_shared<PolyTriangle>(translationPoint, getAngle()+180.f, scaleX_/40.f, scaleY_/20.f, 1.f, 1.f, 1.f, Point{getX(), getY() + (scaleY_/4.f)}));
}


void Animal::setColor(float r, float g, float b) {
    for (int i = 0; i < _myShapes.size(); i++) {
        switch(i) {
            // we will manually set the color of all my shapes
            // we know which ones to set the colors of based on their order of creation in _init_()
            case 0:
            case 1:
            case 2:
            case 3:
                _myShapes.at(i)->setColor(r, g, b);
        }
    }
}


void Animal::update(float dt) {
    
    for (int i = 0; i < _myShapes.size(); i++) {
        //_myShapes.at(i)->setX(_myShapes.at(i)->getX()+0.01);
        _myShapes.at(i)->rotateWithOffset(_myShapes.at(i)->getAngle()+0.5);
    }
    
}
