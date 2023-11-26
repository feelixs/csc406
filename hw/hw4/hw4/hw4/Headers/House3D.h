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
    
    /// stores the number of vertices for each face
    static std::vector<unsigned int> faceVertexCounts_;
    static unsigned int numFaces_;
    GLfloat*** XYZ_;
    
    /// Load the shape from an obj file
    /// @param fp the system filepath to the .obj file
    void initFromFile_(const char* fp);
    
    /// Load the shape from vectors containing vertex points and faces pointing to the vertex indices
    /// @param vertices a list of vertex points, where each vector index is 3 floating points {x, y, x}
    /// @param faces a list of int lists vect<vect<int>> where each index of the int vector refers to an index of the vertices vect (just like how obj files work)
    void initFromVectors_(std::vector<std::vector<float>>& vertices, std::vector<std::vector<int>>& faces);
    
    /// if the obj file provided to this class is invalid, revert to this init
    void defaultInit_();
    
public:
    House3D(float scaleX, float scaleY, const Pose& pose, const Motion& motion = Motion::NULL_MOTION);
    House3D(const char* filepath, float scaleX, float scaleY, const Pose& pose, const Motion& motion =  Motion::NULL_MOTION);
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
