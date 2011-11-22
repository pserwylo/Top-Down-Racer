#ifndef TRACK_H_
#define TRACK_H_

#include <vector>
#include "io/trackreader/TrackReader.h"
#include "core/GameObject.h"
#include "Box2D.h"

class Waypoint;

class Track : public GameObject, public b2ContactListener
{

	friend class TrackReader;

public:
	Track( b2World* world );
	virtual ~Track();

public:
	std::vector<b2Shape*> & getHazards();
	std::vector<b2Shape*> & getBorders();
	std::vector<Waypoint*> & getWaypoints();

	// Contact listener functions...
	void BeginContact( b2Contact* contact );

	// GameObject functions...
	virtual void update() {};
	virtual bool collide( GameObject* object, b2Contact* contact );
	virtual unsigned int getType() { return TYPE_TRACK; }
	virtual b2Body* getBody() { return NULL; };
	virtual std::string toString() { return "Track"; };

public:
	static const unsigned int TYPE_TRACK = 823985294;

private:
	std::vector<b2Shape*> hazards;
	std::vector<b2Shape*> borders;
	std::vector<Waypoint*> waypoints;

};

#endif /* TRACK_H_ */
