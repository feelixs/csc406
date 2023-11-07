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
    float width_, height_, halfWidth_, halfHeight_;
    bool gameIsEgocentric_;
    Velocity initVel_; // the asteroid's starting velocity
    float absoluteBoxMinX_, absoluteBoxMaxX_, absoluteBoxMinY_, absoluteBoxMaxY_;
    
    void initBoundingBox_();
public:
    Asteroid(float centerX, float centerY, float angle, float spin, float width, float height,
            float vx, float vy);
    Asteroid(const WorldPoint& pt, float angle, float spin, float width, float height, const Velocity& vel);
    
    void draw() const;
    void update(float dt);
    bool isInside(const WorldPoint& pt);
    bool collidesWith(std::shared_ptr<GraphicObject> other);
    
    //disabled constructors & operators
    Asteroid() = delete;
    Asteroid(const Asteroid& obj) = delete;    // copy
    Asteroid(Asteroid&& obj) = delete;        // move
    Asteroid& operator = (const Asteroid& obj) = delete;    // copy operator
    Asteroid& operator = (Asteroid&& obj) = delete;        // move operator
    
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
    inline void setEgocentric(bool to) {
        gameIsEgocentric_ = to;
    }
};

#endif /* Asteroid_hpp */
