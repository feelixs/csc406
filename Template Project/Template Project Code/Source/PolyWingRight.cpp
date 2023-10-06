//
//  PolyEarRight.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyWingRight.hpp"
#include "glPlatform.h"
#include <fstream>
#include <iostream>
#include <string>

int PolyWingRight::_numLoadedPnts = 0;
const int PolyWingRight::_maxLoadedPnts = 25;
float** PolyWingRight::_loadedShapePnts;


PolyWingRight::PolyWingRight(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue):
    PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue)
{
    initFromPolygon();
}


PolyWingRight::~PolyWingRight() {
   // std::cout << "Custom polygon at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
    //PolyShape::~PolyShape();
}


void PolyWingRight::draw() const {
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
    for (int k=0; k<PolyWingRight::_maxLoadedPnts; k++) {
        if (k >= PolyWingRight::_numLoadedPnts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        glVertex2f(PolyWingRight::_loadedShapePnts[k][0], PolyWingRight::_loadedShapePnts[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

void PolyWingRight::initFromPolygon() {
    /// hard coded values for the shape
    _numLoadedPnts = 5;
    
    _loadedShapePnts = new float*[_numLoadedPnts];
    for (int i = 0; i < _numLoadedPnts; i++) {
        _loadedShapePnts[i] = new float[2];
    }
    
    PolyWingRight::_loadedShapePnts[0][0] = 0.76;
    PolyWingRight::_loadedShapePnts[0][1] = 0.38;
    PolyWingRight::_loadedShapePnts[1][0] = 0.66;
    PolyWingRight::_loadedShapePnts[1][1] = 0.1;
    PolyWingRight::_loadedShapePnts[2][0] = 0.65;
    PolyWingRight::_loadedShapePnts[2][1] = 0;
    PolyWingRight::_loadedShapePnts[3][0] = 0.83;
    PolyWingRight::_loadedShapePnts[3][1] = 0;
    PolyWingRight::_loadedShapePnts[4][0] = 0.9;
    PolyWingRight::_loadedShapePnts[4][1] = -0.2;
}

void PolyWingRight::initFromFile(const char* filepath) {
    // loads a shape from a file in format:
    //   x1, y1
    //   x2, y2
    //   ...
    
    PolyWingRight::_loadedShapePnts = new float*[PolyWingRight::_maxLoadedPnts];
    
    std::ifstream file_data(filepath);

    if (!file_data.is_open()) {
        std::cout << "Error: Unable to open file " << filepath << std::endl;
        // if the file can't be opened, load the hard-coded values instead
        return initFromPolygon();
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
            PolyWingRight::_loadedShapePnts[totalShapes] = new float[2];
            PolyWingRight::_loadedShapePnts[totalShapes][0] = std::stof(curX); // stof --> string to float
            PolyWingRight::_loadedShapePnts[totalShapes][1] = std::stof(tempVal);
            totalShapes++;
            tempVal = "";
        }
    }

    PolyWingRight::_numLoadedPnts = totalShapes;
}
