
#include <cmath>
#include "World.h"

float World::X_MIN;
float World::X_MAX;
float World::Y_MIN;
float World::Y_MAX;
float World::WIDTH;
float World::HEIGHT;
float World::pixelToWorldScale;
float World::worldToPixelScale;


Point pixelToWorld(float ix, float iy)
{
	return Point{	World::X_MIN + ix*World::pixelToWorldScale,
					World::Y_MAX - iy*World::pixelToWorldScale
				};
}

Point worldToPixel(float wx, float wy)
{
	return Point{(wx - World::X_MIN)*World::worldToPixelScale,
				 (World::Y_MAX - wy)*World::worldToPixelScale};

}

void World::setWorldBounds(float xmin, float xmax, float ymin, float ymax,
						   int& paneWidth, int& paneHeight){
	if ((xmax <= xmin) || (ymax <= xmin)){
		exit(5);
	}
	X_MIN = xmin;
	X_MAX = xmax;
	Y_MIN = ymin;
	Y_MAX = ymax;
	WIDTH = xmax - xmin;
	HEIGHT = ymax - ymin;
	
	float widthRatio = WIDTH / paneWidth;
	float heightRatio = HEIGHT / paneHeight;
	float maxRatio = fmax(widthRatio,heightRatio);
//	/** If the two ratios differ by more than 5%,  then reject the dimensions*/
//	if (fabsf(widthRatio-heightRatio)/maxRatio > 0.05){
//		exit(15);
//	}

	pixelToWorldScale = maxRatio;
	worldToPixelScale = 1.f / pixelToWorldScale;
	
	paneWidth = static_cast<int>(round(WIDTH * worldToPixelScale));
	paneHeight = static_cast<int>(round(HEIGHT * worldToPixelScale));
}

void Point::rotateBy(float angle) {
    x = x * cosf(angle) - y * sinf(angle);
    y = x * sinf(angle) + y * cosf(angle);
}

void Point::rotateAround(Point* other, float theta)
{
    /// rotate this point around another one
    Point relativePoint = Point{x - other->x, y - other->y};
    relativePoint.rotateBy(theta);
    
    x = relativePoint.x;
    y = relativePoint.y;
}
