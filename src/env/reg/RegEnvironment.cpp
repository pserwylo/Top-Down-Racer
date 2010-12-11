#include "env/reg/RegEnvironment.h"
#include "SDL/SDL.h"
#include "GL/gl.h"
#include "io/reg/RegInput.h"

SdlGlEnvironment::SdlGlEnvironment()
{
	this->input = new RegInput();
}

SdlGlEnvironment::~SdlGlEnvironment()
{

}

Input* SdlGlEnvironment::getInput()
{
	return this->input;
}

void SdlGlEnvironment::setup()
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

}

void SdlGlEnvironment::tearDown()
{
	SDL_Quit();
}

void SdlGlEnvironment::startDraw()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void SdlGlEnvironment::endDraw()
{
	SDL_GL_SwapBuffers();
}
