//
//  dolphin.hpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#ifndef dolphin_hpp
#define dolphin_hpp

#include <stdio.h>

int loadShape(float** shapePoints, const char* filename); // returns the amount of vertices in the loaded file
void initShape(float** shapePoints);

#endif /* dolphin_hpp */
