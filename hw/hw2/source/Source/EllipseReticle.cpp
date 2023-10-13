//
//  OutlineEllipse.cpp
//  hw2
//
//  Created by Michael Felix on 10/12/23.
//

#include "EllipseReticle.hpp"


float** EllipseReticle::circlePts_;


EllipseReticle::EllipseReticle(Point centerPnt, float radius, float r, float g, float b, int numPoints):
    GraphicObject(centerPnt.x, centerPnt.y, 0),
    radiusX_(radius),
    radiusY_(radius),
    red_(r),
    green_(g),
    blue_(b),
    numCirclePts_(numPoints)
{
    circlePts_ = new float*[numCirclePts_];
    for (int k=0; k<numCirclePts_; k++) {
        circlePts_[k] = new float[2];
    }
    float angleStep = 2.f*M_PI/numCirclePts_;
    float theta;
    for (int k=0; k<numCirclePts_; k++) {
        theta = k*angleStep;
        circlePts_[k][0] = cosf(theta);
        circlePts_[k][1] = sinf(theta);
    }
}

void EllipseReticle::draw() const {
    // Save the current coordinate system (origin, axes, scale)
    glPushMatrix();

    // Move to the center of the disk
    glTranslatef(getX(), getY(), 0.f);

    // Apply rotation
    glRotatef(getAngle(), 0.f, 0.f, 1.f);

    // Apply the radius as a scale
    glScalef(radiusX_, radiusY_, 1.f);

    // Clear the color to make it transparent
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the outline color
    glColor3f(red_, green_, blue_);

    // Enable line smoothing for anti-aliasing (optional)
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set the line width for the outline
    glLineWidth(2.0f); // You can adjust the line width as needed

    // Draw the outline ellipse using GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
    for (int k = 0; k < numCirclePts_; k++) {
        glVertex2f(circlePts_[k][0], circlePts_[k][1]);
    }
    glEnd();

    // Restore the original coordinate system (origin, axes, scale)
    glPopMatrix();
}

