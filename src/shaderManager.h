#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <cstdarg>
#include <map>
#include <string>
#include "shaderLoader.h"
#include "stdgl.h"

/***************************************************************************//**
 * Manages shader programs.
 * By using a map to create a key from the shader names the ShaderManager
 * holds references to shader programs. When getProgram(..) is called the
 * ShaderManager first queries the map for an existing program. If one isn't
 * found then it creates the program and stores the reference in the map.
 ****************************************************************************//*
 * TODO: Check success of loader.
 ******************************************************************************/

class ShaderManager
{
public:
	/***********************************************************************//**
	 * Default constructor. 
	 * Initializes the shaderDir to "".
	 **************************************************************************/
	ShaderManager();

	/***********************************************************************//**
	 * Constructor that sets the shaderDir. 
	 **************************************************************************/
	ShaderManager(std::string shaderDir);

	/***********************************************************************//**
	 * Creates a program based off the names of shaders passed in. 
	 * \param[in] shaderFileCount
	 *     The number of shader files to be used in a program.
	 * \param[in] shaderFileNames
	 *     Filenames of the shaders to be used in a program.
	 * \return
	 *     A reference to a compiled program.
	 **************************************************************************/
	GLuint getProgram(int shaderFileCount, ...);

	/***********************************************************************//**
	 * Creates a program based off the names of shaders passed in. 
	 * \param[in] shaderFileCount
	 *     The number of shader files to be used in a program.
	 * \param[in] shaderFileNames
	 *     Filenames of the shaders to be used in a program.
	 * \return
	 *     A reference to a compiled program.
	 **************************************************************************/
	GLuint getProgram(int shaderFileCount, va_list shaderFileNames);

private:
	/***********************************************************************//**
	 * Associates keys to programs.
	 **************************************************************************/
	std::map<std::string, GLuint> programMap;

	/***********************************************************************//**
	 * Stores the directory housing the shader files to be loaded.
	 **************************************************************************/
	std::string shaderDir;

	/***********************************************************************//**
	 * Creates a key by combining multiple strings. 
	 * \param[in] stringCount
	 *     The number of strings to be used in generating the key.
	 * \param[in] strings
	 *     The strings to be concatenated into the key.
	 * \return
	 *     The key.
	 **************************************************************************/
	std::string genKey(int stringCount, va_list strings);
};

#endif
