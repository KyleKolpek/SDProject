#ifndef UPDATABLE_H
#define UPDATABLE_H

#include "stdgl.h"
#include <SFML/Window.hpp>

/***************************************************************************//**
 * Allows an object to be updated.
 * Provides a virtual void method, update(), to be run every frame.
 ******************************************************************************/
class Updatable
{
public:
	/***********************************************************************//**
	 * Virtual destructor.
	 **************************************************************************/
    virtual ~Updatable();

	/***********************************************************************//**
	 * Handles input and updates the object.
	 * \param[in] clock
	 *     A clock object holding the time passed since the last update.
	 * \param[in] input
	 *     An input object holding any given user input.
	 **************************************************************************/
	virtual void update(sf::Clock const &clock, sf::Input const &input) = 0;
};

#endif
