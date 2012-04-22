
#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>

#include "drawable.h"
#include "room.h"

class Dungeon : public Drawable
{
public:
	Dungeon(int rows, int cols, int rooms);
	~Dungeon();

	void draw();

	// Return a string representation of dungeon
	std::string str();

private:
	int numRows;
	int numCols;
	int numRooms;

	// 2D array of room pointers
	Room ***dungeon;
	std::vector<Room*> rooms;

	void generateDungeon();
	void assignRoomTypes();
	void orientRooms();
};

#endif
