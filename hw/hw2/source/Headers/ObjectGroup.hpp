//
//  ObjectGroup.hpp
//  hw2
//
//  Created by Michael Felix on 10/10/23.
//

#ifndef ObjectGroup_hpp
#define ObjectGroup_hpp

#include <stdio.h>
#include <vector>
#include "GraphicObject.h"
#include "Animal.hpp"

#endif /* ObjectGroup_hpp */


enum GroupType { HEADS_ON_STICK = 0, HEADS_ON_WHEELS = 1 };

enum GroupSize { LARGE = 0, MEDIUM = 1, SMALL = 2 };


class ObjectGroup: public GraphicObject {
private:
    GroupType type_;
    GroupSize size_;
    float pixelSize_; // convert GroupSize into an actual pixel size to be used for the Animal's scale_
    int num_;
    float speedX_, speedY_; // pixels per second
    float spin_; // degrees per second
    
    static float** headPoints_;
    std::vector<std::shared_ptr<Animal>> groupHeads_;

    void _init_();
    
public:
    ObjectGroup(GroupType type, GroupSize size, int num, float x, float y);
    ObjectGroup(GroupType type, GroupSize size, int num, Point at);
    ~ObjectGroup() = default;
    
    void draw() const;
    void update(float dt);
    
    inline void setSpeed(float vx, float vy) {
        speedX_ = vx;
        speedY_ = vy;
    }
    inline void setSpeedX(float vx) {
        speedX_ = vx;
    }
    inline void setSpeedY(float vy) {
        speedY_ = vy;
    }
    inline void setSpin(float spin) {
        spin_ = spin;
    }
    
    inline float getSpeedX() {
        return speedX_;
    }
    inline float getSpeedY() {
        return speedY_;
    }
    inline float getSpin() {
        return spin_;
    }
    
    //disabled constructors & operators
    ObjectGroup() = delete;
    ObjectGroup(const ObjectGroup& obj) = delete;    // copy
    ObjectGroup(ObjectGroup&& obj) = delete;        // move
    ObjectGroup& operator = (const ObjectGroup& obj) = delete;    // copy operator
    ObjectGroup& operator = (ObjectGroup&& obj) = delete;        // move operator
};
