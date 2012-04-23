
#include "room.h"

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

Room::Room(int row, int col, Camera *camera):
	row(row),
	col(col),
	camera(camera)
{
	y = row * ROOM_LENGTH;
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
			doors.push_back(orient);
			break;

		case TWOA:
			doors.push_back(NORTH + orient);
			doors.push_back(WEST + orient);
			break;

		case TWOB:
			doors.push_back(NORTH + orient);
			doors.push_back(SOUTH + orient);
			break;

		case THREE:
			doors.push_back(NORTH + orient);
			doors.push_back(WEST + orient);
			doors.push_back(SOUTH + orient);
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
		walls.push_back(Wall(0, 0, 4, 0, ROOM_HEIGHT, camera));
		walls.push_back(Wall(6, 0, ROOM_WIDTH, 0, ROOM_HEIGHT, camera));
	}
	else
	{
		walls.push_back(Wall(0, 0, ROOM_WIDTH, 0, ROOM_HEIGHT, camera));
	}

	if(hasDoor[WEST])
	{
		walls.push_back(Wall(0, 0, 0, 4, ROOM_HEIGHT, camera));
		walls.push_back(Wall(0, 6, 0, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}
	else
	{
		walls.push_back(Wall(0, 0, 0, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}

	if(hasDoor[SOUTH])
	{
		walls.push_back(Wall(0, ROOM_LENGTH, 4, ROOM_LENGTH,
			ROOM_HEIGHT, camera));
		walls.push_back(Wall(6, ROOM_LENGTH,
			ROOM_WIDTH, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}
	else
	{
		walls.push_back(Wall(0, ROOM_LENGTH,
			ROOM_WIDTH, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}

	if(hasDoor[EAST])
	{
		walls.push_back(Wall(ROOM_WIDTH, 0, ROOM_WIDTH, 4,
			ROOM_HEIGHT, camera));
		walls.push_back(Wall(ROOM_WIDTH, 6,
			ROOM_WIDTH, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}
	else
	{
		walls.push_back(Wall(ROOM_WIDTH, 0,
			ROOM_WIDTH, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}
	
	
	/* DEBUG
	printf("type: %d orient: %d\n", roomType, orient);
	for(size_t i = 0; i < doors.size(); ++i)
		printf("%d ", doors[i]);
	printf("\n");
	*/
	
}

void Room::draw()
{
	for(vector<Wall>::iterator it = walls.begin(); it < walls.end(); it++)
	{
		(*it).draw();
	}
}

void Room::setShaderManager(ShaderManager *shaderManager)
{
	Drawable::setShaderManager(shaderManager);
	// Add shader manager to walls
	for(vector<Wall>::iterator it = walls.begin(); it < walls.end(); it++)
	{
		(*it).setShaderManager(shaderManager);
	}
}
