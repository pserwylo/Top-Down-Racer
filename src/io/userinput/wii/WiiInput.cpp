#include <io/userinput/wii/WiiInput.h>
#include "wiiuse/wpad.h"

WiiInput::WiiInput()
{

}

WiiInput::~WiiInput()
{

}

void WiiInput::readInput()
{

	WPAD_ScanPads();

	u32 pressed = WPAD_ButtonsDown( 0 );
	u32 held = WPAD_ButtonsHeld( 0 );

	if ( pressed & WPAD_BUTTON_HOME )
	{
		this->quit = !this->quit;
	}

	this->flags[ LEFT ] = ( held & WPAD_BUTTON_UP );
	this->flags[ RIGHT ] = ( held & WPAD_BUTTON_DOWN );
	this->flags[ ACCEL ] = ( held & WPAD_BUTTON_2 );
	this->flags[ DECEL ] = ( held & WPAD_BUTTON_LEFT );
	this->flags[ SHOOT ] = ( held & WPAD_BUTTON_1 );

}
