#ifndef CAMERA_H
#define CAMERA_H

#include "GLM/glm.hpp"

class Camera
{
public:
	Camera();
	glm::mat4 getViewMatrix();
	void resetMatrix();
	void lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	void frustum(float left, float right
				 float bottom, float top,
				 float zNear, float zFar);
private:
	void rotate(glm::vec3 axis, float radians);
	void translate(glm::vec3 delta);
	glm::mat4 viewMatrix;
};

#endif
