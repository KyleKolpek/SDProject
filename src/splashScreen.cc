#include "splashScreen.h"
#include <iostream>

void SplashScreen::Show(sf::RenderWindow &window,
						void (*init)(unsigned int, unsigned int))
{
	sf::Image image, image2;

	if(!image.LoadFromFile("../assets/splash/splash1.png"))
	{
		std::cout << "Failed to Load Splash Screen Image\n";
		return;
	}

	if(!image2.LoadFromFile("../assets/splash/splash2.png"))
	{
		std::cout << "Failed to load a splash screen image\n";
		return;
	}
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	sf::Sprite sprite(image);
	//Setting the splash screen in the middle of the screen.	
	sprite.Resize(window.GetWidth(), window.GetHeight());
	
	sf::Event event;
	window.Draw(sprite);
	window.Display();

	(*init)(window.GetWidth(), window.GetHeight());
	
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	sprite.SetImage(image2);
	
	window.Clear();
	window.Draw(sprite);
	window.Display();
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	while(window.IsOpened())
	{
		while(window.GetEvent(event))
		{
			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)
			{
				window.Close();
				exit(0);
			}
			else if(event.Type == sf::Event::KeyPressed ||
				event.Type == sf::Event::MouseButtonPressed)
			{
				return;		
			}
			else if(event.Type == sf::Event::Closed)
			{
				window.Close();
				exit(0);
			}
		
		}
	}
}
