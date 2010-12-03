/*
 * CarRenderer.h
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#ifndef CARRENDERER_H_
#define CARRENDERER_H_

#include <SDL/SDL.h>
#include "core/Car.h"

class CarSdlRenderer
{

	friend class Car;

public:
	CarSdlRenderer( Car* car );
	virtual ~CarSdlRenderer();

	void render( SDL_Surface* screen );

private:
	static SDL_Surface* surface;
	SDL_Rect carImageBounds;
	Car* car;

};

#endif /* CARRENDERER_H_ */
