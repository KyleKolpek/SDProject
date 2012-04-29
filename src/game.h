#ifndef GAME_H
#define GAME_H

#include "stdgl.h"
#include <SFML/Window.hpp>
#include <vector>
#include "player.h"

class Camera;
class Dungeon;
class ObjLoader;


/***************************************************************************//**
 * This is where all parts of the game happen. From rendering the scene to 
 * holding all the information on actors, and even controlling game states.
 ******************************************************************************/
class Game: public Updatable, public Drawable
{
public:
	/***********************************************************************//**
 	 * Default Constructor
 	 **************************************************************************/
	Game();
	
	/***********************************************************************//**
 	 * Default Destructor
 	 **************************************************************************/
	~Game();

	/***********************************************************************//**
 	 * Updates the Game based on the input received.
	 * \params[in] sec
	 *     Time in seconds since the last update. Game is time based.
	 * \params[in] input
	 *     The input that triggered the update event.
 	 **************************************************************************/
	void update(float sec, sf::Input const &input);

	/***********************************************************************//**
 	 * Draws all the parts of the game, and calls draw methods down the line.
 	 **************************************************************************/
	void draw();

	/***********************************************************************//**
 	 * Gets the stamina rating of the active player to display how much 
	 * movement they have left.
 	 **************************************************************************/
	float getActivePlayerStamina();

	/***********************************************************************//**
	 * Initialize the specifics of the game, such as camera, dungeon and
	 * players
	 **************************************************************************/
	void gameInit();

	/***********************************************************************//**
	 * Sets the number of players for the game. Should never be called in the
	 * middle of a game.
	 **************************************************************************/
	void setNumPlayers(int newNumPlayers);

protected:
	/***********************************************************************//**
 	 * Flag for tab being pressed.
 	 **************************************************************************/
	bool tabPressNew;

	/***********************************************************************//**
 	 * The total number of players.
 	 **************************************************************************/
	int numPlayers;
	
	/***********************************************************************//**
 	 * Index of the current active player.
 	 **************************************************************************/
	int currentPlayer;

	/***********************************************************************//**
 	 * Pointer to the camera.
 	 **************************************************************************/
	Camera *camera;

	/***********************************************************************//**
 	 * Pointer to the dungeon. This is where the map is created and displated.
 	 **************************************************************************/
	Dungeon *dungeon;

	/***********************************************************************//**
 	 * Point to the wavefront obj loader. Loads all the models in the beginning
	 * and then gives out the information as needed.
 	 **************************************************************************/
	ObjLoader *loader;

	/***********************************************************************//**
 	 * Vector of players that will play the game.
 	 **************************************************************************/
	std::vector<Player*> players;


};

#endif
