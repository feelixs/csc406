//
//  Cylinder3D.h
//  Week 09 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-07.
//

#ifndef CYLINDER_3D_H
#define CYLINDER_3D_H

#include <memory>
#include "GraphicObject3D.h"

namespace graphics3d
{
	/**	I define my cylinders as elliptic rings (radiusX, radiusZY)
	 *	stacked along the local Z axis.
	 *	I also define a static "unit" cylinder that can be used
	 *	as ready-made part for any complex object.
	 */
	class Cylinder3D : public GraphicObject3D
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
			
			const static std::shared_ptr<Cylinder3D> UNIT_CYLINDER_OPEN;
			const static std::shared_ptr<Cylinder3D> UNIT_CYLINDER_CLOSED;

			void initMeshAndNormals_();
			
		public:
		
			Cylinder3D(float radiusX, float radiusY, float height,
						unsigned int numCirclePts, unsigned int numRings,
						bool isClosed,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			Cylinder3D(float radius, float height,
						unsigned int numCirclePts, unsigned int numRings,
						bool isClosed,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			~Cylinder3D();
			
			Cylinder3D(const Cylinder3D& obj) = delete;
			Cylinder3D& operator =(const Cylinder3D& obj) = delete;
			Cylinder3D(Cylinder3D&& obj) = delete;
			Cylinder3D& operator =(Cylinder3D&& obj) = delete;
			Cylinder3D() = delete;

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
			
			static const std::shared_ptr<Cylinder3D> getOpenUnitCylinder()
			{
				return UNIT_CYLINDER_OPEN;
			}
			static const std::shared_ptr<Cylinder3D> getClosedUnitCylinder()
			{
				return UNIT_CYLINDER_CLOSED;
			}
			
//			void displaceVertex(unsigned int row, unsigned int col, float dZ);

	};
}

#endif //	CYLINDER_3D_H
