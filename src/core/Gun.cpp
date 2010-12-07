#include "core/Gun.h"
#include "core/Car.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Gun::Gun( b2World* world, Car* car, b2Vec2 offset ) : world( world ), car ( car ), hasShot( false )
{

	world->SetContactListener( this );

	b2BodyDef gunDef;
	gunDef.type = b2_dynamicBody;
	gunDef.position = this->car->carBody->GetPosition() + offset;
	this->gunBody = world->CreateBody( &gunDef );

	b2PolygonShape gunShape;
	gunShape.SetAsBox( 0.1, 3.0f );
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

b2Vec2 Gun::getShootPosition()
{
	b2Vec2 direction;
	direction.Set( 1.0f, 0.0f );
	direction.x = -sin( this->gunBody->GetAngle() );
	direction.y = cos( this->gunBody->GetAngle() );
	direction *= 3;

	return this->gunBody->GetPosition() + direction;
}

b2Vec2 Gun::getShootVelocity()
{
	b2Vec2 direction;
	direction.Set( 0, 1 );
	direction.x = -sin( this->gunBody->GetAngle() );
	direction.y = cos( this->gunBody->GetAngle() );
	direction *= 0.2;
	return direction;
}

void Gun::shoot()
{
	if ( true || !hasShot )
	{
		hasShot = true;
		// if ( timeSinceLastShoot < TIME_BETWEEN_FIRING )
		// {


		b2BodyDef bulletDef;
		bulletDef.type = b2_dynamicBody;
		bulletDef.bullet = true;
		bulletDef.position = this->getShootPosition();
		bulletDef.linearVelocity = this->getShootVelocity();

		b2Body* bulletBody = world->CreateBody( &bulletDef );

		b2PolygonShape bulletShape;
		bulletShape.SetAsBox( 0.1f, 0.1f );
		bulletBody->CreateFixture( &bulletShape, 0.5f );

		this->bullets.push_back( bulletBody );

		// }
	}
}

void Gun::BeginContact( b2Contact* contact )
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	if ( bodyA != this->gunBody && bodyB != this->gunBody )
	{
		for ( std::vector<b2Body*>::iterator it = this->bullets.begin(); it != this->bullets.end(); it ++ )
		{
			if ( *it == bodyA )
			{
				std::cout << "Hit A" << std::endl;
				this->bulletsToDelete.push_back( bodyA );
				this->bullets.erase( it );
				break;
			}
			else if ( *it == bodyB )
			{
				std::cout << "Hit B" << std::endl;
				this->bulletsToDelete.push_back( bodyB );
				this->bullets.erase( it );
				break;
			}
		}
	}
}

void Gun::update()
{
	if ( this->bulletsToDelete.size() > 0 )
	{
		std::cout << "Updating gun, removing " << this->bulletsToDelete.size() << " bullets..." << std::endl;
		for ( std::vector<b2Body*>::iterator it = this->bulletsToDelete.begin(); it != this->bulletsToDelete.end(); it ++ )
		{
			this->world->DestroyBody( *it );
		}
		this->bulletsToDelete.erase( this->bulletsToDelete.begin(), this->bulletsToDelete.end() );
	}
}

b2Body* Gun::getBody()
{
	return this->gunBody;
}

std::vector<b2Body*>& Gun::getBullets()
{
	return this->bullets;
}
