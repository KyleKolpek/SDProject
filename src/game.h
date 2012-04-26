#ifndef GAME_H
#define GAME_H

#include "stdgl.h"
#include <SFML/Window.hpp>
#include <vector>
#include "player.h"

class Camera;
class Dungeon;
class ObjLoader;

class Game: public Updatable, public Drawable
{
public:
	// Constructor
	Game();
	
	//Destructor
	~Game();

	void update(float sec, sf::Input const &input);

	void draw();

	float getActivePlayerStamina();

protected:
	bool tabPressNew;
	int numPlayers;
	int currentPlayer;
	Camera *camera;
	Dungeon *dungeon;
	ObjLoader *loader;
	std::vector<Player*> players;


};

#endif
