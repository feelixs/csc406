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
#include "glPlatform.h"


static int totalLoadedPts = 0;
const int numShapePoints = 25;
float* shapePntBuff[numShapePoints];


void loadShape(const char* filename) {
    // returns the amount of vertices in the loaded file
    
    float** shapePoints = shapePntBuff;
    
    FILE *file_data;
    long sizeb;
    char * buff;
    size_t size;
    
    file_data = fopen(filename, "rb");
    
    if (file_data == nullptr) {
        std::cout << "Error: Unable to open file " << filename << std::endl;
     //   return 0;
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
            if ((curX == "") | (tempVal == "")) {
                // if there's an incorrectly parsed line in the text file
                curX = "";
                tempVal =  "";
                continue;
            } else if ((curX == "-") & (tempVal == "-")) {
                // -,- in text file will exit early
                break;
            }
            std::cout << totalShapes << std::endl;
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
    
    
    totalLoadedPts = totalShapes;
    //return totalShapes;
}


Dolphin::Dolphin(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue)
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

Dolphin::~Dolphin()
{
    std::cout << "Dolphin at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
}



void Dolphin::draw() const
{
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(centerX_, centerY_, 0.f);
        
    // apply rotation
    glRotatef(angle_, 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(scaleX_, scaleY_, 1.f);
    
    glColor3f(red_, green_, blue_);
    
    glBegin(GL_POLYGON);
    for (int k=0; k<numShapePoints; k++) {
        if (k >= totalLoadedPts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        //cout << k << "; " << shapePntBuff[k][0] << ", " << shapePntBuff[k][1]<< endl;
        
        glVertex2f(shapePntBuff[k][0], shapePntBuff[k][1]);
        //std::cout << shapePntBuff[k][0] << ", " << shapePntBuff[k][1] << std::endl;
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}
