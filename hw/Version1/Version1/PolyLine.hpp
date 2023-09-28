//
//  PolyLine.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyLine_hpp
#define PolyLine_hpp

#include "PolyShape.hpp"
#include <iostream>
#include <stdio.h>

class PolyLine: public PolyShape {
private:
    // points for straight line
    static float** _straightLinePoints; // 2x2 float
    
public:
    PolyLine(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
    ~PolyLine();
    
    //disabled constructors & operators
    PolyLine() = delete;
    PolyLine(const PolyLine& obj) = delete;    // copy
    PolyLine(PolyLine&& obj) = delete;        // move
    PolyLine& operator = (const PolyLine& obj) = delete;    // copy operator
    PolyLine& operator = (PolyLine&& obj) = delete;        // move operator
};

#endif /* PolyLine_hpp */
