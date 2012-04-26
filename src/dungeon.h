#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>

#include "GLM/glm.hpp"

#include "drawable.h"
#include "room.h"
#include "camera.h"

class Room;
class ObjLoader;
/***************************************************************************//**
 * The setting of the game.
 * Generates a random dungeon by placing a number of rooms in a 2D grid.
 ******************************************************************************/
class Dungeon : public Drawable
{
public:
	/***********************************************************************//**
	 * Dungeon constructor.
	 * \param[in] rows
	 *     The number of rows in dungeon grid.
	 * \param[in] cols
	 *     The number of columns in dungeon grid.
	 * \param[in] rooms
	 *     The number of rooms to place in the dungeon.
	 * \param[in] *camera
	 *     A pointer to the game camera.
	 **************************************************************************/
	Dungeon(int rows, int cols, int rooms, Camera *camera, 
		ObjLoader *objLoader);

	/***********************************************************************//**
	 * Dungeon destructor.
	 * Deallocates memory that is allocated during dungeon generation.
	 **************************************************************************/
	~Dungeon();

	/***********************************************************************//**
	 * Draw dungeon.
	 * Draws rooms, enemies, and other objects.
	 **************************************************************************/
	void draw();

	void setShaderManager(ShaderManager *shaderManager);

	/***********************************************************************//**
	 * Get the starting position for players.
	 * \param[out] startingPos
	 *     A glm::vec3 with the entrance to the dungeon.
	 **************************************************************************/
	glm::vec3 getStartingPos();

	/***********************************************************************//**
	 * Return a pointer to the room at [r][c].
	 **************************************************************************/
	Room* getRoom(int r, int c);

	void setLights(vector<glm::vec3> const &positions,
				   vector<glm::vec3> const &colors,
				   int count);

private:
	Room ***dungeon;			/** 2D grid of Room pointers. 
									NULL means no room is placed there. */
	std::vector<Room*> rooms;	/** Store a list of rooms in dungeon. */

	bool **visited;				/** Used in maze generation. */

	/***********************************************************************//**
	 * Randomly populate dungeon with rooms.
	 **********************************************************************//**
	 * TODO: Add enemies, items, etc.
	 **************************************************************************/
	void generateDungeon();

	/***********************************************************************//**
	 * Place doors to generate a random maze.
	 * Use a backtracking algorithm to generate a random maze.
	 **************************************************************************/
	void generateMaze();

	/***********************************************************************//**
	 * Return a vector of cell's unvisited neighbors.
	 **************************************************************************/
	std::vector<Room*> getLonelyNeighbors(Room *cell);

	/***********************************************************************//**
	 * Remove the wall (add a door) between two rooms.
	 **************************************************************************/
	void removeWall(Room *a, Room *b);

	int numRows;			/** The number of rows in our grid of rooms. */
	int numCols;			/** The number of columns in our grid of rooms. */
	int numRooms;			/** The number of rooms in our dungeon. */
	int startRow, startCol;	/** The row and column that the game begins in. */

	Camera *camera;	/** Pointer to the game camera. */
	ObjLoader *objLoader;
};

#endif
