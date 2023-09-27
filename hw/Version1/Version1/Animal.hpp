//
//  Animal.hpp
//  Version1
//
//  Created by Michael Felix on 9/27/23.
//

#ifndef Animal_hpp
#define Animal_hpp

#include <stdio.h>

bool initAnimal();
bool initCircle();

class Animal
{
    friend bool initCircle();
    private:
        float centerX_, centerY_, scaleX_, scaleY_, angle_;
        float red_, green_, blue_;
        static float** _pointList;
        static const int _numCirPoints;
    public:
        Animal(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
        ~Animal();
        
        void draw() const;

        //disabled constructors & operators
        Animal() = delete;
        Animal(const Animal& obj) = delete;    // copy
        Animal(Animal&& obj) = delete;        // move
        Animal& operator = (const Animal& obj) = delete;    // copy operator
        Animal& operator = (Animal&& obj) = delete;        // move operator
};

#endif /* Animal_hpp */
