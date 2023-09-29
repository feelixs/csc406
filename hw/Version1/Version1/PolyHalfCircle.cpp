//
//  PolyCustom.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyHalfCircle.hpp"
#include "glPlatform.h"
#include <fstream>
#include <iostream>
#include <string>

int PolyHalfCircle::_numLoadedPnts = 0;
const int PolyHalfCircle::_maxLoadedPnts = 25;
float** PolyHalfCircle::_loadedShapePnts;


PolyHalfCircle::PolyHalfCircle(std::string filepath, float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue):
    PolyShape(centerX, centerY, angle, scaleX, scaleY, red, green, blue),
    _myLoadedFilepath(filepath.c_str())
{
    initFromFile(_myLoadedFilepath);
}


PolyHalfCircle::~PolyHalfCircle() {
   // std::cout << "Custom polygon at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
    //PolyShape::~PolyShape();
}


void PolyHalfCircle::draw() const {
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
    for (int k=0; k<PolyHalfCircle::_maxLoadedPnts; k++) {
        if (k >= PolyHalfCircle::_numLoadedPnts)
            // prevent EXC_BAD_ACCESS when trying to access unexisting/noninitialized indices of shapePntBuff in loadShape()
            break;
        glVertex2f(PolyHalfCircle::_loadedShapePnts[k][0], PolyHalfCircle::_loadedShapePnts[k][1]);
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}


void PolyHalfCircle::initFromPolygon() {
    /// hard coded values for the shape
    _numLoadedPnts = 10;
    
    _loadedShapePnts = new float*[_numLoadedPnts];
    for (int i = 0; i < _numLoadedPnts; i++) {
        _loadedShapePnts[i] = new float[2];
    }
    
    _loadedShapePnts[0][0] = 1.0;
    _loadedShapePnts[0][1] = 0.0;
    _loadedShapePnts[1][0] = 0.9510565162951535;
    _loadedShapePnts[1][1] = 0.3090169943749474;
    _loadedShapePnts[2][0] = 0.8090169943749475;
    _loadedShapePnts[2][1] = 0.5877852522924731;
    _loadedShapePnts[3][0] = 0.5877852522924731;
    _loadedShapePnts[3][1] = 0.8090169943749475;
    _loadedShapePnts[4][0] = 0.30901699437494745;
    _loadedShapePnts[4][1] = 0.9510565162951535;
    _loadedShapePnts[5][0] = 6.123233995736766e-17;
    _loadedShapePnts[5][1] = 1.0;
    _loadedShapePnts[6][0] = -0.30901699437494734;
    _loadedShapePnts[6][1] = 0.9510565162951536;
    _loadedShapePnts[7][0] = -0.587785252292473;
    _loadedShapePnts[7][1] = 0.8090169943749475;
    _loadedShapePnts[8][0] = -0.8090169943749473;
    _loadedShapePnts[8][1] = 0.5877852522924732;
    _loadedShapePnts[9][0] = -0.9510565162951535;
    _loadedShapePnts[9][1] = 0.3090169943749475;
}

void PolyHalfCircle::initFromFile(const char* filepath) {
    /// can load shapes from files
    
    // loads a shape from a file in format:
    //   x1, y1
    //   x2, y2
    //   ...
    
    _loadedShapePnts = new float*[_maxLoadedPnts];
    std::ifstream file_data(filepath);

    if (!file_data.is_open()) {
        std::cout << "Error: Unable to open file " << filepath << std::endl;
        return initFromPolygon();  // if the provided file is not found, default to hardcoded values
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
            _loadedShapePnts[totalShapes] = new float[2];
            _loadedShapePnts[totalShapes][0] = std::stof(curX); // stof --> string to float
            _loadedShapePnts[totalShapes][1] = std::stof(tempVal);
            totalShapes++;
            tempVal = "";
        }
    }

    _numLoadedPnts = totalShapes;
}
