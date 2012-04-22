
#include "room.h"

Room::Room(int i, int j)
{
	row = i;
	col = j;

	y = row * ROOM_HEIGHT;
	x = col * ROOM_WIDTH;
}

void Room::draw()
{


}
