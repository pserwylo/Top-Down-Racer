#ifndef GUN_H_
#define GUN_H_

#include "Box2D.h"
#include "core/GameObject.h"
#include <vector>

class Car;

class Gun : public GameObject, public b2ContactListener
{
public:
	Gun( b2World* world, Car* car, b2Vec2 offset );
	virtual ~Gun();

	void shoot();

	// GameObject functions...
	virtual b2Body* getBody();
	virtual void update();

	std::vector<b2Body*>& getBullets();
	b2Vec2 getShootVelocity();
	b2Vec2 getShootPosition();

	// Contact listener functions...
	void BeginContact( b2Contact* contact );

private:
	b2Body* gunBody;

	// Keep reference to world so that we can create bullets and add them to the simulation...
	b2World* world;
	Car* car;

	bool hasShot;

	std::vector<b2Body*> bullets;
	std::vector<b2Body*> bulletsToDelete;

};

#endif /* GUN_H_ */
