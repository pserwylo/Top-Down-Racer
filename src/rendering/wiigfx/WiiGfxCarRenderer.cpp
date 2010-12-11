#include "core/Car.h"
#include "rendering/wiigfx/WiiGfxCarRenderer.h"
#include "env/wii/WiiEnvironment.h"
#include "gccore.h"
#include <stdio.h>

WiiGfxCarRenderer::WiiGfxCarRenderer( Car* car ) : CarRenderer( car )
{
}

WiiGfxCarRenderer::~WiiGfxCarRenderer()
{
}

void WiiGfxCarRenderer::render()
{

	this->renderBody( this->car->carBody );
	this->renderBody( this->car->frontLeftWheel );
	this->renderBody( this->car->frontRightWheel );
	this->renderBody( this->car->backLeftWheel );
	this->renderBody( this->car->backRightWheel );

	for ( std::vector<Gun*>::iterator it = this->car->getGuns().begin(); it != this->car->getGuns().end(); it ++ )
	{
		this->renderBody( (*it)->getBody() );
		for ( std::vector<b2Body*>::iterator bIt = (*it)->getBullets().begin(); bIt != (*it)->getBullets().end(); bIt ++ )
		{
			this->renderBody( (*bIt) );
		}

		/*b2Vec2 shootPos = (*it)->getShootPosition();
		b2Vec2 endPos = shootPos + (*it)->getShootVelocity();

		glPointSize( 3 );
		glBegin( GL_POINTS );
			glVertex2d( shootPos.x, shootPos.y );
			glVertex2d( endPos.x, endPos.y );
		glEnd();*/
	};

}

void WiiGfxCarRenderer::renderBody( b2Body* body )
{
	Mtx view;
	( (WiiEnvironment*)Environment::getEnvironment() )->getView( view );
	Mtx modelview;

	Mtx rot;
	Mtx trans;

	guMtxIdentity( trans );

	guMtxTransApply( trans, trans, body->GetPosition().x, body->GetPosition().y, -6.0f );
	guMtxConcat( view, trans, modelview );

	guVector axis;
	axis.x = 0.0f;
	axis.y = 0;
	axis.z = 1.0f;
	guMtxRotAxisRad( rot, &axis, body->GetAngle() );
	guMtxConcat( modelview, rot, modelview );

	// load the modelview matrix into matrix memory
	GX_LoadPosMtxImm( modelview, GX_PNMTX0 );

	for ( b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext() )
	{
		this->renderShape( f->GetShape() );
	}

}
