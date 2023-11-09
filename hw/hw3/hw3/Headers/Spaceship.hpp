//
//  Spaceship.hpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#ifndef Spaceship_hpp
#define Spaceship_hpp

#include "GraphicObject.h"
#include "AnimatedObject.h"

using namespace earshooter;

class Spaceship: public GraphicObject, public AnimatedObject {
private:
    /// The game's current view mode (true = egocentric, false = geocentric)
    bool egocentric_;
    
    /// Is the player currently invulnerable (immune to damage)?
    bool invulnerable_;
    
    /// Spaceship's hull integrity
    int integrity_;
    
    /// The integrity value that the spaceship spawned with
    int startingIntegrity_;
    
    /// Spaceship's current amount of lives
    int lives_;
    
    /// How fast the spaceship is currently accelerating
    float accel_;
    
    /// How fast this spaceship can accelerate currently
    float accelRate_;
    
    /// Reference to if the spaceship is currently accelerating
    bool isAccelerating_;
    
    /// Spaceship's color
    float red_, green_, blue_;
    
    /// How fast the spaceship could accelerate when it first spawned
    static float startingAccelRate_;
    
    /// Number of seconds that the spaceship should go invulnerable for after taking damage
    static float INVULNERABLE_SECS;
    
    /// While invulnerable, keeps track of how long to wait before turning off invulnerability
    static float returnFromInvulnerabilityAfter_;
    
    /// Keeps track of how long to wait before toggling visablilty while blinking (during invulnerability period)
    static float blinkTimer_;
    
    /// Keeps track of current visibility while blinking
    static bool blinkIsVisible_;
    
    /// Absolute bounding box's bounds
    static float absoluteBoxMinX_, absoluteBoxMax_, absoluteBoxMinY_, absoluteBoxMaxY_;
    
public:
    /// Create a new Spaceship
    /// @param x the starting x pos of the spaceship
    /// @param y the starting y pos
    /// @param integrity damage required before being destroyed (losing a life)
    /// @param accel_rate how fast the spaceship should accelerate
    /// @param lives number of lives to lose before game over
    Spaceship(float x, float y, int integrity, int accel_rate, int lives);
    
    void draw() const;
    void update(float dt);
    
    /// Returns if a point is inside both of the spaceship's bounding boxes
    /// @param pt the point to check
    bool isInside(const WorldPoint& pt);
    
    /// Do both of the spaceship's bounding boxes overlap with both of the other object's?
    /// First checks if the two absolute bounding boxes overlap, and if so it returns whether their absolute boxes do
    /// @param other the other object to check collision with
    bool collidesWith(std::shared_ptr<GraphicObject> other);
    
    /// Take hits to the spacehip's integrity, and lose a life if integrity==0
    /// @param dmg amount of hits integrity should take
    void takeHits(int dmg);
    
    /// Color getters
    inline float getRed() {
        return red_;
    }
    inline float getGreen() {
        return green_;
    }
    inline float getBlue() {
        return blue_;
    }
    
    /// Return how fast the spaceship is currently accelerating
    inline float getAccel() {
        return accel_;
    }
    
    /// returns true if game is egocentric, and false if geocentric
    inline bool isEgocentric() {
        return egocentric_;
    }
    
    /// returns if the spaceship is currently invulnerable (immune to damage)
    inline bool isInvulnerable() {
        return invulnerable_;
    }
    
    /// returns how many lives the spaceship currently has
    inline int getLives() {
        return lives_;
    }
    
    /// returns the spaceship's current hull integrity
    inline int getIntegrity() {
        return integrity_;
    }
    
    /// returns how fast the spaceship can accelerate
    inline float getAccelRate() {
        return accelRate_;
    }
    
    /// Set the spaceship's current acceleration
    /// @param a the spaceship's new acceleration (magnitude)
    inline void setAccel(float a) {
        accel_ = a;
    }
    
    /// Sets a reference to whether or not the spaceship is currently accelerating
    /// @param t whether or not the spaceship is currently accelerating
    inline void setIsAccelerating(bool t) {
        isAccelerating_ = t;
    }
    
    /// Change the game's view mode between egocentric and geocentric
    /// @param e new mode to change to: true=egocentric, false=geocentric
    inline void setEgocentric(bool e) {
        egocentric_ = e;
    }
    
    /// Set the spaceship's current lives
    /// @param l value to set the spaceship's lives to
    inline void setLives(int l) {
        lives_ = l;
    }
    
    /// Set the spaceship's hull integrity
    /// @param integ value to set the spaceship's integrity to
    inline void setIntegrity(int integ) {
        integrity_ = integ;
    }
    
    /// Makes the spaceship immune to damage for a number of seconds
    /// @param invFor number of seconds to make the spaceship immune to damage
    inline void goInvulnerableFor(float invFor) {
        invulnerable_ = true;
        returnFromInvulnerabilityAfter_ = invFor;
    }
    
    /// Set how fast the spaceship can accelerate
    /// @param a new acceleration rate
    inline void setAccelRate(float a) {
        accelRate_ = a;
    }
};

#endif /* Spaceship_hpp */
