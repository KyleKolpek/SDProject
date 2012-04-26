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
	 * Determine if Actor will collide with any walls after moving to 'next'.
	 * \param[in] next
	 *     vec3 of possibly colliding position.
	 * \param[out] isColliding
	 *     True if colliding with a wall.
	 **************************************************************************/
	virtual glm::vec3 adjustForCollidingWithWalls(const glm::vec3 &delta);
	
	glm::vec3 getPosition();
	glm::mat4 getModelMatrix();
	float getRadius();

	void setPosition(glm::vec3 const &position);
	void setScale(float scale);
	void setRotation(float degrees);

	void move(glm::vec3 const &delta);
	void scale(float factor);
	void rotate(float degrees);

	void setRadius(float radius);

	void resetMovement();
	void setMaxMovement( float newMaxMovement );
	bool canMove();
	
	float getPercentMoved();
protected:
	Dungeon *dungeon;	/** Pointer to the game dungeon for collision 
							detection, etc. */
	Room *currRoom;		/** Current room that Actor resides in. */
	glm::vec3 position;
	float moveSpeed;
	float scaleFactor;
	float rotation;
	float radius;
	int vertexCount;
	GLuint vertexBuffer;
	GLuint dataType;
	GLuint texture;
	Camera *camera;
	glm::mat4 modelMatrix;
	ObjLoader *objLoader;
	void createModelMatrix();

	float maxMovement;
	float distanceMoved;
};

#endif
