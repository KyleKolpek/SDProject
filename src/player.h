#ifndef PLAYER_H
#define PLAYER_H

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
