#include "stdgl.h"
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>
#include "shaderManager.h"
#include "objLoader.h"
#include "character.h"
#include "camera.h"
#include "testDrawable.h"
#include "audioManager.h"
#include "dungeon.h"

void init();

Camera camera;
TestDrawable *test;

int main()
{
	// create dungeon
	Dungeon dungeon(4, 4, 5);

	sf::WindowSettings Settings;
	Settings.DepthBits = 24;
	Settings.StencilBits = 8;
	sf::Window App(sf::VideoMode(800, 600, 32), "SFML Demo", sf::Style::Close, Settings);
	/*
	sf::SoundBuffer Buffer;
	if(!Buffer.LoadFromFile("../assets/sounds/huh.wav"))
	{
		std::cout << "Failure to load sound file\n";
		return 0;
	}
	sf::Clock Clock;
	sf::Sound Sound;
	Sound.SetBuffer(Buffer);
	Sound.SetVolume(50.0f);
	*/
	AudioManager ad;
	ad.load("huh.wav");
	ad.load("doorSqueak.wav");
	ad.load("thunder.wav");
	ad.load("wind.wav");
	init();

	const sf::Input& Input = App.GetInput();
	
	while(App.IsOpened())
	{
		sf::Event Event;
	
		//Some simple event handling.
		while (App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
			{
				App.Close();
			}
			
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
			{
				App.Close();
			}

			if(Event.Type == sf::Event::Resized)
			{
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
			}
			
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
			{
				ad.play("wind");
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
			{
				ad.play("thunder");
			}

			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
			{
				ad.play("huh");
				/*
				sf::Sound Sound = ad.get("huh");
				std::cout << Sound.GetBuffer()->GetDuration() << std::endl;
				if(Sound.GetStatus() == sf::Sound::Playing)
					Sound.Stop();
				Sound.Play();
				*/
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))
			{
				ad.play("doorSqueak");
				/*
				sf::Sound Sound = ad.get("huh");
				if(Sound.GetStatus() == sf::Sound::Playing)
					Sound.Stop();
				Sound.Play();
				*/
			}
		}
		
		App.SetActive();
		
		/*
			Example of getting some values from the input object. Also pretty 
			easy to get mouse below. 
		*/
		bool leftKeyDown = Input.IsKeyDown(sf::Key::Left);
		bool rightButtonDown = Input.IsMouseButtonDown(sf::Mouse::Right);
		unsigned int mouseX = Input.GetMouseX();
		unsigned int mouseY = Input.GetMouseY();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*
			Drawing goes below. Easily done in another function or the method
			of render object! So that is pretty easy.
		*/
		
		//Call to actually display the things.
		test->draw();
		App.Display();
	}

	return EXIT_SUCCESS;
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	// Set clear values.
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glViewport(0, 0, 800, 600);

	// Setup shaders
	ShaderManager manager("../assets/shaders/");
	test = new TestDrawable(&camera);
	test->setProgram(manager.getProgram(2, "phong.vert", "phong.frag"));
	camera.lookAt(glm::vec3(0.0, 0.0, 0.0),
				  glm::vec3(0.0, 0.0, -1.0),
				  glm::vec3(0.0, 1.0, 0.0));
	camera.perspective(45.0, 4.0/3.0, 0.01, 100.0); 
}

