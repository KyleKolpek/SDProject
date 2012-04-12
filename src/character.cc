#include "objLoader.h"

Character::Character(Camera *camera):
	x(0),
	y(0),
	z(-17),
	vertexDataSize(0),
	vertexData(NULL),
	vertexBuffer(NULL),
	camera(camera)
{
	ObjLoader loader();
	loader.getData("../assets/models/Legoman/Legoman.obj",
				   vertexData,
				   indexData,
				   dataDype,
				   vertexCount);
}

void Character::draw()
{
	glUseProgram(program);

	GLint mvLoc = glGetUniformLocation(program, "modelView");
	GLint nmvLoc = glGetUniformLocation(program, "normalModelView");

	glm::mat4 MV = getModelMatrix() * camera.getViewMatrix();

	if(mvLoc != -1)
	{
		glUniformMatrix4v(mvLoc, 1, GL_FALSE, &MV[0][0]);
	}

	if(nmvLoc != -1)
	{
		glUniformMatrix4v(nmvLoc, 1, GL_FALSE,
			glm::transpose(glm::inverse(&MV[0][0])));
	}

	GLuint vertexPosLoc = glGetAttribLocation(program, "position");
	GLuint vertexNormalLoc = glGetAttribLocation(program, "normal");

	glBindBuffer(GL_ARRAY_BUFFER);
	glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), 0);
	glVertexAttribPointer(vertexNormalLoc, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), (void *)(3 * sizeof(float)));

	glDrawArray(GL_TRIANGLES, 0, vertexDataCount);
}

glm::mat4 getModelMatrix()
{
	return glm::mat4(1.0, 0.0, 0.0, 0.0,
					 0.0, 1.0, 0.0, 0.0,
					 0.0, 0.0, 1.0, 0.0,
					   x,   y,   z, 1.0);
}
