/*
 * GlRenderer.cpp
 *
 *  Created on: 03/12/2010
 *      Author: pete
 */

#include <rendering/gl/GlRenderer.h>
#include "GL/gl.h"

GlRenderer::GlRenderer()
{
}

GlRenderer::~GlRenderer()
{
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
