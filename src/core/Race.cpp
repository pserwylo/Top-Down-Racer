/*
 * Race.cpp
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#include "core/Race.h"
#include "io/Input.h"
#include "io/TrackReader.h"
#include "env/Environment.h"
#include <sys/time.h>
#include <Box2D/Box2D.h>
#include <iostream>
#include <stdio.h>

#include "rendering/CarRenderer.h"
#include "rendering/TrackRenderer.h"

Race::Race()
{
	this->input = Environment::getEnvironment()->getInput();
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
	this->carRenderer = CarRenderer::create( this->car );
	this->trackRenderer = TrackRenderer::create( this->track );

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

	this->input->readInput();

	if ( this->input->isAccelarating() )
	{
		this->car->setThrottle( true );
	}
	else
	{
		this->car->setThrottle( false );
	}

	if ( this->input->isTurningLeft() || true )
	{
		this->car->setSteeringAngle( -Car::MAX_STEERING_ANGLE );
	}
	else if ( this->input->isTurningRight() )
	{
		this->car->setSteeringAngle( Car::MAX_STEERING_ANGLE );
	}
	else
	{
		this->car->setSteeringAngle( 0.0f );
	}

	if ( this->input->isShooting() )
	{
		for ( std::vector<Gun*>::iterator it = this->car->getGuns().begin(); it != this->car->getGuns().end(); it ++ )
		{
			(*it)->shoot();
		}
	}

	this->car->update();

	this->world->Step( 1.0f / 60.f, 10, 10 );
	return this->input->isQuitting();
}

void Race::draw()
{
	Environment::getEnvironment()->startDraw();
	this->carRenderer->render();
	this->trackRenderer->render();
	Environment::getEnvironment()->endDraw();
}
