/*
 * Input.cpp
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#include "Input.h"
#include "SDL/SDL.h"

Input::Input() : quit ( false )
{
	this->flags[ ACCEL ] = false;
	this->flags[ DECEL ] = false;
	this->flags[ LEFT ] = false;
	this->flags[ RIGHT ] = false;
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

bool Input::isTurningLeft()
{
	return this->flags[ LEFT ];
}

bool Input::isTurningRight()
{
	return this->flags[ RIGHT ];
}

bool Input::isShooting()
{
	return this->flags[ SHOOT ];
}

bool Input::isQuitting()
{
	return this->quit;
}
