#include "objLoader.h"

ObjLoader::ObjLoader()
{
	data = new ObjInfo;	
}

ObjLoader::~ObjLoader()
{
	delete data;
}

void ObjLoader::load(char* filename)
{
	//TODO: Load Obj's
	delete data;
	data = new ObjInfo();
	std::ifstream objFile(filename);
	while(!objFile.eof() && !objFile.bad())
	{
		std::string buffer;
		getline(objFile, buffer);
	}	
}

ObjInfo ObjLoader::getData()
{
	/* DEEP */
	ObjInfo ret;
	ret.vertices = data->vertices;
	ret.normals = data->normals;
	ret.texture = data->texture;
	ret.faces = data->faces;
	for(size_t i = 0; i < data->faces.size(); ++i)
	{
		Face empty;
		ret.faces.push_back(empty);
		for(size_t j = 0; j < 3; ++j)
		{
			ret.faces[i].verts[j] = data->faces[i].verts[j];
			ret.faces[i].normals[j] = data->faces[i].normals[j];
			ret.faces[i].textures[j] = data->faces[i].normals[j];
		}	
		ret.faces[i].hasTex = data->faces[i].hasTex;
		ret.faces[i].hasNorm = data->faces[i].hasNorm;
	}	
	/* YEAH */

	return ret;
}

