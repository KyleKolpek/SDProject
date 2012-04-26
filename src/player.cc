#include "player.h"
#include "camera.h"
#include <SFML/System.hpp>
#include <iostream>
#include "GLM/gtx/compatibility.hpp"

using namespace std;

Player::Player(Camera *camera, Dungeon *dungeon, string obj, string tex):
	Actor(camera, dungeon, obj, tex)
{
	activePlayer=false;
}

Player::~Player()
{
	// TODO: implement destructor
}

bool Player::isActive()
{
	return activePlayer;
}

void Player::setActive()
{
	activePlayer = true;
}

void Player::setInactive()
{
	activePlayer = false;
}

void Player::update(float sec, sf::Input const &input)
{

	if( activePlayer )
	{
		// Use input sf::Input to move the player character
		
		// playerMoveDistance: calculate distance traveled by multiplying movement
		//                     speed and the time since last frame
		float playerMoveDistance = moveSpeed * sec;
	
		// delta: starts at (0,0,0), changes in following if statements depending
		//        on user input
		glm::vec3 delta(0.0); 
							
		if( input.IsKeyDown( sf::Key::A ) ) // User presses a, wants to move left
		{
			delta.x -= 1;
		}
		if( input.IsKeyDown( sf::Key::S ) ) // user presses s, wants to move down
		{
			delta.z += 1;
		}
		if( input.IsKeyDown( sf::Key::D ) ) // user presses d, wants to move right
		{
			delta.x += 1;
		}
		if( input.IsKeyDown( sf::Key::W ) ) // user presses w, wants to move up
		{
			delta.z -= 1;
		}
		if(glm::length(delta) != 0)         // movement delta = 0, so no movement
		{
			// Normalize delta so player moves at same speed as diagonal
			delta = glm::normalize(delta) * playerMoveDistance;
			
			move(delta);
		}
	
		glm::vec3 cameraDelta((position - camera->getAt()) * 5.0f * sec) ;
		camera->moveEye(cameraDelta);
		camera->moveAt(cameraDelta);
	}
}

