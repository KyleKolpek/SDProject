#ifndef WALL_H
#define WALL_H

#include <string>
#include "GLM/glm.hpp"
#include "camera.h"
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
	 * \param[in] x1
	 *     The starting x coord of the wall.
	 * \param[in] y1
	 *     The starting y coord of the wall.
	 * \param[in] x2
	 *     The ending x coord of the wall.
	 * \param[in] y2
	 *     The ending y coord of the wall.
	 * \param[in] height
	 *     The height of the wall.
	 * \param[in] camera
	 *     A pointer to a camera object to manage the view and projection
	 *     matrices.
	 **************************************************************************/
	Wall(float x1, float y1, float x2, float y2, float height, Camera *camera);

	/***********************************************************************//**
	 * Wall destructor.
	 * Currently empty.
	 **************************************************************************/
	~Wall();

	/***********************************************************************//**
	 * Draws the Wall.
	 **************************************************************************/
	void draw();

	static void loadTexture(std::string const &filename);

private:
	float x1, y1;	/**< Starting point of wall. */
	float x2, y2;	/**< End point of wall. */
	float height;
	int vertexCount;
	glm::vec3 normal;
	GLuint vertexBuffer;
	Camera *camera;

	static GLuint texture;
};

#endif
