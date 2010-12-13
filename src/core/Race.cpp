#include "core/Race.h"
#include "io/userinput/Input.h"
#include "io/trackreader/TrackReader.h"
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
	TrackReader* reader = TrackReader::create( this->world, "test", 10 );
	this->track = reader->getTrack();

	// TODO: Do I need to return a pointer and then delete it? Or can I return a reference to the object which will
	// get removed when the 'reader' var goes out of scope at the end of the constructor? I imagine that if I returned
	// a copy of the object, than it would do what I desire, except it would go to the effort to copy the entire object...
	delete reader;
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

	if ( this->input->isTurningLeft() )
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

#ifdef WII
	this->world->Step( 1.0f / 10.0f, 5, 5);
#else
	this->world->Step( 1.0f / 60.0f, 10, 10 );
#endif

	return this->input->isQuitting();
}

void Race::draw()
{
	Environment::getEnvironment()->startDraw();
	this->carRenderer->render();
	this->trackRenderer->render();
	Environment::getEnvironment()->endDraw();
}
