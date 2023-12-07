//
//  Cylinder3D.cpp
//  Week 09 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-07.
//

#include "Cylinder3D.h"

using namespace std;
using namespace graphics3d;


const shared_ptr<Cylinder3D> UNIT_CYLINDER_OPEN = make_shared<Cylinder3D>(
                1.f, 1.f, 1.f, 12, 12, false,
                Pose{0.f, 0.f, 0.f});
const shared_ptr<Cylinder3D> UNIT_CYLINDER_CLOSED = make_shared<Cylinder3D>(
                1.f, 1.f, 1.f, 12, 12, true,
                Pose{0.f, 0.f, 0.f});
            
Cylinder3D::Cylinder3D(float radiusX, float radiusY, float height,
                        unsigned int numCirclePts, unsigned int numRings,
                        bool isClosed,
                        const Pose& pose, const Motion& motion)
    :    GraphicObject3D(pose, motion),
        //
        radiusX_(radiusX),
        radiusY_(radiusY),
        height_(height),
        numCirclePts_(numCirclePts),
        numRings_(numRings),
        isClosed_(isClosed),
        XYZ_(nullptr),
        normals_(nullptr),
        topNormal_(nullptr),
        bottomNormal_(nullptr)
{
    initMeshAndNormals_();
}

Cylinder3D::Cylinder3D(float radius, float height,
                        unsigned int numCirclePts, unsigned int numRings,
                        bool isClosed,
                        const Pose& pose, const Motion& motion)
    :    Cylinder3D(radius, radius, height, numCirclePts, numRings,
                   isClosed, pose, motion)
{}

Cylinder3D::~Cylinder3D()
{
    for (unsigned int i=0; i<numRings_; i++)
    {
        for (unsigned int j=0; j<numCirclePts_; j++)
        {
            delete []XYZ_[i][j];
        }
        delete []XYZ_[i];
    }
    delete []XYZ_;

    for (unsigned int j=0; j<numCirclePts_; j++)
    {
        delete []normals_[j];
    }
    delete []normals_;

    if (isClosed_)
    {
        delete [] topNormal_;
        delete [] bottomNormal_;
    }
}


void Cylinder3D::draw() const
{
    glPushMatrix();
    applyPose();

    setCurrentMaterial(getMaterial());

    //    draw all the rings
    for (unsigned int i=0; i<numRings_; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
            for (unsigned int j=0; j<numCirclePts_; j++)
            {
                glNormal3fv(normals_[j]);
                glVertex3fv(XYZ_[i][j]);
                glNormal3fv(normals_[j]);
                glVertex3fv(XYZ_[i+1][j]);
            }
            // close the ring
            glNormal3fv(normals_[0]);
            glVertex3fv(XYZ_[i][0]);
            glNormal3fv(normals_[0]);
            glVertex3fv(XYZ_[i+1][0]);
            
        glEnd();
    }
    
    //    If the cylinder is closed, we have to draw the top and bottom sides
    if (isClosed_)
    {
        //    top
        //-----------------------------------
        glBegin(GL_TRIANGLE_FAN);
            //    center
            glNormal3fv(topNormal_);
            glVertex3f(0.f, 0.f, height_);

            glNormal3fv(topNormal_);
            glVertex3fv(XYZ_[numRings_][0]);

            //    For whatever reason, fans list vertices in clockwise order [???]
            for (unsigned int j=0, jp=numCirclePts_-1; j<numCirclePts_; j++, jp--)
            {
                glNormal3fv(topNormal_);
                glVertex3fv(XYZ_[numRings_][jp]);
            }
        glEnd();
        
        //    bottom
        //-----------------------------------
        glBegin(GL_TRIANGLE_FAN);
            //    center
            glNormal3fv(bottomNormal_);
            glVertex3f(0.f, 0.f, 0.f);
            for (unsigned int j=0; j<numCirclePts_; j++)
            {
                glNormal3fv(bottomNormal_);
                glVertex3fv(XYZ_[0][j]);
            }
            glNormal3fv(bottomNormal_);
            glVertex3fv(XYZ_[0][0]);
        glEnd();
    }

    glPopMatrix();
}

void Cylinder3D::initMeshAndNormals_()
{
    //    Allocate arraus of vertex coordinates and normals
    XYZ_ = new GLfloat**[numRings_+1];
    for (unsigned int i=0; i<=numRings_; i++)
    {
        XYZ_[i] = new GLfloat*[numCirclePts_];
        for (unsigned int j=0; j<numCirclePts_; j++)
        {
            XYZ_[i][j] = new GLfloat[3];
        }
    }
    normals_ = new GLfloat*[numCirclePts_];
    for (unsigned int j=0; j<numCirclePts_; j++)
    {
        normals_[j] = new GLfloat[3];
    }
    
    //    Now initialize the vertex and normal coordinates
    //    Here I work with the ring as outer loop
    for (unsigned int j=0; j<numCirclePts_; j++)
    {
        float theta = 2*j*M_PI/numCirclePts_;
        float ct = cosf(theta), st = sinf(theta);
        
        for (unsigned int i=0; i<=numRings_; i++)
        {
            XYZ_[i][j][0] = radiusX_*ct;
            XYZ_[i][j][1] = radiusY_*st;
            XYZ_[i][j][2] = height_*i/numRings_;
        }
        
        //    the normals are constant along a slab
        normals_[j][0] = ct*radiusY_;
        normals_[j][1] = -st*radiusX_;
        normals_[j][2] = 0.f;
    }
    
    //    And take care of top and bottom sides if the cylinder is closed
    if (isClosed_)
    {
        topNormal_ = new GLfloat[3];
        bottomNormal_ = new GLfloat[3];
        topNormal_[0] = topNormal_[1] = bottomNormal_[0] = bottomNormal_[1] = 0.f;
        topNormal_[2] = 1.f;
        bottomNormal_[2] = -1.f;
    }
}
