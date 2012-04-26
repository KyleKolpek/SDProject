#include "player.h"
#include "camera.h"
#include <SFML/System.hpp>
#include <iostream>

Player::Player(Camera *camera):
	Actor(camera)
{
	
}

Player::~Player()
{
	
}

void Player::update(float sec, sf::Input const &input)
{
#ifdef DEBUG
	// Make him move
	float playerMoveDistance = moveSpeed * sec;

	if( input.IsKeyDown( sf::Key::A ) ) //move left
	{
		// move player and camera
		move( glm::vec3( playerMoveDistance*(-1.0), 0.0, 0.0 ) );
		camera->moveEye( glm::vec3( playerMoveDistance*(-1.0), 0.0, 0.0 ));
		camera->setAt( this->position );

		// rotate
		setRotation(270.0);
	}
	else if( input.IsKeyDown( sf::Key::S ) ) //move down
	{
		// move player and camera
		move( glm::vec3( 0.0, 0.0, playerMoveDistance ) );
		camera->moveEye( glm::vec3( 0.0, 0.0, playerMoveDistance ));
		camera->setAt( this->position );
		
		// rotate
		setRotation(180.0);
	}
	else if( input.IsKeyDown( sf::Key::D ) ) //move right
	{
		// move player and camera
		move( glm::vec3( playerMoveDistance, 0.0, 0.0 ) );
		camera->moveEye( glm::vec3( playerMoveDistance, 0.0, 0.0 ));
		camera->setAt( this->position );

		// rotate
		setRotation(90.0);
	}
	else if( input.IsKeyDown( sf::Key::W ) ) //move up
	{
		// move player and camera
		move( glm::vec3( 0.0, 0.0, playerMoveDistance*(-1.0) ) );
		camera->moveEye( glm::vec3( 0.0, 0.0, playerMoveDistance*(-1.0) ));
		camera->setAt( this->position );

		//rotate
		setRotation(0.0);
	}
#endif
}
