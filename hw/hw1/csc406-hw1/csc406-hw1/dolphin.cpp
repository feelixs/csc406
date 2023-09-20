//
//  dolphin.cpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#include "dolphin.hpp"

void initShape(float** shapePoints) {
    shapePoints[0] = new float[2];
    shapePoints[0][0] = 1;
    shapePoints[0][1] = 0;
    
    shapePoints[1] = new float[2];
    shapePoints[1][0] = 0.965926;
    shapePoints[1][1] = 0.258819;
    
    shapePoints[2] = new float[2];
    shapePoints[2][0] = 0.866025;
    shapePoints[2][1] = 0.5;
    
    shapePoints[2] = new float[2];
    shapePoints[2][0] = 0.707107;
    shapePoints[2][1] = 0.707107;
    
    shapePoints[2] = new float[2];
    shapePoints[2][0] = 0.5;
    shapePoints[2][1] = 0.866025;
    
    shapePoints[2] = new float[2];
    shapePoints[2][0] = 0.258819;
    shapePoints[2][1] = 0.965926;
    
    /*
     circle pts
     
     1, 0
     0.965926, 0.258819
     0.866025, 0.5
     0.707107, 0.707107
     0.5, 0.866025
     0.258819, 0.965926
     -4.37114e-08, 1
     -0.258819, 0.965926
     
     -0.5, 0.866025
     -0.707107, 0.707107
     -0.866025, 0.5
     -0.965926, 0.258819
     -1, -8.74228e-08
     -0.965926, -0.258819
     -0.866025, -0.5
     -0.707107, -0.707107
     -0.5, -0.866025
     -0.258819, -0.965926
     1.19249e-08, -1
     0.258819, -0.965926
     0.5, -0.866025
     0.707107, -0.707107
     0.866026, -0.5
     0.965926, -0.258819
     */
}
