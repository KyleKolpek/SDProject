#include "stdgl.h"
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>
#include "audioManager.h"
#include "splashScreen.h"
#include "game.h"

using namespace std;

Game *game;

void init(unsigned int width, unsigned int height);

int main()
{
	srand(time(NULL));	
	sf::WindowSettings Settings;
	Settings.DepthBits = 24;
	Settings.StencilBits = 8;
	
	//sf::VideoMode current = sf::VideoMode(800,600,32);//
	sf::VideoMode current = sf::VideoMode::GetDesktopMode();	

	// Show splash screen
	sf::RenderWindow App(current, 
						"Dungeon Extravaganza", 
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
	const sf::Input& input = App.GetInput();

	// Show splash screen
	screen.Show(App, init);
	
	cout << current.Width << " " << current.Height << endl;
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
				cout << Event.Size.Width << " " << Event.Size.Height << endl;
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
			}
			if((Event.Type == sf::Event::KeyPressed) &&
				(Event.Key.Code == sf::Key::Escape))
			{
				App.Close();
			}
		}
		
		App.SetActive();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// This should be migrated to a HUD class at some point
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		sf::Image health(200, 20, sf::Color(255, 0, 0));
		sf::Sprite sprite(health);
		App.Draw(sprite);

		sf::Image total(200, 20, sf::Color(0, 255, 255));
		sf::Sprite sprite3(total);
		sf::Vector2f vec(0, 20);
		sprite3.SetPosition(vec);
		App.Draw(sprite3);

		sf::Image distance((1-game->getActivePlayerStamina())*200,
			20, sf::Color(0, 0, 255));
		sf::Sprite sprite2(distance);
		sprite2.SetPosition(vec);
		App.Draw(sprite2);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		// end HUD

		game->update(App.GetFrameTime(), input);
		game->draw();
		App.Display();
	}

	delete game;
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

	game = new Game();
} 

