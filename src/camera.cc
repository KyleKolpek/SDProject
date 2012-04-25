#include "camera.h"
#include "GLM/gtc/matrix_transform.hpp"
#include <iostream>
#include <SFML/System.hpp>

float Camera::camSpeed(50.0);

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

void Camera::update(float sec, sf::Input const &input)
{
	// ADD CAMERA MOVEMENT HERE
	float cameraMoveDistance = camSpeed * sec;
	
	if( input.IsKeyDown(sf::Key::Left ) )
	{
		moveEye(glm::vec3( cameraMoveDistance*(-1.0), 0.0, 0.0 ));
		moveAt(glm::vec3( cameraMoveDistance*(-1.0), 0.0, 0.0 ));
	}
	else if( input.IsKeyDown(sf::Key::Right) )
	{
		moveEye(glm::vec3( cameraMoveDistance, 0.0, 0.0 ));
		moveAt(glm::vec3( cameraMoveDistance, 0.0, 0.0 ));
	}
	if( input.IsKeyDown(sf::Key::Up ))
	{
		moveEye(glm::vec3( 0.0, 0.0, cameraMoveDistance*(-1.0) ));
		moveAt(glm::vec3( 0.0, 0.0, cameraMoveDistance*(-1.0) ));
	}
	else if( input.IsKeyDown(sf::Key::Down ))
	{
		moveEye(glm::vec3( 0.0, 0.0, cameraMoveDistance ));
		moveAt(glm::vec3( 0.0, 0.0, cameraMoveDistance ));
	}
	if( input.IsKeyDown(sf::Key::PageUp) )
	{
		moveTowardsAt( cameraMoveDistance );
	}
	else if( input.IsKeyDown(sf::Key::PageDown) )
	{
		moveTowardsAt( cameraMoveDistance*(-1.0) );
	}

	// TODO: play with rotation
	if( input.IsKeyDown( sf::Key::LBracket ) )	// rotate camera clockwise
	{
		std::cout << "rotate left" << std::endl;
	}
	else if( input.IsKeyDown( sf::Key::RBracket ) ) // rotate camere counter-clockwise
	{
		std::cout << "rotate right" << std::endl;
	}
}
