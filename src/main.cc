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
#include "wall.h"
#include "splashScreen.h"

void init();

Camera camera;
Character *test;
Dungeon *dungeon;

int main()
{
	
	sf::WindowSettings Settings;
	Settings.DepthBits = 24;
	Settings.StencilBits = 8;
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), 
						"Delfino's Dungeon Extravaganza", 
						sf::Style::Close, Settings);

	sf::Clock Clock;

	AudioManager ad;
	ad.loadMusic("forest.ogg");
	ad.loadSound("huh.wav");
	ad.loadSound("doorSqueak.wav");
	ad.loadSound("thunder.wav");
	ad.loadSound("wind.wav");
	
	SplashScreen screen;
	ad.playMusic("forest", true);
	const sf::Input& Input = App.GetInput();
	
	screen.Show(App);
	init();
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
				ad.playSound("wind");
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
			{
				ad.playSound("thunder");
			}

			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
			{
				ad.playSound("huh");
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))
			{
				ad.playSound("doorSqueak");
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
		dungeon->draw();

		App.Display();
	}

	return EXIT_SUCCESS;
}

void init()
{
	// Initialize glew -- should fix segfaults on linux machines
#ifdef _NIX
	glewInit();
#endif
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

	test = new Character(&camera);

	// create dungeon
	dungeon = new Dungeon(3, 3, 1, &camera);
	std::cout << dungeon->str() << std::endl;

	// This could probably be done cleaner
	Wall::loadTexture("../assets/models/wall/stoneWall.jpg");

	// Setup shaders
	ShaderManager *shaderManager = new ShaderManager("../assets/shaders/");
	test->setShaderManager(shaderManager);
	dungeon->setShaderManager(shaderManager);
	camera.lookAt(glm::vec3(0.0, 0.0, 0.0),
				  glm::vec3(0.0, 0.0, -1.0),
				  glm::vec3(0.0, 1.0, 0.0));
	camera.perspective(45.0, 4.0/3.0, 0.01, 100.0); 
}

