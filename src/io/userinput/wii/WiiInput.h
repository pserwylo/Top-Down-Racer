#ifndef WIIINPUT_H_
#define WIIINPUT_H_

#include "io/userinput/Input.h"
#include "wiiuse/wpad.h"

class WiiInput : public Input
{
public:
	WiiInput();
	virtual ~WiiInput();

	virtual void readInput();
	virtual float getSteeringAngle();

protected:
	WPADData* wpadData;
	static const int STRAIGHT_THRESHOLD = 5;
};

#endif /* WIIINPUT_H_ */
