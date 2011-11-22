#include "core/Gun.h"
#include "core/Car.h"
#include "core/Track.h"
#include "core/Bullet.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Gun::Gun( b2World* world, Car* car, b2Vec2 offset ) : world( world ), car ( car ), hasShot( false )
{

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

bool Gun::collide( GameObject* object, b2Contact* contact )
{
	if ( object->getType() == Track::TYPE_TRACK )
	{
		// Remove...
	}
	return true;
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
	direction *= 5;
	return direction;
}

void Gun::shoot()
{
	if ( true || !hasShot )
	{
		hasShot = true;
		// if ( timeSinceLastShoot < TIME_BETWEEN_FIRING )
		// {

		Bullet* bullet = new Bullet( this->world, this );
		this->bullets.push_back( bullet );

		// }
	}
}

void Gun::update()
{
	if ( this->bulletsToDelete.size() > 0 )
	{
		for ( std::vector<Bullet*>::iterator it = this->bulletsToDelete.begin(); it != this->bulletsToDelete.end(); it ++ )
		{
			std::vector<Bullet*>::iterator found = std::find( this->bullets.begin(), this->bullets.end(), *it );

			if ( found != this->bullets.end() )
			{
				this->bullets.erase( found );
			}
			delete *it;
		}
		this->bulletsToDelete.erase( this->bulletsToDelete.begin(), this->bulletsToDelete.end() );
	}
}

b2Body* Gun::getBody()
{
	return this->gunBody;
}

std::vector<Bullet*>& Gun::getBullets()
{
	return this->bullets;
}
