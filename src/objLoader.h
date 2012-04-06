#include<iostream>
#include<fstream>
#include<string>
#include<vector>

/*
	For All:
	0->x
	1->y
	2->z
*/
struct Face
{
	int verts[3];
	int normals[3];
	int textures[3];
	
	bool hasTex;
	bool hasNorm;
};

struct ObjInfo
{
	std::vector<std::vector<float> > vertices;
	std::vector<std::vector<float> > normals;
	std::vector<std::vector<float> > texture;
	std::vector<Face> faces;
};

class ObjLoader
{
	public:
		ObjLoader();
		~ObjLoader();
		void load(char* filename);
		ObjInfo getData();

	private:
		ObjInfo* data;
		
};
