/*----------------------------------------------------------------------------------+
 |																					|
 |	Vehicle.h	Class for general vehicle objects controled by a keyframe animator	|									|
 |																					|
 |	Author:		Jean-Yves Hervé,	University of Rhode Island						|
 |									Dept. of Computer Science and Statistics		|
 |									3D Group for Interactive Visualization			|
 |	Fall 2023																		|
 +---------------------------------------------------------------------------------*/

#ifndef COLORED_VEHICLE_H
#define COLORED_VEHICLE_H

#include "glPlatform.h"
#include "KeyframeAnimator.h"

#include <vector>
#include <memory>

//-----------------------------------------------------
//  Linear interpolation
//-----------------------------------------------------

class ColoredVehicle
{
    public:
        
        ColoredVehicle(std::shared_ptr<KeyframeAnimator> anim, bool recordPath=false, bool drawWaypoints=false);
        
 //       Vehicle(float x, float y, float angle, bool recordPath=false, bool drawWaypoints=false);

        ~ColoredVehicle();
        
        void update(float dt);
        void draw() const;
        
        void setPosition(GLfloat theX, GLfloat theY);

        void setOrientation(GLfloat theAngle);

		ColoredVehicle(const ColoredVehicle& ) = delete;
		ColoredVehicle(ColoredVehicle&& ) = delete;
		ColoredVehicle& operator = (const ColoredVehicle& ) = delete;
		ColoredVehicle& operator = (ColoredVehicle&& ) = delete;

	private:
    
		std::shared_ptr<KeyframeAnimator> animator_;
        GLfloat x_, y_, angle_;
        float scale_;
        float r_, g_, b_;
        float ut_;

        //  I record the path just for the demo.  
        std::vector<GLfloat*> _path;     
        bool recordPath_;
        bool drawWaypoints_;

};        


#endif	//COLORED_VEHICLE_H
