#include"objLoader.h"

using namespace std;
ObjLoader::ObjLoader()
{
	vertices.clear();
	normals.clear();
	texCoords.clear();

	faceV.clear();
	faceN.clear();
	faceT.clear();

	vertexData = NULL;
	vertexType = 0;
	vertexCount = 0;
}

void ObjLoader::loadObjFile(string filename)
{	
	ifstream objFile(filename.c_str());
	if(!objFile)
	{
		return;
	}
	
	while(objFile.good())
	{
		string buffer;
		getline(objFile, buffer);
		stringstream bufferReader(buffer);
		while(bufferReader.good())
		{
			string type;
			bufferReader >> type;
			if(type[0] == 'v')
			{
				if(type.size() == 1)
				{
					vector3 holds;
					bufferReader >> holds.x >> holds.y >> holds.z;
					vertices.push_back(holds);
				}
				else if(type[1] == 'n')
				{
					vector3 holds;
					bufferReader >> holds.x >> holds.y >> holds.z;
					normals.push_back(holds);
				}
				else if(type[1] == 't')
				{
					vector2 holds;
					bufferReader >> holds.x >> holds.y; 
					texCoords.push_back(holds);
				}
			}
			else if(type[0] == 'f')
			{
				vector<int> Vs, Ns, Ts;
				while(bufferReader.good())
				{
					string vertex;
					bufferReader >> vertex;
					if(vertex.find("/") != string::npos)
					{
						
						int V, N, T;
						int pos = vertex.find("/");
						V = atoi(vertex.substr(0,pos).c_str());
						vertex = vertex.substr(pos+1);
						pos = vertex.find("/");
						T = atoi(vertex.substr(0,pos).c_str());
						vertex = vertex.substr(pos+1);
						pos = vertex.find("/");
						N = atoi(vertex.substr(0,pos).c_str());
						vertex = vertex.substr(pos+1);
						
						Vs.push_back(V);
						Ns.push_back(N);
						Ts.push_back(T);
					}
					
				}
	
				faceV.push_back(Vs);
				faceN.push_back(Ns);
				faceT.push_back(Ts);

				if(faceV[faceV.size()-1].size() != Vs.size())
				{
					cout << "sizes not equal!" << endl;
				}
			}
			else
			{
				//Some other form of tag.
			}
		}
	}
}

void ObjLoader::formatVertexData()
{
	if(faceV[0].size() == 3)
	{
		//GL_TRIANGLES
		vertexType = 3;
	}
	else
	{
		//GL_QUADS
		vertexType = 4;
	}


	vertexCount = faceV.size() * faceV[1].size();
	
	vertexData = new float[vertexCount*8];
	size_t iCount = 0;


	for(size_t i = 0; i < faceV.size(); ++i)
	{
		for(size_t j = 0; j < faceV[i].size(); ++j)
		{
			int V = faceV[i][j]-1;
			vertexData[iCount] = vertices[V].x;
			vertexData[iCount+1] = vertices[V].y;
			vertexData[iCount+2] = vertices[V].z;
			
			int N = faceN[i][j]-1;
			vertexData[iCount+3] = normals[N].x;
			vertexData[iCount+4] = normals[N].y;
			vertexData[iCount+5] = normals[N].z;

			int T = faceT[i][j]-1;
			vertexData[iCount+6] = texCoords[T].x;
			vertexData[iCount+7] = texCoords[T].y;
		
			iCount += 8;
		}
	}
}

float* ObjLoader::getVertexData()
{
	return vertexData;
}

GLuint ObjLoader::getVertexType()
{
	return vertexType;
}

GLsizei ObjLoader::getVertexCount()
{
	return vertexCount;
}
