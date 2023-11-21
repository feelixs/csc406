//
//  House3D.hpp
//  hw4
//
//  Created by Michael Felix on 11/21/23.
//

#ifndef House3D_h
#define House3D_h

#include "GraphicObject3D.h"
#include "common.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>


namespace graphics3d {
class House3D: public GraphicObject3D {
private:
    float scaleX_, scaleY_;
    
    static std::vector<unsigned int> faceVertexCounts_;
    static unsigned int numFaces_;
    
    GLfloat*** XYZ_;
    
    void initFromFile_(const char* fp);
    void initFromVectors_(std::vector<std::vector<float>>& vertices, std::vector<std::vector<int>>& faces);
    
public:
    House3D(float scaleX, float scaleY, const Pose& pose, const Motion& motion = Motion::NULL_MOTION);
    
    ~House3D();
    
    House3D(const House3D& obj) = delete;
    House3D& operator =(const House3D& obj) = delete;
    House3D(House3D&& obj) = delete;
    House3D& operator =(House3D&& obj) = delete;
    House3D() = delete;

    void draw() const;
};

}

#endif /* House3D_h */
