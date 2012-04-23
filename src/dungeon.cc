
#include <iostream>
#include <cstdlib>
#include <algorithm> // max/min

#include "dungeon.h"

using namespace std;

void Dungeon::draw()
{
	for(vector<Room*>::iterator it = rooms.begin(); it < rooms.end(); it++)
	{
		(*it)->draw();
	}
}

void Dungeon::setShaderManager(ShaderManager *shaderManager)
{
	Drawable::setShaderManager(shaderManager);
	for(vector<Room*>::iterator it = rooms.begin(); it < rooms.end(); it++)
	{
		(*it)->setShaderManager(shaderManager);
	}
}

Dungeon::Dungeon(int rows, int cols, int rooms, Camera *camera)
{
	numRows = rows;
	numCols = cols;
	numRooms = rooms;
	this->camera = camera;

	// Allocate dungeon memory
	dungeon = new Room**[numRows];
	for(size_t i = 0; i < numRows; ++i)
	{
		dungeon[i] = new Room*[numCols];
		for(size_t j = 0; j < numCols; ++j)
		{
			dungeon[i][j] = NULL;
		}
	}

	generateDungeon();
}

Dungeon::~Dungeon()
{
	// free room memory
	for(size_t i = 0; i < rooms.size(); ++i)
	{
		delete rooms[i];
	}

	for(size_t r = 0; r < numRows; ++r)
	{
		delete dungeon[r];
	}
	delete dungeon;
}

void Dungeon::generateDungeon()
{
	// fill in first room as a seed. Just place it in the middle.
	int startI = numRows / 2;
	int startJ = numCols / 2;
	dungeon[startI][startJ] = new Room(startI, startJ, camera);
	rooms.push_back(dungeon[startI][startJ]);

	
	// After choosing whether to change i or j, we have to decide whether to 
	// increment or decrement it. Store the two options in this array and then
	// choose one.
	int possibleCoords[2];

	// Now generate the rest of the rooms.
	for(size_t n = 0; n < numRooms - 1; ++n)
	{
		// Keep trying until we get a room that works
		while(true)
		{
			// Pick a random room to build off of
			int randRoom = rand() % rooms.size();	
			int i = rooms[randRoom]->row;
			int j = rooms[randRoom]->col;

			// Either expand off of i or j
			if(rand() % 2 == 0)
			{
				// Expand off of i
				possibleCoords[0] = max(0, i-1);
				possibleCoords[1] = min(numRows-1, i+1);
				// Grab new value
				i = possibleCoords[rand() % 2];
				
			}
			else // j
			{
				possibleCoords[0] = max(0, j-1);
				possibleCoords[1] = min(numCols-1, j+1);
				// Grab new value
				j = possibleCoords[rand() % 2];
			}

			// If we chose an empty location
			if(dungeon[i][j] == NULL)
			{
				dungeon[i][j] = new Room(i, j, camera);
				rooms.push_back(dungeon[i][j]);
				// move to next room
				break;
			}
		} // end repeat until success
	} // end foreach room to create

	// Now that all of our rooms created, determine which type and orientation
	// to assign to each room
	assignRoomTypes();
	orientRooms();

	// have each room create its walls
	for(size_t i = 0; i < rooms.size(); ++i)
		rooms[i]->placeWalls();
}

void Dungeon::assignRoomTypes()
{
	// Iterate through each room and determine what type to assign.
	for(size_t ind = 0; ind < rooms.size(); ++ind)
	{
		int i = rooms[ind]->row;
		int j = rooms[ind]->col;

		int numNeighbors = 0;

		if(i > 0 && dungeon[i-1][j] != NULL)
			numNeighbors++;
		if(i < numRows - 1 && dungeon[i+1][j] != NULL)
			numNeighbors++;
		if(j > 0 && dungeon[i][j-1] != NULL)
			numNeighbors++;
		if(j < numCols - 1 && dungeon[i][j+1] != NULL)
			numNeighbors++;

		switch(numNeighbors)
		{
			case 1:
				dungeon[i][j]->roomType = Room::ONE;
				break;
			case 2:
				// check for TWOB. This two opposite sides. 
				if(i > 0 && dungeon[i-1][j] != NULL && i < numRows - 1 && dungeon[i+1][j] != NULL)
				{
					dungeon[i][j]->roomType = Room::TWOB;
					break;
				}
				if(j > 0 && dungeon[i][j-1] != NULL && j < numCols - 1 && dungeon[i][j+1] != NULL)
				{
					dungeon[i][j]->roomType = Room::TWOB;
					break;
				}

				// Nope, it's two adjacent sides.
				dungeon[i][j]->roomType = Room::TWOA;
				break;
			case 3:
				dungeon[i][j]->roomType = Room::THREE;
				break;
			case 4:
				dungeon[i][j]->roomType = Room::FOUR;
				break;
		}
	}
}

