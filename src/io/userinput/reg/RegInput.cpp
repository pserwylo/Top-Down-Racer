#include <io/userinput/reg/RegInput.h>

RegInput::RegInput()
{
	this->keyFlagMap[ ACCEL ] = SDLK_UP;
	this->keyFlagMap[ DECEL ] = SDLK_DOWN;
	this->keyFlagMap[ SHOOT ] = SDLK_SPACE;
	this->keyFlagMap[ LEFT ] = SDLK_LEFT;
	this->keyFlagMap[ RIGHT ] = SDLK_RIGHT;
}

RegInput::~RegInput()
{

}

float RegInput::getSteeringAngle()
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
		return 0.0f;
	}
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
			for ( int i = 0; i < NUM_FLAGS; i ++ )
			{
				if ( event.key.keysym.sym == this->keyFlagMap[ i ] )
				{
					this->flags[ i ] = true;
					break;
				}
			}

			if ( this->flags[ LEFT ] )
			{
				// Orient the steering wheel...
				this->setSteeringAngle( -1.0f );
			}
			else if ( this->flags[ RIGHT ] )
			{
				// Orient the steering wheel...
				this->setSteeringAngle( 1.0f );
			}
		}
		else if ( event.type == SDL_KEYUP )
		{
			// Reset the steering wheel...
			if ( event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT )
			{
				this->setSteeringAngle( 0.0f );
			}

			for ( int i = 0; i < NUM_FLAGS; i ++ )
			{
				if ( event.key.keysym.sym == this->keyFlagMap[ i ] )
				{
					this->flags[ i ] = false;
					break;
				}
			}

			if ( !this->flags[ LEFT ] && !this->flags[ RIGHT ] )
			{
				// Reset the steering wheel...
				this->setSteeringAngle( 0.0f );
			}
		}
	}
}
