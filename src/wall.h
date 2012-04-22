#ifndef WALL_H
#define WALL_H

#include "drawable.h"

/***************************************************************************//**
 * A wall to be drawn in our dungeon. 
 * Each room in the dungeon has a list of walls. Walls are defined by two
 * points, a start and end point.
*******************************************************************************/
class Wall : public Drawable
{
public:
	/***********************************************************************//**
	 * Wall constructor.
	 * \param[in] x_1 y_1
	 *     The starting point of the wall.
	 * \param[in] x_2 y_2
	 *     The ending point of the wall.
	 **************************************************************************/
	Wall(float x_1, float y_1, float x_2, float y_2);

	/***********************************************************************//**
	 * Wall destructor.
	 * Currently empty.
	 **************************************************************************/
	~Wall();
		
	/***********************************************************************//**
	 * Draws wall.
	 **************************************************************************/
	void draw();
	
private:
	float x1, y1;	/** Starting point of wall. */
	float x2, y2;	/** End point of wall. */
};
#endif

