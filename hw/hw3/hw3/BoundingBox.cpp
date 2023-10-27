//
//  BoundingBox.cpp
//  Week 08 - Earshooter

#include <cfloat>
#include "glPlatform.h"
#include "BoundingBox.h"

using namespace earshooter;

BoundingBox::BoundingBox(float xmin, float xmax, float ymin, float ymax, float angle,
						 ColorIndex color)
	: 	xmin_(xmin),
		xmax_(xmax),
		ymin_(ymin),
		ymax_(ymax),
        angle_(angle),
		color_(color)
{
}

BoundingBox::BoundingBox(const WorldPoint& cornerUL, const WorldPoint& cornerLR, float angle,
						ColorIndex color)
	: 	xmin_(cornerUL.x),
		xmax_(cornerLR.x),
		ymin_(cornerUL.y),
		ymax_(cornerLR.y),
        angle_(angle),
		color_(color)
{
}

BoundingBox::BoundingBox(ColorIndex color)
	: 	xmin_(FLT_MAX),
		xmax_(FLT_MAX),
		ymin_(FLT_MAX),
		ymax_(FLT_MAX),
		color_(color)
	{
	}


void BoundingBox::setDimensions(float xmin, float xmax, float ymin, float ymax, float angle)
{
	xmin_ = xmin;
	xmax_ = xmax;
	ymin_ = ymin;
	ymax_ = ymax;
    angle_ = angle;
}

void BoundingBox::draw(void) const
{
	glPushMatrix();
    //glRotatef(getAngle(), 0.f, 0.f, 1.f);
	glColor4fv(COLOR[static_cast<int>(color_)]);
//	const GLfloat worldToPixel = World::getWorldToPixel();
//	glScalef(worldToPixel, worldToPixel, worldToPixel);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin_, ymin_);
		glVertex2f(xmax_, ymin_);
		glVertex2f(xmax_, ymax_);
		glVertex2f(xmin_, ymax_);
	glEnd();
	glPopMatrix();
}

WorldPoint BoundingBox::getCornerUL(void) const
{
	WorldPoint pt = {xmin_, ymax_};
	return pt;
}
		
WorldPoint BoundingBox::getCornerLR(void) const
{
	WorldPoint pt = {xmax_, ymin_};
	return pt;
}
