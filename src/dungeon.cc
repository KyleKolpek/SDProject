
#include <iostream>
#include <cstdlib>
#include <algorithm> // max/min
#include <stack>

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

Dungeon::Dungeon(int rows, int cols, int rooms, Camera *camera, 
				ObjLoader *objLoader)
{
	numRows = rows;
	numCols = cols;
	numRooms = rooms;
	this->camera = camera;
	this->objLoader = objLoader;
	// Allocate dungeon memory
	dungeon = new Room**[numRows];
	visited = new bool*[numRows];
	for(size_t i = 0; i < numRows; ++i)
	{
		dungeon[i] = new Room*[numCols];
		visited[i] = new bool[numCols];
		for(size_t j = 0; j < numCols; ++j)
		{
			dungeon[i][j] = NULL;
			visited[i][j] = false;
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
		delete [] dungeon[r];
		delete [] visited[r];
	}
	delete [] dungeon;
	delete [] visited;
}

void Dungeon::generateDungeon()
{
	// fill in first room as a seed. Just place it in the middle.
	startRow = numRows - 1;
	startCol = numCols / 2;
	dungeon[startRow][startCol] = new Room(startRow, startCol, camera, this, 
											objLoader);
	rooms.push_back(dungeon[startRow][startCol]);
	
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
				dungeon[i][j] = new Room(i, j, camera, this, objLoader);
				rooms.push_back(dungeon[i][j]);
				// move to next room
				break;
			}
		} // end repeat until success
	} // end foreach room to create

	// We've now created all rooms. Run a maze-generation algorithm to 
	// determine door placement.
	generateMaze();

	// Seed room has a door manually placed on south wall.
	rooms[0]->placeDoor(0,0,1,0);

	// have each room create its walls
	for(size_t i = 0; i < rooms.size(); ++i)
		rooms[i]->placeWalls(); 
}

void Dungeon::generateMaze()
{
	// Grab the start room
	Room* currRoom = dungeon[startRow][startCol];

	// mark seed room as visited
	visited[startRow][startCol] = true;

	// stack to simulate recursion
	stack<Room*> toVisit;
	toVisit.push(currRoom);

	// How many are left to visit
	int unvisited = numRooms - 1;

	// continue until every room has been visited
	while(unvisited > 0)
	{
		// Neighbors we have to choose from
		vector<Room*> neighbors = getLonelyNeighbors(currRoom);
		if(neighbors.size() > 0)
		{
			// Pick a random neighbor
			int chosen = rand() % neighbors.size();
			toVisit.push(neighbors[chosen]);

			// Remove the wall between them
			removeWall(currRoom, neighbors[chosen]);

			// Move on
			currRoom = neighbors[chosen];
			visited[currRoom->row][currRoom->col] = true;
			unvisited--;
		}
		else
		{
			// backtrack
			currRoom = toVisit.top();
			toVisit.pop();
		}
	}
}

void Dungeon::removeWall(Room *a, Room *b)
{
	// If they are north/south of each other
	if(a->row != b->row)
	{
		// If a is above b
		if(a->row < b->row)
		{
			a->placeDoor(0,0,1,0);
			b->placeDoor(1,0,0,0);
		}
		else
		{
			a->placeDoor(1,0,0,0);
			b->placeDoor(0,0,1,0);
		}
	}
	else // east/west
	{
		// a is left of b
		if(a->col < b->col)
		{
			a->placeDoor(0,0,0,1);
			b->placeDoor(0,1,0,0);
		}
		else
		{
			a->placeDoor(0,1,0,0);
			b->placeDoor(0,0,0,1);
		}
	}
}

/*
 * For each neighbor, check to see if they have been visited yet. If not,
 * return them.
 */
vector<Room*> Dungeon::getLonelyNeighbors(Room *cell)
{
	// neighbors to return
	vector<Room*> ret;

	int r = cell->row;
	int c = cell->col;

	// North neighbor
	if(r > 0 && dungeon[r-1][c] != NULL && !visited[r-1][c])
	{
		ret.push_back(dungeon[r-1][c]);
	}

	// South neighbor
	if(r < numRows - 1 && dungeon[r+1][c] != NULL && !visited[r+1][c])
	{
		ret.push_back(dungeon[r+1][c]);
	}

	// West neighbor
	if(c > 0 && dungeon[r][c-1] != NULL && !visited[r][c-1])
	{
		ret.push_back(dungeon[r][c-1]);
	}

	// East neighbor
	if(c < numCols - 1 && dungeon[r][c+1] != NULL && !visited[r][c+1])
	{
		ret.push_back(dungeon[r][c+1]);
	}

	return ret;
}

glm::vec3 Dungeon::getStartingPos()
{
	float x, y;

	// south wall
	y = numRows * ROOM_LENGTH;

	// middle of wall
	x = (startCol * ROOM_WIDTH) + (ROOM_WIDTH / 2);

	return glm::vec3(x, 0, y);
}

Room* Dungeon::getRoom(int r, int c)
{
	// Check for an invalid request
	if(r < 0 || r >= numRows || c < 0 || c >= numCols)
	{
		return NULL;
	}

	return dungeon[r][c];
}

void Dungeon::setLights(float const * const positions,
						float const * const colors,
						int const count)
{
	// Store a ShaderManager over a program
	GLuint program = shaderManager->getProgram(2, "phongTex.vert",
		"phongTexPtLights.frag");
	glUseProgram(program);

	GLint lightLoc = glGetUniformLocation(program, "cameraSpaceLights");
	GLint lightColorLoc = glGetUniformLocation(program, "lightColors");
	GLint lightCntLoc = glGetUniformLocation(program, "lightCount");

	if(lightLoc != -1 && lightColorLoc != -1 && lightCntLoc != -1)
	{
		glUniform3fv(lightLoc, count, positions);
		glUniform3fv(lightColorLoc, count, colors);
		glUniform1i(lightCntLoc, count);
	}
	else
	{
		cerr << "Error: Cannot find point light locations" << endl;
		return;
	}
	
	glUseProgram(0);
}
