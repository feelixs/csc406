//
//  Ellipse.hpp
//  CSC406-inclass
//
//  Created by Michael Felix on 9/14/23.
//

#ifndef Ellipse_hpp  // prevent duplicate loading of this header
#define Ellipse_hpp

#include <stdio.h>


class Ellipse {
private:
    float _centerX, _centerY, _radiusX, _radiusY, _angle;
    float _red, _green, _blue;
    
public:
    Ellipse(float centerX, float centerY, float angle, float radiusX, float radiusY, float r, float g, float b);
    
    void draw() const; // const = this function is unable to modify the parent object
    
};


#endif /* Ellipse_hpp */
