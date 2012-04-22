#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<sstream>
#include"GLM/glm.hpp"

/*
struct Mtl
{
	std::string texture = "";
	float alpha = 1.0f;
	float shininess = 0.0f;
	float illum;
	glm::vec3 specular(1.0f, 1.0f, 1.0f);
	glm::vec3 ambient(0.2f, 0.2f, 0.2f);
	glm::vec3 diffuse(0.8f, 0.8f, 0.8f);
}
*/

class MtlLoader
{
	public:
	MtlLoader();
	~MtlLoader();

	void loadFile(std::string filename);
	
	std::string getTextureName();
	
	float getAlpha();
	float getShininess();
	float getIllum();

	glm::vec3 getSpecular();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();

	private:
	//std::map<std::string, Mtl> nameToMtlData;
	
	std::string texture;
	float alpha;
	float shininess;
	float illum;
	glm::vec3 specular;
	glm::vec3 ambient;
	glm::vec3 diffuse;

};
