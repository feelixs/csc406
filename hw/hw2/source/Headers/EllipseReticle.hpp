//
//  OutlineEllipse.hpp
//  hw2
//
//  Created by Michael Felix on 10/12/23.
//

#ifndef OutlineEllipse_HPP
#define OutlineEllipse_HPP


#include "GraphicObject.h"
#include "glPlatform.h"
#include "World.h"


class EllipseReticle : public GraphicObject
{
    private:
        float radiusX_, radiusY_;
        float red_, green_, blue_;
            
        const int numCirclePts_;
        static float** circlePts_;

    public:
    
        EllipseReticle(Point centerpnt, float radius, float r, float g, float b, int numPoints);
        ~EllipseReticle() = default;
        
        void draw() const;

        //disabled constructors & operators
        EllipseReticle() = delete;
        EllipseReticle(const EllipseReticle& obj) = delete;    // copy
        EllipseReticle(EllipseReticle&& obj) = delete;        // move
        EllipseReticle& operator = (const EllipseReticle& obj) = delete;    // copy operator
        EllipseReticle& operator = (EllipseReticle&& obj) = delete;        // move operator
};

#endif // OutlineEllipse_HPP
