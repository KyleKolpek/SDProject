#ifndef OBJLOADER_H
#define OBJLOADER_H

#include<vector>
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
 	 * Returns the vertexData that contains vertex info as follows
	 * (PositionX, PositionY, PositionZ, NormalX, NormalY, NormalZ, TexX, TexY).
 	 **************************************************************************/
	float* getVertexData();

	/***********************************************************************//**
 	 * Returns the type of faces used in the model. Either GL_QUADS or
	 * GL_TRIANGLES.
 	 **************************************************************************/
	GLuint getVertexType();

	/***********************************************************************//**
 	 * Returns how many vertices are in the vertexData array.
 	 **************************************************************************/
	GLsizei getVertexCount();
	
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
};

#endif
