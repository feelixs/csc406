//
//  dolphin.cpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#include "dolphin.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>

int loadShape(float** shapePoints, const char* filename) {
    // returns the amount of vertices in the loaded file
    FILE *file_data;
    long sizeb;
    char * buff;
    size_t size;
    
    file_data = fopen(filename, "rb");
    
    if (file_data == nullptr) {
        std::cout << "Error: Unable to open file " << filename << std::endl;
        return 0;
    }
    
    fseek(file_data , 0 , SEEK_END);
    sizeb = ftell(file_data);
    rewind (file_data);
    buff = (char*) malloc (sizeof(char)*sizeb);
    size = fread (buff,1,sizeb,file_data);
    
    std::string tempVal = "";
    std::string curX = "";
    
    int totalShapes = 0;
    for (int i = 0; i < size; i++) {
        //std::cout << totalShapes << std::endl;
        const char letter = buff[i];
        if (letter == *" ")
            // ignore spaces
            continue;
        if (letter == *"\n") {
            // newlines mean that two new points have been read from the file
            shapePoints[totalShapes] = new float[2];
            shapePoints[totalShapes][0] = std::stof(curX); // stof --> string to float
            shapePoints[totalShapes][1] = std::stof(tempVal);
            totalShapes++;
            tempVal = "";
        } else if (letter == *",") {
            // commas mean that we just read an X, and the next value will be a Y
            curX = tempVal;
            tempVal = "";
        } else {
            tempVal += letter;
        }
        //std::cout << std::endl << curX << std::endl;
    }
    
    fclose(file_data);
    free(buff);
    
    return totalShapes;
}



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
