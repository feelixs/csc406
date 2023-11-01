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
    
    bool egocentric_;
    bool invulnerable_;
    int life_;
    
    static float blinkTimer_;
    static bool blinkIsVisible_;
    static float returnFromInvulnerabilityAfter_; // after taking damage, we must store when to stop being invulnerable
    static float boundingBoxXmin_, boundingBoxXmax_, boundingBoxYmin_, boundingBoxYmax_;
    float red_, green_, blue_, accel_;
    bool isAccelerating_;
    std::unique_ptr<BoundingBox> collisionBox_;
    
public:
    Spaceship(float x, float y);
    
    void draw() const;
    bool isInside(const WorldPoint& pt);
    void update(float dt);
    
    inline void setAccel(float a) {
        accel_ = a;
    }
    inline float getRed() {
        return red_;
    }
    inline float getGreen() {
        return green_;
    }
    inline float getBlue() {
        return blue_;
    }
    inline float getAccel() {
        return accel_;
    }
    inline void setIsAccelerating(bool t) {
        isAccelerating_ = t;
    }
    inline bool isEgocentric() {
        return egocentric_;
    }
    inline void setEgocentric(bool e) {
        egocentric_ = e;
    }
    inline bool isInvulnerable() {
        return invulnerable_;
    }
    inline void setLife(int l) {
        life_ = l;
    }
    inline int getLife() {
        return life_;
    }
    inline void goInvulnerableFor(float invFor) {
        invulnerable_ = true;
        returnFromInvulnerabilityAfter_ = invFor;
    }
};

#endif /* Spaceship_hpp */
