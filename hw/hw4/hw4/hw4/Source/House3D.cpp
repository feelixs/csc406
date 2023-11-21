//
//  House3D.cpp
//  hw4
//
//  Created by Michael Felix on 11/21/23.
//

#include "House3D.h"
#include "common.h"
#include <math.h>
using namespace graphics3d;

const unsigned int House3D::numVertices_ = 14;
const unsigned int House3D::numFaces_ = 12;


House3D::House3D(float scaleX, float scaleY, const Pose& pose, const Motion& motion)
:   GraphicObject3D(pose, motion),
    XYZ_(nullptr),
    scaleX_(scaleX),
    scaleY_(scaleY)
{
    XYZ_ = new GLfloat**[numFaces_+1];
    for (unsigned int i=0; i<=numFaces_; i++)
    {
        XYZ_[i] = new GLfloat*[numVertices_];
        for (unsigned int j=0; j<numVertices_; j++)
        {
            XYZ_[i][j] = new GLfloat[3];
        }
    }
   
    for (unsigned int j=0; j<numVertices_; j++)
    {
        float theta = 2*j*M_PI/numVertices_;
        float ct = cosf(theta), st = sinf(theta);
        
        for (unsigned int i=0; i<=numFaces_; i++)
        {
            XYZ_[i][j][0] = scaleX_*ct;
            XYZ_[i][j][1] = scaleY_*st;
            XYZ_[i][j][2] = scaleY_*i/numFaces_;
        }
        

    }
}


House3D::~House3D() {
    for (unsigned int i=0; i<numFaces_; i++)
    {
        for (unsigned int j=0; j<numVertices_; j++)
        {
            delete []XYZ_[i][j];
        }
        delete []XYZ_[i];
    }
    delete []XYZ_;
}


void House3D::draw() const
{
    glPushMatrix();
    applyPose();

    setCurrentMaterial(getMaterial());

    for (unsigned int i=0; i<numFaces_; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
            for (unsigned int j=0; j<numVertices_; j++)
            {
                glVertex3fv(XYZ_[i][j]);
                glVertex3fv(XYZ_[i+1][j]);
            }
            
        glEnd();
    }

    glPopMatrix();
}
