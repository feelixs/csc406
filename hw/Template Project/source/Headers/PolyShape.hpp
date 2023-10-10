//
//  PolyShape.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyShape_hpp
#define PolyShape_hpp

#include <stdio.h>
#include "GraphicObject.h"


class PolyShape: public GraphicObject
/// base class for all shapes
{    
    private:
        // all children share these attributes
    float scaleX_, scaleY_;
        float red_, green_, blue_;
    
    public:
        PolyShape(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
        PolyShape(Point centerPoint, float angle, float scaleX, float scaleY, float r, float g, float b);
        ~PolyShape();
        
        virtual void draw() const; // children will override this function

        //disabled constructors & operators
        PolyShape() = delete;
        PolyShape(const PolyShape& obj) = delete;    // copy
        PolyShape(PolyShape&& obj) = delete;        // move
        PolyShape& operator = (const PolyShape& obj) = delete;    // copy operator
        PolyShape& operator = (PolyShape&& obj) = delete;        // move operator
    
    inline float getScaleX() const {
        return scaleX_;
    }
    inline float getScaleY() const {
        return scaleY_;
    }
    inline float getRed() const {
        return red_;
    }
    inline float getGreen() const {
        return green_;
    }
    inline float getBlue() const {
        return blue_;
    }
};

#endif /* PolyShape_hpp */
