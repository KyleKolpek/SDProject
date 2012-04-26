#ifndef ACTOR_H
#define ACTOR_H

#include "stdgl.h"
#include <SFML/Window.hpp>
#include "drawable.h"
#include "updatable.h"
#include "dungeon.h"
#include "GLM/glm.hpp"
#include <string>
#include "objLoader.h"

class Camera;
class Dungeon;
class Room;

/***************************************************************************//**
 * A drawable class that can undergo most affine transformations.
 * This is one of the more basic drawable classes. It loads a model and a
 * texture using objLoader and maintains the necessary data to draw itself,
 * including a Dungeon and a Camera.
 ****************************************************************************//*
 * TODO: Check success of loader.
 ******************************************************************************/
class Actor: public Drawable, public Updatable
{
public:
	Actor(Camera *camera, 
		Dungeon *dungeon, 
		std::string obj, 
		std::string tex,
		ObjLoader *objLoader);
	virtual ~Actor();

	// Inherited methods
	virtual void draw();
	virtual void update(float sec, sf::Input const &input);

	/***********************************************************************//**
	 * Determine if Actor will collide with any walls after moving by 'delta'.
	 * \param[in] delta
	 *     vec3 of possibly colliding position.
	 * \return
	 *     The delta that the actor is actually capable of moving
	 *     post-collision.
	 **************************************************************************/
	virtual glm::vec3 adjustForCollidingWithWalls(const glm::vec3 &delta);
	
	/***********************************************************************//**
	 * Retrieve the actor's position in world/dungeon space.
	 * \return  
	 *     The actor's position in world/dungeon space.
	 **************************************************************************/
	glm::vec3 getPosition();

	/***********************************************************************//**
	 * Retrieve the actor's model matrix.
	 * \return  
	 *     The model matrix that contains all of the transformations to be
	 *     applied to the actor.
	 **************************************************************************/
	glm::mat4 getModelMatrix();

	/***********************************************************************//**
	 * Retrieve the actor's radius.
	 * \return  
	 *     The radius of an actor, generally to be used for collision.	It
	 *     currently returns 0.5 * scaleFactor.
	 **************************************************************************/
	float getRadius();

	/***********************************************************************//**
	 * Sets the actor's position in world/dungeon space.
	 * (0,0) is the top left point of the dungeon.
	 * \param[in] position
	 *     A position that will be assigned to the position member and used to
	 *     translate the actor.
	 **************************************************************************/
	void setPosition(glm::vec3 const &position);

	/***********************************************************************//**
	 * Sets the actor's scale and modifies the radius accordingly.
	 * \param[in] scale
	 *     The scale of the actor to be used.
	 **************************************************************************/
	void setScale(float scale);

	/***********************************************************************//**
	 * Sets the actor's rotation in degrees.
	 * \param[in] degrees
	 *     The number of degrees to rotate the actor counter-clockwise.
	 **************************************************************************/
	void setRotation(float degrees);

	/***********************************************************************//**
	 * Moves the actor position by delta.
	 * \param[in] delta
	 *     The amount to translate the position by.
	 **************************************************************************/
	void move(glm::vec3 const &delta);
	
	/***********************************************************************//**
	 * Scales the actor scale by a factor.
	 * \param[in] factor
	 *     The factor to multiply the scale by.
	 **************************************************************************/
	void scale(float factor);

	/***********************************************************************//**
	 * Scales the actor by a factor.
	 * \param[in] factor
	 *     The factor to multiply the scale by.
	 **************************************************************************/
	void rotate(float degrees);

	/***********************************************************************//**
	 * Changes the actor's radius.
	 * \param[in] radius
	 *     The new radius to be assigned.
	 **************************************************************************/
	void setRadius(float radius);

	/***********************************************************************//**
	 * Resets the distnaceMoved variable to 0.
	 **************************************************************************/
	void resetMovement();

	/***********************************************************************//**
	 * Changes the maximum distance an actor is able to move.
	 * \param[in] newMaxMovement
	 *     The new maximum movement distance.
	 **************************************************************************/
	void setMaxMovement( float newMaxMovement );

	/***********************************************************************//**
	 * Checks whether a player is allowed to move based on distanceMoved and
	 * maxMovement.
	 * \return
	 *     Returns true if the player should be able to move, false otherwise.
	 **************************************************************************/
	bool canMove();
	
	/***********************************************************************//**
	 * Checks whether a player is allowed to move based on distanceMoved and
	 * maxMovement.
	 * \return
	 *     Returns true if the player should be able to move, false otherwise.
	 **************************************************************************/
	float getPercentMoved();

protected:
	/***********************************************************************//**
	 * Pointer to the game dungeon for collision detection, etc.
	 **************************************************************************/
	Dungeon *dungeon;

	/***********************************************************************//**
	 * A pointer to the room the actor currently resides in..
	 **************************************************************************/
	Room *currRoom;

	/***********************************************************************//**
	 * The world/dungeon position of the actor.
	 **************************************************************************/
	glm::vec3 position;

	/***********************************************************************//**
	 * The speed the actor moves in m/s. 
	 **************************************************************************/
	float moveSpeed;
	
	/***********************************************************************//**
	 * The amount to scale the actor's model.
	 **************************************************************************/
	float scaleFactor;

	/***********************************************************************//**
	 * The rotation of the actor's model.
	 **************************************************************************/	
	float rotation;

	/***********************************************************************//**
	 * The collision radius. Our game uses radial collision detection.
	 **************************************************************************/
	float radius;

	/***********************************************************************//**
	 * The number of vertices in the actor's model.
	 **************************************************************************/
	int vertexCount;

	/***********************************************************************//**
	 * An OpenGL buffer for the actor's vertex information.
	 **************************************************************************/
	GLuint vertexBuffer;

	/***********************************************************************//**
	 * Whether the actor's model uses triangles or quads.
	 **************************************************************************/
	GLuint dataType;

	/***********************************************************************//**
	 * The actor's texture data.
	 **************************************************************************/
	GLuint texture;

	/***********************************************************************//**
	 * A reference to the game camera.
	 **************************************************************************/
	Camera *camera;

	/***********************************************************************//**
	 * The actor's model matrix, used for transformations and other operations.
	 **************************************************************************/
	glm::mat4 modelMatrix;

	/***********************************************************************//**
	 * A utility for loading models in .obj format.
	 **************************************************************************/
	ObjLoader *objLoader;

	/***********************************************************************//**
	 * Creates the actor's model view matrix.
	 **************************************************************************/
	void createModelMatrix();

	/***********************************************************************//**
	 * The maximum distance an actor can move in a single turn.
	 **************************************************************************/
	float maxMovement;
	
	/***********************************************************************//**
	 * The distance moved in the current turn.
	 **************************************************************************/
	float distanceMoved;
};

#endif
