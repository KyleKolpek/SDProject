#ifndef PLAYER_H
#define PLAYER_H

#include "stdgl.h"
#include "actor.h"

class Camera;

/***************************************************************************//**
 * Player Character
 * Holds information and methods for the player character. The one the user gets
 * to manipulate.
 ******************************************************************************/
class Player: public Actor
{
public:

	/***********************************************************************//**
 	 * Default Constructor
 	 * \params[in] camera
	 *     Pointer to the camera class
	 * \params[in] dungeon
	 *     Pointer to the dungeon for collision detection with walls.
	 * \params[in] obj
	 *     String containing the obj file to open for this model.
	 * \params[in] tex
	 *     String containing the texture file to open for this model.
	 * \params[in] objLoader
	 *     Pointer to ObjLoader class, that allows this class use of loaded
	 *     models.
 	 **************************************************************************/
	Player(Camera *camera, 
		Dungeon *dungeon, 
		std::string obj, 
		std::string tex,
		ObjLoader *objLoader);
	
	/***********************************************************************//**
 	 * Default Destructor()
 	 **************************************************************************/
	~Player();

	/***********************************************************************//**
 	 * Updates the information of the player.
	 * \params[in] sec
	 *     Time in seconds since last update. This class is time based not frame.
	 * \params[in] input
	 *     The input that was read that triggered the update event. It will check
	 *     this to see if it is one of it's actions.
 	 **************************************************************************/
	virtual void update(float sec, sf::Input const &input);
	
	/***********************************************************************//**
 	 * Checks if the player is the current active player (e.g. it's the players
	 * turn).
 	 **************************************************************************/
	bool isActive();

	/***********************************************************************//**
 	 * Set the current player as the active player. Make it this player's turn.
 	 **************************************************************************/
	void setActive();

	/***********************************************************************//**
 	 * End the player's turn. Not active in moving anymore.
 	 **************************************************************************/
	void setInactive();

protected:
	/***********************************************************************//**
 	 * Tells us if this player is currently active or not.
 	 **************************************************************************/
	bool activePlayer;
};
#endif
