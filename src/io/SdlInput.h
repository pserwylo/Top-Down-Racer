/*
 * SdlInput.h
 *
 *  Created on: 08/12/2010
 *      Author: pete
 */

#ifndef SDLINPUT_H_
#define SDLINPUT_H_

#include "io/Input.h"
#include <SDL/SDL.h>

class SdlInput : public Input
{
public:
	SdlInput();
	virtual ~SdlInput();

	virtual void readInput();

private:
	SDLKey keyFlagMap[ NUM_KEYS ];
};

#endif /* SDLINPUT_H_ */
