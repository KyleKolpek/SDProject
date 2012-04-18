#include "audioManager.h"

AudioManager::AudioManager()
{
	path = "../assets/sounds/";
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

void AudioManager::load(std::string filename)
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
	std::cout << filename.substr(0, dot) + "\n";
	sounds[filename.substr(0, dot)] = sound;
}

//Mostly for testing.
sf::Sound* AudioManager::get(std::string sound)
{
	return sounds[sound];
}

//Plays the requested sound.
void AudioManager::play(std::string sound)
{
	sf::Sound* sd = sounds[sound];
	if(sd->GetStatus() == sf::Sound::Playing)
		sd->Stop();
	sd->Play();
}
