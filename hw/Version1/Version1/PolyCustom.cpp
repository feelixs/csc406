//
//  PolyCustom.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyCustom.hpp"
#include "glPlatform.h"
#include <iostream>


int PolyCustom::_numLoadedPnts = 0;
const int PolyCustom::_maxLoadedPnts = 25;
float** PolyCustom::_loadedShapePnts;


PolyCustom::PolyCustom(const char* filepath, float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue):
    PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue),
    _myLoadedFilepath(filepath)
{
    // loads a shape from a file in format:
    //   x1, y1
    //   x2, y2
    //   ...
    
    PolyCustom::_loadedShapePnts = new float*[PolyCustom::_maxLoadedPnts];
    
    FILE *file_data;
    long sizeb;
    char * buff;
    size_t size;
    
    file_data = fopen(_myLoadedFilepath, "rb");
    if (file_data == nullptr) {
        std::cout << "Error: Unable to open file " << _myLoadedFilepath << std::endl;
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
            //std::cout << totalShapes << std::endl;
            PolyCustom::_loadedShapePnts[totalShapes] = new float[2];
            PolyCustom::_loadedShapePnts[totalShapes][0] = std::stof(curX); // stof --> string to float
            PolyCustom::_loadedShapePnts[totalShapes][1] = std::stof(tempVal);
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

    PolyCustom::_numLoadedPnts = totalShapes;
}


PolyCustom::~PolyCustom() {
    std::cout << "Custom polygon at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
    //PolyShape::~PolyShape();
}


void PolyCustom::draw() const {
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
    for (int k=0; k<PolyCustom::_maxLoadedPnts; k++) {
        if (k >= PolyCustom::_numLoadedPnts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        glVertex2f(PolyCustom::_loadedShapePnts[k][0], PolyCustom::_loadedShapePnts[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}
