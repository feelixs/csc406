//
//  QuadMesh.cpp
//  Week 10 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-02.
//

#include <random>
#include "QuadMesh3D.h"

using namespace graphics3d;
using namespace std;

QuadMesh3D::QuadMesh3D(float width, float height, unsigned int numRows, unsigned int numCols,
                       const Pose& pose, const Motion& motion)
    :    GraphicObject3D(pose, motion),
        width_(width),
        height_(height),
        numRows_(numRows),
        numCols_(numCols),
        XYZ_(new GLfloat**[numRows]),
        normal_(nullptr)
{
    for (unsigned int i=0; i<numRows; i++)
    {
        XYZ_[i] = new GLfloat*[numCols];
        for (unsigned int j=0; j<numCols; j++)
        {
            XYZ_[i][j] = new GLfloat[3];
        }
    }
    
    //    My indices (0, 0) start from bottom left of the mesh
    const GLfloat stepX = width / (numCols-1);
    const GLfloat stepY = height / (numRows-1);
    for (unsigned int i=0; i<numRows; i++)
    {
        const GLfloat y = -0.5f*height + i*stepY;
        for (unsigned int j=0; j<numCols; j++)
        {
            //    X
            XYZ_[i][j][0] = -0.5f*width + j*stepX;
            // Y same for all row
            XYZ_[i][j][1] = y;
            //    Z is zero all over the mesh
            XYZ_[i][j][2] = 0.f;
        }
    }
}

QuadMesh3D::QuadMesh3D(float width, float height, unsigned int numRows, unsigned int numCols,
                       float perturbationAmplitude, const Pose& pose, const Motion& motion)
    : QuadMesh3D(width, height, numRows, numCols, pose, motion)
{
    normal_ = new GLfloat**[numRows];
    for (unsigned int i=0; i<numRows; i++)
    {
        normal_[i] = new GLfloat*[numCols];
        for (unsigned int j=0; j<numCols; j++)
        {
            normal_[i][j] = new GLfloat[3];
        }
    }

    // let's perturn the Z component
    random_device myRandDev;
    default_random_engine myEngine(myRandDev());
    normal_distribution<float> perturbationDist(0.f, perturbationAmplitude/2);
        
    for (unsigned int i=0; i<numRows; i++)
    {
        for (unsigned int j=0; j<numCols; j++)
        {
            XYZ_[i][j][2] += perturbationDist(myEngine);
        }
    }
    
    // compute the vertex normals
}


QuadMesh3D::~QuadMesh3D()
{
    for (unsigned int i=0; i<numRows_; i++)
    {
        for (unsigned int j=0; j<numCols_; j++)
        {
            delete []XYZ_[i][j];
        }
        delete []XYZ_[i];
    }
    delete []XYZ_;
}

void QuadMesh3D::draw() const
{
    glPushMatrix();
    applyPose();

    drawReferenceFrame();
    
    setCurrentMaterial(getMaterial());
    for (unsigned int i=0; i<numRows_-1; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (unsigned int j=0; j<numCols_; j++)
        {
            glVertex3fv(XYZ_[i][j]);
            glVertex3fv(XYZ_[i+1][j]);
        }
        glEnd();
    }
    glPopMatrix();
}
    
void QuadMesh3D::displaceVertex(unsigned int row, unsigned int col, float dZ)
{
    if ((row < numRows_) && (col < numCols_))
        XYZ_[row][col][2] += dZ;
        
}

void QuadMesh3D::faceNormal(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLfloat* v4,
                float normal[]) const
{
    // compute the coordomates of vectors between vertices
    float dV12[] = {v1[0] - v2[0], v1[1] - v2[2], v1[2] - v2[2]};
    float dV34[] = {v3[0] - v4[0], v3[1] - v4[2], v3[2] - v4[2]};
    
    // compute crossproduct
    normal[0] = dV12[1]*dV34[2] - dV34[1]*dV12[2];
    normal[1] = dV12[2]*dV34[0] - dV34[2]*dV12[0];
    normal[2] = dV12[0]*dV34[1] - dV34[0]*dV12[1];
    
    // normalize
    float norm = sqrtf(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
    normal[0] /= norm;
    normal[1] /= norm;
    normal[2] /= norm;
}
