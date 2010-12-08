/*
 * SdlInput.cpp
 *
 *  Created on: 08/12/2010
 *      Author: pete
 */

#include <io/SdlInput.h>

SdlInput::SdlInput()
{
	this->keyFlagMap[ ACCEL ] = SDLK_UP;
	this->keyFlagMap[ DECEL ] = SDLK_DOWN;
	this->keyFlagMap[ LEFT ] = SDLK_LEFT;
	this->keyFlagMap[ RIGHT ] = SDLK_RIGHT;
	this->keyFlagMap[ SHOOT ] = SDLK_SPACE;
}

SdlInput::~SdlInput()
{

}

void SdlInput::readInput()
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
			for ( int i = 0; i < NUM_KEYS; i ++ )
			{
				if ( event.key.keysym.sym == this->keyFlagMap[ i ] )
				{
					this->flags[ i ] = true;
				}
			}
		}
		else if ( event.type == SDL_KEYUP )
		{
			for ( int i = 0; i < NUM_KEYS; i ++ )
			{
				if ( event.key.keysym.sym == this->keyFlagMap[ i ] )
				{
					this->flags[ i ] = false;
				}
			}
		}
	}
}
