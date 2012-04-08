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
	std::string buffer;

	// prime loop
	getline(objFile, buffer);
	// ifstream.good() is the same as !eof() && !fail() && !bad()
	while(objFile.good())
	{
		getline(objFile, buffer);
		std::stringstream bufferReader(buffer);
		std::string type;
		std::vector<float> info;
		std::vector<int> faceInfo;
		Face face;

		//Get the type
		bufferReader >> type;
		if(type[0] == 'v')
		{
			while(bufferReader.good())
			{
				float holder;
				bufferReader >> holder;
				info.push_back(holder);
			}
			if(type.size() == 1)
			{
				data->vertices.push_back(info);
			}
			else if(type[1] == 't')
			{
				data->texture.push_back(info);
			}
			else if(type[1] == 't')
			{
				data->normals.push_back(info);
			}
		}
		else if(type[0] == 'f')
		{
			//Specific face stuff
			while(bufferReader.good())
			{
				int index[3];
				std::string holder;
				bufferReader >> holder;
				
				for(int i = 0; i < 2; ++i)
				{
					int place;
					std::string num;
					place = holder.find('/');
					num = holder.substr(0, place);
					holder = holder.substr(place + 1);
					
					index[i] = atoi(num.c_str());
				}
				index[3] = atoi(holder.c_str());
				face.verts.push_back(index[0]);
				face.normals.push_back(index[1]);
				face.textures.push_back(index[2]);
				face.hasTex = true;
				face.hasNorm = true;
			}
			data->faces.push_back(face);

		}
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

