#ifndef TRACK_H_
#define TRACK_H_

#include <vector>
#include "io/trackreader/TrackReader.h"

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
