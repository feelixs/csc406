//
//  dolphin.cpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#include "dolphin.hpp"

void initShape(float** shapePoints) {
    shapePoints[0] = new float[2];
    shapePoints[0][0] = 10;
    shapePoints[0][1] = 10;
    
    shapePoints[1] = new float[2];
    shapePoints[1][0] = 100;
    shapePoints[1][1] = 100;
    
    shapePoints[2] = new float[2];
    shapePoints[2][0] = 0;
    shapePoints[2][1] = 0;
}
