#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<cstdlib>

/***************************************************************************//**
* A class that just displays the splash screen.
*******************************************************************************/
class SplashScreen
{
public:
	/***********************************************************************//**
	* Actually displays the splash screen.
	* \params[in] window
	*     Pass in the window to draw to.
	* \params[in] init
	*     A function pointer to a function that loads the game.
	***************************************************************************/
	void Show(sf::RenderWindow &window, void (*init)(unsigned int, unsigned int));
};

#endif

