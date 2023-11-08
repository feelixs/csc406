//
//  RelBoundingBox.hpp
//  hw3
//
//  Created by Michael Felix on 11/1/23.
//

#ifndef RelBoundingBox_hpp
#define RelBoundingBox_hpp

#include <stdio.h>
#include "commonTypes.h"
#include "World.h"

void getCorners(float corners[4][2], float xmin_, float xmax_, float ymin_, float ymax_, float angle_);

namespace earshooter
{
    class RelBoundingBox
    {

        private:
            float xmin_, xmax_, ymin_, ymax_, angle_;
            ColorIndex color_;
    
        public:
        
            /**    Creates a new bounding box at set dimensions and color.
             *
             * Note: Should verify that xmin ≤ xmax and ymin ≤ ymax
             *  (but doesn't)
             *
             * @param xmin    left bound of the box
             * @param xmax    right bound of the box
             * @param ymin    lower bound of the box
             * @param ymax    upper bound of the box
             * @param color    color of the box's contour
             */
            RelBoundingBox(float xmin, float xmax, float ymin, float ymax, float angle,
                        ColorIndex color = ColorIndex::NO_COLOR);

            /**    Creates a new bounding box at set dimensions and color.
             *
             * Note: Should verify that xmin ≤ xmax and ymin ≤ ymax
             *  (but doesn't)
             *
             * @param cornerUL    upper-left corner of the box
             * @param cornerLR    lower-right corner the box
             */
            RelBoundingBox(const WorldPoint& cornerUL, const WorldPoint& cornerLR, float angle,
                        ColorIndex color = ColorIndex::NO_COLOR);

            /**    Creates an empty bounding box with the specified contour color
             *
             * @param color    color of the box's contour
             */
            RelBoundingBox(ColorIndex color = ColorIndex::NO_COLOR);


            /**    Updates the box's position and dimensions
             *
             * Note: Should verify that xmin ≤ xmax and ymin ≤ ymax
             *  (but doesn't)
             *
             * @param xmin    left bound of the box
             * @param xmax    right bound of the box
             * @param ymin    lower bound of the box
             * @param ymax    upper bound of the box
             */
            void setDimensions(float xmin, float xmax, float ymin, float ymax, float angle);


            /**    Updates the box's position and dimensions
             *
             * Note: Should verify that xmin ≤ xmax and ymin ≤ ymax
             *  (but doesn't)
             *
             * @param cornerUL    upper-left corner of the box
             * @param cornerLR    lower-right corner the box
             */
            void setDimensions(const WorldPoint& cornerUL, const WorldPoint& cornerLR);
        
            void setColor(ColorIndex color) {
                color_ = color;
            }
            
            ColorIndex getColor() {
                return color_;
            }
        
            /// detects if this bounding box is overlapping with another Relative Box
            /// @param other the other Relative bounding box to test collision with
            bool overlaps(const RelBoundingBox& other) const;
            
            /**    Returns the min value of the x coordinate
             * @RETURN min value of the x coordinate
             */
            inline float getXmin() const
            {
                return xmin_;
                
            }

            /**    Returns the min value of the x coordinate
             * @RETURN min value of the x coordinate
             */
            inline float getXmax() const
            {
                return xmax_;
            }

            /**    Returns the min value of the x coordinate
             * @RETURN min value of the x coordinate
             */
            inline float getYmin() const
            {
                return ymin_;
                
            }

            /**    Returns the min value of the x coordinate
             * @RETURN min value of the x coordinate
             */
            inline float getYmax() const
            {
                return ymax_;

            }
        
            /** Returns this box's angle
             * @RETURN this box's current angle
             */
            inline float getAngle() const {
                return angle_;
            }

            /**    Returns the box's upper-left corner
             * @RETURN the box's upper-left corner
             */
            WorldPoint getCornerUL() const;
            
            /**    Returns the box's lower-right corner
             * @RETURN the box's lower-right corner
             */
            WorldPoint getCornerLR() const;
            
                
            inline float calcWidth() const {
                return xmax_ - xmin_;
                
            }
        
            inline float calcHeight() const {
                return ymax_ - ymin_;
                
            }
            
            /**    Checks whether a point is inside the box
             * @PARAM x    horizontal coordinate of the point
             * @PARAM y    vertical coordinate of the point
             * @RETURN true if the point is inside the bounding box
             */
            bool isInside(float x, float y) const;
        
            /** Renders the object
             */
            void draw() const;
    };
}


#endif /* RelBoundingBox_hpp */
