#ifndef GUN_H_
#define GUN_H_

#include "Box2D.h"
#include "core/GameObject.h"
#include <vector>

class Car;
class Bullet;

/**
 * Guns generally belong to cars, but perhaps down the track we can have turrets in the game which track cars.
 * Calling the shoot button will create a bullet which has is represented by a b2Body.
 * When a gun is rendered, so are all of its bullets.
 * Likewise, a gun is also responsible for listening for collisions of its bullets, and removing them if neccesary.
 */
class Gun : public GameObject
{

	friend class Bullet;

public:
	Gun( b2World* world, Car* car, b2Vec2 offset );
	virtual ~Gun();

	static const int ID_GUN = 527229;

	unsigned int getType() { return ID_GUN; }

	void shoot();

	// GameObject functions...
	virtual b2Body* getBody();
	virtual std::string toString() { return "Gun"; }
	virtual void update();
	virtual bool collide( GameObject* object, b2Contact* contact );

	std::vector<Bullet*>& getBullets();
	b2Vec2 getShootVelocity();
	b2Vec2 getShootPosition();

protected:
	b2Body* gunBody;

	// Keep reference to world so that we can create bullets and add them to the simulation...
	b2World* world;
	Car* car;

	// In order to stop a gun from firing as fast as the game loop ticks over, we need to keep track
	// of when we last fired, and when we can fire again. Each gun type will have different characteristics.
	bool hasShot;

	std::vector<Bullet*> bullets;

	// I don't remember why I had to defer the destruction of the bullets, but it had to happen in the update 
	// function, not the collision callback.
	std::vector<Bullet*> bulletsToDelete;

};

#endif /* GUN_H_ */
