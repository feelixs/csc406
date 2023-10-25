//
//  Asteroid.hpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include <stdio.h>

#include "GraphicObject.h"
#include "AnimatedObject.h"

namespace earshooter {
    class Asteroid: public GraphicObject, public AnimatedObject {
    private:
        float scaleX_, scaleY_;
        
    public:
        Asteroid(float centerX, float centerY, float angle, float width, float height,
                float vx, float vy);
        Asteroid(const WorldPoint& pt, float angle, float width, float height, const WorldPoint& velPt);
        
        void draw() const;
        bool isInside(const WorldPoint& pt);
        
        inline float getScaleY() {
            return scaleY_;
        }
        inline float getScaleX() {
            return scaleX_;
        }
    };
}

#endif /* Asteroid_hpp */
