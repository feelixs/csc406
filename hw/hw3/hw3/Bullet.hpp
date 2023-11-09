//
//  Bullet.hpp
//  hw3
//
//  Created by Michael Felix on 10/27/23.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "GraphicObject.h"
#include "AnimatedObject.h"

using namespace earshooter;

class Bullet : public GraphicObject, public AnimatedObject {
private:
    const float lifetime_;
    float age_, vel_;
    WorldPoint relativePos_;
    
    void initVel_();
public:
    /**
        @param x starting x pos of the bullet
        @param y starting y pos of the bullet
        @param angle starting angle of the bullet
        @param vel velocity (magnitude) of the bullet
        @param lifetime how many seconds the bullet should last before deleting
     */
    Bullet(float x, float y, float angle, float vel, float lifetime);
    Bullet(WorldPoint& xy, float angle, float vel, float lifetime);
    
    void draw() const;
    void update(float dt);
    void update(float dt, float playerAngle, bool egocentric);
    
    bool isInside(const WorldPoint& pt);
    
    inline void setVel(float v) {
        vel_ = 0;
        setVx(0);
        setVy(0);
    }
    
    inline void setRelativePos(WorldPoint pt) {
        relativePos_ = pt;
    }
    inline void setRelativeX(float x) {
        relativePos_.x = x;
    }
    inline void setRelativeY(float y) {
        relativePos_.y = y;
    }
    
    inline WorldPoint getRelativePos() {
        return relativePos_;
    }
    inline float getLife() {
        return lifetime_;
    }
    inline float getAge() {
        return age_;
    }
    inline WorldPoint getPos() {
        return WorldPoint{getX(), getY()};
    }
};

#endif /* Bullet_hpp */
