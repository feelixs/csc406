//
//  GraphicObject.h
//
//  Created by Jean-Yves Hervé on 2023-10-05.
//

#ifndef GRAPHIC_OBJECT_H
#define GRAPHIC_OBJECT_H

#include "World.h"
#include "Object.h"
#include "AbsBoundingBox.h"
#include "RelBoundingBox.hpp"

namespace earshooter
{
	class GraphicObject	: public virtual Object	// abstract class
	{
		private:
		
			/**	The object's relative bounding box
			 */
			mutable std::shared_ptr<RelBoundingBox> relativeBox_;

			/**	The object's absolute bounding box
			 */
			mutable std::shared_ptr<AbsBoundingBox> absoluteBox_;


		public:
		
			GraphicObject(const WorldPoint& pt, float angle);
			
			GraphicObject(float x, float y, float angle);

			//	The rule of thumb is:  If your class contains at least one virtual
			//	method (which indicates that it may be used polymorphically), then
			//	its destructor should be virtual
			virtual ~GraphicObject() = default;
			
			virtual void draw() const = 0;  // pure virtual function

			//disabled constructors & operators
			GraphicObject() = delete;
			GraphicObject(const GraphicObject& obj) = delete;	// copy
			GraphicObject(GraphicObject&& obj) = delete;		// move
			GraphicObject& operator = (const GraphicObject& obj) = delete;	// copy operator
			GraphicObject& operator = (GraphicObject&& obj) = delete;		// move operator

			virtual bool isInside(const WorldPoint& pt) = 0;
			
            void setRelativeBox(std::shared_ptr<RelBoundingBox> box) {
                relativeBox_ = box;
            }
        
            void setAbsoluteBox(std::shared_ptr<AbsBoundingBox> box) {
                absoluteBox_ = box;
            }
        
            std::shared_ptr<RelBoundingBox> getRelativeBox() const
			{
				return relativeBox_;
			}
			
            std::shared_ptr<AbsBoundingBox> getAbsoluteBox() const
			{
				return absoluteBox_;
			}
			
//			const WorldPoint
			
		
	};
}

#endif // GRAPHIC_OBJECT_H 
