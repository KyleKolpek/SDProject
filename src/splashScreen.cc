#include "splashScreen.h"
#include <iostream>

void SplashScreen::Show(sf::RenderWindow &window)
{
	sf::Image image;

	if(!image.LoadFromFile("../assets/splash/screen.jpg"))
	{
		std::cout << "Failed to Load Splash Screen Image\n";
		return;
	}
	sf::Sprite sprite(image);

	window.Draw(sprite);
	window.Display();

	sf::Event event;
	while(true)
	{
		window.Display();
		while(window.GetEvent(event))
		{
			if(event.Type == sf::Event::KeyPressed ||
				event.Type == sf::Event::MouseButtonPressed)
			{
				return;		
			}
			else if(event.Type == sf::Event::Closed)
			{
				exit(0);
			}
		}
	}
}
