#include <io/userinput/wii/WiiInput.h>
#include "wiiuse/wpad.h"

WiiInput::WiiInput()
{

}

WiiInput::~WiiInput()
{

}

float WiiInput::getSteeringAngle()
{
	if ( this->flags[ LEFT ] )
	{
		return -1.0f;
	}
	else if ( this->flags[ RIGHT ] )
	{
		return 1.0f;
	}
	else
	{
		return Input::getSteeringAngle();
	}
}

void WiiInput::readInput()
{
	WPAD_ScanPads();
	this->wpadData = WPAD_Data( WPAD_CHAN_0 );

	if ( this->wpadData->btns_d & WPAD_BUTTON_HOME )
	{
		this->quit = !this->quit;
	}

	// Only bother going up to about 50 degrees, because you don't want to turn much more than that when
	// steering with the wiimote...
	if ( -WiiInput::STRAIGHT_THRESHOLD < this->wpadData->orient.pitch && this->wpadData->orient.pitch < WiiInput::STRAIGHT_THRESHOLD )
	{
		this->setSteeringAngle( 0 );
	}
	else
	{
		this->setSteeringAngle( - this->wpadData->orient.pitch / 50.0f );
	}

	this->flags[ LEFT ] = ( this->wpadData->btns_h & WPAD_BUTTON_UP );
	this->flags[ RIGHT ] = ( this->wpadData->btns_h & WPAD_BUTTON_DOWN );
	this->flags[ ACCEL ] = ( this->wpadData->btns_h & WPAD_BUTTON_2 );
	this->flags[ DECEL ] = ( this->wpadData->btns_h & WPAD_BUTTON_LEFT );
	this->flags[ SHOOT ] = ( this->wpadData->btns_h & WPAD_BUTTON_1 );

}
