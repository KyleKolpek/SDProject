#ifndef ACTOR_H
#define ACTOR_H

#include "drawable.h"
#include "GLM/glm.hpp"

class Camera;

class Actor: public Drawable
{
public:
	Actor(Camera *camera);
	~Actor();

	void draw();
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
