//
//  PolyCircle.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyCircle_hpp
#define PolyCircle_hpp

#include "PolyShape.hpp"
#include <stdio.h>

class PolyCircle: public PolyShape {
private:
    // shape points of circle calculated in constructor
    static float** _circlePoints; // Nx2 float
    static const int _numCirPoints;
    
public:
    PolyCircle(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
    ~PolyCircle();
    
    //disabled constructors & operators
    PolyCircle() = delete;
    PolyCircle(const PolyCircle& obj) = delete;    // copy
    PolyCircle(PolyCircle&& obj) = delete;        // move
    PolyCircle& operator = (const PolyCircle& obj) = delete;    // copy operator
    PolyCircle& operator = (PolyCircle&& obj) = delete;        // move operator
};

#endif /* PolyCircle_hpp */
