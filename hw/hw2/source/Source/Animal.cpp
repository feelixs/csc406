//
//  Animal.cpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#include "Animal.hpp"
#include <iostream>


float** Animal::_loadedShapePnts;
float** Animal::_circlePoints;
const int Animal::_numCirPoints = 12;
float** Animal::_trianPoints;
const int numTrianPts = 3;

Animal::Animal(Point centerPoint, float angle, float scale, float red, float green, float blue)
:   GraphicObject(centerPoint.x, centerPoint.y, angle),
    scaleX_(scale),
    scaleY_(scale),
    red_(red),
    green_(green),
    blue_(blue)
{
    _init_();
}


Animal::Animal(float centerX, float centerY, float angle, float scaleX, float scaleY, float red, float green, float blue)
// Animal _init_() will use World::Point to initialize its shapes, regardless of which constructor is used
    :   GraphicObject(centerX, centerY, angle),
        scaleX_(scaleX),
        scaleY_(scaleY),
        red_(red),
        green_(green),
        blue_(blue)
{
    _init_();
}


void Animal::_init_() {
    // calculate circle points
    _circlePoints = new float*[_numCirPoints];
    for (int k=0; k < _numCirPoints; k++) {
        _circlePoints[k] = new float[2];
    }
    float angleStep = 2.f*M_PI/_numCirPoints;
    float theta;
    for (int k=0; k<_numCirPoints; k++) {
        theta = k*angleStep;
        _circlePoints[k][0] = cosf(theta);
        _circlePoints[k][1] = sinf(theta);
    }
    circleVertices_ = glGenLists(1);
    glNewList(circleVertices_, GL_COMPILE);
    glBegin(GL_POLYGON);
    for (int k=0; k < _numCirPoints; k++) {
        glVertex2f(_circlePoints[k][0], _circlePoints[k][1]);
    }
    glEnd();
    glEndList();
    
    // calculate triangle points
    _trianPoints = new float*[numTrianPts];
    for (int i = 0; i < numTrianPts; i++) {
        _trianPoints[i] = new float[2];
    }
    float width = 5.f;
    float height = width * sqrt(3.f);

    // vertex 1
    _trianPoints[0][0] = 0;
    _trianPoints[0][1] = height / 2.f;
    // vertex 2
    _trianPoints[1][0] =  -width;
    _trianPoints[1][1] = -height / 2.f;
    // vertex 3
    _trianPoints[2][0] = width;
    _trianPoints[2][1] = -height / 2.f;
    
    triangleVertices_ = glGenLists(1);
    glNewList(triangleVertices_, GL_COMPILE);
    glBegin(GL_POLYGON);
    for (int k=0; k<numTrianPts; k++) {
        glVertex2f(_trianPoints[k][0], _trianPoints[k][1]);
    }
    glEnd();
    glEndList();
}

