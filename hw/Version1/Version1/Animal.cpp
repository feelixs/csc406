//
//  Animal.cpp
//  Version1
//
//  Created by Michael Felix on 9/27/23.
//

#include "Animal.hpp"
#include <iostream>
#include <math.h>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "glPlatform.h"


float** Animal::_pointList;
const int Animal::_numCirPoints = 12;
const bool animalInitted = initAnimal();

bool initAnimal() {
    bool mainCircle = initCircle();
    return mainCircle;
}

bool initCircle() {
    Animal::_pointList = new float*[Animal::_numCirPoints];
    for (int k=0; k<Animal::_numCirPoints; k++) {
        Animal::_pointList[k] = new float[2];
    }
    float angleStep = 2.f*M_PI/Animal::_numCirPoints;
    float theta;
    for (int k=0; k<Animal::_numCirPoints; k++) {
        theta = k*angleStep;
        Animal::_pointList[k][0] = cosf(theta);
        Animal::_pointList[k][1] = sinf(theta);
    }
    return true;
}

Animal::Animal(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue)
    :    centerX_(centerX),
        centerY_(centerY),
        angle_(angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue)
{
}

Animal::~Animal()
{
    std::cout << "Animal at " << centerX_ << ", " << centerY_ << " was deleted" << std::endl;
}



void Animal::draw() const
{
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(centerX_, centerY_, 0.f);
        
    // apply rotation
    glRotatef(angle_, 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(scaleX_, scaleY_, 1.f);
    
    glColor3f(red_, green_, blue_);
    
    glBegin(GL_POLYGON);
    for (int i=0; i<_numCirPoints; i++) {
        //cout << k << "; " << shapePntBuff[k][0] << ", " << shapePntBuff[k][1]<< endl;
    
        glVertex2f(_pointList[i][0], _pointList[i][1]);
        //std::cout << shapePntBuff[k][0] << ", " << shapePntBuff[k][1] << std::endl;
    }
    glEnd();
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

