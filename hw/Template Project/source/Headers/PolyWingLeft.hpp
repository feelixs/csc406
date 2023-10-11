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

class PolyWingLeft: public PolyShape {
private:
    // shape points loaded from file shapeCoords.txt in loadShape()
    const char* _myLoadedFilepath;
    static int _numLoadedPnts;
    static const int _maxLoadedPnts; // stop loading from the file after this limit is reached
    static float** _loadedShapePnts; // Nx2 float
    
public:
    PolyWingLeft(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
    PolyWingLeft(Point centerPoint, float angle, float scaleX, float scaleY, float r, float g, float b);
    ~PolyWingLeft();
    
    void draw() const override;
    
    void initFromPolygon();
    //disabled constructors & operators
    PolyWingLeft() = delete;
    PolyWingLeft(const PolyWingLeft& obj) = delete;    // copy
    PolyWingLeft(PolyWingLeft&& obj) = delete;        // move
    PolyWingLeft& operator = (const PolyWingLeft& obj) = delete;    // copy operator
    PolyWingLeft& operator = (PolyWingLeft&& obj) = delete;        // move operator
};

#endif /* PolyEarLeft_hpp */
