/*
 * CarRenderer.cpp
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#include "core/Car.h"
#include "CarRenderer.h"
#include "GL/gl.h"

CarGlRenderer::CarGlRenderer( Car* car ) : car( car )
{
}

CarGlRenderer::~CarGlRenderer()
{
}

void CarGlRenderer::render()
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

		glPointSize( 3 );
		glBegin( GL_POINTS );
			glVertex2d( shootPos.x, shootPos.y );
			glVertex2d( endPos.x, endPos.y );
		glEnd();
	};

}

void CarGlRenderer::renderBody( b2Body* body )
{
	glColor3f( 1.0f, 1.0f, 1.0f );
	glPushMatrix();
		glTranslated( body->GetPosition().x, body->GetPosition().y, 0 );
		glRotated( body->GetAngle() * 180 / 3.14159, 0, 0, 1 );

		for ( b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext() )
		{
			this->renderShape( f->GetShape() );
		}
	glPopMatrix();
}
