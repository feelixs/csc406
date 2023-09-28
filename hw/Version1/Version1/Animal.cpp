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



const char* animalShapeFilePath = "/Users/michaelfelix/Documents/GitHub/csc406/hw/Version1/Version1/shapeCoords.txt";

bool initAnimal() {
    bool mainShapeInitted = initPolyShape(animalShapeFilePath);
    Animal::_myShapes.push_back(std::make_shared<PolyShape>(420, 400, 12, 100, 100, 0.f, 1.f, 1.f));
    Animal::_myShapes.push_back(std::make_shared<PolyShape>(420, 400, 0, 100, 100, 0.f, 1.f, 1.f));
    return mainShapeInitted;
}


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
