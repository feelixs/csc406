/*----------------------------------------------------------------------------------+
 |																					|
 |	Vehicle4.h		Trajectory generation by polynomial fitting						|
 |																					|
 |	Author:		Jean-Yves Hervé,	University of Rhode Island						|
 |									Dept. of Computer Science and Statistics		|
 |									3D Group for Interactive Visualization			|
 |	Fall 2010, rev. Fall 2022														|
 +---------------------------------------------------------------------------------*/
 
#ifndef VEHICLE4_H
#define VEHICLE4_H

#include "glPlatform.h"

#include <vector>

//-----------------------------------------------------
//  Polynomial fit
//-----------------------------------------------------


class Vehicle4 {

    public:
        
        Vehicle4(void);
        
        ~Vehicle4(void);
        
        void update(float t);
        void draw();
        
        void setPosition(GLfloat theX, GLfloat theY);

        void setOrientation(GLfloat theAngle);

		Vehicle4(const Vehicle4& obj) = delete;
		Vehicle4(Vehicle4&& obj) = delete;
		Vehicle4& operator = (const Vehicle4& obj) = delete;
		Vehicle4& operator = (Vehicle4&& obj) = delete;

	private:
    
        GLfloat _x, _y, _angle;
        float _ut;

        //  I record the path just for the demo.  
        std::vector<GLfloat*> _path;     
        bool _recordPath;
        
        GLfloat** _a;       //  arrays of coefficients of the polynomial
		
	
};        


#endif
