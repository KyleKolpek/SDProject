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
Dungeon *dungeon;
Wall *wall1, *wall2;
Room *room;
int numPlayers, currentPlayer;
// Player *test;
std::vector<Player*> players;

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
	bool tabPressNew = true;

	// Show splash screen
	screen.Show(App, init);
	
	std::cout << current.Width << " " << current.Height << "\n";
	//init(current.Width, current.Height);
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
		
		/****   Free-form camera movement   ******************/
		camera->update(secondsSinceLastFrame, Input);
		/****	End	Free-form camera movement   **************/

		/****   Testing Character Movement   *****************/
		// test->update(secondsSinceLastFrame, Input);	

		for( int p=0; p<numPlayers; p++ )
		{
			players.at(p)->update(secondsSinceLastFrame, Input);
		}
		/****   End	Character Movement      ******************/


		// character switching
		if( Input.IsKeyDown( sf::Key::Tab ) && tabPressNew )
		{
			players.at(currentPlayer++)->setInactive();
			currentPlayer %= numPlayers;
			players.at(currentPlayer)->setActive();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
			Drawing goes below.
		*/
		
		//Call to actually display the things.
		//test->draw();
		for( int p=0; p<numPlayers; p++ )
		{
			players.at(p)->draw();
		}
		dungeon->draw();
		//wall1->draw();
		//wall2->draw();
		//room->draw();

		tabPressNew = !(Input.IsKeyDown( sf::Key::Tab ));
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

	// create dungeon
	dungeon = new Dungeon(5, 5, 15, camera);

	// Create players
	numPlayers = 4;
	
	std::string obj = "../assets/models/knight/knight.obj";
	
	/* make a single player unit
	std::string tex = "../assets/models/knight/blue.png";
	test = new Player(camera, dungeon, obj, tex);
	test->setRotation(180.0);
	test->setPosition(dungeon->getStartingPos());
	 */
	
	/* make several player units */
	std::string textures [4] = { "../assets/models/knight/blue.png",
								"../assets/models/knight/yellow.png",
								"../assets/models/knight/red.png",
								"../assets/models/knight/green.png"};
	for( int p=0; p<numPlayers; p++ )
	{
		players.push_back( new Player( camera, dungeon, obj, textures[p] ) );
		players.at(p)->setRotation(180.0);
		players.at(p)->setPosition(dungeon->getStartingPos());
	}
	currentPlayer=0;
	players.at(currentPlayer)->setActive();

	camera->setAt(dungeon->getStartingPos());
	camera->setEye(dungeon->getStartingPos() + glm::vec3(0.0, 10.0, 10.0));
	camera->setUp(glm::vec3(0.0, 1.0, 0.0));

	// This could probably be done cleaner
	Wall::loadTexture("../assets/models/wall/stoneWall.jpg");
	Room::loadTexture("../assets/models/floor/stone.jpg");

	// Setup shaders
	ShaderManager *shaderManager = new ShaderManager("../assets/shaders/");
//	test->setShaderManager(shaderManager);
	for( int p=0; p<numPlayers; p++ )
	{
		players.at(p)->setShaderManager(shaderManager); 
	}

	dungeon->setShaderManager(shaderManager);
} 

