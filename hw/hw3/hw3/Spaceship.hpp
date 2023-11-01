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
    std::unique_ptr<BoundingBox> absBoundingBox_;
    
public:
    /// @param x the starting x pos of the spaceship
    /// @param y the starting y pos
    /// @param life damage required before being destroyed (game over)
    Spaceship(float x, float y, int life);
    
    void draw() const;
    bool isInside(const WorldPoint& pt);
    void update(float dt);
    
    inline BoundingBox& getAbsBoundingbox() {
        return *absBoundingBox_;
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
    
    inline bool isEgocentric() {
        return egocentric_;
    }
    inline bool isInvulnerable() {
        return invulnerable_;
    }
    inline int getLife() {
        return life_;
    }
    
    
    /// @param a the spaceship's new acceleration (magnitude)
    inline void setAccel(float a) {
        accel_ = a;
    }
    inline void setIsAccelerating(bool t) {
        isAccelerating_ = t;
    }
    inline void setEgocentric(bool e) {
        egocentric_ = e;
    }
    inline void setLife(int l) {
        life_ = l;
    }
    inline void goInvulnerableFor(float invFor) {
        invulnerable_ = true;
        returnFromInvulnerabilityAfter_ = invFor;
    }
};

#endif /* Spaceship_hpp */
