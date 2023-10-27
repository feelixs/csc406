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
    const float vel_;
    void initVel_();
public:
    Bullet(float x, float y, float angle, float vel);
    Bullet(WorldPoint& xy, float angle, float vel);
    
    void draw() const;
    bool isInside(const WorldPoint& pt);
    //void update(float dt);
};

#endif /* Bullet_hpp */
