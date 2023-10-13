//
//  PolyTriangle.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyTriangle_hpp
#define PolyTriangle_hpp

#include "PolyShape.hpp"
#include <stdio.h>


class PolyTriangle: public PolyShape {
    private:
        static float** _trianPoints;
        void _init_();
    public:
        PolyTriangle(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
        PolyTriangle(Point centerPoint, float angle, float scaleX, float scaleY, float r, float g, float b, Point offset, float angleOffset);
        ~PolyTriangle();

        //disabled constructors & operators
        PolyTriangle() = delete;
        PolyTriangle(const PolyTriangle& obj) = delete;    // copy
        PolyTriangle(PolyTriangle&& obj) = delete;        // move
        PolyTriangle& operator = (const PolyTriangle& obj) = delete;    // copy operator
        PolyTriangle& operator = (PolyTriangle&& obj) = delete;        // move operator
};

#endif /* PolyTriangle_hpp */
