//
//  RelBoundingBox.cpp
//  hw3
//
//  Created by Michael Felix on 11/1/23.
//

#include <cfloat>
#include "glPlatform.h"
#include "RelBoundingBox.hpp"


using namespace earshooter;

RelBoundingBox::RelBoundingBox(float xmin, float xmax, float ymin, float ymax, float angle,
                         ColorIndex color)
    :     xmin_(xmin),
        xmax_(xmax),
        ymin_(ymin),
        ymax_(ymax),
        color_(color),
        angle_(angle)
{
}

RelBoundingBox::RelBoundingBox(const WorldPoint& cornerUL, const WorldPoint& cornerLR, float angle,
                        ColorIndex color)
    :     xmin_(cornerUL.x),
        xmax_(cornerLR.x),
        ymin_(cornerUL.y),
        ymax_(cornerLR.y),
        color_(color),
        angle_(angle)
{
}

RelBoundingBox::RelBoundingBox(ColorIndex color)
    :     xmin_(FLT_MAX),
        xmax_(FLT_MAX),
        ymin_(FLT_MAX),
        ymax_(FLT_MAX),
        color_(color)
    {
    }


void RelBoundingBox::setDimensions(float xmin, float xmax, float ymin, float ymax, float angle)
{
    xmin_ = xmin;
    xmax_ = xmax;
    ymin_ = ymin;
    ymax_ = ymax;
    angle_ = angle;
}

void RelBoundingBox::draw(void) const
{
    glPushMatrix();
    glRotatef(getAngle(), 0.f, 0.f, 1.f);
    glColor4fv(COLOR[static_cast<int>(color_)]);
//    const GLfloat worldToPixel = World::getWorldToPixel();
//    glScalef(worldToPixel, worldToPixel, worldToPixel);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin_, ymin_);
        glVertex2f(xmax_, ymin_);
        glVertex2f(xmax_, ymax_);
        glVertex2f(xmin_, ymax_);
    glEnd();
    glPopMatrix();
}

WorldPoint RelBoundingBox::getCornerUL(void) const
{
    WorldPoint pt = {xmin_, ymax_};
    return pt;
}
        
WorldPoint RelBoundingBox::getCornerLR(void) const
{
    WorldPoint pt = {xmax_, ymin_};
    return pt;
}


bool RelBoundingBox::overlaps(const RelBoundingBox& other) const {
    return !(xmin_ > other.xmax_ ||
             xmax_ < other.xmin_ ||
             ymin_ > other.ymax_ ||
             ymax_ < other.ymin_);
}

bool RelBoundingBox::isInside(float x, float y) const
{
    float dx = x - (xmin_ + xmax_) / 2.0f;
        float dy = y - (ymin_ + ymax_) / 2.0f;
        
        if (getAngle() != 0.f) {
            float ca = cosf(-getAngle()), sa = sinf(-getAngle());
            
            float rdx = ca * dx - sa * dy, rdy = sa * dx + ca * dy;

            float halfWidth = (xmax_ - xmin_) / 2.0f;
            float halfHeight = (ymax_ - ymin_) / 2.0f;

            return (rdx >= -halfWidth) && (rdx <= halfWidth) &&
                   (rdy >= -halfHeight) && (rdy <= halfHeight);
        } else {
            return (x >= xmin_) && (x <= xmax_) && (y >= ymin_) && (y <= ymax_);
        }
}
