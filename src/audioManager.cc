#include "audioManager.h"

AudioManager::AudioManager()
{
	path = "../assets/sounds/";
	musicPath = "../assets/music/";
}

AudioManager::~AudioManager()
{
	//Deleting the SoundBuffer objects.
	for(int i = 0; i < buffers.size(); ++i)
	{
		delete buffers[i];
	}

	//Deleting the Sound objects.
	std::map<std::string, sf::Sound*>::iterator itr;
	for(itr = sounds.begin(); itr != sounds.end(); itr++)
	{
		delete itr->second;
	}
	
}

void AudioManager::loadSound(std::string filename)
{
	//Variables Needed.
	sf::Sound *sound = new sf::Sound;
	sf::SoundBuffer *buffer = new sf::SoundBuffer;
	std::string file = path + filename;
	size_t dot;
	
	//Load sound from file.
	if(!buffer->LoadFromFile(file))
	{
		std::cout << "Failure to load " + filename + "\n";
		return;
	}

	//Store the SoundBuffers and Sounds in the class.
	buffers.push_back(buffer);
	sound->SetBuffer(*buffer);
	sound->SetVolume(50.0f);

	//Parsing out the name of the sound for the map.
	dot = filename.find(".");
	sounds[filename.substr(0, dot)] = sound;
}

void AudioManager::loadMusic(std::string filename)
{
	//Some variables we will need.
	sf::Music *music = new sf::Music;
	std::string file = musicPath + filename;
	size_t dot;

	//Loading the file.
	if(!music->OpenFromFile(file))
	{
		std::cout << "Failure to load " + filename + "\n";
		return;
	}	

	//Some variable settings
	music->SetVolume(50.0f);
	
	//Parsing out the name for the map
	dot = filename.find(".");
	musics[filename.substr(0, dot)] = music;
}

//Mostly for testing.
sf::Sound* AudioManager::getSound(std::string sound)
{
	return sounds[sound];
}

//Plays the requested sound.
void AudioManager::playSound(std::string sound)
{
	sf::Sound* sd = sounds[sound];
	if(sd->GetStatus() == sf::Sound::Playing)
		sd->Stop();
	sd->Play();
}

void AudioManager::playMusic(std::string music, bool loop)
{
	sf::Music *ms = musics[music];
	if(ms->GetStatus() == sf::Sound::Playing)
	{
		ms->Stop();
	}
	ms->SetLoop(loop);
	ms->Play();
}

void AudioManager::stopMusic(std::string music)
{
	sf::Music *ms = musics[music];
	if(ms->GetStatus() == sf::Sound::Playing)
	{
		ms->Stop();
	}
}
