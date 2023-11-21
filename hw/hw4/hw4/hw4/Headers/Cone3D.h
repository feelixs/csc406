//
//  Cone3D.h
//  Week 09 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-07.
//

#ifndef CONE_3D
#define CONE_3D

#include <memory>
#include "GraphicObject3D.h"

namespace graphics3d
{

    class Cone3D : public GraphicObject3D
	{
		private:
		
			float radiusX_;
			float radiusY_;
			float height_;
			unsigned int numCirclePts_;
			unsigned int numRings_;
			bool isClosed_;
			//	Switching back to a pointer, but I make it a 3D array
			//	numCirclePts_ x (numRings_+1) x 3
			GLfloat*** XYZ_;
			//	only need to index around the ellipse
			GLfloat** normals_;
			GLfloat* topNormal_;
			GLfloat* bottomNormal_;
			
			const static std::shared_ptr<Cone3D> UNIT_CYLINDER_OPEN;
			const static std::shared_ptr<Cone3D> UNIT_CYLINDER_CLOSED;

			void initMeshAndNormals_();
			
		public:
		
			Cone3D(float radiusX, float radiusY, float height,
						unsigned int numCirclePts, unsigned int numRings,
						bool isClosed,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			Cone3D(float radius, float height,
						unsigned int numCirclePts, unsigned int numRings,
						bool isClosed,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			~Cone3D();
			
			Cone3D(const Cone3D& obj) = delete;
			Cone3D& operator =(const Cone3D& obj) = delete;
			Cone3D(Cone3D&& obj) = delete;
			Cone3D& operator =(Cone3D&& obj) = delete;
			Cone3D() = delete;

			void draw() const;
			
			inline float getRadiusX()
			{
				return radiusX_;
			}
			
			inline float getRadiusY()
			{
				return radiusY_;
			}
			inline float getHeight()
			{
				return height_;
			}
			
			static const std::shared_ptr<Cone3D> getOpenUnitCylinder()
			{
				return UNIT_CYLINDER_OPEN;
			}
			static const std::shared_ptr<Cone3D> getClosedUnitCylinder()
			{
				return UNIT_CYLINDER_CLOSED;
			}
			
//			void displaceVertex(unsigned int row, unsigned int col, float dZ);

	};
}

#endif //	CONE_3D
