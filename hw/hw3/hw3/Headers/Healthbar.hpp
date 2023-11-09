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

#include "GraphicObject.h"
#include "AnimatedObject.h"
#include "Spaceship.hpp"

using namespace earshooter;

class Healthbar : public GraphicObject, public AnimatedObject {
private:
    /// Horizontal length constant, multiplied by obj's current integrity to get actual onscreen length
    float len_;
    
    /// Vertical height of the healthbar
    float height_;
    
    /// Healthbar's color
    float red_, green_, blue_;
    
    /// The Spaceship object whose hull integrity this Healthbar keeps track of
    std::shared_ptr<Spaceship> obj_;
    
    /// The Spaceship's current hull integrity, should always be equal to obj->getIntegrity()
    static float curHealth_;
    
    /// How much integrity the Spaceship originally spawned with
    static float totalHealth_;
    
    /// The Healthbar rectangle's vertices (always stores full rectangle of when obj is at full integrity)
    static float** rectVertices_;
public:
    /// Creates a new Healthbar for a Spaceship object
    ///@param pt starting coords
    ///@param obj the spaceship whose hull integrity this will keep track of
    ///@param len horizontal length constant for the onscreen display
    ///@param height virtical width of the healthbar
    Healthbar(const WorldPoint &pt, std::shared_ptr<Spaceship> obj, float len, float height);
    
    void draw() const;
    void update(float dt);
    
    /// This is never used but needs to be declared since it's virtual
    bool isInside(const WorldPoint& pt);
};


#endif /* Healthbar_hpp */
