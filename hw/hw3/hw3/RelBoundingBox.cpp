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


bool RelBoundingBox::isInside(float x, float y) const
{
    float dx = x - (xmin_ + xmax_) / 2.0f;
    float dy = y - (ymin_ + ymax_) / 2.0f;
    
    if (getAngle() != 0.f) {
        float ca = cosf(getAngle()), sa = sinf(getAngle());
        
        float rdx = ca * dx - sa * dy, rdy = sa * dx + ca * dy;

        float halfWidth = (xmax_ - xmin_) / 2.0f;
        float halfHeight = (ymax_ - ymin_) / 2.0f;

        return (rdx >= -halfWidth) && (rdx <= halfWidth) &&
               (rdy >= -halfHeight) && (rdy <= halfHeight);
    } else {
        return (x >= xmin_) && (x <= xmax_) && (y >= ymin_) && (y <= ymax_);
    }
}


bool RelBoundingBox::overlaps(const RelBoundingBox& other) const {
    float myCorners[4][2]; // these containers will store the corner coords of the rotated bounding boxes
    
    // calculate the rotated corner coords
    getCorners(myCorners, xmin_, xmax_, ymin_, ymax_, angle_);

    // is any corner of 'this' is inside 'other'?
    for (int i = 0; i < 4; i++) {
        if (other.isInside(myCorners[i][0], myCorners[i][1])) {
            return true;
        }
    }

    return false;
}


void getCorners(float corners[4][2], float xmin_, float xmax_, float ymin_, float ymax_, float angle_) {
    
    float cx = (xmin_ + xmax_) / 2.0f, cy = (ymin_ + ymax_) / 2.0f;
    float halfWidth = (xmax_ - xmin_) / 2.0f, halfHeight = (ymax_ - ymin_) / 2.0f;
    
    float unrotatedCorners[4][2] = {
        { cx - halfWidth, cy - halfHeight },
        { cx + halfWidth, cy - halfHeight },
        { cx + halfWidth, cy + halfHeight },
        { cx - halfWidth, cy + halfHeight }
    };
    
    float ca = cosf(angle_), sa = sinf(angle_);
    
    for (int i = 0; i < 4; i++) {
        float x = unrotatedCorners[i][0], y = unrotatedCorners[i][1];
        
        // calc points rotated around the center of the asteroid (rectangle)
        float rotatedX = cx + (x - cx) * ca - (y - cy) * sa, rotatedY = cy + (x - cx) * sa + (y - cy) * ca;
        
        corners[i][0] = rotatedX;
        corners[i][1] = rotatedY;
    }
}
