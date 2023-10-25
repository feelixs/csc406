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

namespace earshooter {
    class Asteroid: public GraphicObject {
    private:
        float scaleX_, scaleY_, spin_;
        float vx_, vy_;  // velocity
        
    public:
        Asteroid(float centerX, float centerY, float angle, float width, float height,
                float r, float g, float b);
        Asteroid(const WorldPoint& pt, float angle, float width, float height,
                float r, float g, float b);
        
        void draw() const;
        bool isInside(const WorldPoint& pt);
        
        inline float getVx() {
            return vx_;
        }
        inline float getVy() {
            return vy_;
        }
        inline float getSpin() {
            return spin_;
        }
        inline float getScaleY() {
            return scaleY_;
        }
        inline float getScaleX() {
            return scaleX_;
        }
    };
}

#endif /* Asteroid_hpp */
