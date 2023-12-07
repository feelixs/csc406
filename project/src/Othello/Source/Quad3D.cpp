//
//  Quad3D.cpp
//  Week 10 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-02.
//

#include "drawingUtilities.h"
#include "Quad3D.h"

using namespace graphics3d;

Quad3D::Quad3D(float width, float height, const Pose& pose, const Motion& motion)
    :    GraphicObject3D(pose, motion),
        width_(width),
        height_(height)
{}


void Quad3D::draw() const
{
    glPushMatrix();
    applyPose();
    drawReferenceFrame();
    
    setCurrentMaterial(getMaterial());
    glBegin(GL_POLYGON);
        glVertex3f(-0.5f*width_, -0.5f*height_, 0.f);
        glVertex3f(+0.5f*width_, -0.5f*height_, 0.f);
        glVertex3f(+0.5f*width_, +0.5f*height_, 0.f);
        glVertex3f(-0.5f*width_, +0.5f*height_, 0.f);
    glEnd();
    
    glPopMatrix();
}
            


