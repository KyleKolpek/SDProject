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

void init();

Camera *camera;
Actor *test;
Dungeon *dungeon;
Wall *wall1, *wall2;
Room *room;

int main()
{
	
	sf::WindowSettings Settings;
	Settings.DepthBits = 24;
	Settings.StencilBits = 8;

	// Show splash screen
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), 
						"Delfino's Dungeon Extravaganza", 
						sf::Style::Close, Settings);

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
			if(Event.Type == sf::Event::Resized)
			{
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
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
		
		camera->update(App.GetFrameTime(), Input);

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
	camera = new Camera(glm::vec3(75.0, 100.0, 250.0),
						glm::vec3(75.0, 0.0, 125.0),
						glm::vec3(0.0, 1.0, 0.0));
	camera->perspective(45.0, 4.0/3.0, 0.01, 200.0); 

	test = new Actor(camera);
	//wall1 = new Wall(-10, -10, 10, -10, 4, &camera);
	//wall2 = new Wall(-10, 10, -10, -10, 4, &camera);
	//room = new Room(0, 0, &camera);
	//room->roomType = Room::FOUR;
	//room->orient = Room::ROT_ZERO;
	//room->placeWalls();

	// create dungeon
	dungeon = new Dungeon(5, 5, 15, camera);
	std::cout << dungeon->str() << std::endl;
	glm::vec3 sp = dungeon->getStartingPos();
	std::cout << "Starting Pos: " << sp.x << "," << sp.z << std::endl;

	// This could probably be done cleaner
	Wall::loadTexture("../assets/models/wall/stoneWall.jpg");
	Room::loadTexture("../assets/models/floor/stone.jpg");

	// Setup shaders
	ShaderManager *shaderManager = new ShaderManager("../assets/shaders/");
	test->setShaderManager(shaderManager);
	//wall1->setShaderManager(shaderManager);
	//wall2->setShaderManager(shaderManager);
	//room->setShaderManager(shaderManager);
	dungeon->setShaderManager(shaderManager);
}

