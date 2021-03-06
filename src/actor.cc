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

Actor::Actor(Camera *camera, 
			Dungeon *dungeon, 
			string obj, 
			string tex,
			ObjLoader *objLoader):
	position(0.0),
	moveSpeed(5),
	scaleFactor(1.0),
	rotation(0.0),
	radius(0.5),
	vertexCount(0),
	vertexBuffer(NULL),
	texture(NULL),
	camera(camera),
	dungeon(dungeon),
	maxMovement(30),
	distanceMoved(0.0),
	modelMatrix(1.0),
	objLoader(objLoader)
{
	
	vertexBuffer = objLoader->getVertexBuffer(obj);
	dataType     = objLoader->getVertexType(obj);
	vertexCount  = objLoader->getVertexCount(obj);
	texture		 = objLoader->getTexture(tex);
}

Actor::~Actor()
{
}

float Actor::getPercentMoved()
{
	float ret = distanceMoved/maxMovement;
	if(ret > 1.0f)
	{
		ret = 1.0f;
	}
	return ret;
}
void Actor::draw()
{
	// Store a ShaderManager over a program
	GLuint program = shaderManager->getProgram(2, "phongTex.vert",
		"phongTexPtLights.frag");
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
 * Algorithm for intersection taken from
 * http://www.gamedev.net/topic/533967-collision-response-calc-sliding-plane/
 */
glm::vec3 Actor::adjustForCollisions(const glm::vec3 &delta)
{
	// adjusted delta
	glm::vec3 newD = delta;

	// compute next position
	glm::vec3 next = position + delta;

	// First, compute which room Actor is in.
	int row = next.z / ROOM_LENGTH;
	int col = next.x / ROOM_WIDTH;
	currRoom = dungeon->getRoom(row, col);

	// Player next
	glm::vec2 C(next.x, next.z);

	// this shouldn't happen!
	if(currRoom == NULL)
	{
		return newD;
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
			// Use this to enable sliding: delta -= norm * dot(delta, norm)
			glm::vec2 d(newD.x, newD.z); // 2D delta
			glm::vec2 collideVec = B - A;

			glm::vec2 norm(-collideVec.y, collideVec.x);
			norm = glm::normalize(norm);
			
			d -= norm * glm::dot(norm, d);

			// Store the new values in return
			newD.x = d.x;
			newD.z = d.y;

			break;
		}
	}

	// Now check for collision with objects in room.
	for(size_t i = 0; i < currRoom->objects.size(); ++i)
	{
		Actor *obj = currRoom->objects[i];

		// compute the radial distance between the object and the actor.
		float distance = glm::distance(obj->getPosition(), next);

		// If the distance is less than the sum of their radii, there is a
		// collision. For now, just stop movement.
		if(distance < obj->getRadius() + this->radius)	
		{
			newD.x = 0;
			newD.z = 0;
		}
	}

	return newD;
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
	this->radius = 0.5 * scale; //TODO: fix magic numbers
	createModelMatrix();
}

void Actor::setRotation(float degrees)
{
	this->rotation = degrees;
	createModelMatrix();
}

void Actor::move(glm::vec3 const &delta)
{
	// Move if there won't be a collision.
	position += adjustForCollisions(delta);
	//position += delta;

	// Calculate the direction the player should face
	float theta = glm::degrees(glm::atan2(-delta.x, delta.z));
	setRotation(theta);
	createModelMatrix();
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

void Actor::resetMovement()
{
	distanceMoved=0.0;
}

void Actor::setMaxMovement( float newMaxMovement )
{
	maxMovement = newMaxMovement;
}

bool Actor::canMove()
{
	return distanceMoved < maxMovement;
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

glm::mat4 Actor::getModelMatrix()
{
	return modelMatrix;
}
