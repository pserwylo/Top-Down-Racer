/*
 * Bullet.h
 *
 *  Created on: Apr 17, 2011
 *      Author: pete
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "GameObject.h"

class b2Body;
class b2World;
class b2Contact;
class Gun;

class Bullet : public GameObject
{

public:
	static const unsigned int ID_BULLET = 816513;

public:
	Bullet( b2World* world, Gun* gun );
	virtual ~Bullet();

	virtual b2Body* getBody() { return this->body; };
	virtual std::string toString() { return "Bullet"; };
	virtual unsigned int getType() { return Bullet::ID_BULLET; };

	virtual void update();
	virtual bool collide( GameObject* object, b2Contact* contact );

protected:
	b2World* world;
	b2Body* body;
	Gun* gun;
};

#endif /* BULLET_H_ */
