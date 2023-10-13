//
//  PolyEarRight.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyEarRight_hpp
#define PolyEarRight_hpp

#include "PolyShape.hpp"
#include "World.h"
#include <stdio.h>
#include <string>

class PolyWingRight: public PolyShape {
private:
    // shape points loaded from file shapeCoords.txt in loadShape()
    static int _numLoadedPnts;
    static const int _maxLoadedPnts; // stop loading from the file after this limit is reached
    static float** _loadedShapePnts; // Nx2 float
    
public:
    PolyWingRight(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
    PolyWingRight(Point centerPoint, float angle, float scaleX, float scaleY, float r, float g, float b, Point offset);
    ~PolyWingRight();
    
    void initFromPolygon();
    //disabled constructors & operators
    PolyWingRight() = delete;
    PolyWingRight(const PolyWingRight& obj) = delete;    // copy
    PolyWingRight(PolyWingRight&& obj) = delete;        // move
    PolyWingRight& operator = (const PolyWingRight& obj) = delete;    // copy operator
    PolyWingRight& operator = (PolyWingRight&& obj) = delete;        // move operator
};

#endif /* PolyEarRight_hpp */
