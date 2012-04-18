#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<map>
#include<iostream>
#include<vector>

/***************************************************************************//**
 * Manages audio loading and playback.
 * Using a map we store pointers to the different sounds we have loaded in.
 * It also simplifies playback of sounds by using play(..) instead of getting
 * the sounds and checking if they are playing and then play.
 ****************************************************************************//*
 * TODO: Add music if time allows.
 ******************************************************************************/


class AudioManager
{
	public:
	/***************************************************************************//**
 	* Default Constructor. 
 	* Sets the path variable.
 	******************************************************************************/
	AudioManager();

	/***************************************************************************//**
 	* Default Destructor. 
 	* Releases dynamically allocated memory.
 	******************************************************************************/
	~AudioManager();
	
	/***************************************************************************//**
 	* Loads sound file, filename, and adds it to the map. 
 	* \param[in] filename
	*     The name of the file in path that you want to load.
 	******************************************************************************/
	void load(std::string filename);

	/***************************************************************************//**
 	* Returns a pointer to the Sound you wanted.
 	* \param[in] sound
	*     The name of the sound you want to here. essentially the filename minus
	*	  the extension.
 	******************************************************************************/
	sf::Sound* get(std::string sound);

	/***************************************************************************//**
 	* Plays the sound you requested.
 	* \params[in] sound
	*     The name of the sound you want to hear. essentially the filename minus
	*     the extension.
 	******************************************************************************/	
	void play(std::string sound);

	private:
	/***************************************************************************//**
 	* Holds the path to the sound files.
 	******************************************************************************/
	std::string path;

	/***************************************************************************//**
 	* Associates the key (sound name) with the actual loaded sound.
 	******************************************************************************/	
	std::map<std::string, sf::Sound*> sounds;

	/***************************************************************************//**
 	* Holds all the SoundBuffer objects loaded in, just in case if it is needed. 
 	******************************************************************************/
	std::vector<sf::SoundBuffer*> buffers;
};
