//
//  Animal.hpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#ifndef Animal_hpp
#define Animal_hpp

#include <stdio.h>

bool loadAnimal(const char* filename);
bool initAnimal(const char* coordFile);
bool initACircle();
bool initAStraightLine();


class Animal
{
    friend bool loadAnimal(const char* filename);
    friend bool initACircle();
    friend bool initAStraightLine();
    
    private:
        float centerX_, centerY_, scaleX_, scaleY_, angle_;
        float red_, green_, blue_;
    
        // shape points of circle calculated in initCircle()
        static float** _circlePoints; // Nx2 float
        static const int _numCirPoints;
    
        // shape points loaded from file shapeCoords.txt in loadShape()
        static int _numLoadedPnts;
        static const int _maxLoadedPnts;
        static float** _loadedShapePnts; // Nx2 float
    
        // points for straight line
        static float** _straightLinePoints; // 2x2 float
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
