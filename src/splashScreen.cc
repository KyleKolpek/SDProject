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
	sf::Vector2f pos = sprite.GetSize();
	//Setting the splash screen in the middle of the screen.	
	sprite.SetPosition((window.GetWidth()-pos.x)/2, (window.GetHeight()-pos.y)/2);
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
