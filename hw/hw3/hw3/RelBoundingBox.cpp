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
    // Check using the current bounding box's axes
    if (!projectionsOverlap(*this, other, getEdgeNormal(xmin_, ymin_, xmax_, ymin_)) ||
        !projectionsOverlap(*this, other, getEdgeNormal(xmin_, ymin_, xmin_, ymax_))) {
        return false;
    }

    // Check using the other bounding box's axes
    if (!projectionsOverlap(*this, other, other.getEdgeNormal(other.xmin_, other.ymin_, other.xmax_, other.ymin_)) ||
        !projectionsOverlap(*this, other, other.getEdgeNormal(other.xmin_, other.ymin_, other.xmin_, other.ymax_))) {
        return false;
    }

    // No separating axis found, the bounding boxes overlap
    return true;
}

bool RelBoundingBox::projectionsOverlap(const RelBoundingBox& a, const RelBoundingBox& b, std::pair<float, float> axis) const {
    float minProjA, maxProjA, minProjB, maxProjB;
    projectOntoAxis(a, axis, minProjA, maxProjA);
    projectOntoAxis(b, axis, minProjB, maxProjB);

    // Check if projections overlap
    return !(maxProjA < minProjB || maxProjB < minProjA);
}

void RelBoundingBox::projectOntoAxis(const RelBoundingBox& box, std::pair<float, float> axis, float& minProj, float& maxProj) const {
    // Get all four corners of the bounding box and project them onto the axis
    float projections[4];
    projections[0] = project(box.getRotatedCorner(box.xmin_, box.ymin_), axis);
    projections[1] = project(box.getRotatedCorner(box.xmax_, box.ymin_), axis);
    projections[2] = project(box.getRotatedCorner(box.xmax_, box.ymax_), axis);
    projections[3] = project(box.getRotatedCorner(box.xmin_, box.ymax_), axis);

    // Find the minimum and maximum projection
    minProj = *std::min_element(projections, projections + 4);
    maxProj = *std::max_element(projections, projections + 4);
}

float RelBoundingBox::project(std::pair<float, float> point, std::pair<float, float> axis) const {
    return point.first * axis.first + point.second * axis.second;
}

std::pair<float, float> RelBoundingBox::getEdgeNormal(float x1, float y1, float x2, float y2) const {
    // Calculate the direction of the edge
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Return the normal (perpendicular direction)
    return std::make_pair(-dy, dx);
}

std::pair<float, float> RelBoundingBox::getRotatedCorner(float x, float y) const {
    // Calculate the center of the bounding box
    float centerX = (xmin_ + xmax_) / 2.0f;
    float centerY = (ymin_ + ymax_) / 2.0f;

    // Translate point so the center of the bounding box is the origin
    float dx = x - centerX;
    float dy = y - centerY;

    // Rotate around the origin by -angle_
    float ca = cosf(-getAngle());
    float sa = sinf(-getAngle());

    float rdx = ca * dx - sa * dy;
    float rdy = sa * dx + ca * dy;

    // Translate back
    return std::make_pair(rdx + centerX, rdy + centerY);
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
