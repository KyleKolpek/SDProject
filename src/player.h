#ifndef PLAYER_H
#define PLAYER_H

#include "stdgl.h"
#include <SFML/Window.hpp>
#include "actor.h"

class Player: public Actor
{
public:
	Player();
	~Player();
	virtual void update(float sec, sf::Input const &input);

protected:
	float speed;
};
#endif
