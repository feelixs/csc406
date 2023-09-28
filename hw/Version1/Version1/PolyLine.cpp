//
//  PolyLine.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyLine.hpp"
#include "PolyShape.hpp"
#include "glPlatform.h"
#include <iostream>


float** PolyLine::_straightLinePoints;


PolyLine::PolyLine(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue): PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue) {
    
}


PolyLine::~PolyLine() {
    for (int i = 0; i < 2; i++) {
        delete[] _straightLinePoints[i];
    }
    delete[] _straightLinePoints;
    std::cout << "Line at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
    //PolyShape::~PolyShape();
}


void PolyLine::draw() const {
    std::cout << "line draw" << std::endl;
}
