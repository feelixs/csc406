//
//  PolyEarLeft.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyEarLeft.hpp"
#include "glPlatform.h"
#include <fstream>
#include <iostream>
#include <string>

int PolyEarLeft::_numLoadedPnts = 0;
const int PolyEarLeft::_maxLoadedPnts = 25;
float** PolyEarLeft::_loadedShapePnts;


PolyEarLeft::PolyEarLeft(std::string filepath, float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue):
    PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue),
    _myLoadedFilepath(filepath.c_str())
{
    initFromFile(_myLoadedFilepath);
}


PolyEarLeft::~PolyEarLeft() {
   // std::cout << "Custom polygon at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
    //PolyShape::~PolyShape();
}


void PolyEarLeft::draw() const {
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
    for (int k=0; k<PolyEarLeft::_maxLoadedPnts; k++) {
        if (k >= PolyEarLeft::_numLoadedPnts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        glVertex2f(PolyEarLeft::_loadedShapePnts[k][0], PolyEarLeft::_loadedShapePnts[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}


void PolyEarLeft::initFromPolygon() {
    /// hard coded values for the shape
    _numLoadedPnts = 5;
    
    _loadedShapePnts = new float*[_numLoadedPnts];
    for (int i = 0; i < _numLoadedPnts; i++) {
        _loadedShapePnts[i] = new float[2];
    }
    
    PolyEarLeft::_loadedShapePnts[0][0] = -0.76;
    PolyEarLeft::_loadedShapePnts[0][1] = 0.38;
    PolyEarLeft::_loadedShapePnts[1][0] = -0.66;
    PolyEarLeft::_loadedShapePnts[1][1] = 0.1;
    PolyEarLeft::_loadedShapePnts[2][0] = -0.65;
    PolyEarLeft::_loadedShapePnts[2][1] = 0;
    PolyEarLeft::_loadedShapePnts[3][0] = -0.83;
    PolyEarLeft::_loadedShapePnts[3][1] = 0;
    PolyEarLeft::_loadedShapePnts[4][0] = -0.9;
    PolyEarLeft::_loadedShapePnts[4][1] = -0.2;
}


void PolyEarLeft::initFromFile(const char* filepath) {
    // loads a shape from a file in format:
    //   x1, y1
    //   x2, y2
    //   ...
    
    PolyEarLeft::_loadedShapePnts = new float*[PolyEarLeft::_maxLoadedPnts];
    
    std::ifstream file_data(filepath);

    if (!file_data.is_open()) {
        std::cout << "Error: Unable to open file " << _myLoadedFilepath << std::endl;
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
            PolyEarLeft::_loadedShapePnts[totalShapes] = new float[2];
            PolyEarLeft::_loadedShapePnts[totalShapes][0] = std::stof(curX); // stof --> string to float
            PolyEarLeft::_loadedShapePnts[totalShapes][1] = std::stof(tempVal);
            totalShapes++;
            tempVal = "";
        }
    }

    PolyEarLeft::_numLoadedPnts = totalShapes;
}
