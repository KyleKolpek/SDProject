#ifndef MTLLOADER_H
#define MTLLOADER_H

#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<sstream>
#include"GLM/glm.hpp"


/***************************************************************************//**
 * A loader for loading mtl files for materials for obj files.
 * Loads a mtl file that corresponds to a obj file that uses the described
 * material from an obj file for texturing and lighting.
 ******************************************************************************/
class MtlLoader
{
public:
	/***********************************************************************//**
 	 * Default Constructor, called when new mtlLoader is constructed.
 	 **************************************************************************/
	MtlLoader();

	/***********************************************************************//**
 	 * Default Destructor, called when new mtlLoader is deleted.
 	 **************************************************************************/
	~MtlLoader();

	/***********************************************************************//**
 	 * Called to load a mtl file.
	 * \param[in] filename
	 *     The file to be opened and read from.
 	 **************************************************************************/
	void loadFile(std::string filename);

	/***********************************************************************//**
 	 * Returns the texture file name and relative path.
 	 **************************************************************************/
	std::string getTextureName();
	
	/***********************************************************************//**
 	 * Returns the alpha that was read from the file.
 	 **************************************************************************/
	float getAlpha();

	/***********************************************************************//**
  	 * Returns the shininess read from the file.
 	 **************************************************************************/
	float getShininess();

	/***********************************************************************//**
 	 * Returns the illumination variabled from the file read in.
 	 **************************************************************************/
	float getIllum();

	/***********************************************************************//**
 	 * Returns the Specular light from the mtl file.
 	 **************************************************************************/
	glm::vec3 getSpecular();

	/***********************************************************************//**
 	 * Returns the Ambient light from the mtl file.
 	 **************************************************************************/
	glm::vec3 getAmbient();

	/***********************************************************************//**
 	 * Returns the Diffuse light from the mtl file.
 	 **************************************************************************/
	glm::vec3 getDiffuse();

private:
	//std::map<std::string, Mtl> nameToMtlData;
	
	/***********************************************************************//**
 	 * Holds the texture filename and relative path.
 	 **************************************************************************/
	std::string texture;

	/***********************************************************************//**
 	 * Holds the alpha 
 	 **************************************************************************/
	float alpha;

	/***********************************************************************//**
 	 * Holds the shininess variable from the file.
 	 **************************************************************************/
	float shininess;

	/***********************************************************************//**
 	 * Holds the illumination variable stored in the file.
 	 **************************************************************************/
	float illum;

	/***********************************************************************//**
 	 * Holds the specular light vector. 
 	 **************************************************************************/
	glm::vec3 specular;

	/***********************************************************************//**
 	 * Holds the ambient light vector.
 	 **************************************************************************/
	glm::vec3 ambient;

	/***********************************************************************//**
 	 * Holds the diffuse light vector.
 	 **************************************************************************/
	glm::vec3 diffuse;

};
#endif
