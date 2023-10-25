//
//  SmilingFace.cpp
//  Week 08 - Earshooter

#include <random>
#include "glPlatform.h"
#include "World.h"
#include "SmilingFace.h"
#include "Ellipse.h"

using namespace std;
using namespace earshooter;

unsigned int SmilingFace::counter_ = 0;
unsigned int SmilingFace::liveCounter_ = 0;

const int SmilingFace::LEFT_EAR = 0;
const int SmilingFace::RIGHT_EAR = 1;
const int SmilingFace::FACE = 2;
const int SmilingFace::HEAD_NUM_PARTS = 3;
const int SmilingFace::HEAD = SmilingFace::HEAD_NUM_PARTS;
const ColorIndex SmilingFace::PART_BOX_COLOR[] =
							{ColorIndex::GREEN,	//	LEFT_EAR
							 ColorIndex::GREEN,	//	RIGHT_EAR
							 ColorIndex::RED,	//	FACE
							 ColorIndex::BLUE};	//	HEAD

const float SmilingFace::FACE_DIAMETER = 2.f;
const float SmilingFace::EAR_DIAMETER = FACE_DIAMETER/2;
const float SmilingFace::EYE_OUTER_DIAMETER = FACE_DIAMETER/4;
const float SmilingFace::EYE_INNER_DIAMETER = FACE_DIAMETER/6;
const float SmilingFace::MOUTH_V_DIAMETER = FACE_DIAMETER/4;
const float SmilingFace::MOUTH_H_DIAMETER = FACE_DIAMETER/2.5f;
//
const float SmilingFace::EAR_V_OFFSET = 0.3f*FACE_DIAMETER;
const float SmilingFace::EAR_H_OFFSET = 0.45f*FACE_DIAMETER;
const float SmilingFace::EYE_V_OFFSET = 0.2f*FACE_DIAMETER;
const float SmilingFace::EYE_H_OFFSET = 0.2f*FACE_DIAMETER;
const float SmilingFace::LEFT_EAR_X = -EAR_H_OFFSET;
const float SmilingFace::LEFT_EAR_Y = EAR_V_OFFSET;
const float SmilingFace::RIGHT_EAR_X = EAR_H_OFFSET;
const float SmilingFace::RIGHT_EAR_Y = EAR_V_OFFSET;
//
const float SmilingFace::LEFT_EYE_X = -EYE_H_OFFSET;
const float SmilingFace::LEFT_EYE_Y = EYE_V_OFFSET;
const float SmilingFace::RIGHT_EYE_X = EYE_H_OFFSET;
const float SmilingFace::RIGHT_EYE_Y = EYE_V_OFFSET;
//
const float SmilingFace::MOUTH_H_OFFSET = 0.f;
const float SmilingFace::MOUTH_V_OFFSET = -SmilingFace::FACE_DIAMETER*0.04f;

SmilingFace::SmilingFace(const WorldPoint& pt, float angle, const Velocity& vel, float spin,
						 float scale, float red, float green, float blue)
	:	Object(pt.x, pt.y, angle),
		ComplexGraphicObject(pt, angle),
		AnimatedObject(pt, angle, vel, spin),
		scale_(scale),
//		partRelativeBox_(vector<unique_ptr<BoundingBox> >(HEAD_NUM_PARTS)),
//		partAbsoluteBox_(vector<unique_ptr<BoundingBox> >(HEAD_NUM_PARTS)),
		index_(counter_++)
{
	color_[0] = red;
	color_[1] = green;
	color_[2] = blue;
	color_[3] = 1.f;
	liveCounter_++;

	initializeRelativeBox_();
}

SmilingFace::SmilingFace()
:	SmilingFace(randomWorldPoint(),
				randomAngleDeg(),
				randomVelocity(World::WIDTH/20.f, World::WIDTH/5.f),
				randomSpinDeg(), randomObjectScale(),
				randomColor(), randomColor(), randomColor())
{
}

SmilingFace::SmilingFace(float red, float green, float blue)
:	SmilingFace(randomWorldPoint(),
				randomAngleDeg(),
				randomVelocity(World::WIDTH/20.f, World::WIDTH/5.f),
				randomSpinDeg(), randomObjectScale(),
				red, green, blue)
{
}

