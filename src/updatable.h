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
	 * \param[in] sec
	 *     The number of seconds since the last update.
	 * \param[in] input
	 *     An input object holding any given user input.
	 **************************************************************************/
	virtual void update(float sec, sf::Input const &input) = 0;
};

#endif
