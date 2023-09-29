//
//  PolyEarLeft.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyEarLeft_hpp
#define PolyEarLeft_hpp

#include "PolyShape.hpp"
#include <stdio.h>
#include <string>

bool loadPolyShape(const char* filename);
bool initPolyShape(const char* coordFile);

class PolyEarLeft: public PolyShape {
    friend bool loadPolyShape(const char* filename);
private:
    // shape points loaded from file shapeCoords.txt in loadShape()
    const char* _myLoadedFilepath;
    static int _numLoadedPnts;
    static const int _maxLoadedPnts; // stop loading from the file after this limit is reached
    static float** _loadedShapePnts; // Nx2 float
    
public:
    PolyEarLeft(std::string filepath, float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
    ~PolyEarLeft();
    
    void draw() const override;
    
    //disabled constructors & operators
    PolyEarLeft() = delete;
    PolyEarLeft(const PolyEarLeft& obj) = delete;    // copy
    PolyEarLeft(PolyEarLeft&& obj) = delete;        // move
    PolyEarLeft& operator = (const PolyEarLeft& obj) = delete;    // copy operator
    PolyEarLeft& operator = (PolyEarLeft&& obj) = delete;        // move operator
};

#endif /* PolyEarLeft_hpp */
