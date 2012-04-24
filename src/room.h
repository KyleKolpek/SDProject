#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "drawable.h"
#include "wall.h"
#include "camera.h"

#define ROOM_WIDTH 30
#define ROOM_LENGTH 15
#define ROOM_HEIGHT 4
#define DOOR_WIDTH 2

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
	Room(int row, int col, Camera *camera);

	/***********************************************************************//**
	 * Draws room walls and other internal components.
	 ***************************************************************************/
	void draw();

	void setShaderManager(ShaderManager *shaderManager);

	/***********************************************************************//**
	 * Creates walls and doors.
	 * Walls must be created AFTER roomType and orient have been assigned. Doors
	 * are then created by actually generating two walls separated by a gap.
	 ***************************************************************************/
	void placeWalls();

	/***********************************************************************//**
	 * Coordinates in dungeon grid of rooms.
	 * Rooms store their placement in the dungeon's grid. Room [0,0] would have
	 * the top-left coordinant (0,0) and the bottom-right
	 * (0 + ROOM_WIDTH, 0 + ROOM_HEIGHT). Thus, we're looking at rooms from a
	 * top-down perspective.
	 **************************************************************************/
	int row, col;

	/***********************************************************************//**
	 * Enum representing type of room.
	 * Rooms are given a type based on the number of doors they contain. In the
	 * following descriptions, the described placement of doors is assuming NO
	 * rotation. We may also describe rotation in 90-degree increments which 
	 * changes which walls have doors.
	 **************************************************************************/
	enum RoomType
	{
		ONE,	/** A single door on the north wall. */ 
		TWOA,	/** Two adjacent doors placed on the north and west walls. */
		TWOB,	/** Two opposite doors placed on the north and south walls. */
		THREE,	/** Three doors placed on the north, west, and south walls. */
		FOUR	/** Each wall has a door. */
	} roomType;

	/***********************************************************************//**
	 * Enum representing orientation of rooms.
	 * Each member represents how many 90-degree counter-clockwise increments to
	 * rotate room while placing doors. For instance, roomType ONE with ROT_ONE
	 * would place the door on the west wall instead of the north.
	 **************************************************************************/
	enum Orientation
	{
		ROT_ZERO,
		ROT_ONE,
		ROT_TWO,
		ROT_THREE
	} orient;

private:
	/***********************************************************************//**
	 * Coordinates in x-y plane.
	 * (x,y) points to the north-west (top-left) corner of the room. The rest 
	 * can be derived from ROOM_WIDTH and ROOM_HEIGHT.
	 **************************************************************************/
	float x, y;

	/***********************************************************************//**
	 * List of walls that have been placed in room.
	 * Each room has a list of walls that is traversed in draw(). Doors are
	 * represented via two walls with a gap between them.
	 **************************************************************************/
	std::vector<Wall> walls;

	Camera *camera;	/** Pointer to the game camera. */
};

#endif
