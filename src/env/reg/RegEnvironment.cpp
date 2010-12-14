#include "env/reg/RegEnvironment.h"
#include "SDL/SDL.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "io/userinput/reg/RegInput.h"
#include "core/Race.h"
#include <math.h>

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
	// glOrtho( 0, 50, 37.5, 0, -1, 1 );
	gluPerspective( 60, 800.0 / 600.0, 1.0, 1000.0 );
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

void SdlGlEnvironment::startDraw( Race* race )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	b2Body* carBody = race->getCar()->getBody();

	b2Vec2 carLoc = carBody->GetPosition();
	double angle = carBody->GetAngle();
	b2Vec2 velocity = carBody->GetLinearVelocity();
	double speed = 1; //  + sqrt( velocity.x * velocity.x + velocity.y * velocity.y );
	double cameraX = carLoc.x + sin( angle ) * 50 * speed;
	double cameraY = carLoc.y - cos( angle ) * 50 * speed;
	double cameraZ = -50 * speed;

	glLoadIdentity();
	gluLookAt( cameraX, cameraY, cameraZ, carLoc.x, carLoc.y, 0, 0, 0, -1 );

}

void SdlGlEnvironment::endDraw()
{
	SDL_GL_SwapBuffers();
}
