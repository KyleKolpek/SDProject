#include "stdgl.h"
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>
#include "shaderManager.h"
#include "objLoader.h"
#include "character.h"
#include "camera.h"

void init();

Camera camera;
Character character(&camera);


int main()
{
	sf::WindowSettings Settings;
	Settings.DepthBits = 24;
	Settings.StencilBits = 8;
	sf::Window App(sf::VideoMode(800, 600, 32), "SFML Demo", sf::Style::Close, Settings);
	sf::SoundBuffer Buffer;
	if(!Buffer.LoadFromFile("../assets/sounds/huh.wav"))
	{
		std::cout << "Failure to load sound filei\n";
		return 0;
	}
	sf::Clock Clock;
	sf::Sound Sound;
	Sound.SetBuffer(Buffer);
	Sound.SetVolume(50.0f);

	init();

	const sf::Input& Input = App.GetInput();
	
	while(App.IsOpened())
	{
		sf::Event Event;
	
		//Some simple event handling.
		while (App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();
			
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App.Close();

			if(Event.Type == sf::Event::Resized)
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
			
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
			{
				if(Sound.GetStatus() == sf::Sound::Playing)
					Sound.Stop();
				Sound.Play();
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))
			{
				if(Sound.GetStatus() == sf::Sound::Playing)
					Sound.Stop();
				Sound.Play();
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
		character.draw();
		App.Display();
	}

	return EXIT_SUCCESS;
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	// Set clear values.
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Setup shaders
	ShaderManager manager("../assets/shaders/");
	manager.getProgram(2, "phong.vert",
		"phong.frag");
	camera.lookAt(glm::vec3(0.0, 0.0, 0.0),
				  glm::vec3(0.0, 0.0, -1.0),
				  glm::vec3(0.0, 1.0, 0.0));
	camera.perspective(60.0, 800.0/600.0, 0.01, 100.0); 
}

