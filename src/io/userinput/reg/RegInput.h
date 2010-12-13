#ifndef REGINPUT_H_
#define REGINPUT_H_

#include "io/userinput/Input.h"
#include <SDL/SDL.h>

class RegInput : public Input
{
public:
	RegInput();
	virtual ~RegInput();

	virtual void readInput();

private:
	SDLKey keyFlagMap[ NUM_KEYS ];
};

#endif /* REGINPUT_H_ */
