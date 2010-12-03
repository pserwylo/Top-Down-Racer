/*
 * CarRenderer.cpp
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#include "CarRenderer.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "rendering/cars_offsets.h"
#include "core/Car.h"
#include <iostream>

SDL_Surface* CarSdlRenderer::surface = NULL;

CarSdlRenderer::CarSdlRenderer( Car* car ) : car( car )
{

	if ( CarSdlRenderer::surface == NULL )
	{
		SDL_Surface* tmpSurface = NULL;
		tmpSurface = IMG_Load( "/home/pete/code/sdl/images/cars_all.png" );
		if ( tmpSurface == NULL )
		{
			std::cerr << "Could not load car images" << std::endl;
		}

		CarSdlRenderer::surface = SDL_DisplayFormat( tmpSurface );
		Uint32 clearColour = SDL_MapRGB( CarSdlRenderer::surface->format, 0, 0xff, 0 );
		SDL_SetColorKey( CarSdlRenderer::surface, SDL_SRCCOLORKEY, clearColour );
		SDL_FreeSurface( tmpSurface );

		this->carImageBounds.x = CAR_2_X_OFFSET;
		this->carImageBounds.y = CAR_2_Y_OFFSET;
		this->carImageBounds.w = CAR_2_WIDTH;
		this->carImageBounds.h = CAR_2_HEIGHT;
	}
}

CarSdlRenderer::~CarSdlRenderer()
{
}

void CarSdlRenderer::render( SDL_Surface* screen )
{
	SDL_Surface* rotatedSurface = NULL;
	SDL_Surface* carSurface = SDL_CreateRGBSurface
	(
		SDL_SWSURFACE,
		this->carImageBounds.w,
		this->carImageBounds.h,
		screen->format->BitsPerPixel,
		screen->format->Rmask,
		screen->format->Gmask,
		screen->format->Bmask,
		screen->format->Amask
	);
	SDL_BlitSurface( CarSdlRenderer::surface, &this->carImageBounds, carSurface, NULL );
	rotatedSurface = rotozoomSurface( carSurface, this->car->carBody->GetAngle() * 180 / 3.14159 - 90, 1, 0 );

	SDL_Rect location;
	location.x = this->car->carBody->GetPosition().x - rotatedSurface->w / 2;
	location.y = this->car->carBody->GetPosition().y - rotatedSurface->h / 2;
	location.w = rotatedSurface->w;
	location.h = rotatedSurface->h;

	SDL_BlitSurface( rotatedSurface, NULL, screen, &location );

	SDL_FreeSurface( rotatedSurface );
	SDL_FreeSurface( carSurface );
}
