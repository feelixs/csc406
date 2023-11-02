//
//  LifeCounter.hpp
//  hw3
//
//  Created by Michael Felix on 10/31/23.
//

#ifndef LifeCounter_hpp
#define LifeCounter_hpp

#include <stdio.h>
#include "GraphicObject.h"
#include "AnimatedObject.h"
#include "Spaceship.hpp"

using namespace earshooter;

class LifeCounter : public GraphicObject, public AnimatedObject {
private:
    float len_, width_, red_, green_, blue_;
    std::shared_ptr<Spaceship> obj_;
    
    static float totalLife_, curLife_; // totalLife is set to this->obj_'s life when this is initialized
    static float** displayLinePts_;
public:
    ///@param pt starting coords
    ///@param obj the spaceship whose life this will keep track of
    ///@param len horizontal length constant for the onscreen display
    ///@param width virtical width of the healthbar
    LifeCounter(const WorldPoint &pt, std::shared_ptr<Spaceship> obj, float len, float width);
    void draw() const;
    void update(float dt);
    bool isInside(const WorldPoint& pt);
};


#endif /* LifeCounter_hpp */
