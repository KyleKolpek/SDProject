#ifndef ROOM_H
#define ROOM_H

#include "wall.h"

/*

	There are five room types. They are all square and vary only by where doors
	are placed. There are as follows:
	
	ONE: One door. Without rotation it is placed on the north wall.
	TWOA: Two doors, adjacent to each other. Without rotation they are on the
		north and west walls.
	TWOB: Two doors, opposite each other. Without rotation they are on the
		north and south walls.
	THREE: Three doors, with the empty wall on the east wall by default.
	FOUR: Each wall has a door.

	Rotation is defined in terms of 90 degrees counter-clockwise rotations. So
	for example, RoomType ONE with ROT_ONE would put the door on the west wall
	instead of the north.
*/

struct Room
{
	int row, col;

	enum RoomType{ ONE, TWOA, TWOB, THREE, FOUR } roomType;
	enum orient{ ROT_ZERO, ROT_ONE, ROT_TWO, ROT_THREE } myOrient;

	std::vector<Wall> walls;

	Room(int i, int j) { row = i; col = j; }
};

#endif
