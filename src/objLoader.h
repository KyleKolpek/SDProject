#ifndef OBJLOADER
#define OBJLOADER

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cstdlib>
#ifndef SHADERMANAGER
#include"stdgl.h"
#endif

/***************************************************************************//**
* Holds information for each face.
* Holds the f value information for the obj file to compile the complete
* vertex info for returning.
******************************************************************************/

struct Face
{
	std::vector<int> verts;
	std::vector<int> normals;
	std::vector<int> textures;
	
	bool hasTex;
	bool hasNorm;
};

/***************************************************************************//**
* Holds information for each vertex, normal, and texture.
* Holds the actual values for position, normals, and texture coordinates from
* the obj file.
******************************************************************************/

struct ObjInfo
{
	std::vector<std::vector<float> > vertices;
	std::vector<std::vector<float> > normals;
	std::vector<std::vector<float> > texture;
	std::vector<Face> faces;
};

/***************************************************************************//**
 * Loads information from Wavefront obj files.
 * Gets obj file and parsers out the needed information to be able to display
 * correct model on screen using OpenGL. To use all you have to do is create an
 * instance of ObjLoader and call the method getData(..) with appropriate params
 * and it will return the information.
 ******************************************************************************/

class ObjLoader
{
public:
	/***********************************************************************//**
	 * Default Constructor.
	 **************************************************************************/
	ObjLoader();

	/***********************************************************************//**
	 * Default Destructor.
	 **************************************************************************/
	~ObjLoader();

	/***********************************************************************//**
	 * Loads obj file and parses out the information.(Moved to private maybe?)
	 * \param[in] filename
	 *     The filename of the obj file to load.
	 **************************************************************************/
	void load(std::string filename);

	/***********************************************************************//**
	 * Gets appropriated data, and returns the data with vertexData, indexData
	 * and type.
	 * \param[in] filename
	 * 	  The filename of the obj file to load.
	 **************************************************************************/
	void loadModelData(std::string filename);

	/***********************************************************************//**
	 * Returns vertex data for the loaded model.
	 **************************************************************************/
	float* getVertexData();
	
	/***********************************************************************//**
	 * Returns type (quads or triangles) for loaded model.
	 **************************************************************************/	
	GLuint getType();

	/***********************************************************************//**
	 * Returns vertex data count for the loaded model.
	 **************************************************************************/	
	GLsizei getVertexCount();

private:
	/***********************************************************************//**
	 * Holds the data from the obj for later conversion to output format.
	 **************************************************************************/
	ObjInfo* data;
	float* vertexData;
	GLuint type;
	GLsizei count;
};
#endif 
