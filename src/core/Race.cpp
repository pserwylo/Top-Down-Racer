#include "core/Race.h"
#include "io/userinput/Input.h"
#include "io/trackreader/TrackReader.h"
#include "env/Environment.h"

#include <sys/time.h>
#include <ctime>
#include <Box2D/Box2D.h>
#include <iostream>
#include <stdio.h>

#include "rendering/CarRenderer.h"
#include "rendering/TrackRenderer.h"

double myDifftime( timeval& start, timeval& end )
{
	unsigned long int diff = ( end.tv_sec * 1000000 + end.tv_usec ) - ( start.tv_sec * 1000000 + start.tv_usec );
	return (double)diff / 1000000;
}

Race::Race() : state( STATE_WAITING )
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
	return (long int)( ( (long double)( clock() ) / CLOCKS_PER_SEC ) * 1000 );
}

void Race::runRace()
{
	timeval lastUpdateTime;
	gettimeofday( &lastUpdateTime, NULL );

	bool done = false;
	this->carRenderer = CarRenderer::create( this->car );
	this->trackRenderer = TrackRenderer::create( this->track );

	do
	{
		timeval currentUpdateTime;
		gettimeofday( &currentUpdateTime, NULL );
		time_t test;
		double timeDiff = myDifftime( lastUpdateTime, currentUpdateTime );
		// std::cout << "Time since update: " << timeDiff << std::endl;
		if ( timeDiff > 1.0f / 25 )
		{
			done = this->update( timeDiff );
			lastUpdateTime = currentUpdateTime;
			this->draw();
		}

	} while ( !done );
}

bool Race::update( double timeDiff )
{
	bool finished = false;
	switch( this->state )
	{
		case STATE_WAITING:
			// Maybe a flyover of the track, or some other stuff, but before we begin the countdown.
			// if ( time() - enteredStateTime > Config::getRaceIntroDuration() )
			{
				this->state = Race::STATE_STARTING;
				std::cout << "State Change: Waiting -> Starting" << std::endl;
			}
		break;
		
		case STATE_STARTING:
			// Counting down, or showing the colourful lights in a countdown fasion. 
			// Either way, its pretty much "ready, set, go!"
			// if ( !this->updateCountdown() )
			{
				// If updateCountdown() returend false then we have finished and are go for racing.
				this->state = Race::STATE_RACING;
				std::cout << "State Change: Starting -> Racing" << std::endl;
			}
		break;
		
		case STATE_RACING:
			// The main deal.
			// Keep track of cars, check their progress, let the user drive them, and wait for
			// them to finish.
			this->updateRace( timeDiff );
			if ( false ) // we are finished
			{
				this->state = Race::STATE_FINISHED_WAITING;
				std::cout << "State Change: Racing -> Finished-waiting" << std::endl;
			}
		break;
		
		case STATE_FINISHED_WAITING:
			// If one car has finished, then we can either wait for a timeout before bailing, or wait
			// for all racers to finish. You'd probably want to wait for the second last racer to come
			// home, like in mario kart, or else you may be waiting ages...
			this->state = Race::STATE_FINISHED;
			std::cout << "State Change: Finished -> Finished" << std::endl;
		break;
		
		case STATE_FINISHED:
		default:
			// Wait for a few seconds, then return false to break out of the loop and finish the race.
			// if ( time() - enteredStateTime > Config::getFinishedHangTime()
			{
				finished = true;
			}
			break;
	}
	return finished;
}

bool Race::updateRace( double timeSinceUpdate )
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

	this->car->setSteeringAngle( Car::MAX_STEERING_ANGLE * this->input->getSteeringAngle() );

	if ( this->input->isShooting() )
	{
		for ( std::vector<Gun*>::iterator it = this->car->getGuns().begin(); it != this->car->getGuns().end(); it ++ )
		{
			(*it)->shoot();
		}
	}

	this->car->update();

#ifdef WII
	this->world->Step( 1.0f / 5.0f, 5, 5);
#else
	this->world->Step( timeSinceUpdate, 10, 10 );
#endif

	return this->input->isQuitting();
}

void Race::draw()
{
	Environment::getEnvironment()->startDraw( this );
	this->carRenderer->render();
	this->trackRenderer->render();
	Environment::getEnvironment()->endDraw();
}
