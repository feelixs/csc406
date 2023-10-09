#ifndef WORLD_H
#define WORLD_H

#include <cmath>

/** Struct used to store the coordinates of a "potential Point," by which
 *	we mean a geometric point that hasn't been confirmed as a Point object.
 */
struct Point{
	
	/** The point's horizontal coordinate.
	 */
	float x;

	/** The point's vertical coordinate.
	 */
	float y;
    
    void rotateBy(float angle) {
        x = x * cosf(angle) - y * sinf(angle);
        y = x * sinf(angle) + y * cosf(angle);
    }

};


/** Essentially a set of application-wide global variables defining the
 * dimensions of the "world" and the conversion factors from pixel to world
 * units and back, as well as a few rendering constants.
 *
 */
struct World {

	/**	Minimum x value to get mapped to the display area.
	 *	Set in the main program by a call to setWorldBounds.
	 *	@see setWorldBounds
	 */
	static float X_MIN;

	/**	Maximum x value to get mapped to the display area.
	 *	Set in the main program by a call to setWorldBounds.
	 *	@see setWorldBounds
	 */
	static float X_MAX;

	/**	Minimum y value to get mapped to the display area.
	 *	Set in the main program by a call to setWorldBounds.
	 *	@see setWorldBounds
	 */
	static float Y_MIN;

	/**	Maximum x value to get mapped to the display area.
	 *	Set in the main program by a call to setWorldBounds.
	 *	@see setWorldBounds
	 */
	static float Y_MAX;

	/**	Calculated as X_MAX-X_MIN in the main program by a call to setWorldBounds.
	 *	@see setWorldBounds
	 */
	static float WIDTH;

	/**	Calculated as Y_MAX-Y_MIN in the main program by a call to setWorldBounds.
	 *	@see setWorldBounds
	 */
	static float HEIGHT;

	/**	Scaling factor converting pixel units to world units.
	 *	Calculated in the main program by a call to setWorldBounds.
	 *	@see setWorldBounds
	 */
	static float pixelToWorldScale;

	/**	Scaling factor converting world units to pixel units.
	 *	Calculated in the main program by a call to setWorldBounds.
	 *	@see setWorldBounds
	 */
	static float worldToPixelScale;
	

	/** Function called through the initialization of a global variable in the
	 *	main program.  Although the user specifies dimensions for the rendering pane,
	 *	the function may set different values that agree better with the world
	 *	aspect ratio.
	 * @param xmin	Minimum x value to get mapped to the display area.
	 * @param xmax	Maximum x value to get mapped to the display area.
	 * @param ymin	Minimum y value to get mapped to the display area.
	 * @param ymax	Maximum y value to get mapped to the display area.
	 * @param paneWidth		user-set width of the redering pane
	 * @param paneHeight	user-set height of the redering pane
	 * */
	static void setWorldBounds(float xmin, float xmax, float ymin, float ymax,
								int& paneWidth, int& paneHeight);	

};

Point pixelToWorld(float ix, float iy);
Point worldToPixel(float wx, float wy);

#endif  //  WORLD_H
