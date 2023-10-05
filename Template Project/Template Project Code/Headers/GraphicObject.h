//
//  GraphicObject.h
//  Template Project
//
//  Created by Jean-Yves Hervé on 2023-10-05.
//

#ifndef GRAPHIC_OBJECT_H
#define GRAPHIC_OBJECT_H

class GraphicObject		// abstract class
{
	private:
	
		float x_ , y_, angle_;

	public:
	
		GraphicObject(float x, float y, float angle);
		~GraphicObject();
		
		virtual void draw() const = 0;  // pure virtual function

		//disabled constructors & operators
		GraphicObject() = delete;
		GraphicObject(const GraphicObject& obj) = delete;	// copy
		GraphicObject(GraphicObject&& obj) = delete;		// move
		GraphicObject& operator = (const GraphicObject& obj) = delete;	// copy operator
		GraphicObject& operator = (GraphicObject&& obj) = delete;		// move operator

};

#endif /* GRAPHIC_OBJECT_H */
