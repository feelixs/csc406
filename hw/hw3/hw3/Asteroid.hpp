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

using namespace earshooter;

class Asteroid: public GraphicObject, public AnimatedObject {
private:
    float scaleX_, scaleY_;
    std::unique_ptr<BoundingBox> collisionBox_;
    
public:
    Asteroid(float centerX, float centerY, float angle, float width, float height,
            float vx, float vy);
    Asteroid(const WorldPoint& pt, float angle, float spin, float width, float height, const Velocity& vel);
    
    void draw() const;
    void update(float dt);
    bool isInside(const WorldPoint& pt);
    
    inline float getScaleY() {
        return scaleY_;
    }
    inline float getScaleX() {
        return scaleX_;
    }
};

#endif /* Asteroid_hpp */
