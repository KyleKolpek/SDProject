#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cstdlib>

/*
	For All:
	0->x
	1->y
	2->z
*/
struct Face
{
	std::vector<int> verts;
	std::vector<int> normals;
	std::vector<int> textures;
	
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
