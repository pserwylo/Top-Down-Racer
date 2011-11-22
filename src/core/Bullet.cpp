#include "core/Bullet.h"
#include "core/Gun.h"
#include "Box2D.h"

Bullet::Bullet( b2World* world, Gun* gun ) : world( world ), gun( gun )
{

	b2BodyDef bulletDef;
	bulletDef.type = b2_dynamicBody;
	bulletDef.bullet = true;
	bulletDef.position = gun->getShootPosition();
	bulletDef.linearVelocity = gun->getShootVelocity();
	bulletDef.userData = this;

	this->body = world->CreateBody( &bulletDef );

	b2PolygonShape bulletShape;
	bulletShape.SetAsBox( 0.1f, 0.1f );
	this->body->CreateFixture( &bulletShape, 0.5f );

}

Bullet::~Bullet()
{
	this->world->DestroyBody( this->body );
}

void Bullet::update()
{
}

bool Bullet::collide( GameObject* object, b2Contact* contact )
{
	// Let the gun take care of removing this bullet...
	this->gun->bulletsToDelete.push_back( this );
	return true;
}
