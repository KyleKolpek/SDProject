#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

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
	/***********************************************************************//**
 	* Default Constructor. 
 	* Sets the path variable.
 	***************************************************************************/
	AudioManager();

	/***********************************************************************//**
 	* Default Destructor. 
 	* Releases dynamically allocated memory.
 	***************************************************************************/
	~AudioManager();
	
	/***********************************************************************//**
 	* Loads sound file, filename, and adds it to the map. 
 	* \param[in] filename
	*     The name of the file in path that you want to load.
 	***************************************************************************/
	void loadSound(std::string filename);

	/***********************************************************************//**
 	* Returns a pointer to the Sound you wanted.
 	* \param[in] sound
	*     The name of the sound you want to here. essentially the filename minus
	*	  the extension.
 	***************************************************************************/
	sf::Sound* getSound(std::string sound);

	/***********************************************************************//**
 	* Plays the sound you requested.
 	* \params[in] sound
	*     The name of the sound you want to hear. essentially the filename minus
	*     the extension.
 	***************************************************************************/	
	void playSound(std::string sound);

	/***********************************************************************//**
 	* Loads the music you requested.
 	* \params[in] filename
	*     The name of the music you want to load.
 	***************************************************************************/		
	void loadMusic(std::string filename);

	/***********************************************************************//**
 	* Plays the music you requested.
 	* \params[in] music
	*     The name of the sound you want to hear. essentially the filename minus
	*     the extension.
	* \params[in] loop
	*     Tells if you want to song to loop.
 	***************************************************************************/	
	void playMusic(std::string music, bool loop);

	/***********************************************************************//**
 	* Stops the music that is currently playing.
 	* \params[in] music
	*     The name of the music you want to stop.
 	***************************************************************************/		
	void stopMusic(std::string music);
private:
	/***********************************************************************//**
 	* Holds the path to the sound files.
 	***************************************************************************/
	std::string path;

	/***********************************************************************//**
 	* Holds the path to the music files.
 	***************************************************************************/	
	std::string musicPath;

	/***********************************************************************//**
 	* Associates the key (sound name) with the actual loaded sound.
 	***************************************************************************/	
	std::map<std::string, sf::Sound*> sounds;

	/***********************************************************************//**
 	* Holds all the SoundBuffer objects loaded in, just in case if it is needed. 
 	***************************************************************************/
	std::vector<sf::SoundBuffer*> buffers;

	/***********************************************************************//**
 	* Holds all the Music objects for playbck. 
 	***************************************************************************/
	std::map<std::string, sf::Music*> musics;
};

#endif
