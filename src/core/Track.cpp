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
	new TrackReader( "/home/pete/code/TDR/data/tracks/test/test.svg" );
	b2Vec2* borderPoints = new b2Vec2[ 5 ];
	borderPoints[ 0 ] = b2Vec2( 10, 10 );
	borderPoints[ 1 ] = b2Vec2( 15, 10 );
	borderPoints[ 2 ] = b2Vec2( 16, 12 );
	borderPoints[ 3 ] = b2Vec2( 16, 15 );
	borderPoints[ 4 ] = b2Vec2( 13, 12 );
	b2PolygonShape* border = new b2PolygonShape();
	border->Set( borderPoints, 5 );

	this->borders.push_back( border );
}

Track::~Track()
{
}

std::vector<b2PolygonShape*> & Track::getObstacles()
{
	return this->obstacles;
}

std::vector<b2PolygonShape*> & Track::getBorders()
{
	return this->borders;
}

std::vector<b2PolygonShape*> & Track::getWaypoints()
{
	return this->waypoints;
}
