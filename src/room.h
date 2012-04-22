#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "drawable.h"
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

// Room dimensions
#define ROOM_WIDTH 10
#define ROOM_HEIGHT 10

class Room : public Drawable
{
public:
	Room(int i, int j);
	void draw();
	void placeWalls();

	int row, col;

	enum RoomType{ ONE, TWOA, TWOB, THREE, FOUR } roomType;
	enum orient{ ROT_ZERO, ROT_ONE, ROT_TWO, ROT_THREE } myOrient;

	std::vector<Wall> walls;

private:
	// Coordinates in x-y plane of north-west (top-left) corner of room.
	// The rest can be derived from ROOM_WIDTH and ROOM_HEIGHT
	float x, y;

};

#endif
