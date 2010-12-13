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
	virtual float getSteeringAngle();

private:
	SDLKey keyFlagMap[ NUM_FLAGS ];
};

#endif /* REGINPUT_H_ */
