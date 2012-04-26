#include <cstdio>
#include <algorithm>
#include <iostream>

#include "room.h"
#include "SOIL/SOIL.h"
#include <time.h>
#include <cstdlib>

using namespace std;

GLuint Room::texture(NULL);

#define NORTH 0
#define WEST 1
#define SOUTH 2
#define EAST 3

Room::Room(int row, 
		int col, 
		Camera *camera, 
		Dungeon *dungeon,
		ObjLoader *objLoader):
	row(row),
	col(col),
	camera(camera),
	vertexBuffer(NULL),
	vertexCount(4),
	modelMatrix(1.0),
	dungeon(dungeon),
	objLoader(objLoader)
{
	for(int i = 0; i < ROOM_WIDTH; ++i)
	{
		for(int j = 0; j < ROOM_LENGTH; ++j)
		{
			objPresent[i][j] = false;
		}
	}
	// Initialize hasDoor
	hasDoor = vector<int>(4, 0);

	y = row * ROOM_LENGTH;
	x = col * ROOM_WIDTH;

	float u = ROOM_WIDTH/3,
		  v = ROOM_LENGTH/3;

	float tmpVertexData[] = {0.0, 0.0, 0.0,
							 0.0, 1.0, 0.0,
							      0.0, 0.0,
							 0.0, 0.0, ROOM_WIDTH,
							 0.0, 1.0, 0.0,
							      0.0, v, // may need swapped
							 ROOM_LENGTH, 0.0, ROOM_WIDTH,
							 0.0, 1.0, 0.0,
							      u, v, // may need swapped
							 ROOM_LENGTH, 0.0, 0.0,
							 0.0, 1.0, 0.0,
							      u, 0.0};

	modelMatrix = glm::mat4(1.0, 0.0, 0.0, 0.0,
							0.0, 1.0, 0.0, 0.0,
							0.0, 0.0, 1.0, 0.0,
							  x, 0.0,   y, 1.0);

    // Prepare vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 8 * sizeof(float), tmpVertexData,
		GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create some objects.
	for(int i = 0; i < 1; ++i)
	{
		string objName = "../assets/models/box/box.obj";
		string texName = "../assets/models/box/box.jpg";
		Actor *newObj = new Actor(camera, dungeon, objName, texName, objLoader);
		int xPlace = rand() % ROOM_WIDTH;
		int yPlace = rand() % ROOM_LENGTH;
		while(objPresent[xPlace][yPlace])
		{
			xPlace = rand() % ROOM_WIDTH;
			yPlace = rand() % ROOM_LENGTH;
		}	
		float scale = (float)(rand() % 10 + 10)/10;
		float rot = (float) (rand() % 90);
		glm::vec3 pos(xPlace + this->x, 0, yPlace + this->y);
		objPresent[xPlace][yPlace] = true;
		newObj->setPosition(pos);
		newObj->setScale(scale);
		newObj->setRotation(rot);
		objects.push_back(newObj);
	}
}

void Room::placeWalls()
{
	// The points to place the beginning and end of doors. Since rooms are
	// square we the same values can be used for either x or y.
	// Center them in walls.
	float doorStart = (ROOM_WIDTH / 2) - (DOOR_WIDTH / 2);
	float doorEnd = (ROOM_WIDTH / 2) + (DOOR_WIDTH / 2);

	// Now traverse each wall and create the wall objects
	if(hasDoor[NORTH])
	{
		walls.push_back(Wall(0, 0, doorStart, 0, ROOM_HEIGHT, camera));
		walls.push_back(Wall(doorEnd, 0, ROOM_WIDTH, 0, ROOM_HEIGHT, camera));
	}
	else
	{
		walls.push_back(Wall(0, 0, ROOM_WIDTH, 0, ROOM_HEIGHT, camera));
	}

	if(hasDoor[WEST])
	{
		walls.push_back(Wall(0, 0, 0, doorStart, ROOM_HEIGHT, camera));
		walls.push_back(Wall(0, doorEnd, 0, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}
	else
	{
		walls.push_back(Wall(0, 0, 0, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}

	if(hasDoor[SOUTH])
	{
		walls.push_back(Wall(0, ROOM_LENGTH, doorStart, ROOM_LENGTH,
			ROOM_HEIGHT, camera));
		walls.push_back(Wall(doorEnd, ROOM_LENGTH,
			ROOM_WIDTH, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}
	else
	{
		walls.push_back(Wall(0, ROOM_LENGTH,
			ROOM_WIDTH, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}

	if(hasDoor[EAST])
	{
		walls.push_back(Wall(ROOM_WIDTH, 0, ROOM_WIDTH, doorStart,
			ROOM_HEIGHT, camera));
		walls.push_back(Wall(ROOM_WIDTH, doorEnd,
			ROOM_WIDTH, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}
	else
	{
		walls.push_back(Wall(ROOM_WIDTH, 0,
			ROOM_WIDTH, ROOM_LENGTH, ROOM_HEIGHT, camera));
	}
	
	for(vector<Wall>::iterator it = walls.begin(); it < walls.end(); it++)
	{
		(*it).translate(col * ROOM_WIDTH, row * ROOM_LENGTH);
	}
}

void Room::placeDoor(int n, int w, int s, int e)
{
	hasDoor[NORTH] += n;
	hasDoor[SOUTH] += s;
	hasDoor[EAST] += e;
	hasDoor[WEST] += w;
}

void Room::draw()
{
	// Draw the floor
	if(texture == NULL)
	{
		cerr << "Error: No texture loaded" << endl;
		return;
	}

	// Store a ShaderManager over a program
	GLuint program = shaderManager->getProgram(2, "phongTex.vert",
		"phongTexPtLights.frag");
	glUseProgram(program);

	GLint mvLoc = glGetUniformLocation(program, "modelView");
	GLint nmvLoc = glGetUniformLocation(program, "normalModelView");
	GLint projLoc = glGetUniformLocation(program, "projection");
	GLint texLoc = glGetUniformLocation(program, "texture");
	GLint lightLoc = glGetUniformLocation(program, "cameraSpaceLights");
	GLint lightColorLoc = glGetUniformLocation(program, "lightColors");
	GLint lightCntLoc = glGetUniformLocation(program, "lightCount");

	

	glm::mat4 MV = camera->getViewMatrix() * getModelMatrix();
	glm::mat4 proj = camera->getProjectionMatrix();

	if(lightLoc != -1 && lightColorLoc != -1 && lightCntLoc != -1)
	{
		glUniform3f(lightLoc, 0.0, 0.0, -5.0);
		glUniform3f(lightColorLoc, 0.5, 0.0, 0.0);
		glUniform1i(lightCntLoc, 1);
	}
	else
	{
		cerr << "Error: Cannot find modelView location" << endl;
		return;
	}

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

	// Draw the walls
	for(vector<Wall>::iterator it = walls.begin(); it < walls.end(); it++)
	{
		(*it).draw();
	}

	for(size_t i = 0; i < objects.size(); ++i)
	{
		objects[i]->setShaderManager(shaderManager);
		objects[i]->draw();
	}
}

void Room::setShaderManager(ShaderManager *shaderManager)
{
	Drawable::setShaderManager(shaderManager);
	
	// Add shader manager to walls
	for(vector<Wall>::iterator it = walls.begin(); it < walls.end(); it++)
	{
		(*it).setShaderManager(shaderManager);
	}
}

glm::mat4 Room::getModelMatrix()
{
	return modelMatrix;
}

void Room::loadTexture(string const &filename)
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
