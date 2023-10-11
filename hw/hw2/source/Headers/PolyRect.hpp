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

class PolyRect: public PolyShape {
private:
    // points for straight line
    static float** _rectPoints; // 2x2 float
    float width_, length_;
    void _init_();
public:
    PolyRect(float centerX, float centerY, float angle, float length, float width, float r, float g, float b);
    PolyRect(Point centerPoint, float angle, float length, float width, float r, float g, float b);
    ~PolyRect();
    
    void draw() const override;
    
    //disabled constructors & operators
    PolyRect() = delete;
    PolyRect(const PolyRect& obj) = delete;    // copy
    PolyRect(PolyRect&& obj) = delete;        // move
    PolyRect& operator = (const PolyRect& obj) = delete;    // copy operator
    PolyRect& operator = (PolyRect&& obj) = delete;        // move operator
};

#endif /* PolyLine_hpp */
