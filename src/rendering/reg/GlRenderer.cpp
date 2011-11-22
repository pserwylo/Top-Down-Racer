/*
 * GlRenderer.cpp
 *
 *  Created on: 03/12/2010
 *      Author: pete
 */

#include <rendering/reg/GlRenderer.h>
#include "GL/gl.h"
#include "Box2D.h"

GlRenderer::GlRenderer()
{
}

GlRenderer::~GlRenderer()
{
}


void GlRenderer::renderBody( b2Body* body )
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


void GlRenderer::renderShape( b2Shape* shape )
{
	glBegin( GL_LINE_LOOP );
		if ( shape->GetType() == b2Shape::e_loop )
		{
			for ( int i = 0; i < ((b2LoopShape*)shape)->GetCount(); i ++ )
			{
				glVertex2d( ((b2LoopShape*)shape)->GetVertices()[ i ].x, ((b2LoopShape*)shape)->GetVertices()[ i ].y );
			}
		}
		else
		{
			for ( int i = 0; i < ((b2PolygonShape*)shape)->GetVertexCount(); i ++ )
			{
				glVertex2d( ((b2PolygonShape*)shape)->GetVertex( i ).x, ((b2PolygonShape*)shape)->GetVertex( i ).y );
			}
		}
	glEnd();
}

void GlRenderer::renderAxis()
{
	glLineWidth( 2 );
	glBegin( GL_LINES );

		// RED == X AXIS
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 10.0f, 0.0f, 0.0f );

		// GREEN == Y AXIS
		glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 10.0f, 0.0f );

		// BLUE == Z AXIS
		glColor3f( 0.0f, 0.0f, 1.0f );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 0.0f, 10.0f );

	glEnd();
	glColor3f( 1.0, 1.0f, 1.0f );
	glLineWidth( 1.0f );
}
