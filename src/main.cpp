/*
 * main.cpp
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#include "SDL/SDL.h"
#include "GL/gl.h"
#include "core/Car.h"
#include "core/global.h"
#include "core/Race.h"
#include <iostream>

int main( int argc, char** argv )
{
	SDL_Init( SDL_INIT_EVERYTHING );

	SDL_SetVideoMode( 800, 600, 32, SDL_HWSURFACE | SDL_OPENGL );

	glViewport( 0, 0, 800, 600 );
	glMatrixMode( GL_PROJECTION );
	glOrtho( 0, 50, 37.5, 0, -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glDisable( GL_DEPTH_TEST );

	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	glPopMatrix();
	SDL_GL_SwapBuffers();

	Race race;
	race.runRace();

	SDL_Quit();
	return 0;

}
