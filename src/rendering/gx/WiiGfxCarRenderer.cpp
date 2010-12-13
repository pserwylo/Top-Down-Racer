#include "core/Car.h"
#include "rendering/gx/WiiGfxCarRenderer.h"
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

		b2Vec2 shootPos = (*it)->getShootPosition();
		b2Vec2 endPos = shootPos + (*it)->getShootVelocity();

		// Revert to the default modelview matrix...
		Mtx view;
		Mtx model;
		Mtx modelview;
		( (WiiEnvironment*)Environment::getEnvironment() )->getView( view );
		guMtxIdentity( model );
		guMtxConcat( view, model, modelview );

		GX_LoadPosMtxImm( modelview, GX_PNMTX0 );
		GX_Begin( GX_POINTS, GX_VTXFMT0, 2 );
			GX_Position3f32( shootPos.x, shootPos.y, 0 );
			GX_Color3f32( 1.0f, 1.0f, 1.0f );
			GX_Position3f32( endPos.x, endPos.y, 0 );
			GX_Color3f32( 1.0f, 1.0f, 1.0f );
		GX_End();
	};

}

void WiiGfxCarRenderer::renderBody( b2Body* body )
{
	Mtx view;
	Mtx modelview;

	Mtx rot;
	Mtx trans;

	( (WiiEnvironment*)Environment::getEnvironment() )->getView( view );
	guMtxIdentity( trans );

	guMtxTransApply( trans, trans, body->GetPosition().x, body->GetPosition().y, 0.0f );
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
