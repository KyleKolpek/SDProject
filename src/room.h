#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>

#include "drawable.h"
#include "wall.h"
#include "camera.h"
#include "GLM/glm.hpp"
#include "actor.h"
#include "dungeon.h"

#define ROOM_WIDTH 30
#define ROOM_LENGTH 30
#define ROOM_HEIGHT 4
#define DOOR_WIDTH 2

class Dungeon;
class Actor;
class ObjLoader;
/**************************************************************************//**
 * A room in the dungeon.
 * Represents a room that may be traversed by the player. Room inherits from
 * Drawable, so the dungeon should be able to traverse each of its room objects
 * and simply call draw() in order to render their walls and other models.
 *****************************************************************************/
class Room : public Drawable
{
public:
	/***********************************************************************//**
	 * Creates a room and computes its global x-y coordinates.
	 * \param[in] row
	 *     Row in dungeon grid of rooms.
	 * \param[in] col
	 *     Column in dungeon grid of rooms.
	 * \param[in] *camera
	 *     Pointer to the game camera.
	 ***************************************************************************/
	Room(int row, int col, Camera *camera, Dungeon *dungeon, 
		ObjLoader *objLoader);

	/***********************************************************************//**
	 * Draws room walls and other internal components.
	 ***************************************************************************/
	void draw();

	void setShaderManager(ShaderManager *shaderManager);

	/***********************************************************************//**
	 * Creates door.
	 * Walls must be created AFTER roomType and orient have been assigned. Doors
	 * are then created by actually generating two walls separated by a gap.
	 * \param[in] wall
	 *     For each wall, state whether to place a door.
	 ***************************************************************************/
	void placeDoor(int northDoor, int westDoor, int southDoor, int eastDoor);

	/***********************************************************************//**
	 * Once doors have been placed, create the physical walls.
	 **************************************************************************/
	void placeWalls();

	/***********************************************************************//**
	 * Coordinates in dungeon grid of rooms.
	 * Rooms store their placement in the dungeon's grid. Room [0,0] would have
	 * the top-left coordinant (0,0) and the bottom-right
	 * (0 + ROOM_WIDTH, 0 + ROOM_HEIGHT). Thus, we're looking at rooms from a
	 * top-down perspective.
	 **************************************************************************/
	int row, col;

	static void loadTexture(std::string const &filename);
	glm::mat4 getModelMatrix();

	/***********************************************************************//**
	 * List of walls that have been placed in room.
	 * Each room has a list of walls that is traversed in draw(). Doors are
	 * represented via two walls with a gap between them. These are public
	 * to allow for easy access by Actor during collision detection.
	 **************************************************************************/
	std::vector<Wall> walls;


	std::vector<Actor*> objects;

private:
	/***********************************************************************//**
	 * Coordinates in x-y plane.
	 * (x,y) points to the north-west (top-left) corner of the room. The rest 
	 * can be derived from ROOM_WIDTH and ROOM_HEIGHT.
	 **************************************************************************/
	float x, y;

	Camera *camera;	/**< Pointer to the game camera. */
	GLuint vertexBuffer;
	GLuint vertexCount;
	glm::mat4 modelMatrix;
	static GLuint texture;
	std::vector<glm::vec3> lights;
	bool objPresent[ROOM_WIDTH][ROOM_LENGTH];
	Dungeon *dungeon;
	ObjLoader *objLoader;
	std::vector<int> hasDoor;
};

#endif
