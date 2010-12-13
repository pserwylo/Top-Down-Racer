#include "Track.h"
#include "Box2D.h"
#include "io/trackreader/TrackReader.h"

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
