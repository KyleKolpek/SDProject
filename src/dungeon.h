#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>

#include "drawable.h"
#include "room.h"

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
	 **************************************************************************/
	Dungeon(int rows, int cols, int rooms);

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

	/***********************************************************************//**
	 * Create a string representation of the dungeon.
	 * \param[out]
	 *     std::string describing the placement and orientation of rooms in
	 *     dungeon.
	 ***********************************************************************//**
	 * TODO: Add enemy and item placement to string representation.
	 **************************************************************************/
	std::string str();

private:
	Room ***dungeon;			/** 2D grid of Room pointers. 
									NULL means no room is placed there. */
	std::vector<Room*> rooms;	/** Store a list of rooms in dungeon. */

	/***********************************************************************//**
	 * Randomly populate dungeon with rooms.
	 **********************************************************************//**
	 * TODO: Add enemies, items, etc.
	 **************************************************************************/
	void generateDungeon();

	/***********************************************************************//**
	 * Assign type information to rooms.
	 * After rooms are placed in the grid, use this to determine what RoomType
	 * each room requires. This corresponds to how many doors are needed.
	 **************************************************************************/
	void assignRoomTypes();

	/***********************************************************************//**
	 * Determine orientation of each room.
	 * After rooms are given types they need to be oriented. This determines 
	 * which orientation (which walls to place doors on).
	 **************************************************************************/
	void orientRooms();

	int numRows;	/** The number of rows in our grid of rooms. */
	int numCols;	/** The number of columns in our grid of rooms. */
	int numRooms;	/** The number of rooms in our dungeon. */
};

#endif
