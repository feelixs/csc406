//
//  PolyCustom.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyCustom_hpp
#define PolyCustom_hpp

#include "PolyShape.hpp"
#include <stdio.h>
#include <string>


class PolyHalfCircle: public PolyShape {
private:
    // shape points loaded from file shapeCoords.txt in loadShape()
    static int _numLoadedPnts;
    static const int _maxLoadedPnts; // stop loading from the file after this limit is reached
    static float** _loadedShapePnts; // Nx2 float
    
public:
    PolyHalfCircle(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
    ~PolyHalfCircle();
    
    void draw() const override;
    void initFromPolygon();
    //disabled constructors & operators
    PolyHalfCircle() = delete;
    PolyHalfCircle(const PolyHalfCircle& obj) = delete;    // copy
    PolyHalfCircle(PolyHalfCircle&& obj) = delete;        // move
    PolyHalfCircle& operator = (const PolyHalfCircle& obj) = delete;    // copy operator
    PolyHalfCircle& operator = (PolyHalfCircle&& obj) = delete;        // move operator
};

#endif /* PolyCustom_hpp */
