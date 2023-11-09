//
//  Asteroid.hpp
//  hw3
//
//  Created by Michael Felix on 10/25/23.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include "GraphicObject.h"
#include "AnimatedObject.h"

using namespace earshooter;

class Asteroid: public GraphicObject, public AnimatedObject {
private:
    /// The asteroid's measurements
    float width_, height_;
    
    /// Half the asteroid's width & height
    float halfWidth_, halfHeight_; // these are defined so we don't need to compute them everytime in bounding box calculations
    
    /// The asteroid's velocity relative to the camera in geocentric mode
    Velocity relativeVel_;
    
    /// The asteroid's position as seen in geocentric mode
    WorldPoint relativePos_;
    
    /// Absolute box's bounds
    float absoluteBoxMinX_, absoluteBoxMaxX_, absoluteBoxMinY_, absoluteBoxMaxY_;
    
    /// Compute the bounds of the bounding box based on the asteroid's maximum rectangular area (when it's rotated by 45 degrees)
    /// @param showBox should the box be visable (true) or invisible (false)
    void initBoundingBox_(bool showBox);
public:
    /// Create a new Asteroid
    /// @param centerX central x position
    /// @param centerY central y position
    /// @param angle starting angle
    /// @param spin angular momentum
    /// @param width scale along the x
    /// @param height scale along the y
    /// @param vx starting x velocity
    /// @param vy starting y velocity
    Asteroid(float centerX, float centerY, float angle, float spin, float width, float height, float vx, float vy);
    
    /// Create a new Asteroid
    /// @param pt starting central position
    /// @param angle starting angle
    /// @param spin angular momentum
    /// @param width scale along the x
    /// @param height scale along the y
    /// @param vel x and y velocity
    Asteroid(const WorldPoint& pt, float angle, float spin, float width, float height, const Velocity& vel);
    
    /// Create a new Asteroid
    /// @param pt starting central position
    /// @param angle starting angle
    /// @param spin angular momentum
    /// @param width scale along the x
    /// @param height scale along the y
    /// @param vel x and y veloc
    /// @param showBoundingBoxes should we render the bounding boxes?
    Asteroid(const WorldPoint& pt, float angle, float spin, float width, float height, const Velocity& vel, bool showBoundingBoxes);
    
    void draw() const;
    
    /// In egocentric mode the asteroid needs to know some of the player's variables in order to correctly compute its position
    /// @param playerVx the player's x velocity
    /// @param playerVy the player's y velocity
    /// @param playerAngle the player's angle
    /// @param egocentric is the game in egocentric (true) or geocentric (false) mode
    void update(float dt, float playerVx, float playerVy, float playerAngle, bool egocentric);
    
    /// Even though we won't be using this update fn, we still need to declare it
    void update(float dt);
    
    /// Returns if a point is inside both of the asteroid's bounding boxes
    /// @param pt the point to check
    bool isInside(const WorldPoint& pt);
    
    /// Do both of the asteroid's bounding boxes overlap with both of the other object's?
    /// First checks if the two absolute bounding boxes overlap, and if so it returns whether their absolute boxes do
    /// @param other the other object to check collision with
    bool collidesWith(std::shared_ptr<GraphicObject> other);
    
    //disabled constructors & operators
    Asteroid() = delete;
    Asteroid(const Asteroid& obj) = delete;    // copy
    Asteroid(Asteroid&& obj) = delete;        // move
    Asteroid& operator = (const Asteroid& obj) = delete;    // copy operator
    Asteroid& operator = (Asteroid&& obj) = delete;        // move operator
    
    /// Set the asteroid's geocentric x position
    /// @param x value to set my geocentric x to
    inline void setRelativeX(float x) {
        relativePos_.x = x;
    }
    
    /// Set the asteroid's geocentric y position
    /// @param y value to set my geocentric y to
    inline void setRelativeY(float y) {
        relativePos_.y = y;
    }
    
    /// Set the asteroid's relative position
    /// @param pt point to set my geocentric position to
    inline void setRelativePos(WorldPoint pt) {
        relativePos_ = pt;
    }
    
    /// Returns the asteroid's onscreen position
    inline WorldPoint getPos() {
        return WorldPoint{getX(), getY()};
    }
    
    /// Returns the asteroid's geocentric x velocity
    inline float getRelativeVx() {
        return relativeVel_.vx;
    }
    
    /// Returns the asteroid's geocentric y velocity
    inline float getRelativeVy() {
        return relativeVel_.vy;
    }
    
    /// Returns the asteroid's geocentric position as a point
    inline WorldPoint getRelativePos() {
        return relativePos_;
    }
    
    /// Measurement getters
    inline float getHeight() {
        return height_;
    }
    inline float getWidth() {
        return width_;
    }
};

#endif /* Asteroid_hpp */
