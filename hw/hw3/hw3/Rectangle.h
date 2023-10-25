//
//  Rectangle.h
//  Template Project
//
//  Created by Jean-Yves Hervé on 2023-10-12.
//


#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GraphicObject.h"

namespace earshooter
{
	class Rectangle : public GraphicObject
	{
		private:
		
			float width_, height_;
			float red_, green_, blue_;
				
		public:
		
			Rectangle(float centerX, float centerY, float angle, float width, float height,
					float r, float g, float b);
			Rectangle(const WorldPoint& pt, float angle, float width, float height,
					float r, float g, float b);
			~Rectangle() = default;
			
			void draw() const;

			//disabled constructors & operators
			Rectangle() = delete;
			Rectangle(const Rectangle& obj) = delete;	// copy
			Rectangle(Rectangle&& obj) = delete;		// move
			Rectangle& operator = (const Rectangle& obj) = delete;	// copy operator
			Rectangle& operator = (Rectangle&& obj) = delete;		// move operator

			bool isInside(const WorldPoint& pt);

	};
}

#endif // RECTANGLE_H
