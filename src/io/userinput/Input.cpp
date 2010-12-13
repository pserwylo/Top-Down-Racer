#include "io/userinput/Input.h"

Input::Input() : quit ( false ), steeringAngle ( 0 )
{
	this->flags[ ACCEL ] = false;
	this->flags[ DECEL ] = false;
	this->flags[ SHOOT ] = false;
}

Input::~Input()
{
}

bool Input::isAccelarating()
{
	return this->flags[ ACCEL ];
}

bool Input::isDecelarating()
{
	return this->flags[ DECEL ];
}

float Input::getSteeringAngle()
{
	return this->steeringAngle;
}

void Input::setSteeringAngle( float angle )
{
	if ( angle > 1.0f )
	{
		angle = 1.0f;
	}
	else if ( angle < -1.0f )
	{
		angle = -1.0f;
	}
	this->steeringAngle = angle;
}

bool Input::isShooting()
{
	return this->flags[ SHOOT ];
}

bool Input::isQuitting()
{
	return this->quit;
}
