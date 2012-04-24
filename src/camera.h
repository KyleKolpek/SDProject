#ifndef CAMERA_H
#define CAMERA_H

#include "GLM/glm.hpp"

class Camera
{
public:
	Camera(glm::vec3 const &eye,
		   glm::vec3 const &at,
		   glm::vec3 const &up);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void setAt(glm::vec3 const &at);
	void setEye(glm::vec3 const &eye);
	void setUp(glm::vec3 const &up);
	void moveAt(glm::vec3 const &at);
	void moveEye(glm::vec3 const &eye);
	void moveUp(glm::vec3 const &up);
	void moveCloser(float distance);
	void perspective(float fov, float aspect, float zNear, float zFar);
private:
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
};

#endif
