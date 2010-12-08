#include <io/WiiInput.h>

WiiInput::WiiInput()
{

}

WiiInput::~WiiInput()
{

}

void WiiInput::readInput()
{

	// Call WPAD_ScanPads each loop, this reads the latest controller states
	WPAD_ScanPads();

	// WPAD_ButtonsDown tells us which buttons were pressed in this loop
	// this is a "one shot" state which will not fire again until the button has been released
	u32 pressed = WPAD_ButtonsDown(0);

	// We return to the launcher application via exit
	if ( pressed & WPAD_BUTTON_HOME )
	{
		this->quit = true;
	}

}
