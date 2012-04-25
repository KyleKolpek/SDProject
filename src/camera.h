#ifndef CAMERA_H
#define CAMERA_H

#include "GLM/glm.hpp"
#include "updatable.h"

class Camera: public Updatable
{
public:
	Camera(glm::vec3 const &eye,
		   glm::vec3 const &at,
		   glm::vec3 const &up);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	
	// These set the 3 vectors
	void setAt(glm::vec3 const &at);
	void setEye(glm::vec3 const &eye);
	void setUp(glm::vec3 const &up);

	// These modify the 3 vectors
	void moveAt(glm::vec3 const &at);
	void moveEye(glm::vec3 const &eye);
	void moveUp(glm::vec3 const &up);
	void moveTowardsAt(float distance);

	void perspective(float fov, float aspect, float zNear, float zFar);
	void update(sf::Clock const &clock, sf::Input const &input);
private:
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
};

#endif
