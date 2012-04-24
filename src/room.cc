#include <cstdio>
#include <algorithm>
#include <iostream>

#include "room.h"
#include "SOIL/SOIL.h"

using namespace std;

GLuint Room::texture(NULL);

Room::Room(int row, int col, Camera *camera):
	row(row),
	col(col),
	camera(camera),
	vertexBuffer(NULL),
	vertexCount(4),
	modelMatrix(1.0)
{
	y = row * ROOM_LENGTH;
	x = col * ROOM_WIDTH;

	float tmpVertexData[] = {0.0, 0.0, 0.0,
							 0.0, 1.0, 0.0,
							      0.0, 0.0,
							 0.0, 0.0, ROOM_WIDTH,
							 0.0, 1.0, 0.0,
							      0.0, 1.0, // may need swapped
							 ROOM_LENGTH, 0.0, ROOM_WIDTH,
							 0.0, 1.0, 0.0,
							      1.0, 1.0, // may need swapped
							 ROOM_LENGTH, 0.0, 0.0,
							 0.0, 1.0, 0.0,
							      1.0, 0.0};

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
}

void Room::placeWalls(int northDoor, int westDoor, int southDoor, int eastDoor)
{
	// First determine which walls need doors. Store a vector sides with doors.
	#define NORTH 0
	#define WEST 1
	#define SOUTH 2
	#define EAST 3

	vector<int> doors;

	switch(roomType)
	{
		case ONE:
			doors.push_back(orient);
			break;

		case TWOA:
			doors.push_back(NORTH + orient);
			doors.push_back(WEST + orient);
			printf("TWOA: doors: %d %d\n", doors[0], doors[1]);
			break;

		case TWOB:
			doors.push_back(NORTH + orient);
			doors.push_back(SOUTH + orient);
			break;

		case THREE:
			doors.push_back(NORTH + orient);
			doors.push_back(WEST + orient);
			doors.push_back(SOUTH + orient);
			break;

		case FOUR:
			doors.push_back(NORTH);
			doors.push_back(WEST);
			doors.push_back(SOUTH);
			doors.push_back(EAST);
			break;
	}

	vector<int> hasDoor(4, 0);

	// User has option of manually placing doors.
	hasDoor[NORTH] = northDoor;
	hasDoor[WEST] = westDoor;
	hasDoor[SOUTH] = southDoor;
	hasDoor[EAST] = eastDoor;

	// The points to place the beginning and end of doors. Since rooms are
	// square we the same values can be used for either x or y.
	// Center them in walls.
	float doorStart = (ROOM_WIDTH / 2) - (DOOR_WIDTH / 2);
	float doorEnd = (ROOM_WIDTH / 2) + (DOOR_WIDTH / 2);

	// now do each wall mod 4 (to fix going all the way around for some sides)
	for(size_t i = 0; i < doors.size(); ++i)
	{
		doors[i] = doors[i] % 4;
		hasDoor[doors[i]] = 1;
	}

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
	
	/* DEBUG
	printf("type: %d orient: %d\n", roomType, orient);
	for(size_t i = 0; i < doors.size(); ++i)
		printf("%d ", doors[i]);
	printf("\n");
	*/
	
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
	GLuint program = shaderManager->getProgram(2, "phongTex.vert", "phongTex.frag");
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

	// Draw the walls
	for(vector<Wall>::iterator it = walls.begin(); it < walls.end(); it++)
	{
		(*it).draw();
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
