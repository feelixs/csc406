//
//  GraphicObject3D.cpp
//  Week 10 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-02.
//

#include "string.h"
#include "stdlib.h"
#include "GraphicObject3D.h"

using namespace graphics3d;

const Motion Motion::NULL_MOTION{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

GraphicObject3D::GraphicObject3D(const Pose& pose, const Motion& motion)
	:	pose_(pose),
		motion_(motion)
{}

void GraphicObject3D::update(float dt)
{
	pose_.tX += motion_.vX * dt;
	pose_.tY += motion_.vY * dt;
	pose_.tZ += motion_.vZ * dt;
	pose_.pitch += motion_.spinX * dt;
	pose_.yaw += motion_.spinY * dt;
	pose_.roll += motion_.spinZ * dt;
}

void GraphicObject3D::setMaterial(const Material& material)
{
//	material_.sMaterial = material.sMaterial;
	memcpy(material_.aMaterial, material.aMaterial, 17*sizeof(float));
}
			
const Material& GraphicObject3D::getMaterial() const
{
	return material_;
}
