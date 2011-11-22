#ifndef CAR_H_
#define CAR_H_

#include <vector>
#include "Box2D.h"
#include "Gun.h"
#include "GameObject.h"

#ifdef WII
#include "rendering/gx/WiiGfxCarRenderer.h"
#else
#include "rendering/reg/RegCarRenderer.h"
#endif

/**
 * The car is controlled by the user through the setSteeringAngle() and the setThrottle() methods.
 * It also has a collection of guns which belong to it, available via the getGuns() method.
 * Cars can have multiple guns because the user decides where to put them and how many to have.
 */
class Car : public GameObject
{

#ifdef WII
	friend class WiiGfxCarRenderer;
#else
	friend class RegCarRenderer;
#endif

	friend class Gun;

public:
	Car( b2World* world );
	virtual ~Car();

	static const unsigned int ID_CAR = 239820;

	unsigned int getType() { return ID_CAR; }

	void setThrottle( bool apply );
	void setSteeringAngle( float angle );
	void update();
	void setLocation( b2Vec2 loc );
	std::vector<Gun*>& getGuns();
	virtual b2Body* getBody() { return this->carBody; }
	virtual bool collide( GameObject* object, b2Contact* contact );
	virtual std::string toString() { return "Car"; }

public:
	const static float MAX_STEERING_ANGLE = 0.5f;

protected:
	b2Body* carBody;
	b2PolygonShape* carBodyShape;
	b2Body* frontLeftWheel;
	b2Body* frontRightWheel;
	b2Body* backLeftWheel;
	b2Body* backRightWheel;
	b2RevoluteJoint* frontLeftJoint;
	b2RevoluteJoint* frontRightJoint;
	bool isThrottleApplied;
	float steeringWheelAngle;
	std::vector<Gun*> guns;

	void createGeometry( b2World* world, float width, float height );
	void killOrthogonalVelocity( b2Body* targetBody );

};

#endif /* CAR_H_ */
