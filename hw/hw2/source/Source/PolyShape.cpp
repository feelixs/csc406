//
//  PolyShape.cpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#include "PolyShape.hpp"
#include <iostream>
#include "glPlatform.h"


PolyShape::PolyShape(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue)
:   GraphicObject(centerX, centerY, angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue)
{
}

PolyShape::PolyShape(Point centerPoint, float angle, float scaleX, float scaleY, float red, float green, float blue)
:   GraphicObject(centerPoint.x, centerPoint.y, angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue)
{
}

PolyShape::PolyShape(Point centerPoint, float angle, float scaleX, float scaleY, float red, float green, float blue, GLuint vertices)
:   GraphicObject(centerPoint.x, centerPoint.y, angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue),
        vertexList(vertices)
{
}

PolyShape::~PolyShape() {
}



void PolyShape::draw() const
{
    //    save the current coordinate system (origin, axes, scale)
    glPushMatrix();
    
    //    move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);
        
    // apply rotation
    glRotatef(getAngle(), 0.f, 0.f, 1.f);
    
    //    apply the radius as a scale
    glScalef(getScaleX(), getScaleY(), 1.f);
    
    glColor3f(getRed(), getGreen(), getBlue());
    
    glCallList(vertexList);
    
    //    restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

void PolyShape::update(float dt) {
    setAngle(getAngle() + spin_ * dt);
}
