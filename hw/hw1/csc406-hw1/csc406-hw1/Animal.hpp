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
bool initAnimal();
bool initCircle();


class Animal
{
    friend void loadShape(const char* filename);
    friend bool initCircle();
    
    private:
        float centerX_, centerY_, scaleX_, scaleY_, angle_;
        float red_, green_, blue_;
    
        // shape points of circle calculated in initCircle()
        static float** _circlePoints;
        static const int _numCirPoints;
    
        // shape points loaded from file shapeCoords.txt in loadShape()
        static int _numLoadedPnts;
        static const int _maxLoadedPnts;
        static float** _loadedShapePnts;
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
