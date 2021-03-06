#ifndef OBJLOADER_H
#define OBJLOADER_H

#include<vector>
#include<map>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include<cstdlib>

#include "stdgl.h"

/***************************************************************************//**
 * Struct to hold data that has x, y, and z components
 ******************************************************************************/
struct vector3
{
	float x,y,z;
};

/***************************************************************************//**
 * Struct to hold data that only has x, and y components.
 ******************************************************************************/
struct vector2
{
	float x, y;
};

/***************************************************************************//**
 * Loader for model data.
 * Loads data from a given obj file and formats it to something that can be
 * used to render.
 ******************************************************************************/
class ObjLoader
{
public:
	/***********************************************************************//**
 	 * Default Constructor.
 	 **************************************************************************/
	ObjLoader();

	/***********************************************************************//**
 	 * Loads an Wavefront obj files into private data below.
	 * \params[in] filename
	 *     The name of the file you want to open with relative path.
 	 **************************************************************************/
	void loadObjFile(std::string filename);

	/***********************************************************************//**
 	 * Formats the obj file data into a vertexData array, size, and type.
 	 **************************************************************************/
	void formatVertexData();

	/***********************************************************************//**
 	 * Returns the vertexData that contains vertex info as a vertex buffer.
	 * \params[in] name
	 *     Name of the file that provided the data.
 	 **************************************************************************/
	GLuint getVertexBuffer(std::string name);

	/***********************************************************************//**
 	 * Returns the type of faces used in the model. Either GL_QUADS or
	 * GL_TRIANGLES.
	 * \params[in] name
	 * 	   Name of the file the data was collected from.
 	 **************************************************************************/
	GLuint getVertexType(std::string name);

	/***********************************************************************//**
 	 * Returns how many vertices are in the vertexData array.
	 * \params[in] name
	 *     Name of the file the data was gathered from.
 	 **************************************************************************/
	GLsizei getVertexCount(std::string name);

	/***********************************************************************//**
 	 * Clears out the data.
 	 **************************************************************************/
	void clear();

	/***********************************************************************//**
 	 * Loads a texture from a file.
	 * \params[in] filename
	 *     Name of texture fiel you want to load in.
 	 **************************************************************************/	
	void loadTexture(std::string filename);

	/***********************************************************************//**
 	 * Returns texture OpenGL context.
	 * \params[in] filename
	 *     The name of the file you want the texture data from.
 	 **************************************************************************/	
	GLuint getTexture(std::string filename);
private:
	/***********************************************************************//**
 	 * Holds all the vertices found in the obj file.
 	 **************************************************************************/
	std::vector<vector3> vertices;

	/***********************************************************************//**
 	 * Holds all the normals found in the obj file.
 	 **************************************************************************/
	std::vector<vector3> normals;

	/***********************************************************************//**
 	 * Holds all the texture coordinates found in the obj file.
 	 **************************************************************************/
	std::vector<vector2> texCoords;

	/***********************************************************************//**
 	 * Holds all the face vertices found in the file.
 	 **************************************************************************/
	std::vector<std::vector<int> > faceV;

	/***********************************************************************//**
 	 * Holds all the face normals found in the file.
 	 **************************************************************************/
	std::vector<std::vector<int> > faceN;

	/***********************************************************************//**
 	 * Holds all the face texture coordinates found in the file.
 	 **************************************************************************/
	std::vector<std::vector<int> > faceT;

	/***********************************************************************//**
 	 * Holds the formated data for drawing.
 	 **************************************************************************/
	float* vertexData;

	/***********************************************************************//**
 	 * Holds the type of faces used in the model.
 	 **************************************************************************/
	GLuint vertexType;

	/***********************************************************************//**
 	 * Holds the number of vertices in the complete model.
 	 **************************************************************************/
	GLsizei vertexCount;

	/***********************************************************************//**
 	 * Holds the name of the file.
 	 **************************************************************************/
	std::string name;

	/***********************************************************************//**
 	 * Holds the information for all loaded models.
 	 **************************************************************************/
	std::map<std::string, GLuint> vertexBufferMap;

	/***********************************************************************//**
 	 * Holds all the type information for all loaded files.
 	 **************************************************************************/
	std::map<std::string, GLuint> vertexTypeMap;

	/***********************************************************************//**
 	 * Holds all the count data for all files.
 	 **************************************************************************/
	std::map<std::string, GLsizei> vertexCountMap;
	
	/***********************************************************************//**
 	 * Holds texture image information.
 	 **************************************************************************/	
	std::map<std::string, GLuint> textureImgMap;
};

#endif
