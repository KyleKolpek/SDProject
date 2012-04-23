#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include<SFML/window.hpp>
#include<SFML/graphics.hpp>
#include<SFML/system.hpp>

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

