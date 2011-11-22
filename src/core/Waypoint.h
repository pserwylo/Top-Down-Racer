#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include "core/GameObject.h"

class b2Body;

class Waypoint : public GameObject
{

public:
	Waypoint( b2Body* body, int index );
	virtual ~Waypoint();

	static const unsigned int ID_WAYPOINT = 9847529;

	unsigned int getType() { return ID_WAYPOINT; }

	virtual b2Body* getBody() { return this->body; }
	virtual std::string toString() { return this->description; }

protected:
	b2Body* body;
	int index;
	std::string description;

};

#endif /* WAYPOINT_H_ */
