#ifndef ACTOR_H
#define ACTOR_H

#include "stdgl.h"
#include <SFML/Window.hpp>
#include "drawable.h"
#include "updatable.h"
#include "GLM/glm.hpp"

class Camera;

class Actor: public Drawable, public Updatable
{
public:
	Actor(Camera *camera);
	~Actor();

	virtual void draw();
	virtual void update(float sec, sf::Input const &input);

private:
	int x;
	int y;
	int z;
	int vertexCount;
	int *indexData;
	float *vertexData;
	GLuint vertexBuffer;
	GLuint dataType;
	GLuint texture;
	Camera *camera;

	glm::mat4 getModelMatrix();
};

#endif
