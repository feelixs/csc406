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
{
    friend class PolyCircle;
    friend class PolyLine;
    friend class PolyCustom;
    
    private:
        float centerX_, centerY_, scaleX_, scaleY_, angle_;
        float red_, green_, blue_;
    
    public:
        PolyShape(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
        ~PolyShape();
        
        virtual void draw() const = 0;

        //disabled constructors & operators
        PolyShape() = delete;
        PolyShape(const PolyShape& obj) = delete;    // copy
        PolyShape(PolyShape&& obj) = delete;        // move
        PolyShape& operator = (const PolyShape& obj) = delete;    // copy operator
        PolyShape& operator = (PolyShape&& obj) = delete;        // move operator
};

#endif /* PolyShape_hpp */
