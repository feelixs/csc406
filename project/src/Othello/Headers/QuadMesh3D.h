//
//  QuadMesh.hpp
//  Week 10 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-02.
//

#ifndef QUAD_MESH_3D_H
#define QUAD_MESH_3D_H

#include <memory>
#include "GraphicObject3D.h"

namespace graphics3d
{
    /**    A Quad3D has weight and height dimensions in a plane perpendicular
     *    to the Z axis.
     */
    class QuadMesh3D : public GraphicObject3D
    {
        private:
        
            float width_;
            float height_;
            unsigned int numRows_;
            unsigned int numCols_;
            //    Switching back to a pointer, but I make it a 3D array
            //    numRows x numCols x 3
            GLfloat*** XYZ_;
            GLfloat*** normal_;
            
        public:
        
            QuadMesh3D(float width, float height, unsigned int numRows, unsigned int numCols, const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

            QuadMesh3D(float width, float height, unsigned int numRows, unsigned int numCols, float perturbationAmplitude, const Pose& pose, const Motion& motion = Motion::NULL_MOTION);
    
            ~QuadMesh3D();
            
            QuadMesh3D(const QuadMesh3D& obj) = delete;
            QuadMesh3D& operator =(const QuadMesh3D& obj) = delete;
            QuadMesh3D(QuadMesh3D&& obj) = delete;
            QuadMesh3D& operator =(QuadMesh3D&& obj) = delete;
            QuadMesh3D() = delete;

            void draw() const;
            
            inline float getWidth()
            {
                return width_;
            }
            
            inline float getHeight()
            {
                return height_;
            }
            
            void displaceVertex(unsigned int row, unsigned int col, float dZ);
            
            void faceNormal(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLfloat* v4,
                            float normal[]) const;
    };
}

#endif //    QUAD_MESH_3D_H
