#include "camera.h"
#include "GLM/gtc/matrix_transform.hpp"

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
	viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::moveEye(glm::vec3 const &eye)
{
	this->eye += eye;
	viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::moveUp(glm::vec3 const &up)
{
	this->up += up;
	viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::moveCloser(float distance)
{
	this->at = glm::normalize(at - eye) * distance;
	viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::perspective(float fov, float aspect, float zNear, float zFar)
{
	projMatrix = glm::perspective(fov, aspect, zNear, zFar);
}
