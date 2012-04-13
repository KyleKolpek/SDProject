#ifndef CAMERA_H
#define CAMERA_H

#include "GLM/glm.hpp"

class Camera
{
public:
	Camera();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void lookAt(glm::vec3 const &eye,
				glm::vec3 const &center,
				glm::vec3 const &up);
	void perspective(float fov, float aspect, float zNear, float zFar);
private:
	void rotate(glm::vec3 axis, float radians);
	void translate(glm::vec3 delta);
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
};

#endif
