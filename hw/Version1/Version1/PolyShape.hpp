//
//  PolyShape.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyShape_hpp
#define PolyShape_hpp

#include <stdio.h>


class PolyShape
/// base class for all shapes
{
    friend class PolyCircle;
    friend class PolyRect;
    friend class PolyCustom;
    friend class PolyTriangle;
    
    private:
        // all children share these attributes
        float centerX_, centerY_, scaleX_, scaleY_, angle_;
        float red_, green_, blue_;
    
    public:
        PolyShape(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
        ~PolyShape();
        
        virtual void draw() const; // children will override this function

        //disabled constructors & operators
        PolyShape() = delete;
        PolyShape(const PolyShape& obj) = delete;    // copy
        PolyShape(PolyShape&& obj) = delete;        // move
        PolyShape& operator = (const PolyShape& obj) = delete;    // copy operator
        PolyShape& operator = (PolyShape&& obj) = delete;        // move operator
};

#endif /* PolyShape_hpp */
