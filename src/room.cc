
#include "room.h"

#include <cstdio>
#include <algorithm>

using namespace std;

Room::Room(int i, int j)
{
	row = i;
	col = j;

	y = row * ROOM_HEIGHT;
	x = col * ROOM_WIDTH;
}

void Room::placeWalls()
{
	// First determine which walls need doors. Store a vector sides with doors.
	#define NORTH 0
	#define WEST 1
	#define SOUTH 2
	#define EAST 3

	vector<int> doors;

	switch(roomType)
	{
		case ONE:
			doors.push_back(myOrient);
			break;

		case TWOA:
			doors.push_back(NORTH + myOrient);
			doors.push_back(WEST + myOrient);
			break;

		case TWOB:
			doors.push_back(NORTH + myOrient);
			doors.push_back(SOUTH + myOrient);
			break;

		case THREE:
			doors.push_back(NORTH + myOrient);
			doors.push_back(WEST + myOrient);
			doors.push_back(SOUTH + myOrient);
			break;

		case FOUR:
			doors.push_back(NORTH);
			doors.push_back(WEST);
			doors.push_back(SOUTH);
			doors.push_back(EAST);
			break;
	}

	vector<bool> hasDoor(4, false);

	// now do each wall mod 4 (to fix going all the way around for some sides)
	for(size_t i = 0; i < doors.size(); ++i)
	{
		doors[i] = doors[i] % 4;
		hasDoor[i] = true;
	}

	// Now traverse each wall and create the wall objects
	if(hasDoor[NORTH])
	{
		walls.push_back(Wall(x, y, x + 4, y));
		walls.push_back(Wall(x+6, y, x + ROOM_WIDTH, y));
	}
	else
	{
		walls.push_back(Wall(x,y, x + ROOM_WIDTH, y));
	}

	if(hasDoor[WEST])
	{
		walls.push_back(Wall(x, y, x, y + 4));
		walls.push_back(Wall(x, y+6, x, y + ROOM_HEIGHT));
	}
	else
	{
		walls.push_back(Wall(x, y, x, y + ROOM_HEIGHT));
	}

	if(hasDoor[SOUTH])
	{
		walls.push_back(Wall(x, y + ROOM_HEIGHT, x + 4, y + ROOM_HEIGHT));
		walls.push_back(Wall(x+6, y + ROOM_HEIGHT, x + ROOM_WIDTH, y + ROOM_HEIGHT));
	}
	else
	{
		walls.push_back(Wall(x, y + ROOM_HEIGHT, x + ROOM_WIDTH, y + ROOM_HEIGHT));
	}

	if(hasDoor[EAST])
	{
		walls.push_back(Wall(x + ROOM_WIDTH, y, x + ROOM_WIDTH, y + 4));
		walls.push_back(Wall(x + ROOM_WIDTH, y+6, x + ROOM_WIDTH, y + ROOM_HEIGHT));
	}
	else
	{
		walls.push_back(Wall(x + ROOM_WIDTH, y, x + ROOM_WIDTH, y + ROOM_HEIGHT));
	}
	
	
	/* DEBUG
	printf("type: %d orient: %d\n", roomType, myOrient);
	for(size_t i = 0; i < doors.size(); ++i)
		printf("%d ", doors[i]);
	printf("\n");
	*/
	
}

void Room::draw()
{


}
