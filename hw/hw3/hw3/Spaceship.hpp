//
//  Spaceship.hpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#ifndef Spaceship_hpp
#define Spaceship_hpp

#include <stdio.h>
#include "GraphicObject.h"
#include "AnimatedObject.h"

using namespace earshooter;

class Spaceship: public GraphicObject, public AnimatedObject {
private:
    float red_, green_, blue_;
    float vel_;
    
public:
    Spaceship(float x, float y);
    
    void draw() const;
    void update(float dt);
    bool isInside(const WorldPoint& pt);
    
    inline float getRed() {
        return red_;
    }
    inline float getGreen() {
        return green_;
    }
    inline float getBlue() {
        return blue_;
    }
    inline float getVel() {
        return vel_;
    }
    inline void setVel(float v) {
        vel_ = v;
    }
};

#endif /* Spaceship_hpp */
