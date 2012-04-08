#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <stdgl.h>

/***************************************************************************//**
 * Allows an object to be drawn using OpenGL.
 * Provides two methods, draw() and setProgram(..) that are used to set up any
 * given Drawable object so that it can subsequently be drawn.
 ******************************************************************************/
class Drawable
{
public:
	/***********************************************************************//**
	 * Virtual destructor.
	 **************************************************************************/
    virtual ~Drawable();

	/***********************************************************************//**
	 * Draws the object.
	 * Requires an OpenGL context to be initialized and draws using the shaders
	 * contained in program.
	 **************************************************************************/
    virtual void draw() = 0;

	/***********************************************************************//**
	 * Sets the program to be used for drawing.
	 * Stores the program passed in as a parameter in the program member
	 * variable.
	 **************************************************************************/
    virtual void setProgram(GLuint program);

protected:
	/***********************************************************************//**
	 * Stores the shader program.
	 **************************************************************************/
    GLuint program;
};

#endif
