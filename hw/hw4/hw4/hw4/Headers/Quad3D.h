//
//  Quad3D.h
//  Week 10 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-02.
//

#ifndef QUAD_3D_H
#define QUAD_3D_H

#include "GraphicObject3D.h"

namespace graphics3d
{
    /**    A Quad3D has weight and height dimensions in a plane perpendicular
     *    to the Z axis.
     */
    class Quad3D : public GraphicObject3D
    {
        private:
        
            float width_, height_;
            
        public:
        
            Quad3D(float width, float height, const Pose& pose, const Motion& motion = Motion::NULL_MOTION);
    
            ~Quad3D() = default;
            //    I allow copy for a change
            Quad3D(const Quad3D& obj) = default;
            Quad3D& operator =(const Quad3D& obj) = default;
            //but still not move
            Quad3D(Quad3D&& obj) = delete;
            Quad3D& operator =(Quad3D&& obj) = delete;
            Quad3D() = delete;

            void draw() const;
            
            inline float getWidth()
            {
                return width_;
            }
            
            inline float getHeight()
            {
                return height_;
            }
    };
}

#endif //    QUAD_3D_H
