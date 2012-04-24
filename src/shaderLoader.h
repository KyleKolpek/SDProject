#ifndef SHADERLOADER_H
#define SHADERLOADER_H

// Adapted source for ShaderLoader from
// http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/loading.php
#include "stdgl.h"

/***************************************************************************//**
 * A buffered reader.
 * Loads a file into a 2d char array and returns the relevant information to be
 * used by glShaderSource(). Currently each char array is set to 256 characters.
 ******************************************************************************/
class ShaderLoader
{
public:
	/***********************************************************************//**
	 * Creates a ShaderLoader ready to load from a file.
	 **************************************************************************/
	ShaderLoader();

	/***********************************************************************//**
	 * Creates a ShaderLoader and immediately loads a file.
	 * \param[in] filename
	 *     The file to be opened and read from.
	 **************************************************************************/
	ShaderLoader(char const *const filename);

	/***********************************************************************//**
	 * Deletes shaderSource's contents via unloadShader.
	 **************************************************************************/
	~ShaderLoader();

	/***********************************************************************//**
	 * Loads the source of a shader from a file.
	 * \param[in] filename
	 *     The file to be opened and read from.
	 **************************************************************************/
	int loadShader(char const *const filename);

	/***********************************************************************//**
	 * Returns the number of strings in shaderSource.
	 **************************************************************************/
	int getStringCount();
	const GLchar **getShaderSource();

private:

	/***********************************************************************//**
	 * Stores the source in a series of 256 character arrays.
	 **************************************************************************/
	GLchar **shaderSource;

	/***********************************************************************//**
	 * Stores the number of strings in shaderSource.
	 **************************************************************************/
	int stringCount;

	/***********************************************************************//**
	 * Deletes shaderSource's contents and sets the pointer to NULL.
	 **************************************************************************/
	void unloadShader();
};

#endif
