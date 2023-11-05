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

#include <stdio.h>
#include "GraphicObject.h"
#include "AnimatedObject.h"
#include "Spaceship.hpp"

using namespace earshooter;

class LivesDisplay : public GraphicObject, public AnimatedObject {
private:
    std::shared_ptr<Spaceship> obj_;
    static float totalLives_, remainingLives_;
    float spacing_, scale_;
public:
    ///@param pt starting coords
    ///@param obj the spaceship whose life this will keep track of
    ///@param posOffset how much space to leave between each Life Indicator
    ///@param scale scaleY and scaleX
    LivesDisplay(const WorldPoint &pt, std::shared_ptr<Spaceship> obj, float posOffset, float scale);
    void draw() const;
    void update(float dt);
    bool isInside(const WorldPoint& pt);
};


#endif /* LivesDisplay_hpp */
