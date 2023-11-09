//
//  Bullet.hpp
//  hw3
//
//  Created by Michael Felix on 10/27/23.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "GraphicObject.h"
#include "AnimatedObject.h"

using namespace earshooter;

class Bullet : public GraphicObject, public AnimatedObject {
private:
    /// How many seconds the bullet should last before deleting
    const float lifetime_;
    
    /// How long the bullet has been active for
    float age_;
    
    /// How fast should the bullet move
    float vel_;
    
    /// The bullet's geocentric position
    WorldPoint relativePos_;
public:
    /// Create a new bullet
    /// @param x starting x pos of the bullet
    /// @param y starting y pos of the bullet
    /// @param angle starting angle of the bullet
    /// @param vel velocity (magnitude) of the bullet
    /// @param lifetime how many seconds the bullet should last before deleting
    Bullet(float x, float y, float angle, float vel, float lifetime);
    
    /// Create a new bullet
    /// @param xy starting position point of the bullet
    /// @param angle starting angle of the bullet
    /// @param vel velocity (magnitude) of the bullet
    /// @param lifetime how many seconds the bullet should last before deleting
    Bullet(WorldPoint& xy, float angle, float vel, float lifetime);
    
    void draw() const;
    
    /// In egocentric mode the bullet needs to know some of the player's variables in order to correctly compute its position
    /// @param playerAngle the player's angle
    /// @param egocentric is the game in egocentric (true) or geocentric (false) mode
    void update(float dt, float playerAngle, bool egocentric);
    
    /// Even though we won't be using this update fn, we still need to declare it
    void update(float dt);
    
    /// Because the bullet can be considered a point we can return if the bullet's position is equal to the other point's
    /// @param pt the point to check if is inside the bullet
    inline bool isInside(const WorldPoint& pt) {
        return (pt.x == getX() && pt.y == getY());
    }
    
    /// Calculate the bullet's velocity based on its angle
    void calcVel();
    
    /// Set the bullets's geocentric position
    /// @param pt point to set my geocentric position to
    inline void setRelativePos(WorldPoint pt) {
        relativePos_ = pt;
    }
    
    /// Set the bullet's geocentric x position
    /// @param x value to set my geocentric x to
    inline void setRelativeX(float x) {
        relativePos_.x = x;
    }
    
    /// Set the bullet's geocentric y position
    /// @param y value to set my geocentric y to
    inline void setRelativeY(float y) {
        relativePos_.y = y;
    }
    
    /// Returns the bullet's geocentric position as a point
    inline WorldPoint getRelativePos() {
        return relativePos_;
    }
    
    /// Returns the bullet's actual onscreen position as a point
    inline WorldPoint getPos() {
        return WorldPoint{getX(), getY()};
    }
    
    /// Returns how many seconds the bullet should last
    inline float getLife() {
        return lifetime_;
    }
    
    /// Returns how many seconds have passed since the bullet's creation
    inline float getAge() {
        return age_;
    }
};

#endif /* Bullet_hpp */
