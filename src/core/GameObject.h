#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class b2Body;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void update() {};
	virtual b2Body* getBody() = 0;
};

#endif /* GAMEOBJECT_H_ */
