#ifndef CHARACTER_H
#define CHARACTER_H

#include "drawable.h"
#include "GLM/glm.hpp"

class Camera;

class Character: public Drawable
{
public:
	Character(Camera *camera);
	~Character();

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