void Animal::draw() const {
    float atx = getX();
    float aty = getY();
    float atangle = getAngle();
    float r = red_;
    float g = green_;
    float b = blue_;
    float scale = scaleX_;
    Point thisShapeCenter = Point{atx, aty};
    
    // right wing
    static float rightWing[5][2] = {{0.76f, 0.38f}, {0.66f, 0.1f}, {0.65f, 0.f}, {0.83f, 0.f}, {0.9f, -0.2f}};
    Point posWOffset = Point{atx + (scale/10.f), aty + (scale/1.6f)};  // all animal shapes have constant offsets
    posWOffset.rotateAround(&thisShapeCenter, getAngle());
    glPushMatrix();
    glTranslatef(posWOffset.x, posWOffset.y, 0.f);
    glRotatef(atangle-10.f, 0.f, 0.f, 1.f);
    glScalef(scale, scale, 1.f);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int k=0; k<5; k++) {
        glVertex2f(rightWing[k][0], rightWing[k][1]);
    }
    glEnd();
    glPopMatrix();

    // left wing
    static float leftWing[5][2] = {{-0.76f, 0.38f}, {-0.66f, 0.1f}, {-0.65f, 0.f}, {-0.83f, 0.f}, {-0.9f, -0.2f}};
    posWOffset = Point{atx - (scale/10.f), aty + (scale/1.6f)};
    posWOffset.rotateAround(&thisShapeCenter, getAngle());
    glPushMatrix();
    glTranslatef(posWOffset.x, posWOffset.y, 0.f);
    glRotatef(atangle + 10.f, 0.f, 0.f, 1.f);
    glScalef(scale, scale, 1.f);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int k=0; k<5; k++) {
        glVertex2f(leftWing[k][0], leftWing[k][1]);
    }
    glEnd();
    glPopMatrix();
    
    // two half-circles at different angles (face/body)
    static float halfCircle[10][2] = {{1.f, 0.f}, {0.9510565162951535f, 0.3090169943749474f}, {0.8090169943749475f, 0.5877852522924731f}, {0.5877852522924731f, 0.8090169943749475f}, {0.30901699437494745f, 0.9510565162951535f}, {6.123233995736766e-17f, 1.f}, {-0.30901699437494734f, 0.9510565162951536f}, {-0.587785252292473f, 0.8090169943749475}, {-0.8090169943749473f, 0.5877852522924732f}, {-0.9510565162951535f, 0.3090169943749475}};
    posWOffset = Point{atx, aty};
    glPushMatrix();
    glTranslatef(posWOffset.x, posWOffset.y, 0.f);
    glRotatef(atangle + 4.f, 0.f, 0.f, 1.f);
    glScalef(scale, scale, 1.f);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int k=0; k<10; k++) {
        glVertex2f(halfCircle[k][0], halfCircle[k][1]);
    }
    glEnd();
    glPopMatrix();
    posWOffset = Point{atx, aty};
    glPushMatrix();
    glTranslatef(posWOffset.x, posWOffset.y, 0.f);
    glRotatef(atangle + 14.f, 0.f, 0.f, 1.f);
    glScalef(scale, scale, 1.f);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int k=0; k<10; k++) {
        glVertex2f(halfCircle[k][0], halfCircle[k][1]);
    }
    glEnd();
    glPopMatrix();
    
    // left eye
    posWOffset = Point{atx + (scaleX_/2.4f), aty + (scaleY_/1.9f)};
    posWOffset.rotateAround(&thisShapeCenter, getAngle());
    glPushMatrix();
    glTranslatef(posWOffset.x, posWOffset.y, 0.f);
    glRotatef(atangle, 0.f, 0.f, 1.f);
    glScalef(scale/8.f, scale/8.f, 1.f);
    glColor3f(0.f, 0.f, 0.f);
    glCallList(circleVertices_);
    glPopMatrix();
    
    // left eyeball
    posWOffset = Point{atx + (scaleX_/2.5f), aty + (scaleY_/1.8f)};
    posWOffset.rotateAround(&thisShapeCenter, getAngle());
    glPushMatrix();
    glTranslatef(posWOffset.x, posWOffset.y, 0.f);
    glRotatef(atangle, 0.f, 0.f, 1.f);
    glScalef(scale/28.f, scale/28.f, 1.f);
    glColor3f(1.f, 1.f, 1.f);
    glCallList(circleVertices_);
    glPopMatrix();

    // right eye
    posWOffset = Point{atx - (scaleX_/2.4f), aty + (scale/1.9f)};
    posWOffset.rotateAround(&thisShapeCenter, getAngle());
    glPushMatrix();
    glTranslatef(posWOffset.x, posWOffset.y, 0.f);
    glRotatef(atangle, 0.f, 0.f, 1.f);
    glScalef(scale/8.f, scale/8.f, 1.f);
    glColor3f(0.f, 0.f, 0.f);
    glCallList(circleVertices_);
    glPopMatrix();
    
    // right eyeball
    posWOffset = Point{atx - (scaleX_/2.3f), aty + (scaleY_/1.8f)};
    posWOffset.rotateAround(&thisShapeCenter, getAngle());
    glPushMatrix();
    glTranslatef(posWOffset.x, posWOffset.y, 0.f);
    glRotatef(atangle, 0.f, 0.f, 1.f);
    glScalef(scale/28.f, scale/28.f, 1.f);
    glColor3f(1.f, 1.f, 1.f);
    glCallList(circleVertices_);
    glPopMatrix();
    
    // nose
    posWOffset = Point{atx, aty + (scaleY_/4.f)};
    posWOffset.rotateAround(&thisShapeCenter, getAngle());
    glPushMatrix();
    glTranslatef(posWOffset.x, posWOffset.y, 0.f);
    glRotatef(atangle + 180.f, 0.f, 0.f, 1.f);
    glScalef(scale/40.f, scale/20.f, 1.f);
    glColor3f(1.f, 1.f, 1.f);
    glCallList(triangleVertices_);
    glPopMatrix();
}


void Animal::update(float dt) {
    setAngle(getAngle()+0.5);
    //setX(getX()+0.01);
}
