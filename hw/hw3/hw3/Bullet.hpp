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
    const float vel_, lifetime_;
    float age_;
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
    
    bool isInside(const WorldPoint& pt);
    
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
