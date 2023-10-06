//
//  Ellipse.hpp
//  Prog 02
//
//  Created by Jean-Yves Hervé on 2023-09-14.
//

#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include <stdio.h>
//
#include "GraphicObject.h"

class Ellipse : public GraphicObject
{
	friend bool initEllipseFunc();
	
	private:
	
		float radiusX_, radiusY_;
		float red_, green_, blue_;
			
		static const int numCirclePts_;
		static float** circlePts_;


	public:
	
		Ellipse(float centerX, float centerY, float angle, float radiusX, float radiusY,
				float r, float g, float b);
		Ellipse(float centerX, float centerY, float radius,
				float r, float g, float b);
		~Ellipse();
		
		void draw() const;

		//disabled constructors & operators
		Ellipse() = delete;
		Ellipse(const Ellipse& obj) = delete;	// copy
		Ellipse(Ellipse&& obj) = delete;		// move
		Ellipse& operator = (const Ellipse& obj) = delete;	// copy operator
		Ellipse& operator = (Ellipse&& obj) = delete;		// move operator

};

bool initEllipseFunc();

#endif // ELLIPSE_HPP
