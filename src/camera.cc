#include "camera.h"
#include "GLM/gtc/matrix_transform.hpp"
#include <iostream>

Camera::Camera(glm::vec3 const &eye,
			   glm::vec3 const &at,
			   glm::vec3 const &up):
	eye(eye),
	at(at),
	up(up),
	viewMatrix(1.0),
	projMatrix(1.0)
{
	viewMatrix = glm::lookAt(eye, at, up);
}

glm::mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return projMatrix;
}

void Camera::setAt(glm::vec3 const &at)
{
	this->at = at;
	viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::setEye(glm::vec3 const &eye)
{
	this->eye = eye;
	viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::setUp(glm::vec3 const &up)
{
	this->up = up;
	viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::moveAt(glm::vec3 const &at)
{
	this->at += at;
	viewMatrix = glm::lookAt(this->eye, this->at, this->up);
}

void Camera::moveEye(glm::vec3 const &eye)
{
	this->eye += eye;
	viewMatrix = glm::lookAt(this->eye, this->at, this->up);
}

void Camera::moveUp(glm::vec3 const &up)
{
	this->up += up;
	viewMatrix = glm::lookAt(this->eye, this->at, this->up);
}

void Camera::moveTowardsAt(float distance)
{
	this->eye += glm::normalize(at - eye) * distance;
	viewMatrix = glm::lookAt(this->eye, this->at, this->up);
}

void Camera::perspective(float fov, float aspect, float zNear, float zFar)
{
	projMatrix = glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::update(sf::Clock const &clock, sf::Input const &input)
{
	// ADD CAMERA MOVEMENT HER
	if( input.IsKeyDown(sf::Key::Left ) )
	{
		std::cout << "move left" << std::endl;
		moveEye(glm::vec3( -1.0,0.0,0.0 ));
		moveAt(glm::vec3( -1.0,0.0,0.0 ));
	}
	else if( input.IsKeyDown(sf::Key::Right) )
	{
		std::cout << "move right" << std::endl;
		moveEye(glm::vec3( 1.0,0.0,0.0 ));
		moveAt(glm::vec3( 1.0,0.0,0.0 ));
	}
	if( input.IsKeyDown(sf::Key::Up ))
	{
		std::cout << "move up" << std::endl;
		moveEye(glm::vec3( 0.0,0.0,-1.0 ));
		moveAt(glm::vec3( 0.0,0.0,-1.0 ));
	}
	else if( input.IsKeyDown(sf::Key::Down ))
	{
		std::cout << "move down" << std::endl;
		moveEye(glm::vec3( 0.0,0.0,1.0 ));
		moveAt(glm::vec3( 0.0,0.0,1.0 ));
	}
	if( input.IsKeyDown(sf::Key::PageUp) )
	{
		std::cout << "zoom in" << std::endl;
		moveTowardsAt( 1.0 ); //TODO: Broken
	}
	else if( input.IsKeyDown(sf::Key::PageDown) )
	{
		std::cout << "zoom out" << std::endl;
		moveTowardsAt( -1.0 ); //TODO: Broken
	}
}
