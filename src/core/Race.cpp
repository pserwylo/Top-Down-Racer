/*
 * Race.cpp
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#include "Race.h"
#include "global.h"
#include "io/TrackReader.h"
#include "rendering/gl/CarRenderer.h"
#include "rendering/gl/TrackRenderer.h"
#include <sys/time.h>
#include <GL/gl.h>
#include <Box2D.h>
#include <iostream>

Race::Race()
{

	this->world = new b2World( b2Vec2( 0.0f, 0.0f ), true );
	this->car = new Car( this->world );
	TrackReader reader( this->world, "/home/pete/code/TDR/data/tracks/test/test.svg", 10 );
	this->track = reader.getTrack();
}

Race::~Race()
{

}

long int Race::getMilliseconds()
{
	/*timeval* time;
	timezone* test;
	gettimeofday( time, test );
	return time->tv_usec / 1000;*/
	return 10;
}

void Race::runRace()
{
	long int lastUpdateTime = this->getMilliseconds();
	bool done = false;
	this->carRenderer = new CarGlRenderer( this->car );
	this->trackRenderer = new TrackGlRenderer( this->track );

	do
	{
		long int currentUpdateTime = this->getMilliseconds();
		int timeDiff = currentUpdateTime - lastUpdateTime;

		done = this->update( timeDiff );
		this->draw();

	} while ( !done );
}

bool Race::update( int timeDiff )
{
	this->input.readInput();

	if ( this->input.isAccelarating() )
	{
		this->car->setThrottle( true );
	}
	else
	{
		this->car->setThrottle( false );
	}

	if ( this->input.isTurningLeft() )
	{
		this->car->setSteeringAngle( -Car::MAX_STEERING_ANGLE );
	}
	else if ( this->input.isTurningRight() )
	{
		this->car->setSteeringAngle( Car::MAX_STEERING_ANGLE );
	}
	else
	{
		this->car->setSteeringAngle( 0.0f );
	}

	if ( this->input.isShooting() )
	{
		for ( std::vector<Gun*>::iterator it = this->car->getGuns().begin(); it != this->car->getGuns().end(); it ++ )
		{
			(*it)->shoot();
		}
	}

	this->car->update();

	this->world->Step( 1.0f / 60.f, 10, 10 );
	return this->input.isQuitting();
}

void Race::draw()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	this->carRenderer->render();
	this->trackRenderer->render();
	SDL_GL_SwapBuffers();
}