SmilingFace::SmilingFace(ColorIndex fillColor)
	:	SmilingFace(COLOR[static_cast<int>(fillColor)][0],
					COLOR[static_cast<int>(fillColor)][1],
					COLOR[static_cast<int>(fillColor)][2])
{

}

SmilingFace::SmilingFace(const WorldPoint& pt, float angle, const Velocity& vel, float spin,
						 float scale, ColorIndex fillColor)
	:	SmilingFace(pt, angle, vel, spin, scale,
					COLOR[static_cast<int>(fillColor)][0],
					COLOR[static_cast<int>(fillColor)][1],
					COLOR[static_cast<int>(fillColor)][2])
{
}

SmilingFace::SmilingFace(const WorldPoint& pt, float angle, float scale,
						 float red, float green, float blue)
	:	SmilingFace(pt, angle, Velocity::NULL_VELOCITY, 0.f, scale,
					red, green, blue)
{
}


SmilingFace::SmilingFace(const WorldPoint& pt, float angle, float scale,
						 ColorIndex fillColor)
	:	SmilingFace(pt, angle, Velocity::NULL_VELOCITY, 0.f, scale,
					COLOR[static_cast<int>(fillColor)][0],
					COLOR[static_cast<int>(fillColor)][1],
					COLOR[static_cast<int>(fillColor)][2])
{
}


SmilingFace::~SmilingFace(void)
{
	liveCounter_--;
}

unsigned int SmilingFace::getIndex(void) const
{
	return index_;
}

unsigned int SmilingFace::getLiveCounter(void)
{
	return liveCounter_;
}

void SmilingFace::initializeRelativeBox_(void) const
{
//	partRelativeBox_[LEFT_EAR] = make_unique<BoundingBox>(scale_*(LEFT_EAR_X - EAR_DIAMETER/2), 	//	xmin
//											 scale_*(LEFT_EAR_X + EAR_DIAMETER/2),	//	xmax
//											 scale_*(LEFT_EAR_Y - EAR_DIAMETER/2), 	//	ymin
//											 scale_*(LEFT_EAR_Y + EAR_DIAMETER/2), 	//	ymax
//											 ColorIndex::GREEN);
//	partRelativeBox_[RIGHT_EAR] = make_unique<BoundingBox>(scale_*(RIGHT_EAR_X - EAR_DIAMETER/2), 	//	xmin
//											  scale_*(RIGHT_EAR_X + EAR_DIAMETER/2),		//	xmax
//											  scale_*(RIGHT_EAR_Y - EAR_DIAMETER/2), 	//	ymin
//											  scale_*(RIGHT_EAR_Y + EAR_DIAMETER/2), 	//	ymax
//											  ColorIndex::GREEN);
//	partRelativeBox_[FACE] = make_unique<BoundingBox>( -scale_*FACE_DIAMETER/2, 	//	xmin
//										  +scale_*FACE_DIAMETER/2,		//	xmax
//										  -scale_*FACE_DIAMETER/2, 		//	ymin
//										  +scale_*FACE_DIAMETER/2, 		//	ymax
//										  ColorIndex::BLUE);
//	setRelativeBox_(scale_*(LEFT_EAR_X - EAR_DIAMETER/2), 	//	xmin of left ear
//				  scale_*(RIGHT_EAR_X + EAR_DIAMETER/2),	//	xmax of right ear
//				  -scale_*FACE_DIAMETER/2, 					//	ymin of face
//				  scale_*(LEFT_EAR_Y + EAR_DIAMETER/2)); 	//	ymax of either ear
}

