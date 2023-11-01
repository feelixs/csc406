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
    float width_, height_;
    Velocity initVel_; // the asteroid's starting velocity
    float boundingBoxXmin_, boundingBoxXmax_, boundingBoxYmin_, boundingBoxYmax_;
    
    void initBoundingBox_(float halfWidth, float halfHeight);
public:
    Asteroid(float centerX, float centerY, float angle, float spin, float width, float height,
            float vx, float vy);
    Asteroid(const WorldPoint& pt, float angle, float spin, float width, float height, const Velocity& vel);
    
    void draw() const;
    void update(float dt);
    bool isInside(const WorldPoint& pt);
    
    inline float getScaleY() {
        return height_;
    }
    inline float getScaleX() {
        return width_;
    }
    inline float getInitVx() {
        return initVel_.vx;
    }
    inline float getInitVy() {
        return initVel_.vy;
    }
};

#endif /* Asteroid_hpp */
