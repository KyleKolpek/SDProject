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
	// Make him move
	float playerMoveDistance = moveSpeed * sec;

	if( input.IsKeyDown( sf::Key::A ) ) //move left
	{
		move( glm::vec3( playerMoveDistance*(-1.0), 0.0, 0.0 ) );
		camera->moveEye( glm::vec3( playerMoveDistance*(-1.0), 0.0, 0.0 ));
		camera->setAt( this->position );
	}
	else if( input.IsKeyDown( sf::Key::S ) ) //move down
	{
		move( glm::vec3( 0.0, 0.0, playerMoveDistance ) );
		camera->moveEye( glm::vec3( 0.0, 0.0, playerMoveDistance ));
		camera->setAt( this->position );

	}
	else if( input.IsKeyDown( sf::Key::D ) ) //move right
	{
		move( glm::vec3( playerMoveDistance, 0.0, 0.0 ) );
		camera->moveEye( glm::vec3( playerMoveDistance, 0.0, 0.0 ));
		camera->setAt( this->position );
	}
	else if( input.IsKeyDown( sf::Key::W ) ) //move up
	{
		move( glm::vec3( 0.0, 0.0, playerMoveDistance*(-1.0) ) );
		camera->moveEye( glm::vec3( 0.0, 0.0, playerMoveDistance*(-1.0) ));
		camera->setAt( this->position );
	}
}
