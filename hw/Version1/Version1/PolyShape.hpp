//
//  PolyShape.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyShape_hpp
#define PolyShape_hpp

#include <stdio.h>

bool loadPolyShape(const char* filename);
bool initPolyShape(const char* coordFile);
bool initStraightLine();


class PolyShape
{
    friend class PolyCircle;
    friend bool loadPolyShape(const char* filename);
    friend bool initStraightLine();
    
    private:
        float centerX_, centerY_, scaleX_, scaleY_, angle_;
        float red_, green_, blue_;
    
        // shape points loaded from file shapeCoords.txt in loadShape()
        static int _numLoadedPnts;
        static const int _maxLoadedPnts;
        static float** _loadedShapePnts; // Nx2 float
    
        // points for straight line
        static float** _straightLinePoints; // 2x2 float
    public:
        PolyShape(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
        ~PolyShape();
        
        void draw() const;

        //disabled constructors & operators
        PolyShape() = delete;
        PolyShape(const PolyShape& obj) = delete;    // copy
        PolyShape(PolyShape&& obj) = delete;        // move
        PolyShape& operator = (const PolyShape& obj) = delete;    // copy operator
        PolyShape& operator = (PolyShape&& obj) = delete;        // move operator
};

#endif /* PolyShape_hpp */
