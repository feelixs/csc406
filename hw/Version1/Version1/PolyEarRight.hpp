//
//  PolyEarRight.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyEarRight_hpp
#define PolyEarRight_hpp

#include "PolyShape.hpp"
#include <stdio.h>
#include <string>

class PolyEarRight: public PolyShape {
private:
    // shape points loaded from file shapeCoords.txt in loadShape()
    const char* _myLoadedFilepath;
    static int _numLoadedPnts;
    static const int _maxLoadedPnts; // stop loading from the file after this limit is reached
    static float** _loadedShapePnts; // Nx2 float
    
public:
    PolyEarRight(std::string filepath, float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
    ~PolyEarRight();
    
    void draw() const override;
    
    void initFromPolygon();
    void initFromFile(const char* filepath);
    //disabled constructors & operators
    PolyEarRight() = delete;
    PolyEarRight(const PolyEarRight& obj) = delete;    // copy
    PolyEarRight(PolyEarRight&& obj) = delete;        // move
    PolyEarRight& operator = (const PolyEarRight& obj) = delete;    // copy operator
    PolyEarRight& operator = (PolyEarRight&& obj) = delete;        // move operator
};

#endif /* PolyEarRight_hpp */
