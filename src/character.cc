#include <iostream>
#include "SOIL/SOIL.h"
#include "character.h"
#include "camera.h"
#include "objLoader.h"

using namespace std;

Character::Character(Camera *camera):
	x(0),
	y(0),
	z(-17),
	vertexCount(0),
	vertexData(NULL),
	vertexBuffer(NULL),
	texture(NULL),
	camera(camera)
{
	ObjLoader loader;
	loader.loadModelData("../assets/models/Legoman/LegoMan.obj");
	vertexData  = loader.getVertexData();
	dataType    = loader.getType();
	vertexCount = loader.getVertexCount();
	texture = SOIL_load_OGL_texture(
		 "../assets/models/Legoman/Texture.png",
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
		 SOIL_FLAG_NTSC_SAFE_RGB |
		 SOIL_FLAG_COMPRESS_TO_DXT);

    // Prepare vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // Add vertedData to a buffer
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 8 * sizeof(float), vertexData,
        GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Character::~Character()
{
	delete[] vertexData;
	delete[] indexData;
}

void Character::draw()
{
	// Store a ShaderManager over a program
	GLuint program = shaderManager->getProgram(2, "phong.vert", "phong.frag");
	glUseProgram(program);

	GLint mvLoc = glGetUniformLocation(program, "modelView");
	GLint nmvLoc = glGetUniformLocation(program, "normalModelView");
	GLint projLoc = glGetUniformLocation(program, "projection");

	glm::mat4 MV = getModelMatrix() * camera->getViewMatrix();
	glm::mat4 proj = camera->getProjectionMatrix();

	// TODO: Error check here.
	if(mvLoc != -1)
	{
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &MV[0][0]);
	}
	else
	{
		cout << "Error" << endl;
		return;
	}

	if(nmvLoc != -1)
	{
		glUniformMatrix4fv(nmvLoc, 1, GL_FALSE,
			&glm::transpose(glm::inverse(MV))[0][0]);
	}
	else
	{
		cout << "Error" << endl;
		return;
	}
	
	if(projLoc != -1)
	{
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
	}
	else
	{
		cout << "Error" << endl;
		return;
	}

	GLuint vertexPosLoc = glGetAttribLocation(program, "vertexPosition");
	GLuint vertexNormalLoc = glGetAttribLocation(program, "vertexNormal");

	if(vertexPosLoc == -1)
	{
		cout << "Error" << endl;
		return;
	}
	if(vertexNormalLoc == -1)
	{
		cout << "Error" << endl;
		return;
	}

	glEnableVertexAttribArray(vertexPosLoc);
	glEnableVertexAttribArray(vertexNormalLoc);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), 0);
	glVertexAttribPointer(vertexNormalLoc, 3, GL_FLOAT, GL_TRUE,
		8 * sizeof(float), (void *)(3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glDisableVertexAttribArray(vertexPosLoc);
	glDisableVertexAttribArray(vertexNormalLoc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

glm::mat4 Character::getModelMatrix()
{
	return glm::mat4(1.0, 0.0, 0.0, 0.0,
					 0.0, 1.0, 0.0, 0.0,
					 0.0, 0.0, 1.0, 0.0,
					   x,   y,   z, 1.0);
}