void Dungeon::orientRooms()
{
	// Iterate through each room and determine what orientation to assign.
	for(size_t ind = 0; ind < rooms.size(); ++ind)
	{
		int i = rooms[ind]->row;
		int j = rooms[ind]->col;

		switch(rooms[ind]->roomType)
		{
			// just one door, find it.
			case Room::ONE:
				// door on north
				if(i > 0 && dungeon[i-1][j] != NULL)
					rooms[ind]->orient = Room::ROT_ZERO;
				// door on south
				else if(i < numRows - 1 && dungeon[i+1][j] != NULL)
					rooms[ind]->orient = Room::ROT_TWO;
				// door on west
				else if(j > 0 && dungeon[i][j-1] != NULL)
					rooms[ind]->orient = Room::ROT_ONE;
				// door on east
				else
					rooms[ind]->orient = Room::ROT_THREE;
				break;

			// Two adjacent doors
			case Room::TWOA:
				// If one door is north (one row up)
				if(i > 0 && dungeon[i-1][j] != NULL)
				{
					// If other door is west
					if(j > 0 && dungeon[i][j-1] != NULL)
						rooms[ind]->orient = Room::ROT_ZERO;
					else // Door should be east then
						rooms[ind]->orient = Room::ROT_THREE;
				}
				// Then one of the doors must be on the south side
				else if(i < numRows - 1 && dungeon[i+1][j] != NULL)
				{
					// If other door is west
					if(j > 0 && dungeon[i][j-1] != NULL)
						rooms[ind]->orient = Room::ROT_ONE;
					else // Door should be east then
						rooms[ind]->orient = Room::ROT_TWO;
				}
				break;

			// Two opposite doors
			case Room::TWOB:
				// If the doors are north-south
				if(i > 0 && dungeon[i-1][j] != NULL)
					rooms[ind]->orient = Room::ROT_ZERO;
				else // east-west
					rooms[ind]->orient = Room::ROT_ONE;
				break;
			
			// TODO: Fix meeee
			// Three doors, just find the side without a door
			case Room::THREE:
				// north
				if(i > 0 && dungeon[i-1][j] == NULL)
					rooms[ind]->orient = Room::ROT_ONE;
				// south
				else if(i < numRows - 1 && dungeon[i+1][j] == NULL)
					rooms[ind]->orient = Room::ROT_THREE;
				// east
				else if(j > 0 && dungeon[i][j+1] == NULL)
					rooms[ind]->orient = Room::ROT_ZERO;
				// west
				else
					rooms[ind]->orient = Room::ROT_TWO;
				break;

			// Four doors, orientation doesn't matter
			case Room::FOUR:
				dungeon[i][j]->orient = Room::ROT_ZERO;
				break;
		} // end switch(roomType)
	} // end foreach room
}

string Dungeon::str()
{
	string ret = "Room Types:\n";
	for(size_t i = 0; i < numRows; ++i)
	{
		for(size_t j = 0; j < numCols; ++j)
		{
			if(dungeon[i][j] == NULL)
				ret += "0";
			else
			{
				switch(dungeon[i][j]->roomType)
				{
					case Room::ONE:
						ret += "1";
						break;
					case Room::TWOA:
						ret += "A";
						break;
					case Room::TWOB:
						ret += "B";
						break;
					case Room::THREE:
						ret += "3";
						break;
					case Room::FOUR:
						ret += "4";
						break;
				}
			}
		}
		ret += "\n";
	}
	ret += "Orientations:\n";
	for(size_t i = 0; i < numRows; ++i)
	{
		for(size_t j = 0; j < numCols; ++j)
		{
			if(dungeon[i][j] == NULL)
				ret += ".";
			else
			{
				switch(dungeon[i][j]->orient)
				{
					case Room::ROT_ZERO:
						ret += "0";
						break;
					case Room::ROT_ONE:
						ret += "1";
						break;
					case Room::ROT_TWO:
						ret += "2";
					break;
					case Room::ROT_THREE:
						ret += "3";
						break;
				}
			}
		}
		ret += "\n";
	}
	
	return ret;
}
/* DEBUG
int main()
{
	srand(time(NULL));
	Dungeon d(4, 4, 5);

	cout << d.str() << endl;

	return 0;
}
*/
