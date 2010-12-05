/*
 * Track.h
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#ifndef TRACK_H_
#define TRACK_H_

#include <vector>

class b2PolygonShape;
class b2World;

class Track
{
public:
	Track( b2World* world );
	virtual ~Track();

public:
	std::vector<b2PolygonShape*> & getObstacles();
	std::vector<b2PolygonShape*> & getBorders();
	std::vector<b2PolygonShape*> & getWaypoints();

private:
	std::vector<b2PolygonShape*> obstacles;
	std::vector<b2PolygonShape*> borders;
	std::vector<b2PolygonShape*> waypoints;

};

#endif /* TRACK_H_ */
