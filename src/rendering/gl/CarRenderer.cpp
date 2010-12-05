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

	b2Body* bodiesToDraw[] = { this->car->carBody, this->car->frontLeftWheel, this->car->frontRightWheel, this->car->backLeftWheel, this->car->backRightWheel };
	glColor3f( 1.0f, 1.0f, 1.0f );
	for ( int i = 0; i < 5; i ++ )
	{
		b2Body* body = bodiesToDraw[ i ];
		glPushMatrix();
			glTranslated( body->GetPosition().x, body->GetPosition().y, 0 );
			glRotated( body->GetAngle() * 180 / 3.14159, 0, 0, 1 );

			for ( b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext() )
			{
				this->renderShape( (b2PolygonShape*)f->GetShape() );
			}
		glPopMatrix();
	}
}
