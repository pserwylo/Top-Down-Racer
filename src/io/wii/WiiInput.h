#ifndef WIIINPUT_H_
#define WIIINPUT_H_

#include "io/Input.h"

class WiiInput : public Input
{
public:
	WiiInput();
	virtual ~WiiInput();

	virtual void readInput();
};

#endif /* WIIINPUT_H_ */
