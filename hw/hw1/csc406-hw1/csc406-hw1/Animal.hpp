//
//  Animal.hpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#ifndef Animal_hpp
#define Animal_hpp

#include <stdio.h>

void loadShape(const char* filename); // returns the amount of vertices in the loaded file

class Animal
{
    friend int loadShape();
    
    private:
        float centerX_, centerY_, scaleX_, scaleY_, angle_;
        float red_, green_, blue_;

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
