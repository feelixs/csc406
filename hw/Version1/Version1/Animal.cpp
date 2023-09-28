//
//  Animal.cpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#include "Animal.hpp"
#include "PolyShape.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "glPlatform.h"


std::vector<std::shared_ptr<PolyShape>> Animal::_myShapes;
float** Animal::_loadedShapePnts;
float** Animal::_circlePoints;


static bool mainShapeInitted = false;

const char* animalShapeFilePath = "/Users/michaelfelix/Documents/GitHub/csc406/hw/Version1/Version1/shapeCoords.txt";


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
    if (!mainShapeInitted) {
        mainShapeInitted = initPolyShape(animalShapeFilePath);
    }
    
    // this is where we will programatically draw the animal
    Animal::_myShapes.push_back(std::make_shared<PolyShape>(this->centerX_, this->centerY_, this->angle_, this->scaleX_, this->scaleY_, this->red_, this->green_, this->blue_));
    Animal::_myShapes.push_back(std::make_shared<PolyShape>(this->centerX_, this->centerY_, this->angle_,  this->scaleX_, this->scaleY_, this->red_, this->green_, this->blue_));
    
    std::cout << "Animal was created at " << centerX_ << ", " << centerY_ << std::endl;
}

Animal::~Animal() {
    std::cout << "Animal at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
}

void Animal::draw() const {
    for (auto obj : _myShapes)
    {
        if (obj != nullptr)
            obj->draw();
    }
}
