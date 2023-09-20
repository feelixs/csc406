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
friend bool ellipseInit();
private:
    
    float _centerX, _centerY, _radiusX, _radiusY, _angle;
    float _red, _green, _blue;

    static const int _numCirclePts;
    static float** _circlePts;
public:
    Ellipse(float centerX, float centerY, float angle, float radiusX, float radiusY, float r, float g, float b);
    ~Ellipse() = default;
    
    void draw() const; // const = this function is unable to modify the parent object
    
    //disabled constructors & operators
            Ellipse() = delete;
            Ellipse(const Ellipse& obj) = delete;    // copy
            Ellipse(Ellipse&& obj) = delete;        // move
            Ellipse& operator = (const Ellipse& obj) = delete;    // copy operator
            Ellipse& operator = (Ellipse&& obj) = delete;        // move operator

    
};

bool ellipseInit();

#endif /* Ellipse_hpp */
