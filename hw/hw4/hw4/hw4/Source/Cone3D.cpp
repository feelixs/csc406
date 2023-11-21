//
//  Cone3D.cpp
//  Week 09 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-07.
//

#include "Cone3D.h"

using namespace std;
using namespace graphics3d;


const shared_ptr<Cone3D> UNIT_CYLINDER_OPEN = make_shared<Cone3D>(
				1.f, 1.f, 1.f, 12, 12, false,
				Pose{0.f, 0.f, 0.f});
const shared_ptr<Cone3D> UNIT_CYLINDER_CLOSED = make_shared<Cone3D>(
				1.f, 1.f, 1.f, 12, 12, true,
				Pose{0.f, 0.f, 0.f});
			
Cone3D::Cone3D(float radiusX, float radiusY, float height,
						unsigned int numCirclePts, unsigned int numRings,
						bool isClosed,
						const Pose& pose, const Motion& motion)
	:	GraphicObject3D(pose, motion),
		//
		radiusX_(radiusX),
		radiusY_(radiusY),
		height_(height),
		numCirclePts_(numCirclePts),
		numRings_(numRings),
		isClosed_(isClosed),
		XYZ_(nullptr),
		normals_(nullptr),
		topNormal_(nullptr),
		bottomNormal_(nullptr)
{
	initMeshAndNormals_();
}

Cone3D::Cone3D(float radius, float height,
						unsigned int numCirclePts, unsigned int numRings,
						bool isClosed,
						const Pose& pose, const Motion& motion)
	:	Cone3D(radius, radius, height, numCirclePts, numRings,
				   isClosed, pose, motion)
{}

Cone3D::~Cone3D()
{
	for (unsigned int i=0; i<numRings_; i++)
	{
		for (unsigned int j=0; j<numCirclePts_; j++)
		{
			delete []XYZ_[i][j];
		}
		delete []XYZ_[i];
	}
	delete []XYZ_;

	for (unsigned int j=0; j<numCirclePts_; j++)
	{
		delete []normals_[j];
	}
	delete []normals_;

	if (isClosed_)
	{
		delete [] topNormal_;
		delete [] bottomNormal_;
	}
}


void Cone3D::draw() const
{
	glPushMatrix();
	applyPose();

	setCurrentMaterial(getMaterial());

	//	draw all the rings
	for (unsigned int i=0; i<numRings_; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
			for (unsigned int j=0; j<numCirclePts_; j++)
			{
				glNormal3fv(normals_[j]);
				glVertex3fv(XYZ_[i][j]);
				glNormal3fv(normals_[j]);
				glVertex3fv(XYZ_[i+1][j]);
			}
			// close the ring
			glNormal3fv(normals_[0]);
			glVertex3fv(XYZ_[i][0]);
			glNormal3fv(normals_[0]);
			glVertex3fv(XYZ_[i+1][0]);
			
		glEnd();
	}
	
	//	If the cylinder is closed, we have to draw the top and bottom sides
	if (isClosed_)
	{
		//	top
		//-----------------------------------
		glBegin(GL_TRIANGLE_FAN);
			//	center
			glNormal3fv(topNormal_);
			glVertex3f(0.f, 0.f, height_);

			glNormal3fv(topNormal_);
			glVertex3fv(XYZ_[numRings_][0]);

			//	For whatever reason, fans list vertices in clockwise order [???]
			for (unsigned int j=0, jp=numCirclePts_-1; j<numCirclePts_; j++, jp--)
			{
				glNormal3fv(topNormal_);
				glVertex3fv(XYZ_[numRings_][jp]);
			}
		glEnd();
		
		//	bottom
		//-----------------------------------
		glBegin(GL_TRIANGLE_FAN);
			//	center
			glNormal3fv(bottomNormal_);
			glVertex3f(0.f, 0.f, 0.f);
			for (unsigned int j=0; j<numCirclePts_; j++)
			{
				glNormal3fv(bottomNormal_);
				glVertex3fv(XYZ_[0][j]);
			}
			glNormal3fv(bottomNormal_);
			glVertex3fv(XYZ_[0][0]);
		glEnd();
	}

	glPopMatrix();
}


void Cone3D::initMeshAndNormals_() {
    // Allocate arrays of vertex coordinates and normals
    XYZ_ = new GLfloat**[numRings_ + 1];
    for (unsigned int i = 0; i <= numRings_; i++) {
        XYZ_[i] = new GLfloat*[numCirclePts_];
        for (unsigned int j = 0; j < numCirclePts_; j++) {
            XYZ_[i][j] = new GLfloat[3];
        }
    }

    normals_ = new GLfloat*[numCirclePts_];
    for (unsigned int j = 0; j < numCirclePts_; j++) {
        normals_[j] = new GLfloat[3];
    }

    // Initialize the vertex and normal coordinates
    for (unsigned int j = 0; j < numCirclePts_; j++) {
        float theta = 2 * j * M_PI / numCirclePts_;
        float ct = cosf(theta), st = sinf(theta);

        for (unsigned int i = 0; i <= numRings_; i++) {
            // decrease the radius as we go up the cone
            float decRate = (float)i / numRings_;
            float curRadX = radiusX_ * (1 - decRate);
            float curRadY = radiusY_ * (1 - decRate);
            XYZ_[i][j][0] = curRadX * ct;
            XYZ_[i][j][1] = curRadY * st;
            XYZ_[i][j][2] = height_ * decRate;

            // Calculate normals for the cone surface
            float normalLength = sqrt(ct*ct / (curRadX*curRadX) + st*st / (curRadY*curRadY) + 1);
            normals_[j][0] = ct / (curRadX * normalLength);
            normals_[j][1] = st / (curRadY * normalLength);
            normals_[j][2] = 1 / normalLength;
        }
    }
    
    // Take care of top and bottom sides if the cone is closed
    if (isClosed_) {
        topNormal_ = new GLfloat[3];
        bottomNormal_ = new GLfloat[3];
        topNormal_[0] = topNormal_[1] = bottomNormal_[0] = bottomNormal_[1] = 0.f;
        topNormal_[2] = 1.f;
        bottomNormal_[2] = -1.f;
    }
}
