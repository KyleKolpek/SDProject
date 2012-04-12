#ifdef CHARACTER_H
#define CHARACTER_H

#include "camera.h"
#include "drawable.h"
#include "GLM/glm.hpp"

class Character: Drawable
{
public:
	Character(Camera *camera);
	~Character();

	void draw();
private:
	int     x;
	int     y;
	int     z;
	int     vertexCount;
	float  *vertexData;
	float  *indexData;
	GLuint  vertexBuffer;
	GLuint  dataType;
	Camera *camera;

	glm::mat4 getModelMatrix();
};

#endif
