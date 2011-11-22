#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class b2Body;
class b2Contact;

#include <string>

/**
 * Game objects are things which have a physical presence in the game,
 * objects which are either rendered, have physics applied, or both.
 */
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void update() {};
	virtual b2Body* getBody() = 0;
	virtual std::string toString() = 0;
	virtual unsigned int getType() = 0;

	virtual bool collide( GameObject* object, b2Contact* contact ) { return true; };
};

#endif /* GAMEOBJECT_H_ */
