//
//  Healthbar.hpp
//  hw3
//
//  Displays a healthbar of the Player's remaining hull integrity as a Graphic object
//
//  Created by Michael Felix on 10/31/23.
//

#ifndef Healthbar_hpp
#define Healthbar_hpp

#include <stdio.h>
#include "GraphicObject.h"
#include "AnimatedObject.h"
#include "Spaceship.hpp"

using namespace earshooter;

class Healthbar : public GraphicObject, public AnimatedObject {
private:
    float len_, width_, red_, green_, blue_;
    std::shared_ptr<Spaceship> obj_;
    
    static float totalHealth_, curHealth_; // totalLife is set to this->obj_'s life when this is initialized
    static float** displayLinePts_;
public:
    ///@param pt starting coords
    ///@param obj the spaceship whose life this will keep track of
    ///@param len horizontal length constant for the onscreen display
    ///@param width virtical width of the healthbar
    Healthbar(const WorldPoint &pt, std::shared_ptr<Spaceship> obj, float len, float width);
    void draw() const;
    void update(float dt);
    bool isInside(const WorldPoint& pt);
};


#endif /* Healthbar_hpp */
