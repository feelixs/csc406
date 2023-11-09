
#include <cmath>
#include "World.h"

using namespace earshooter;

Velocity Velocity::NULL_VELOCITY{0.f, 0.f};

void World::setScalingRatios(int& paneWidth, int& paneHeight){
	float widthRatio = WIDTH / paneWidth;
	float heightRatio = HEIGHT / paneHeight;
	float maxRatio = fmax(widthRatio,heightRatio);
//	Removed because this doesn’t work happily with interactive window resizing,
//	// If the two ratios differ by more than 5%,  then reject the dimensions
//	if (fabsf(widthRatio-heightRatio)/maxRatio > 0.05){
//		exit(15);
//	}

	pixelToWorldRatio = maxRatio;
	worldToPixelRatio = 1.f / pixelToWorldRatio;
	drawInPixelScale = pixelToWorldRatio;
	
	paneWidth = static_cast<int>(round(WIDTH * worldToPixelRatio));
	paneHeight = static_cast<int>(round(HEIGHT * worldToPixelRatio));
}

WorldPoint earshooter::pixelToWorld(float ix, float iy)
{
	return WorldPoint{	World::X_MIN + ix*World::pixelToWorldRatio,
					World::Y_MAX - iy*World::pixelToWorldRatio
				};
}

WorldPoint earshooter::pixelToWorld(const PixelPoint& pt)
{
	return WorldPoint{	World::X_MIN + pt.x*World::pixelToWorldRatio,
					World::Y_MAX - pt.y*World::pixelToWorldRatio
				};
}

PixelPoint earshooter::worldToPixel(float wx, float wy)
{
	return PixelPoint{(wx - World::X_MIN)*World::worldToPixelRatio,
				 (World::Y_MAX - wy)*World::worldToPixelRatio};

}

PixelPoint earshooter::worldToPixel(const WorldPoint& pt)
{
	return PixelPoint{(pt.x - World::X_MIN)*World::worldToPixelRatio,
				 (World::Y_MAX - pt.y)*World::worldToPixelRatio};

}

void earshooter::rotatePointBy(WorldPoint* pt, float degrees) {
    degrees *= (M_PI/180.f); // convert from degrees to radians
    float xo = pt->x; // store our original x before we change it
    pt->x = pt->x * cosf(degrees) - pt->y * sinf(degrees);
    pt->y = xo * sinf(degrees) + pt->y * cosf(degrees);
}

void earshooter::rotatePointAround(WorldPoint* first, WorldPoint* other, float degrees) {
    /// rotate this point around another one
    
    // find this point's position relative to the origin, if the origin was 'other'
    WorldPoint relativePoint{first->x - other->x, first->y - other->y};
    rotatePointBy(&relativePoint, degrees); // apply rotation around temp origin

    // undo the temporary relative origin
    first->x = other->x + relativePoint.x;
    first->y = other->y + relativePoint.y;
}

void earshooter::rotatePointAround(WorldPoint* first, float x, float y, float degrees) {
    /// rotate this point around another one
    
    // find this point's position relative to the origin, if the origin was 'other'
    WorldPoint relativePoint{first->x - x, first->y - y};
    rotatePointBy(&relativePoint, degrees); // apply rotation around temp origin

    // undo the temporary relative origin
    first->x = x + relativePoint.x;
    first->y = y + relativePoint.y;
}
