#include "stdgl.h"
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>
#include "shaderManager.h"
#include "actor.h"
#include "camera.h"
#include "audioManager.h"
#include "dungeon.h"
#include "wall.h"
#include "splashScreen.h"
#include "room.h"
#include "player.h"

void init(unsigned int width, unsigned int height);

Camera *camera;
Player *test;
Dungeon *dungeon;
Wall *wall1, *wall2;
Room *room;

int main()
{
	
	sf::WindowSettings Settings;
	Settings.DepthBits = 24;
	Settings.StencilBits = 8;
	
	sf::VideoMode current = sf::VideoMode(800,600,32);//sf::VideoMode::GetDesktopMode();	
	// Show splash screen
	sf::RenderWindow App(current, 
						"Delfino's Dungeon Extravaganza", 
						//sf::Style::Fullscreen,
						sf::Style::Close | sf::Style::Resize, 
						Settings);

	AudioManager ad;
	ad.loadMusic("forest.ogg");
	ad.loadSound("huh.wav");
	ad.loadSound("doorSqueak.wav");
	ad.loadSound("thunder.wav");
	ad.loadSound("wind.wav");
	
	SplashScreen screen;
	ad.playMusic("forest", true);
	const sf::Input& Input = App.GetInput();
	
	// Show splash screen
	screen.Show(App);
	
	std::cout << current.Width << " " << current.Height << "\n";
	init(current.Width, current.Height);
	//screen.Show(App);
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
			if(Event.Type == sf::Event::Resized)
			{
				std::cout << Event.Size.Width << " " << Event.Size.Height<< "\n";
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
			{
				App.Close();
			}
		}
		
		App.SetActive();

		float secondsSinceLastFrame = App.GetFrameTime();
		
		/****   Free-form camera movement	*****************/
		camera->update(secondsSinceLastFrame, Input);
		/****	End	*****************************************/

		/****	Testing Character Movement	***************/
		test->update(secondsSinceLastFrame, Input);	
		/****	End	***************************************/


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
			Drawing goes below.
		*/
		
		//Call to actually display the things.
		test->draw();
		dungeon->draw();
		//wall1->draw();
		//wall2->draw();
		//room->draw();

		App.Display();
	}

	return EXIT_SUCCESS;
}

void init(unsigned int width, unsigned int height)
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

	glViewport(0, 0, width, height);
	camera = new Camera();
	camera->perspective(45.0, 4.0/3.0, 0.01, 200.0); 

	test = new Player(camera, dungeon);
	test->setRotation(180.0);

	// create dungeon
	dungeon = new Dungeon(5, 5, 15, camera);
	test->setPosition(dungeon->getStartingPos());

	camera->setAt(dungeon->getStartingPos());
	camera->setEye(dungeon->getStartingPos() + glm::vec3(0.0, 10.0, 10.0));
	camera->setUp(glm::vec3(0.0, 1.0, 0.0));

	// This could probably be done cleaner
	Wall::loadTexture("../assets/models/wall/stoneWall.jpg");
	Room::loadTexture("../assets/models/floor/stone.jpg");

	// Setup shaders
	ShaderManager *shaderManager = new ShaderManager("../assets/shaders/");
	test->setShaderManager(shaderManager);
	dungeon->setShaderManager(shaderManager);
}

