#include "game.h"
#include "shaderManager.h"
#include "camera.h"
#include "dungeon.h"
#include "actor.h"
#include "objLoader.h"
#include <iostream>

using namespace std;

Game::Game():
	tabPressNew(true),
	numPlayers(1),
	currentPlayer(0),
	camera(NULL),
	dungeon(NULL)
{
	setShaderManager(new ShaderManager("../assets/shaders/"));

	//Loading objs.
	loader = new ObjLoader();
	loader->loadObjFile("../assets/models/knight/knight.obj");
	loader->loadObjFile("../assets/models/box/box.obj");
	loader->loadObjFile("../assets/models/dragon/dragon.obj");
	
	loader->loadTexture("../assets/models/knight/blue.png");
	loader->loadTexture("../assets/models/knight/red.png");
	loader->loadTexture("../assets/models/knight/yellow.png");
	loader->loadTexture("../assets/models/knight/green.png");
	loader->loadTexture("../assets/models/box/box.jpg");
	loader->loadTexture("../assets/models/dragon/dragon.tga");

	// Create Camera
	camera = new Camera();

	// Create Dungeon
	dungeon = new Dungeon(5, 5, 15, camera, loader);

	// Create players
	numPlayers = 2;

	// make several player units
	string obj = "../assets/models/knight/knight.obj";
	string textures [4] = { "../assets/models/knight/blue.png",
								"../assets/models/knight/yellow.png",
								"../assets/models/knight/red.png",
								"../assets/models/knight/green.png"};

	for( int p=0; p<numPlayers; p++ )
	{
		players.push_back( new Player( camera, dungeon, obj, textures[p], loader ) );
		players.at(p)->setRotation(180.0);
		players.at(p)->setPosition(dungeon->getStartingPos());
	}
	currentPlayer=0;
	players.at(currentPlayer)->setActive();

	// set up camera
	camera->perspective(45.0, 4.0/3.0, 0.01, 200.0); 
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

Game::~Game()
{
	delete camera;
	delete dungeon;
	delete loader;
}

void Game::update(float sec, sf::Input const &input)
{
	/****   Free-form camera movement   ******************/
	camera->update(sec, input);
	/****	End	Free-form camera movement   **************/

	/****   Testing Character Movement   *****************/
	// test->update(secondsSinceLastFrame, Input);	

	for( int p = 0; p < numPlayers; p++ )
	{
		players.at(p)->update(sec, input);
	}
	/****   End	Character Movement      ******************/


	// character switching
	if( input.IsKeyDown( sf::Key::Tab ) && tabPressNew )
	{
		players.at(currentPlayer++)->setInactive();
		currentPlayer %= numPlayers;
		players.at(currentPlayer)->setActive();
	}

	tabPressNew = !(input.IsKeyDown( sf::Key::Tab ));
}

void Game::draw()
{
	// Build arrays of light info
	float positions[3 * players.size()];
	float colors[3 * players.size()];
	for(int i = 0; i < players.size(); ++i)
	{
		glm::vec4 pos = //players[i]->getModelMatrix() *
						camera->getViewMatrix() *
						glm::vec4(players[i]->getPosition(), 1.0);

		// Set the light above each player
		positions[i * 3]     = pos.x;
		positions[i * 3 + 1] = pos.y + 2;
		positions[i * 3 + 2] = pos.z;

		// Set the color to orange
		colors[i * 3]     = 0.5;
		colors[i * 3 + 1] = 0.5;
		colors[i * 3 + 2] = 0.5;
	}

	dungeon->setLights(positions, colors, players.size());
	dungeon->draw();

	for( int p=0; p<numPlayers; ++p )
	{
		players.at(p)->draw();
	}
}

float Game::getActivePlayerStamina()
{
	return players[currentPlayer]->getPercentMoved();
}
