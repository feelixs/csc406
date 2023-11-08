#ifndef WORLD_H
#define WORLD_H

#include <random>
#include <cmath>
#include "commonTypes.h"
#include "glPlatform.h"


namespace earshooter {

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
		static const float X_MIN;

		/**	Maximum x value to get mapped to the display area.
		 *	Set in the main program by a call to setWorldBounds.
		 *	@see setWorldBounds
		 */
		static const float X_MAX;

		/**	Minimum y value to get mapped to the display area.
		 *	Set in the main program by a call to setWorldBounds.
		 *	@see setWorldBounds
		 */
		static const float Y_MIN;

		/**	Maximum x value to get mapped to the display area.
		 *	Set in the main program by a call to setWorldBounds.
		 *	@see setWorldBounds
		 */
		static const float Y_MAX;

		/**	Calculated as X_MAX-X_MIN in the main program by a call to setWorldBounds.
		 *	@see setWorldBounds
		 */
		static const float WIDTH;

		/**	Calculated as Y_MAX-Y_MIN in the main program by a call to setWorldBounds.
		 *	@see setWorldBounds
		 */
		static const float HEIGHT;

		/**	Scaling factor converting pixel units to world units.
		 *	Calculated in the main program by a call to setWorldBounds.
		 *	@see setWorldBounds
		 */
		static float pixelToWorldRatio;

		/**	Scaling factor converting world units to pixel units.
		 *	Calculated in the main program by a call to setWorldBounds.
		 *	@see setWorldBounds
		 */
		static float worldToPixelRatio;
		
		/**	This one is really equal to pixelToWorldRatio, but it looks confusing
		 *	to write glSCalef(pixelToWorldRatio, pixelToWorldRatio, 1.f);
		 *	right before trying to drawe in pixel units.
		 *	@see setWorldBounds
		 */
		static float drawInPixelScale;
		
		static WorldType worldType;


		/** Function called through the initialization of a global variable in the
		 *	main program.  Although the user specifies dimensions for the rendering pane,
		 *	the function may set different values that agree better with the world
		 *	aspect ratio.
		 * @param paneWidth		user-set width of the redering pane
		 * @param paneHeight	user-set height of the redering pane
		 */
		static void setScalingRatios(int& paneWidth, int& paneHeight);


		static std::random_device randDev;
		static std::default_random_engine randEngine;
		//
		static std::uniform_real_distribution<float> wxDist;
		static std::uniform_real_distribution<float> wyDist;
		static std::uniform_real_distribution<float> objectScaleDist;
		static std::uniform_real_distribution<float> colorDist;
		static std::uniform_real_distribution<float> normalDist;
		static std::uniform_real_distribution<float> angleDegDist;
		static std::uniform_real_distribution<float> angleRadDist;
		static std::uniform_real_distribution<float> velocityDist;
		static std::uniform_real_distribution<float> spinDegDist;
		static std::bernoulli_distribution headsOrTailsDist;
        static std::uniform_real_distribution<float> randomWidth;
        static std::uniform_int_distribution<int> randomEdge;

	};

	WorldPoint pixelToWorld(float ix, float iy);
	PixelPoint worldToPixel(float wx, float wy);
	WorldPoint pixelToWorld(const PixelPoint& pt);
	PixelPoint worldToPixel(const WorldPoint& pt);
	
	inline WorldPoint randomWorldPoint()
	{
		return WorldPoint{ World::wxDist(World::randEngine),
						   World::wyDist(World::randEngine)};
	}
	inline float randomAngleDeg()
	{
		return World::angleDegDist(World::randEngine);
	}
	inline float randomAngleRad()
	{
		return World::angleRadDist(World::randEngine);
	}
	inline float randomObjectScale()
	{
		return World::objectScaleDist(World::randEngine);
	}
	inline float randomSpinDeg()
	{
		return World::spinDegDist(World::randEngine) *
				(World::headsOrTailsDist(World::randEngine) ? (+1.f) : (-1.f));
	}
	inline float randomColor()
	{
		return World::colorDist(World::randEngine);
	}
	inline bool headsOrTails()
	{
		return World::headsOrTailsDist(World::randEngine);
	}

    /// generate a random velocity
    /// @param vmin lowest possible velocity
    /// @param vmax highest possible velocity
    inline Velocity randomVelocity(float vmin, float vmax)
    {
        float speed = World::normalDist(World::randEngine)*(vmax-vmin) + vmin;
        float angle = randomAngleRad();
        return Velocity{speed*cosf(angle), speed*sinf(angle)};
    }

    /// generate a random velocity pointing towards the center of the screen based on the object's position
    /// @param pos the object's position
    /// @param vmin lowest possible velocity
    /// @param vmax highest possible velocity
    inline Velocity randomEdgeVelocity(WorldPoint& pos, float vmin, float vmax)
    {
        float speed = World::normalDist(World::randEngine)*(vmax-vmin) + vmin;
        float angle = randomAngleRad();
        float speedy = speed;
        float speedx = speed;
        if (((pos.x < 0) & (speedx < 0)) | ((pos.x > 0) & (speedx > 0))) {
            speedx *= -1; // invert to make it directed towards the center
        }
        if (((pos.y < 0) & (speedy < 0)) | ((pos.y > 0) & (speedy > 0))) {
            speedy *= -1; // invert to make it directed towards the center
        }
        return Velocity{speedx*cosf(angle), speedy*sinf(angle)};
    }
    
    inline WorldPoint randomPos() {
        return WorldPoint{ World::wxDist(World::randEngine), World::wyDist(World::randEngine) };
    }
    
    inline WorldPoint randomEdgePos() {
        // choose random from 4 choices (top, right, bottom, left)
        switch (World::randomEdge(World::randEngine)) {
            case 1:
                // top of screen
                return WorldPoint{ World::wxDist(World::randEngine), World::Y_MAX };
            case 2:
                // right of screen
                return WorldPoint{ World::X_MAX, World::wyDist(World::randEngine) };
            case 3:
                // bottom of screen
                return WorldPoint{ World::wxDist(World::randEngine), World::Y_MIN };
            case 4:
                // left of screen
                return WorldPoint{ World::X_MIN, World::wyDist(World::randEngine) };
                
            default:
                // default should never occur, but let's just return top of screen
                return WorldPoint{ World::wxDist(World::randEngine), World::Y_MAX };
        }
    }
    
    inline float randomPosX() {
        return World::wxDist(World::randEngine);
    }
    inline float randomPosY() {
        return World::wyDist(World::randEngine);
    }
    inline float randWidth() {
        return World::randomWidth(World::randEngine);
    }
}

#endif  //  WORLD_H
