#include <io/userinput/reg/RegInput.h>

RegInput::RegInput()
{
	this->keyFlagMap[ ACCEL ] = SDLK_UP;
	this->keyFlagMap[ DECEL ] = SDLK_DOWN;
	this->keyFlagMap[ LEFT ] = SDLK_LEFT;
	this->keyFlagMap[ RIGHT ] = SDLK_RIGHT;
	this->keyFlagMap[ SHOOT ] = SDLK_SPACE;
}

RegInput::~RegInput()
{

}

void RegInput::readInput()
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
