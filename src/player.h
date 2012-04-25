#ifndef PLAYER_H
#define PLAYER_H

#include "stdgl.h"
#include "actor.h"

class Camera;

class Player: public Actor
{
public:
	Player(Camera *camera);
	~Player();
	virtual void update(float sec, sf::Input const &input);

//protected:

};
#endif
