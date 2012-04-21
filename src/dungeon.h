
#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>

// Room dimensions
#define ROOM_WIDTH 10
#define ROM_HEIGHT 10

struct Room
{
	int row, col;

	enum RoomType{ ONE, TWOA, TWOB, THREE, FOUR } roomType;

	// TODO: Wall class
	int walls[4];

	Room(int i, int j) { row = i; col = j; }
};

class Dungeon
{
	public:
		Dungeon(int rows, int cols, int rooms);
		~Dungeon();

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
};

#endif
