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
    int integrity_, lives_, startingIntegrity_;
    float accelRate_;
    
    static float blinkTimer_, invulnerableSecs_, startingAccelRate_;
    static bool blinkIsVisible_;
    static float returnFromInvulnerabilityAfter_; // after taking damage, we must store when to stop being invulnerable
    static float absoluteBoxMinX_, absoluteBoxMax_, absoluteBoxMinY_, absoluteBoxMaxY_;
    float red_, green_, blue_, accel_;
    bool isAccelerating_;
    
public:
    /// @param x the starting x pos of the spaceship
    /// @param y the starting y pos
    /// @param integrity damage required before being destroyed (losing a life)
    /// @param accel_rate how fast the spaceship should accelerate
    /// @param lives number of lives to lose before game over
    Spaceship(float x, float y, int integrity, int accel_rate, int lives);
    
    void draw() const;
    bool isInside(const WorldPoint& pt);
    void update(float dt);
    bool collidesWith(std::shared_ptr<GraphicObject> other);
    
    void takeHits(float dmg);
    
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
    inline int getLives() {
        return lives_;
    }
    inline int getIntegrity() {
        return integrity_;
    }
    inline float getAccelRate() {
        return accelRate_;
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
    inline void setLives(int l) {
        lives_ = l;
    }
    inline void setIntegtrity(int integ) {
        integrity_ = integ;
    }
    inline void goInvulnerableFor(float invFor) {
        invulnerable_ = true;
        returnFromInvulnerabilityAfter_ = invFor;
    }
    inline void setAccelRate(float a) {
        accelRate_ = a;
    }
};

#endif /* Spaceship_hpp */
