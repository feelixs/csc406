//
//  PolyEarRight.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyEarRight.hpp"
#include "glPlatform.h"
#include <fstream>
#include <iostream>
#include <string>

int PolyEarRight::_numLoadedPnts = 0;
const int PolyEarRight::_maxLoadedPnts = 25;
float** PolyEarRight::_loadedShapePnts;


PolyEarRight::PolyEarRight(std::string filepath, float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue):
    PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue),
    _myLoadedFilepath(filepath.c_str())
{
    // loads a shape from a file in format:
    //   x1, y1
    //   x2, y2
    //   ...
    
    PolyEarRight::_loadedShapePnts = new float*[PolyEarRight::_maxLoadedPnts];
    
    std::ifstream file_data(filepath);

    if (!file_data.is_open()) {
        std::cout << "Error: Unable to open file " << _myLoadedFilepath << std::endl;
        exit(1);
    }
    
    std::string tempVal = "";
    std::string curX = "";
    std::string line;
    char letter;
    int totalShapes = 0;
    while (std::getline(file_data, line)) {
        for (int i = 0; i < line.size(); i++) {
            letter = line.at(i);
            if (letter == *" ") {
                // ignore spaces
                continue;
            } else if (letter == *",") {
              // commas mean that we just read an X, and the next value will be a Y
              curX = tempVal;
              tempVal = "";
          } else {
              tempVal += letter;
          }
        }
        // end of the line
        if ((curX == "") | (tempVal == "")) {
            // if there's an incorrectly parsed line in the text file
            curX = "";
            tempVal =  "";
            continue;
        } else if ((curX == "-") & (tempVal == "-")) {
            // -,- in text file will exit early
            break;
        } else {
            PolyEarRight::_loadedShapePnts[totalShapes] = new float[2];
            PolyEarRight::_loadedShapePnts[totalShapes][0] = std::stof(curX); // stof --> string to float
            PolyEarRight::_loadedShapePnts[totalShapes][1] = std::stof(tempVal);
            totalShapes++;
            tempVal = "";
        }
    }

    PolyEarRight::_numLoadedPnts = totalShapes;
}


PolyEarRight::~PolyEarRight() {
   // std::cout << "Custom polygon at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
    //PolyShape::~PolyShape();
}


void PolyEarRight::draw() const {
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
    for (int k=0; k<PolyEarRight::_maxLoadedPnts; k++) {
        if (k >= PolyEarRight::_numLoadedPnts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        glVertex2f(PolyEarRight::_loadedShapePnts[k][0], PolyEarRight::_loadedShapePnts[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}
