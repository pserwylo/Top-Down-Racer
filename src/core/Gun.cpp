#include <core/Gun.h>
#include <core/Car.h>

Gun::Gun( b2World* world, Car* car, b2Vec2 offset ) : car ( car )
{

	b2BodyDef gunDef;
	gunDef.type = b2_dynamicBody;
	gunDef.position = this->car->carBody->GetPosition() + offset;
	this->gunBody = world->CreateBody( &gunDef );

	b2PolygonShape gunShape;
	gunShape.SetAsBox( 0.1, 0.4 );
	b2Fixture* gunFixture = this->gunBody->CreateFixture( &gunShape, 1.0f );
	b2Filter gunFilter;
	gunFilter.groupIndex = -1;
	gunFixture->SetFilterData( gunFilter );

	b2PrismaticJointDef gunJointDef;
	gunJointDef.Initialize( this->car->carBody, this->gunBody, this->gunBody->GetWorldCenter(), b2Vec2( 1, 0 ) );
	gunJointDef.enableLimit = true;
	gunJointDef.lowerTranslation = gunJointDef.upperTranslation = 0;
	world->CreateJoint( &gunJointDef );

}

Gun::~Gun()
{

}

void Gun::shoot()
{
	// if ( timeSinceLastShoot < TIME_BETWEEN_FIRING )
	// {



	// }
}

b2Body* Gun::getBody()
{
	return this->gunBody;
}
