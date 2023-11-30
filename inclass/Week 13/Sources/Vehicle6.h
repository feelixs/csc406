/*----------------------------------------------------------------------------------+
 |																					|
 |	Vehicle6.h	Trajectory generation by linear interpolation with					|
 |					slope-continuity-preserving parabolic connections about			|
 |					the waypoints													|
 |																					|
 |	Author:		Jean-Yves Hervé,	University of Rhode Island						|
 |									Dept. of Computer Science and Statistics		|
 |									3D Group for Interactive Visualization			|
 |	Fall 2009, rev. Fall 2022														|
 +---------------------------------------------------------------------------------*/
 
#ifndef VEHICLE6_H
#define VEHICLE6_H

#include "glPlatform.h"
#include <vector>

//-----------------------------------------------------
//  Parabolic Connections
//-----------------------------------------------------

class Vehicle6 {

    public:
        
        Vehicle6(void);
        
        ~Vehicle6(void);
        
        void update(float t);
        
        void draw();
        
        void setPosition(GLfloat theX, GLfloat theY);

        void setOrientation(GLfloat theAngle);

		Vehicle6(const Vehicle6& obj) = delete;
		Vehicle6(Vehicle6&& obj) = delete;
		Vehicle6& operator = (const Vehicle6& obj) = delete;
		Vehicle6& operator = (Vehicle6&& obj) = delete;

private:

        float _ut;
        GLfloat _x, _y;
        GLfloat _angle;        
        
        GLfloat ***_a;   //  will store the coefficients of the parabolic segments;
        
        //  I record the path just for the demo.  
        std::vector<GLfloat*> _path;     
        bool _recordPath;
        
};        


#endif
