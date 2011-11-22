#include "core/Waypoint.h"
#include "Box2D.h"
#include <sstream>

Waypoint::Waypoint( b2Body* body, int index ) : body( body ), index( index )
{
	std::stringstream desc;
	desc << "Waypoint " << index;
	this->description = desc.str();
}

Waypoint::~Waypoint()
{


}
