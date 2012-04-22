#include"mtlLoader.h"

using namespace std;

MtlLoader::MtlLoader()
{
	texture = "";
	alpha = 1.0f;
	shininess = 0.0f;
	for(int i = 0; i < 3; ++i)
	{
		specular[i] = 1.0f;
		ambient[i] = 0.2f;
		diffuse[i] = 0.8f;
	}
}

MtlLoader::~MtlLoader()
{

}

void MtlLoader::loadFile(string filename)
{
	ifstream mtlFile(filename.c_str());
	string buffer;
	
	while(mtlFile.good())
	{
		getline(mtlFile, buffer);
		stringstream bufferReader(buffer);
		string type;
		bufferReader >> type;
		cout << type[0] << endl;
		if(type[0] == 'K')
		{
			float r, g, b;
			bufferReader >> r;
			bufferReader >> g;
			bufferReader >> b;

			if(type[1] == 'a')
			{
				ambient[0] = r;
				ambient[1] = g;
				ambient[2] = b;
			}
			else if(type[1] == 'd')
			{
				diffuse[0] = r;
				diffuse[1] = g;
				diffuse[2] = b;
			}
			else if(type[1] == 's')
			{
				specular[0] = r;
				specular[1] = g;
				specular[2] = b;
			}
		}
		else if(type[0] == 'd' || (type[0] == 'T' && type[1] == 'r'))
		{
			float d;
			bufferReader >> d;
			alpha = d;
		}
		else if(type[0] == 'N' && type[1] == 's')
		{
			float s;
			bufferReader >> s;
			shininess = s;
		}
		else if(type.compare("illum") == 0)
		{
			float il;
			bufferReader >> il;
			illum = il;
		}
		else if(type[0] == 'm' && type[1] == 'a' && type[2] == 'p')
		{
			string name;
			size_t pos = filename.find_last_of("/\\");
			bufferReader >> name;
			name = filename.substr(0, pos) + "/" + name;
			texture = name;
		}
		else
		{
			cout << "Didn't enter a goddamn thing BITCH!\n";
		}
	}
	cout << "alpha->" << alpha << "\nshininess->" << shininess << "\nillum->" << illum << "\nfile->" << texture << "\n";
	mtlFile.close();
}

float MtlLoader::getAlpha()
{
	return alpha;
}

float MtlLoader::getShininess()
{
	return shininess;
}

float MtlLoader::getIllum()
{
	return illum;
}

glm::vec3 MtlLoader::getSpecular()
{
	return specular;
}

glm::vec3 MtlLoader::getAmbient()
{
	return ambient;
}

glm::vec3 MtlLoader::getDiffuse()
{
	return diffuse;
}
