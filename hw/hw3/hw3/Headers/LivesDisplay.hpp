//
//  LivesDisplay.hpp
//  hw3
//
//  Displays the Player's remaining Lives as a Graphic object
//
//  Created by Michael Felix on 11/5/23.
//

#ifndef LivesDisplay_hpp
#define LivesDisplay_hpp

#include "GraphicObject.h"
#include "AnimatedObject.h"
#include "Spaceship.hpp"

using namespace earshooter;

class LivesDisplay : public GraphicObject, public AnimatedObject {
private:
    /// The Spaceship object whose lives this keeps track of
    std::shared_ptr<Spaceship> obj_;
    
    /// How much space should be put between each life indicator
    float spacing_;
    
    /// How large each life indicator should be
    float scale_;
    
    /// How many lives the Spaceship objects spawned with
    static float totalLives_;
    
    /// How many lives the Spaceship currently has
    static float remainingLives_;
public:
    /// Create a new Life Indicator instance
    /// @param pt starting coords
    /// @param obj the spaceship whose life this will keep track of
    /// @param posOffset how much space to leave between each Life Indicator
    /// @param scale scaleY and scaleX
    LivesDisplay(const WorldPoint &pt, std::shared_ptr<Spaceship> obj, float posOffset, float scale);
   
    void draw() const;
    void update(float dt);
    
    /// We will never use this, but it needs to be declared to compile
    bool isInside(const WorldPoint& pt);
};


#endif /* LivesDisplay_hpp */
