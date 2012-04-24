#ifndef OBJLOADER_H
#define OBJLOADER_H

#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>


#include "stdgl.h"

struct vector3
{
	float x,y,z;
};

struct vector2
{
	float x, y;
};

class ObjLoader
{
public:
	ObjLoader();
	void loadObjFile(std::string filename);
	void formatVertexData();
	float* getVertexData();
	GLuint getVertexType();
	GLsizei getVertexCount();
	
private:
	std::vector<vector3> vertices;
	std::vector<vector3> normals;
	std::vector<vector2> texCoords;

	std::vector<std::vector<int> > faceV;
	std::vector<std::vector<int> > faceN;
	std::vector<std::vector<int> > faceT;

	float* vertexData;
	GLuint vertexType;
	GLsizei vertexCount;
};

#endif
