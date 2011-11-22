/*
 * Car.cpp
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#include "Car.h"
#include "Gun.h"
#include "Waypoint.h"
#include "Box2D.h"
#include <cmath>
#include <iostream>

const float Car::MAX_STEERING_ANGLE;

Car::Car( b2World* world ) :
	isThrottleApplied( false ),
	steeringWheelAngle( 0.0f )
{
	this->createGeometry( world, 2, 4 );
}

void Car::createGeometry( b2World* world, float width, float height )
{
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;


	// Create bodies for the car and each of its wheels...

	b2BodyDef carBodyDef;
	carBodyDef.type = b2_dynamicBody;
	carBodyDef.angularDamping = 1;
	carBodyDef.linearDamping = 1;
	carBodyDef.userData = this;
	this->carBody = world->CreateBody( &carBodyDef );

	b2BodyDef frontLeftWheelDef;
	frontLeftWheelDef.type = b2_dynamicBody;
	frontLeftWheelDef.position = this->carBody->GetPosition();
	frontLeftWheelDef.position += b2Vec2( - halfWidth, halfHeight - 0.1f );
	this->frontLeftWheel = world->CreateBody( &frontLeftWheelDef );

	b2BodyDef frontRightWheelDef;
	frontRightWheelDef.type = b2_dynamicBody;
	frontRightWheelDef.position = this->carBody->GetPosition();
	frontRightWheelDef.position += b2Vec2( halfWidth, halfHeight - 0.1f );
	this->frontRightWheel = world->CreateBody( &frontRightWheelDef );

	b2BodyDef backLeftWheelDef;
	backLeftWheelDef.type = b2_dynamicBody;
	backLeftWheelDef.position = this->carBody->GetPosition();
	backLeftWheelDef.position += b2Vec2( - halfWidth, - halfHeight + 0.1f );
	this->backLeftWheel = world->CreateBody( &backLeftWheelDef );

	b2BodyDef backRightWheelDef;
	backRightWheelDef.type = b2_dynamicBody;
	backRightWheelDef.position = this->carBody->GetPosition();
	backRightWheelDef.position += b2Vec2( halfWidth, - halfHeight + 0.1f );
	this->backRightWheel = world->CreateBody( &backRightWheelDef );


	// Define and create geometry for each body...

	b2PolygonShape carBodyShape;
	carBodyShape.SetAsBox( width / 2, height / 2 );
	this->carBody->CreateFixture( &carBodyShape, 1.0f );

	// Give a negative index so that the wheels never collide with anything...
	// TODO: Maybe could make this better, so that when wheels collide with something, if it is
	// at sufficient pace, then it could knock them out of alignment and you couldn't steer properly...
	// Sounds like a Box2D "sensor" is the tool for this job..
	b2Filter wheelFilter;
	wheelFilter.groupIndex = -1;

	b2PolygonShape frontLeftWheelShape;
	frontLeftWheelShape.SetAsBox( 0.2, 0.5 );
	b2Fixture* frontLeftWheelFixture = this->frontLeftWheel->CreateFixture( &frontLeftWheelShape, 1.0f );
	frontLeftWheelFixture->SetFilterData( wheelFilter );

	b2PolygonShape frontRightWheelShape;
	frontRightWheelShape.SetAsBox( 0.2, 0.5 );
	b2Fixture* frontRightWheelFixture = this->frontRightWheel->CreateFixture( &frontRightWheelShape, 1.0f );
	frontRightWheelFixture->SetFilterData( wheelFilter );

	b2PolygonShape backLeftWheelShape;
	backLeftWheelShape.SetAsBox( 0.2, 0.5 );
	b2Fixture* backLeftWheelFixture = this->backLeftWheel->CreateFixture( &backLeftWheelShape, 1.0f );
	backLeftWheelFixture->SetFilterData( wheelFilter );

	b2PolygonShape backRightWheelShape;
	backRightWheelShape.SetAsBox( 0.2, 0.5 );
	b2Fixture* backRightWheelFixture = this->backRightWheel->CreateFixture( &backRightWheelShape, 1.0f );
	backRightWheelFixture->SetFilterData( wheelFilter );


	// Connect wheels to car...

	b2RevoluteJointDef frontLeftJointDef;
	frontLeftJointDef.Initialize( this->carBody, this->frontLeftWheel, this->frontLeftWheel->GetWorldCenter() );
	frontLeftJointDef.enableMotor = true;
	frontLeftJointDef.maxMotorTorque = 100;

	b2RevoluteJointDef frontRightJointDef;
	frontRightJointDef.Initialize( this->carBody, this->frontRightWheel, this->frontRightWheel->GetWorldCenter() );
	frontRightJointDef.enableMotor = true;
	frontRightJointDef.maxMotorTorque = 100;


	b2PrismaticJointDef backLeftJointDef;
	backLeftJointDef.Initialize( this->carBody, this->backLeftWheel, this->backLeftWheel->GetWorldCenter(), b2Vec2( 1, 0 ) );
	backLeftJointDef.enableLimit = true;
	backLeftJointDef.lowerTranslation = backLeftJointDef.upperTranslation = 0;

	b2PrismaticJointDef backRightJointDef;
	backRightJointDef.Initialize( this->carBody, this->backRightWheel, this->backRightWheel->GetWorldCenter(), b2Vec2( 1,0 ) );
	backRightJointDef.enableLimit = true;
	backRightJointDef.lowerTranslation = backRightJointDef.upperTranslation = 0;

	this->frontLeftJoint = (b2RevoluteJoint*) world->CreateJoint( &frontLeftJointDef );
	this->frontRightJoint = (b2RevoluteJoint*) world->CreateJoint( &frontRightJointDef );
	world->CreateJoint( &backLeftJointDef );
	world->CreateJoint( &backRightJointDef );

	Gun* gun = new Gun( world, this, b2Vec2( 0.0f, 0.5f ) );
	this->guns.push_back( gun );
}

Car::~Car()
{
}

void Car::setThrottle( bool apply )
{
	this->isThrottleApplied = apply;
}

void Car::setSteeringAngle( float angle )
{
	if ( angle < -Car::MAX_STEERING_ANGLE )
	{
		angle = -Car::MAX_STEERING_ANGLE;
	}
	else if ( angle > Car::MAX_STEERING_ANGLE )
	{
		angle = Car::MAX_STEERING_ANGLE;
	}
	this->steeringWheelAngle = angle;
}

void Car::setLocation( b2Vec2 loc )
{
	this->carBody->SetTransform( loc, 0.0f );
}

std::vector<Gun*>& Car::getGuns()
{
	return this->guns;
}

bool Car::collide( GameObject* object, b2Contact* contact )
{
	if ( object->getType() == Waypoint::ID_WAYPOINT )
	{
		std::cout << "Hit " << object->toString() << std::endl;
	}

	return true;
}

void Car::update()
{

	float engineSpeed = this->isThrottleApplied ? 16.0f : 0.0f;
	b2Vec2 direction;
	float steeringSpeed;

	killOrthogonalVelocity( this->frontLeftWheel );
	killOrthogonalVelocity( this->frontRightWheel );
	killOrthogonalVelocity( this->backLeftWheel );
	killOrthogonalVelocity( this->backRightWheel );


	//Driving

	direction = this->frontLeftWheel->GetTransform().R.col2;
	direction *= engineSpeed;
	this->frontLeftWheel->ApplyForce( direction, this->frontLeftWheel->GetPosition() );

	direction = this->frontRightWheel->GetTransform().R.col2;
	direction *= engineSpeed;
	this->frontRightWheel->ApplyForce( direction, this->frontRightWheel->GetPosition() );


	//Steering

	steeringSpeed = this->steeringWheelAngle - this->frontLeftJoint->GetJointAngle();
	this->frontLeftJoint->SetMotorSpeed( steeringSpeed );
	// steeringSpeed = this->steeringWheelAngle - this->frontRightJoint->GetJointAngle();
	this->frontRightJoint->SetMotorSpeed( steeringSpeed );

	for ( std::vector<Gun*>::iterator it = this->guns.begin(); it != this->guns.end(); it ++ )
	{
		(*it)->update();
	}

}


//This function applies a "friction" in a direction orthogonal to the body's axis.
void Car::killOrthogonalVelocity( b2Body* targetBody )
{
	b2Vec2 localPoint(0,0);
	b2Vec2 velocity;
	velocity = targetBody->GetLinearVelocityFromLocalPoint( localPoint );

	b2Vec2 sidewaysAxis;
	sidewaysAxis = targetBody->GetTransform().R.col2;
	sidewaysAxis *= b2Dot( velocity, sidewaysAxis );

	targetBody->SetLinearVelocity( sidewaysAxis );//targetBody.GetWorldPoint(localPoint));
}


