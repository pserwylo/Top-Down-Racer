#include "Track.h"
#include "Car.h"
#include "Box2D.h"
#include "core/Waypoint.h"
#include "io/trackreader/TrackReader.h"
#include <iostream>

Track::Track( b2World* world )
{
	world->SetContactListener( this );
}

Track::~Track()
{
}

bool Track::collide( GameObject* object, b2Contact* contact )
{
	return true;
}

/**
 * Items which should collide are cars and way-points.
 * We are also interested in cars and obstacles, as they should slow down at some point.
 * Because the car is the critical one, we will always ask for that first, and then we can
 * bother iterating through the other possibilities.
 */
void Track::BeginContact( b2Contact* contact )
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	GameObject* dataA = (GameObject*)( fixA->GetBody()->GetUserData() );
	GameObject* dataB = (GameObject*)( fixB->GetBody()->GetUserData() );

	dataA->collide( dataB, contact );
	dataB->collide( dataA, contact );
}

std::vector<b2Shape*> & Track::getHazards()
{
	return this->hazards;
}

std::vector<b2Shape*> & Track::getBorders()
{
	return this->borders;
}

std::vector<Waypoint*> & Track::getWaypoints()
{
	return this->waypoints;
}