void SmilingFace::draw(void) const
{
	glPushMatrix();
	glTranslatef(getX(), getY(), 0.f);
	glRotatef(getAngle(), 0.f, 0.f, 1.f);
	glScalef(scale_, scale_, 1.f);
	
	glColor4fv(color_);

	glPushMatrix();
	glScalef(FACE_DIAMETER/2, FACE_DIAMETER/2, 1.f);
	drawDisk();
	glPopMatrix();

	//	draw the left ear
	glPushMatrix();
	glTranslatef(LEFT_EAR_X, LEFT_EAR_Y, 0.f);
	glScalef(EAR_DIAMETER/2, EAR_DIAMETER/2, 0.f);
	drawDisk();
	glPopMatrix();

	//	draw the right ear
	glPushMatrix();
	glTranslatef(RIGHT_EAR_X, RIGHT_EAR_Y, 0.f);
	glScalef(EAR_DIAMETER/2, EAR_DIAMETER/2, 0.f);
	drawDisk();
	glPopMatrix();

	//	draw the left and right eyes (I could have gone the Push&pop way here as
	//	well, and would if the eyes were more complex, but here they are simply
	//	ellipses, so no need to make it over-complex.
	//	White of eye
	glColor4f(1.f, 1.f, 1.f, 1.f);
	glPushMatrix();
	glTranslatef(LEFT_EYE_X, LEFT_EYE_Y, 0.f);
	glScalef(EYE_OUTER_DIAMETER/2, EYE_OUTER_DIAMETER/2, 0.f);
	drawDisk();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(RIGHT_EYE_X, RIGHT_EYE_Y, 0.f);
	glScalef(EYE_OUTER_DIAMETER/2, EYE_OUTER_DIAMETER/2, 0.f);
	drawDisk();
	glPopMatrix();
	// pupils
	glColor4f(0.f, 0.f, 0.f, 1.f);
	glPushMatrix();
	glTranslatef(LEFT_EYE_X, LEFT_EYE_Y, 0.f);
	glScalef(EYE_INNER_DIAMETER/2, EYE_INNER_DIAMETER/2, 0.f);
	drawDisk();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(RIGHT_EYE_X, RIGHT_EYE_Y, 0.f);
	glScalef(EYE_INNER_DIAMETER/2, EYE_INNER_DIAMETER/2, 0.f);
	drawDisk();
	glPopMatrix();

	glTranslatef(MOUTH_H_OFFSET, MOUTH_V_OFFSET, 0.f);
	glScalef(MOUTH_H_DIAMETER, MOUTH_V_DIAMETER, 1.f);
	glColor3f(0.f, 0.f, 0.f);
	drawArc(0.7f, 0.85f);

	glPopMatrix();
}


void SmilingFace::updateAbsoluteBox_() const
{

}


bool SmilingFace::isInside(float x, float y) const
{
	bool inside = false;
//	//	If the point is inside the global absolute bounding box
//	if (partAbsoluteBox_[HEAD]->isInside(x, y))
//	{
//		//	test if the point is inside one of the sub-boxes
//		//	Remember that Java (like C, C++, Python) uses lazy evaluation,
//		//	so as soon as one test returns true, the evaluation ends.
//		inside = partAbsoluteBox_[LEFT_EAR]->isInside(x, y) ||
//		partAbsoluteBox_[LEFT_EAR]->isInside(x, y) ||
//		partAbsoluteBox_[FACE]->isInside(x, y);
//	}

	return inside;
}

