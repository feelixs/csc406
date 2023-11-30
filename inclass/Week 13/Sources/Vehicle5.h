/*----------------------------------------------------------------------------------+
 |																					|
 |	Vehicle5.h		Trajectory generation by cubic spline fitting					|
 |																					|
 |	Author:		Jean-Yves Hervé,	University of Rhode Island						|
 |									Dept. of Computer Science and Statistics		|
 |									3D Group for Interactive Visualization			|
 |	Fall 2009, rev. Fall 2022														|
 +---------------------------------------------------------------------------------*/
 
#ifndef VEHICLE5_H
#define VEHICLE5_H

#include "glPlatform.h"

#include <vector>

//-----------------------------------------------------
//  Polynomial fit
//-----------------------------------------------------


class Vehicle5 {

    public:
        
        Vehicle5(void);
        
        ~Vehicle5(void);
        
        void update(float t);
        void draw();
        
        void setPosition(GLfloat theX, GLfloat theY);

        void setOrientation(GLfloat theAngle);

		Vehicle5(const Vehicle5& obj) = delete;
		Vehicle5(Vehicle5&& obj) = delete;
		Vehicle5& operator = (const Vehicle5& obj) = delete;
		Vehicle5& operator = (Vehicle5&& obj) = delete;


	private:
    
        GLfloat _x, _y, _angle;
        float _ut;

        //  I record the path just for the demo.  
        std::vector<GLfloat*> _path;     
        bool _recordPath;
        
        GLfloat ***_a;       //  arrays of coefficients of the polynomials (1 per segment)


};        


#endif
