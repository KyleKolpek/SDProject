#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

/***************************************************************************//**
* A class that just displays the splash screen.
*******************************************************************************/
class SplashScreen
{
public:
	/***********************************************************************//**
	* Actually displays the splash screen.
	* \param[in] window
	*     Pass in the window to draw to.
	***************************************************************************/
	void Show(sf::RenderWindow &window);
};

#endif