#if 0

	//NEW
	//	Here we run into our first true "class refactoring issue"
	//	The parent class GraphicalObject defines
	//		public abstract void draw(PApplet app);
	//	which we must implement.
	//	On the other hand, the Face class we implemented together has a method
	//		public void draw(BoundingBoxMode mode)
	//	Adding the PApplet reference to argument is not a problem.  On the other
	//	hand, the fact that the parent class is BoundingBox-unaware is.
	//	Eventually, bounding boxe support should be folded into the parent class,
	//	but this requires more thought.  This revision is just a cleanup.
	//	Fortunately, the box-drawing code can be fairly easily separated from the
	//	So, we are going to have a Face-specific draw method that invokes the
	//	generic draw of the parent class, then draws the boxes.
	/**	renders the Face object
	 *
	 * @param app		reference to the sketch
	 * @param theMode	should the object be drawn with a bounding box?
	 */
	public void draw(PGraphics g, BoundingBoxMode boxMode)
	{
		//NEW
		//	Invokes method declared in the parent class, that draws the object
		draw_(g);
		
		//	Then draw the boxes, if needed

		if (boxMode == BoundingBoxMode.RELATIVE_BOX)
		{
			// we use this object's instance variable to access the application's instance methods and variables
			g.pushMatrix();

			g.translate(x_,  y_);
			g.rotate(angle_);

			for (BoundingBox box : relativeBox_)
				box.draw(g);
			
			g.popMatrix();
		}
		
		else if (boxMode == BoundingBoxMode.ABSOLUTE_BOX)
		{
			for (BoundingBox box : absoluteBox_)
				if (box != null)
					box.draw(g);
			
		}
	}


	public void drawAllQuadrants(PGraphics g, BoundingBoxMode boxMode)
	{
		draw(g, boxMode);
		
		if (shouldGetDrawn_[NORTH_WEST])
		{
			g.pushMatrix();
			g.translate(XMIN-XMAX, YMIN-YMAX);
			draw(g, boxMode);
			g.popMatrix();
		}
		if (shouldGetDrawn_[NORTH])
		{
			g.pushMatrix();
			g.translate(0, YMIN-YMAX);
			draw(g, boxMode);
			g.popMatrix();
		}
		if (shouldGetDrawn_[NORTH_EAST])
		{
			g.pushMatrix();
			g.translate(XMAX-XMIN, YMIN-YMAX);
			draw(g, boxMode);
			g.popMatrix();
		}
		if (shouldGetDrawn_[EAST])
		{
			g.pushMatrix();
			g.translate(XMAX-XMIN, 0);
			draw(g, boxMode);
			g.popMatrix();
		}
		if (shouldGetDrawn_[SOUTH_EAST])
		{
			g.pushMatrix();
			g.translate(XMAX-XMIN, YMAX-YMIN);
			draw(g, boxMode);
			g.popMatrix();
		}
		if (shouldGetDrawn_[SOUTH])
		{
			g.pushMatrix();
			g.translate(0, YMAX-YMIN);
			draw(g, boxMode);
			g.popMatrix();
		}
		if (shouldGetDrawn_[SOUTH_WEST])
		{
			g.pushMatrix();
			g.translate(XMIN-XMAX, YMAX-YMIN);
			draw(g, boxMode);
			g.popMatrix();
		}
		if (shouldGetDrawn_[WEST])
		{
			g.pushMatrix();
			g.translate(XMIN-XMAX, 0);
			draw(g, boxMode);
			g.popMatrix();
		}
	}

	/**	renders the Face object
	 *
	 * @param app		reference to the sketch
	 * @param theMode	should the object be drawn with a bounding box?
	 */
	public void draw(PGraphics g, BoundingBoxMode boxMode, int quad)
	{
		if (quad >= NORTH && quad <= NORTH_EAST && shouldGetDrawn_[quad])
		{
			//	Invokes method declared in the parent class, that draws the object
			draw_(g);

			//	Then draw the boxes, if needed

			if (boxMode == BoundingBoxMode.RELATIVE_BOX)
			{
				// we use this object's instance variable to access the application's instance methods and variables
				g.pushMatrix();

				g.translate(x_,  y_);
				g.rotate(angle_);

				for (BoundingBox box : relativeBox_)
					box.draw(g);

				g.popMatrix();
			}

			else if (boxMode == BoundingBoxMode.ABSOLUTE_BOX)
			{
				for (BoundingBox box : absoluteBox_)
					if (box != null)
						box.draw(g);

			}
		}
	}

	/**	renders the Face object
	 *
	 * @param app		reference to the sketch
	 */
	public void draw_(PGraphics g)
	{
		// we use this object's instance variable to access the application's instance methods and variables
		g.pushMatrix();

		//		boolean drawRelative = app.keyPressed && app.key == 'r';
		//		boolean drawAbsolute = app.keyPressed && app.key == 'a';

		g.translate(x_,  y_);
		g.rotate(angle_);
		g.noStroke();
		g.fill(color_);
		g.ellipse(0, 0, FACE_DIAMETER, FACE_DIAMETER);

		//	draw the left ear
		g.pushMatrix();
		g.noStroke();
		g.fill(color_);
		g.translate(LEFT_EAR_X, LEFT_EAR_Y);
		g.ellipse(0, 0, EAR_DIAMETER, EAR_DIAMETER);
		g.popMatrix();

		//	draw the right ear
		g.pushMatrix();
		g.noStroke();
		g.fill(color_);
		g.translate(RIGHT_EAR_X, RIGHT_EAR_Y);
		g.ellipse(0, 0, EAR_DIAMETER, EAR_DIAMETER);
		g.popMatrix();

		//	draw the left and right eyes (I could have gone the Push&pop way here as
		//	well, and would if the eyes were more complex, but here they are simply
		//	ellipses, so no need to make it over-complex.
		g.fill(255);
		g.ellipse(LEFT_EYE_X, LEFT_EYE_Y, EYE_OUTER_DIAMETER, EYE_OUTER_DIAMETER);
		g.ellipse(RIGHT_EYE_X, RIGHT_EYE_Y, EYE_OUTER_DIAMETER, EYE_OUTER_DIAMETER);
		g.fill(0);
		g.ellipse(LEFT_EYE_X, LEFT_EYE_Y, EYE_INNER_DIAMETER, EYE_INNER_DIAMETER);
		g.ellipse(RIGHT_EYE_X, RIGHT_EYE_Y, EYE_INNER_DIAMETER, EYE_INNER_DIAMETER);

		// draw the mouth
		g.stroke(0);
		g.noFill();
		g.strokeWeight(2*PIXEL_TO_WORLD);
		g.arc(MOUTH_H_OFFSET, MOUTH_V_OFFSET,
				MOUTH_H_DIAMETER, MOUTH_H_DIAMETER, -7*PApplet.PI/8, -PApplet.PI/8);
		
		g.popMatrix();
	}

	/**
	 * 	Computes the new dimensions of the object's absolute bounding boxes, for
	 * the object's current position and orientation.
	 */
	void updateAbsoluteBoxes_()
	{
		float cA = PApplet.cos(angle_), sA = PApplet.sin(angle_);
		float 	centerLeftEarX = x_ + cA*LEFT_EAR_X - sA*LEFT_EAR_Y,
				centerLeftEarY = y_ + cA*LEFT_EAR_Y + sA*LEFT_EAR_X,
				centerRightEarX = x_ + cA*RIGHT_EAR_X - sA*RIGHT_EAR_Y,
				centerRightEarY = y_ + cA*RIGHT_EAR_Y + sA*RIGHT_EAR_X;
				
		
		absoluteBox_[LEFT_EAR].setDimensions(centerLeftEarX - EAR_DIAMETER/2,	//	xmin
											  centerLeftEarX + EAR_DIAMETER/2,	//	xmax
											  centerLeftEarY - EAR_DIAMETER/2,	//	ymin
											  centerLeftEarY + EAR_DIAMETER/2);	//	ymax
		absoluteBox_[RIGHT_EAR].setDimensions(centerRightEarX - EAR_DIAMETER/2,	//	xmin
											   centerRightEarX + EAR_DIAMETER/2,	//	xmax
											   centerRightEarY - EAR_DIAMETER/2,	//	ymin
											   centerRightEarY + EAR_DIAMETER/2);	//	ymax
		absoluteBox_[FACE].setDimensions(x_ - FACE_DIAMETER/2,		// xmin
										  x_ + FACE_DIAMETER/2,		//	xmax
										  y_ - FACE_DIAMETER/2,		//	ymin
										  y_ + FACE_DIAMETER/2);	//	ymax)

		absoluteBox_[HEAD].setDimensions(	PApplet.min(absoluteBox_[LEFT_EAR].getXmin(),
														 absoluteBox_[RIGHT_EAR].getXmin(),
														 absoluteBox_[FACE].getXmin()),	// xmin
											PApplet.max(absoluteBox_[LEFT_EAR].getXmax(),
													 absoluteBox_[RIGHT_EAR].getXmax(),
													 absoluteBox_[FACE].getXmax()),	// xmax
											PApplet.min(absoluteBox_[LEFT_EAR].getYmin(),
													 absoluteBox_[RIGHT_EAR].getYmin(),
													 absoluteBox_[FACE].getYmin()),	// ymin
											PApplet.max(absoluteBox_[LEFT_EAR].getYmax(),
													 absoluteBox_[RIGHT_EAR].getYmax(),
													 absoluteBox_[FACE].getYmax()));	// xmax;
		
	}


#endif
