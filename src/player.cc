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
	glm::vec3 delta(0.0);

	if( input.IsKeyDown( sf::Key::A ) ) //move left
	{
		delta.x = -1;
	}
	if( input.IsKeyDown( sf::Key::S ) ) //move down
	{
		delta.z = 1;
	}
	if( input.IsKeyDown( sf::Key::D ) ) //move right
	{
		delta.x = 1;
	}
	if( input.IsKeyDown( sf::Key::W ) ) //move up
	{
		delta.z = -1;
	}
	if(glm::length(delta) == 0)
	{
		return;
	}
	delta = glm::normalize(delta) * playerMoveDistance;
	move(delta);
	camera->moveEye(delta);
	camera->moveAt(delta);
}
