#ifndef PLAYER_H
#define PLAYER_H

#include "stdgl.h"
#include "actor.h"

class Camera;

class Player: public Actor
{
public:
	Player(Camera *camera, 
		Dungeon *dungeon, 
		std::string obj, 
		std::string tex,
		ObjLoader *objLoader);
	~Player();
	virtual void update(float sec, sf::Input const &input);
	bool isActive();
	void setActive( bool set );

protected:
	bool activePlayer;
};
#endif
