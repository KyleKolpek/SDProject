#include <iostream>
#include "shaderManager.h"

using namespace std;

ShaderManager::ShaderManager():
	shaderDir("")
{
}

ShaderManager::ShaderManager(string shaderDir):
	shaderDir(shaderDir)
{
}

GLuint ShaderManager::getProgram(int shaderFileCount, ...)
{
	// Set up the parameter list
	va_list vl;
	va_start(vl, shaderFileCount);

	// Call the overloaded version that takes a va_list
	GLuint program = getProgram(shaderFileCount, vl);

	// Stop using the list
	va_end(vl);

	return program;
}

GLuint ShaderManager::getProgram(int shaderFileCount, va_list shaderFileNames)
{
	// Make sure va_copy is defined
	#ifndef va_copy
	#define va_copy(d,s) ((d) = (s))
	#endif

	va_list vl;
	va_copy(vl,shaderFileNames);

	// Generate a key based of the shaders used
	string key;
	key = genKey(shaderFileCount, vl);
	va_end(vl);

	// If the key already exists in the map, return the value
	if(programMap.count(key) != 0)
	{
		return programMap[key];
	}

#ifdef DEBUG_SHADERS
	cout << "Key '" << key << "' not found." << endl;
#endif

	// Otherwise create the program and add it to the map
	GLuint shaders[shaderFileCount];
	for(int i = 0; i < shaderFileCount; ++i)
	{
		string name(va_arg(shaderFileNames, char const *));

		// Determine the shader type
		// TODO: confirm that the .vert or .frag is at the end of the string
		GLenum shaderType = 
#ifdef GL_VERTEX_SHADER
		(name.find(".vert") != string::npos) ?  GL_VERTEX_SHADER :
#endif
#ifdef  GL_FRAGMENT_SHADER
		(name.find(".frag") != string::npos) ?  GL_FRAGMENT_SHADER :
#endif
#ifdef  GL_GEOMETRY_SHADER
		(name.find(".geom") != string::npos) ?  GL_GEOMETRY_SHADER :
#endif
		0;

		if(shaderType == 0)
		{
			return 0;
		}

		// Load the source
		shaders[i] = glCreateShader(shaderType);
		ShaderLoader loader((shaderDir + "/" + name).c_str());
#ifdef DEBUG_SHADERS
		for(int j = 0; j < loader.getStringCount(); ++j)
		{
			cout << loader.getShaderSource()[j];
		}
#endif
		glShaderSource(shaders[i],
			loader.getStringCount(),
			loader.getShaderSource(),
			NULL);

		// Compile shader
		glCompileShader(shaders[i]);

		// Check compilation
		GLint compiled;
		glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			// Error compiling
#ifdef DEBUG_SHADERS
			cerr << "Error compiling shader \"" << name << "\"" << endl;

			GLsizei maxLength = 0; 
			glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH , &maxLength);	   
			if (maxLength > 1)
			{
				maxLength += 1;
				// TODO: see if new is necessary
				GLchar* compilerLog = new GLchar[maxLength];
				glGetShaderInfoLog(shaders[i], maxLength, &maxLength, compilerLog);
				cout << "compilerLog:\n" << compilerLog;
				delete[] compilerLog;
			}
#endif
			return 0;
		}
	}

	// Create program object
	GLuint program = glCreateProgram();

	// Link shaders to program
	for(int i = 0; i < shaderFileCount; ++i)
	{
		glAttachShader(program, shaders[i]);
	}
	glLinkProgram(program);

	// Check link status
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		// Error linking
#ifdef DEBUG_SHADERS
		cout << "Error linking shaders" << endl;

		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		if(maxLength > 1)
		{
			maxLength += 1;
			GLchar *linkerLog = new GLchar[maxLength];
			glGetProgramInfoLog(program, maxLength, &maxLength, linkerLog);
			cout << "linkerLog:\n" << linkerLog;
			delete[] linkerLog;
		}
#endif
		return 0;
	}

	// Add the program to the map
	programMap[key] = program;

	// NOTE: May not be needed
	glUseProgram(0);

	return program;
}

string ShaderManager::genKey(int stringCount, va_list strings)
{
	string key;

	// Generate the key
	for(int i = 0; i < stringCount; ++i)
	{	
		key += va_arg(strings, char const *);
		key += ';';
	}
	return key;
}
