/*
 * Input.cpp
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#include "Input.h"
#include "SDL/SDL.h"

CarInput::CarInput() : quit ( false )
{
	this->flags[ ACCEL ] = false;
	this->flags[ DECEL ] = false;
	this->flags[ LEFT ] = false;
	this->flags[ RIGHT ] = false;
	this->flags[ SHOOT ] = false;
	this->keyFlagMap[ ACCEL ] = SDLK_UP;
	this->keyFlagMap[ DECEL ] = SDLK_DOWN;
	this->keyFlagMap[ LEFT ] = SDLK_LEFT;
	this->keyFlagMap[ RIGHT ] = SDLK_RIGHT;
	this->keyFlagMap[ SHOOT ] = SDLK_SPACE;
}

CarInput::~CarInput()
{
}

void CarInput::readInput()
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		if ( event.type == SDL_QUIT )
		{
			this->quit = true;
		}
		else if ( event.type == SDL_KEYDOWN )
		{
			for ( int i = 0; i < 4; i ++ )
			{
				if ( event.key.keysym.sym == this->keyFlagMap[ i ] )
				{
					this->flags[ i ] = true;
				}
			}
		}
		else if ( event.type == SDL_KEYUP )
		{
			for ( int i = 0; i < 4; i ++ )
			{
				if ( event.key.keysym.sym == this->keyFlagMap[ i ] )
				{
					this->flags[ i ] = false;
				}
			}
		}
	}
}

bool CarInput::isAccelarating()
{
	return this->flags[ ACCEL ];
}

bool CarInput::isDecelarating()
{
	return this->flags[ DECEL ];
}

bool CarInput::isTurningLeft()
{
	return this->flags[ LEFT ];
}

bool CarInput::isTurningRight()
{
	return this->flags[ RIGHT ];
}

bool CarInput::isShooting()
{
	return this->flags[ SHOOT ];
}

bool CarInput::isQuitting()
{
	return this->quit;
}
