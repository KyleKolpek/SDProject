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
	sprite.Resize(window.GetWidth(), window.GetHeight());
	
	float alpha = 255.0f;
	sf::Event event;
	window.Draw(sprite);
	window.Display();
	while(window.IsOpened() && alpha != 0)
	{
		while(window.GetEvent(event))
		{
			if(event.Type == sf::Event::KeyPressed ||
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
