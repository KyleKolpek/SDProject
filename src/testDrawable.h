#ifndef TESTDRAWABLE_H
#define TESTDRAWABLE_H

#include "camera.h"
#include "drawable.h"
#include "GLM/glm.hpp"

class TestDrawable: public Drawable
{
public:
	TestDrawable(Camera *camera);
	~TestDrawable();

	void draw();
private:
	int vertexCount;
	float *vertexData;
	GLuint vertexBuffer;
	Camera *camera;
	glm::mat4 getModelMatrix();
};

#endif
