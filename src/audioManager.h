#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<map>
#include<iostream>
#include<vector>

class AudioManager
{
	public:
	AudioManager();
	~AudioManager();
	
	void load(std::string filename);
	sf::Sound* get(std::string sound);

	void play(std::string sound);

	private:
	std::map<std::string, sf::Sound*> sounds;
	std::vector<sf::SoundBuffer*> buffers;
};
