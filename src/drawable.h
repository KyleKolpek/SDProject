#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "stdgl.h"
#include "shaderManager.h"

/***************************************************************************//**
 * Allows an object to be drawn using OpenGL.
 * Provides two methods, draw() and setProgram(..), that are used to set up any
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
	 * Sets the shader manager to be used to create/retrieve programs.
	 * Stores the shaderManager passed in as a parameter in the shaderManager
	 * variable.
	 * \param[in] shaderManager
	 *     The ShaderManager to be stored.
	 **************************************************************************/
	virtual void setShaderManager(ShaderManager *shaderManager);

protected:
	/***********************************************************************//**
	 * Stores the ShaderManager that will be used to query programs.
	 **************************************************************************/
	 ShaderManager *shaderManager;
};

#endif
