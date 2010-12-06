#ifndef GUN_H_
#define GUN_H_

#include "Box2D.h"
#include "core/GameObject.h"

class Car;

class Gun : public GameObject
{
public:
	Gun( b2World* world, Car* car, b2Vec2 offset );
	virtual ~Gun();

	void shoot();
	virtual b2Body* getBody();

private:
	Car* car;
	b2Body* gunBody;

};

#endif /* GUN_H_ */
