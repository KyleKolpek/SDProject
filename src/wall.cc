#include <iostream>
#include "SOIL/SOIL.h"
#include "wall.h"

using namespace std;

GLuint Wall::texture(NULL);

Wall::Wall(float x1, float y1,
		   float x2, float y2,
		   float height,
		   Camera *camera):
	x1(x1),
	y1(y1),
	x2(x2),
	y2(y2),
	height(height),
	camera(camera),
	vertexCount(4),
	offsetX(0),
	offsetY(0)
{
	glm::vec3 n = glm::cross(glm::vec3(0.0, 1.0, 0.0),
							 glm::vec3(x2 - x1, 0.0, y2 - y1));
	float u = 1.0,
		  v = glm::length(glm::vec3(x2 - x1, 0.0, y2 - y1)) / height; 
	float tmpVertexData[] = { x1, 0.0,  y1,
							 n.x, n.y, n.z,
							      0.0, 0.0,
							  x1, 4.0,  y1,
							 n.x, n.y, n.z,
							      0.0, u, // may need swapped
							  x2, 4.0,  y2,
							 n.x, n.y, n.z,
							      v, u, // may need swapped
							  x2, 0.0,  y2,
							 n.x, n.y, n.z,
							      v, 0.0};

    // Prepare vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 8 * sizeof(float), tmpVertexData,
		GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Wall::~Wall()
{
	//Nothing to do yet.
}

void Wall::draw()
{
	if(texture == NULL)
	{
		cerr << "Error: No texture loaded" << endl;
		return;
	}

	// Enable backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Store a ShaderManager over a program
	GLuint program = shaderManager->getProgram(2, "phongTex.vert",
		"phongTexPtLights.frag");
	glUseProgram(program);

	GLint mvLoc = glGetUniformLocation(program, "modelView");
	GLint nmvLoc = glGetUniformLocation(program, "normalModelView");
	GLint projLoc = glGetUniformLocation(program, "projection");
	GLint texLoc = glGetUniformLocation(program, "texture");

	glm::mat4 MV = camera->getViewMatrix() * getModelMatrix();
	glm::mat4 proj = camera->getProjectionMatrix();

	// TODO: Error check here.
	if(mvLoc != -1)
	{
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &MV[0][0]);
	}
	else
	{
		cerr << "Error: Cannot find modelView location" << endl;
		return;
	}

	if(nmvLoc != -1)
	{
		glUniformMatrix4fv(nmvLoc, 1, GL_FALSE,
			&glm::transpose(glm::inverse(MV))[0][0]);
	}
	else
	{
		cerr << "Error: Cannot find normalModelView location" << endl;
		return;
	}
	
	if(projLoc != -1)
	{
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
	}
	else
	{
		cerr << "Error: Cannot find projection location" << endl;
		return;
	}

	if(texLoc != -1)
	{
		glUniform1i(texLoc, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	else
	{
		cerr << "Error: Cannot find texture location" << endl;
		return;
	}

	GLuint vertexPosLoc = glGetAttribLocation(program, "vertexPosition");
	GLuint vertexNormalLoc = glGetAttribLocation(program, "vertexNormal");
	GLuint vertexTexCoordLoc = glGetAttribLocation(program, "vertexTexCoord");

	if(vertexPosLoc == -1)
	{
		cerr << "Error: Cannot find vertexPosition location" << endl;
		return;
	}
	if(vertexNormalLoc == -1)
	{
		cerr << "Error: Cannot find vertexNormal location" << endl;
		return;
	}
	if(vertexTexCoordLoc == -1)
	{
		cerr << "Error: Cannot find vertexTexCoord location" << endl;
		return;
	}

	glEnableVertexAttribArray(vertexPosLoc);
	glEnableVertexAttribArray(vertexNormalLoc);
	glEnableVertexAttribArray(vertexTexCoordLoc);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), 0);
	glVertexAttribPointer(vertexNormalLoc, 3, GL_FLOAT, GL_TRUE,
		8 * sizeof(float), (void *)(3 * sizeof(float)));
	glVertexAttribPointer(vertexTexCoordLoc, 2, GL_FLOAT, GL_TRUE,
		8 * sizeof(float), (void *)(6 * sizeof(float)));

	glDrawArrays(GL_QUADS, 0, vertexCount);
	glDisableVertexAttribArray(vertexPosLoc);
	glDisableVertexAttribArray(vertexNormalLoc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);

	glDisable(GL_CULL_FACE);
}

glm::mat4 Wall::getModelMatrix()
{
	return modelMatrix;
}

void Wall::translate(float x, float y)
{

	modelMatrix = glm::mat4(1.0, 0.0, 0.0, 0.0,
							0.0, 1.0, 0.0, 0.0,
							0.0, 0.0, 1.0, 0.0,
							  x, 0.0,   y, 1.0);
}
glm::vec2 Wall::getStartPoint()
{
	return glm::vec2(x1, y1);
}

glm::vec2 Wall::getEndPoint()
{
	return glm::vec2(x2, y2);
}

void Wall::loadTexture(string const &filename)
{
	// Load texture data
	texture = SOIL_load_OGL_texture(
		 filename.c_str(),
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
		 SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT |
		 SOIL_FLAG_TEXTURE_REPEATS);
}
