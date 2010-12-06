/*
 * Track.h
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#ifndef TRACK_H_
#define TRACK_H_

#include <vector>
#include "io/TrackReader.h"

class b2Shape;
class b2World;

class Track
{

	friend class TrackReader;

public:
	Track( b2World* world );
	virtual ~Track();

public:
	std::vector<b2Shape*> & getObstacles();
	std::vector<b2Shape*> & getBorders();
	std::vector<b2Shape*> & getWaypoints();

private:
	std::vector<b2Shape*> obstacles;
	std::vector<b2Shape*> borders;
	std::vector<b2Shape*> waypoints;

};

#endif /* TRACK_H_ */
