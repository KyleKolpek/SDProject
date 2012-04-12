#include "camera.h"
#include "GLM/gtc/matrix_transform.hpp"

Camera::Camera():
	viewMatrix(1.0),
	projMatrix(1.0)
{
}

glm::mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return projMatrix;
}

void Camera::lookAt(glm::vec3 const eye,
					glm::vec3 const at,
					glm::vec3 const up)
{
	/*glm::vec3 fN  = glm::normalize(at - eye);
	glm::vec3 upN = glm::normalize(up);
	glm::vec3 s   = glm::cross(f, up);
	glm::vec3 u   = glm::cross(s, f);
	glm::mat4 M   = glm::mat4(1.0);
	M[0][0] =  s[0];
	M[0][1] =  u[0];
	M[0][2] = -f[0];
	M[1][0] =  s[1];
	M[1][1] =  u[1];
	M[1][2] = -f[1];
	M[2][0] =  s[2];
	M[2][1] =  u[2];
	M[2][2] = -f[2];*/
	viewMatrix = glm::lookAt(eye, at, up);
}

void Camera::perspective(float fov, float aspect, float zNear, float zFar)
{
	projMatrix = glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::rotate(glm::vec3 axis, float radians)
{
}

void Camera::translate(glm::vec3 delta)
{
}
