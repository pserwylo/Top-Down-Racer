/*
 * Track.cpp
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#include "Track.h"
#include "Box2D.h"
#include "io/TrackReader.h"

Track::Track( b2World* world )
{
}

Track::~Track()
{
}

std::vector<b2Shape*> & Track::getObstacles()
{
	return this->obstacles;
}

std::vector<b2Shape*> & Track::getBorders()
{
	return this->borders;
}

std::vector<b2Shape*> & Track::getWaypoints()
{
	return this->waypoints;
}
