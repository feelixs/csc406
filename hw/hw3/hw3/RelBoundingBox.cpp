//
//  RelBoundingBox.cpp
//  hw3
//
//  Created by Michael Felix on 11/1/23.
//

#include <cfloat>
#include <math.h>
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

void RelBoundingBox::draw() const
{
    float centerX = (xmin_ + xmax_) / 2.0f;
    float centerY = (ymin_ + ymax_) / 2.0f;
    
    glPushMatrix();
    
    glTranslatef(centerX, centerY, 0.f);
    
    glRotatef(getAngle(), 0.f, 0.f, 1.f);
    glColor4fv(COLOR[static_cast<int>(color_)]);

    // we need to draw relative to the box's center, or else its onscreen pos will be incorrect (since we're applying rotation)
    float halfWidth = (xmax_ - xmin_) / 2.0f, halfHeight = (ymax_ - ymin_) / 2.0f;
    glBegin(GL_LINE_LOOP);
        glVertex2f(-halfWidth, -halfHeight);
        glVertex2f(halfWidth, -halfHeight);
        glVertex2f(halfWidth, halfHeight);
        glVertex2f(-halfWidth, halfHeight);
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


bool RelBoundingBox::overlapsOneWay(const RelBoundingBox& a, const RelBoundingBox& b) {
    float angle1 = a.angle_;
    float angle2 = b.angle_ - a.angle_;

    float cosa1 = cosf(angle1), sina1 = std::sin(angle1);
    float cosa2 = cosf(angle2), sina2 = std::sin(angle2);

    float dx = b.xmin_ - a.xmin_;
    float dy = b.ymin_ - a.ymin_;

    float rx = cosa1 * dx + sina1 * dy;
    float ry = -sina1 * dx + cosa1 * dy;

    float tx = cosa2 * b.calcWidth() + sina2 * b.calcHeight();
    float ty = -sina2 * b.calcWidth() + cosa2 * b.calcHeight();

    return (std::abs(rx) <= a.calcWidth() / 2 + std::abs(tx) / 2) &&
           (std::abs(ry) <= a.calcHeight() / 2 + std::abs(ty) / 2);
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
