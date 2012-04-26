#include "player.h"
#include "camera.h"
#include <SFML/System.hpp>
#include <iostream>
#include "GLM/gtx/compatibility.hpp"

using namespace std;

Player::Player(Camera *camera, Dungeon *dungeon):
	Actor(camera, dungeon)
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

	// Store the previous position for direction
	glm::vec3 prevPos = position;

	delta = glm::normalize(delta) * playerMoveDistance;
	move(delta);
	camera->moveEye(delta);
	camera->moveAt(delta);
#endif

	// Calculate the direction the player should face
	glm::vec3 direction(glm::normalize(position - prevPos));

	float theta = glm::degrees(glm::atan2(direction.y, direction.x)) - 90;
	cout << "Delta: " << direction.x << "," << direction.y << ","<< direction.z
	<< endl;
	cout << "Rotation: " << theta << endl;
	setRotation(theta);
}
