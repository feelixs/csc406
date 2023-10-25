//
//  AnimatedObject.h
//  Template Project
//
//  Created by Jean-Yves Hervé on 2023-10-17.
//

#ifndef ANIMATED_OBJECT_H
#define ANIMATED_OBJECT_H

#include "Object.h"

namespace earshooter
{
	class AnimatedObject : public virtual Object
	{
		private:
		
			float vx_, vy_, spin_;

		public:

			AnimatedObject(float x, float y, float angle, float vx, float vy, float spin);
			AnimatedObject(const WorldPoint& pt, float angle, const Velocity& vel, float spin);
			
			//disabled constructors & operators
			AnimatedObject() = delete;
			AnimatedObject(const AnimatedObject& obj) = delete;	// copy
			AnimatedObject(AnimatedObject&& obj) = delete;		// move
			AnimatedObject& operator = (const AnimatedObject& obj) = delete;	// copy operator
			AnimatedObject& operator = (AnimatedObject&& obj) = delete;		// move operator

			virtual void update(float dt);

		
	};
}

#endif // ANIMATED_OBJECT_H
