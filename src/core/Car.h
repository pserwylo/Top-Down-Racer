/*
 * Car.h
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#ifndef CAR_H_
#define CAR_H_

#include "Box2D.h"
#include "rendering/gl/CarRenderer.h"
#include "rendering/sdl/CarRenderer.h"

class Car
{

	friend class CarGlRenderer;
	friend class CarSdlRenderer;

public:
	Car( b2World* world );
	virtual ~Car();

	void setThrottle( bool apply );
	void setSteeringAngle( float angle );
	void update();

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

	void createGeometry( b2World* world, float width, float height );
	void killOrthogonalVelocity( b2Body* targetBody );

};

#endif /* CAR_H_ */
