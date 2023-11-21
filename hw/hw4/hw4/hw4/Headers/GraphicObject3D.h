//
//  GraphicObject3D.h
//  Week 10 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-02.
//

#ifndef GRAPHIC_OBJECT_3D_H
#define GRAPHIC_OBJECT_3D_H

#include <stdio.h>
#include "common.h"
#include "drawingUtilities.h"

namespace graphics3d
{
	class GraphicObject3D
	{
		private:
		
			Pose pose_;
			Motion motion_;
			Material material_;
			
		public:
		
			GraphicObject3D(const Pose& pose, const Motion& motion = Motion::NULL_MOTION);
	
			~GraphicObject3D() = default;
			//	I allow copy for a change
			GraphicObject3D(const GraphicObject3D& obj) = default;
			GraphicObject3D& operator =(const GraphicObject3D& obj) = default;
			//but still not move
			GraphicObject3D(GraphicObject3D&& obj) = delete;
			GraphicObject3D& operator =(GraphicObject3D&& obj) = delete;
			GraphicObject3D() = delete;

			virtual void draw() const = 0;
			virtual void update(float dt);
			
			void setMaterial(const Material& material);
			
			const Material& getMaterial() const;
			
			inline const Pose& getPose() const
			{
				return pose_;
			}
			
			inline const Motion& getMotion() const
			{
				return motion_;
			}
			
			inline void setPose(const Pose& pose)
			{
				pose_ = pose;
			}
			
			inline void setMotion(const Motion& motion)
			{
				motion_ = motion;
			}
			
			inline void applyPose() const
			{
				glTranslatef(pose_.tX, pose_.tY, pose_.tZ);
				glRotatef(pose_.roll, 0.f, 0.f, 1.f);
				glRotatef(pose_.yaw, 0.f, 1.f, 0.f);
				glRotatef(pose_.pitch, 1.f, 0.f, 0.f);
			}

			inline static void applyPose(const Pose& pose)
			{
				glTranslatef(pose.tX, pose.tY, pose.tZ);
				glRotatef(pose.roll, 0.f, 0.f, 1.f);
				glRotatef(pose.yaw, 0.f, 1.f, 0.f);
				glRotatef(pose.pitch, 1.f, 0.f, 0.f);
			}

	};


}

#endif //	GRAPHIC_OBJECT_3D_H
