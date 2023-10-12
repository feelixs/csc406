//
//  Animal.hpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#ifndef Animal_hpp
#define Animal_hpp

#include "PolyShape.hpp"
#include "World.h"
#include <stdio.h>
#include <vector>

class Animal: public GraphicObject
{
    private:
        void _init_();
    
        float scaleX_, scaleY_;
        float red_, green_, blue_;

        static std::vector<std::shared_ptr<PolyShape>> _myShapes;
    
        // shape points of circle calculated in initCircle()
        static float** _circlePoints; // Nx2 float
        static float** _loadedShapePnts; // Nx2 float
    
    public:
        Animal(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
        Animal(Point centerPoint, float angle, float scale, float r, float g, float b);
        ~Animal() = default;
        
        void draw() const;
        void setColor(float r, float g, float b);
        void setAllAngles(float degrees); // set angle of all constutient shapes
        void setAllScales(float x, float y);
        //disabled constructors & operators
        Animal() = delete;
        Animal(const Animal& obj) = delete;    // copy
        Animal(Animal&& obj) = delete;        // move
        Animal& operator = (const Animal& obj) = delete;    // copy operator
        Animal& operator = (Animal&& obj) = delete;        // move operator
    
    inline void setScale(float x, float y) {
        scaleX_ = x;
        scaleY_ = y;
    }
    
};

#endif /* Animal_hpp */
