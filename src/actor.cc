#include <iostream>
#include <cstdio>
#include <cmath>
#include "SOIL/SOIL.h"
#include "actor.h"
#include "camera.h"
#include "objLoader.h"
#include "GLM/glm.hpp"
#include "GLM/gtx/compatibility.hpp"

using namespace std;

Actor::Actor(Camera *camera, Dungeon *dungeon, string obj, string tex):
	position(0.0),
	scaleFactor(1.0),
	rotation(0.0),
	radius(0.5),
	vertexCount(0),
	vertexData(NULL),
	vertexBuffer(NULL),
	texture(NULL),
	camera(camera),
	dungeon(dungeon),
	modelMatrix(1.0)
{
	
	ObjLoader loader;
	loader.loadObjFile(obj);
	loader.formatVertexData();
	vertexData  = loader.getVertexData();
	dataType    = loader.getVertexType();
	vertexCount = loader.getVertexCount();
	texture = SOIL_load_OGL_texture(
		 tex.c_str(),
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
	
	// How fast the actor moves
	moveSpeed = 15.0;
}

Actor::~Actor()
{
	delete[] vertexData;
}

void Actor::draw()
{
	// Store a ShaderManager over a program
	GLuint program = shaderManager->getProgram(2, "phongTex.vert", "phongTex.frag");
	glUseProgram(program);

	GLint mvLoc = glGetUniformLocation(program, "modelView");
	GLint nmvLoc = glGetUniformLocation(program, "normalModelView");
	GLint projLoc = glGetUniformLocation(program, "projection");
	GLint texLoc = glGetUniformLocation(program, "texture");

	glm::mat4 MV = camera->getViewMatrix() * modelMatrix;
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

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glDisableVertexAttribArray(vertexPosLoc);
	glDisableVertexAttribArray(vertexNormalLoc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void Actor::update(float sec, sf::Input const &input)
{
}

/*
 * Algorithm for intersection taken from http://www.allegro.cc/forums/thread/595918
 */
bool Actor::isCollidingWall(const glm::vec3 &next)
{
	// First, compute which room Actor is in.
	int row = next.z / ROOM_LENGTH;
	int col = next.x / ROOM_WIDTH;
	currRoom = dungeon->getRoom(row, col);

	// Player next
	glm::vec2 C(next.x, next.z);

	// this shouldn't happen!
	if(currRoom == NULL)
	{
		printf("Not currently in a room!\n");
		return false;
	}

	// check collision against each wall in currRoom
	for(size_t i = 0; i < currRoom->walls.size(); ++i)
	{
		// grab the wall to save some typing
		Wall *wall = &(currRoom->walls[i]);

		// Start and end points of wall
		glm::vec2 A = wall->getStartPoint() 
			+ glm::vec2(col * ROOM_WIDTH, row * ROOM_LENGTH);
		glm::vec2 B = wall->getEndPoint() 
			+ glm::vec2(col * ROOM_WIDTH, row * ROOM_LENGTH);

		glm::vec2 CtoA = C - A;
		glm::vec2 BtoA = B - A;

		float dot = glm::dot(CtoA, BtoA);
		float len_sq = (BtoA.x * BtoA.x) + (BtoA.y * BtoA.y);
		float param = dot / len_sq;

		glm::vec2 closestPt;

		if(param < 0)
		{
			closestPt = A;
		}
		else if(param > 1)
		{
			closestPt = B;
		}
		else
		{
			closestPt.x = (A.x + param * BtoA.x);
			closestPt.y = (A.y + param * BtoA.y);
		}

		float distance = glm::distance(C, closestPt);
		if(distance < radius)
		{
			// Collision!
			return true;
		}
	}

	// no collision
	return false;
}

glm::vec3 Actor::getPosition()
{
	return position;
}

float Actor::getRadius()
{
	return radius;
}

void Actor::setPosition(glm::vec3 const &position)
{
	this->position = position;
	createModelMatrix();
}

void Actor::setScale(float scale)
{
	this->scaleFactor = scale;
	createModelMatrix();
}

void Actor::setRotation(float degrees)
{
	this->rotation = degrees;
	createModelMatrix();
}

void Actor::move(glm::vec3 const &delta)
{
	glm::vec3 newPos = this->position + delta;
	
	bool coll = true;
	// Move if there won't be a collision.
	// TODO: Add sliding
	if(!isCollidingWall(newPos))
	{
		position = newPos;

		// Calculate the direction the player should face
		float theta = glm::degrees(glm::atan2(-delta.x, delta.z));
		setRotation(theta);
		createModelMatrix();

		coll = false;;
	}
}

void Actor::scale(float factor)
{
	this->scaleFactor *= factor;
	createModelMatrix();
}

void Actor::rotate(float degrees)
{
	this->rotation += degrees;
	createModelMatrix();
}

void Actor::createModelMatrix()
{
	float theta = glm::radians(rotation);
	glm::mat4 translationMat(1.0, 0.0, 0.0, 0.0,
							 0.0, 1.0, 0.0, 0.0,
							 0.0, 0.0, 1.0, 0.0,
							position.x, position.y, position.z, 1.0);
	glm::mat4 scaleMat(scaleFactor, 0.0, 0.0, 0.0,
					   0.0, scaleFactor, 0.0, 0.0,
					   0.0, 0.0, scaleFactor, 0.0,
					   0.0, 0.0, 0.0, 1.0);
	glm::mat4 rotateMat(glm::cos(theta), 0.0, glm::sin(theta), 0.0,
						0.0, 1.0, 0.0, 0.0,
						-glm::sin(theta), 0.0, glm::cos(theta), 0.0,
						0.0, 0.0, 0.0, 1.0);
	modelMatrix = translationMat * scaleMat * rotateMat;
}
