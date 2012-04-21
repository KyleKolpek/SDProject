/*
	Implementation
	of class defined in
	objLoader.h
*/
#include "objLoader.h"

//Default Constructor
ObjLoader::ObjLoader()
{
	data = new ObjInfo;	
}

//Default Destructor
ObjLoader::~ObjLoader()
{
	delete data;
}

/*
	Load function
	loads data stored in a give .obj file
	and parses out the model data and 
	saves it class member variables.
*/
void ObjLoader::load(std::string filename)
{
	//Delete old data and create a new one.
	delete data;
	data = new ObjInfo();

	//Open file
	std::ifstream objFile(filename.c_str());
	std::string buffer;

	if(!objFile.good())
	{
		if(objFile.eof())
			std::cout << "EOF\n";
		else if(objFile.fail())
			std::cout << "FAIL\n";
		std::cout << "LOLZ NOT GOOD\n";
		return;
	}
	//Loop through all the lines in the file.
	while(objFile.good())
	{
		//Grab a whole line.
		getline(objFile, buffer);
		//Set it into a stringstream for parsing.
		std::stringstream bufferReader(buffer);
		
		//Some temp values for holding data. 
		std::string type;
		std::vector<float> info;
		std::vector<int> faceInfo;
		Face face;

		//Get the type of data stored in the line.
		bufferReader >> type;

		//If it's "v" then it decribes vertex info.
		if(type[0] == 'v')
		{
			//Grab the rest of the data from the line.
			while(bufferReader.good())
			{
				float holder;
				bufferReader >> holder;
				info.push_back(holder);
			}

			/*
			* Find out what kind of vertex data it is.
			* if size is 1 then it's just v and therefore position info
			* if the second letter is "t" then it's a texture coordinate
			* if it's "n" then we have normal information.
			*/
			if(type.size() == 1)
			{
				data->vertices.push_back(info);
			}
			else if(type[1] == 't')
			{
				data->texture.push_back(info);
			}
			else if(type[1] == 'n')
			{
				data->normals.push_back(info);
			}
		}

		//If the first letter is "f" then we are talking about face values.
		else if(type[0] == 'f')
		{
			//Parse out face information.
			while(bufferReader.good())
			{
				//Some data temp data holders.
				int index[3];
				std::string holder;
				bufferReader >> holder;
				
				//Go through and grab the data.
				for(int i = 0; i < 2; ++i)
				{
					int place;
					std::string num;
					place = holder.find('/');
					num = holder.substr(0, place);
					holder = holder.substr(place + 1);
					index[i] = atoi(num.c_str());
				}

				//Last one is when there are no more slashes avaliable. 
				index[2] = atoi(holder.c_str());

				//Add the temp data to a more permanent home.
				face.verts.push_back(index[0]);
				face.normals.push_back(index[1]);
				face.textures.push_back(index[2]);
				face.hasTex = true;
				face.hasNorm = true;
			}
			//Add temp data to a more permanent location.
			data->faces.push_back(face);

		}
	}	
	objFile.close();
}

/*
* Loads a the obj at filename, and returns
* vertexData, indexData, type, and count.
* vertexData is in the following format:
* {pos1x, pos1y, pos1z, norm1x, norm1y, norm1z, tex1x, tex1y, ...,
* posNx, posNy, posNz, normNx, normNy, normNz, texNx, texNy}
*/
void ObjLoader::getData(std::string filename, 
						float* &vertexData, 
						int* &indexData,
						GLuint &type,
						GLsizei &count)
{
	//Load the data.
	load(filename);
	size_t size = 0;

	//Figure out the size needed and what kind of shapes it uses
	//to draw the model.
	
	if(data->faces[0].verts.size() == 3)
	{
		type = GL_TRIANGLES;
		size = data->faces.size() * 3;
	}
	else
	{
		type = GL_QUADS;
		size = data->faces.size() * 4;
	}
	
	//Temporary data holders.
	float* vertData = new float[size * 8];
	int* indxData = new int[data->faces.size()];
	size_t iCount = 0;

	//Set the amount of vertices stored in vertData
	count = size;	

	//Go through everyface and added all the data in order.
	for(size_t i = 0; i < data->faces.size(); ++i)
	{

		//Add positions
		for(size_t j = 0; j < data->faces[i].verts.size(); ++j)
		{
			for(size_t k = 0; k < data->vertices[data->faces[i].verts[j] -1].size(); ++k)
			{
				vertData[iCount] = data->vertices[data->faces[i].verts[j] - 1][k];
				iCount++;
			}
		
		//Add normals
			for(size_t k = 0; k < data->normals[data->faces[i].normals[j] - 1].size(); ++k)
			{
				vertData[iCount] = data->normals[data->faces[i].normals[j] - 1][k];
				iCount++;
			}

		//Add texture coordinates
			for(size_t k = 0; k < data->texture[data->faces[i].textures[j] - 1].size(); ++k)
			{
				vertData[iCount] = data->texture[data->faces[i].textures[j] - 1][k];
				iCount++;
			}	
		}
		indxData[i] = i;
	}

	//Returns
	vertexData = vertData;
	indexData = indxData;
}
