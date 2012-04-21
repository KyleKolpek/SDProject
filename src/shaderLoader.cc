// Adapted source for shaderLoader from
// http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/loading.php
#include <fstream>
#include <iostream>
#include "shaderLoader.h"

using namespace std;
ShaderLoader::ShaderLoader():
	stringCount(0),
	shaderSource(NULL)
{
}

ShaderLoader::ShaderLoader(char const *const filename):
	stringCount(0),
	shaderSource(NULL)
{
	loadShader(filename);
}

ShaderLoader::~ShaderLoader()
{
	unloadShader();
}

int ShaderLoader::loadShader(char const *const filename)
{
	// Delete old shader
	if(shaderSource)
	{
		unloadShader();
	}

	ifstream file;
	file.open(filename, ios::in); // opens as ASCII!

	// Check for file opening success
	if(!file)
	{
		cerr << "Error opening file '" << filename << "'" << endl;
		return -1;
	}

	// TODO: Check memory allocation success
	int i;
	shaderSource = new GLchar*[256];
	for(i=0; file.good(); i++)
	{
		shaderSource[i] = new GLchar[256];
		file.read(shaderSource[i], 255);

		// Terminate string with null character
		shaderSource[i][file.gcount()] = '\0';
	}
	stringCount = i;

	file.close();

	return 0; // No Error
}


void ShaderLoader::unloadShader()
{
	for(int i=0; i<stringCount; i++)
	{
		delete[] shaderSource[i];
	}
	delete[] shaderSource;
	shaderSource = NULL;
}

int ShaderLoader::getStringCount()
{
	return stringCount;
}

const GLchar **ShaderLoader::getShaderSource()
{
	return (const GLchar **)shaderSource;
}
