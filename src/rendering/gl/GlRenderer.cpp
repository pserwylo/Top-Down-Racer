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

void GlRenderer::renderShape( b2PolygonShape* shape )
{
	glBegin( GL_LINE_LOOP );
		for ( int i = 0; i < shape->m_vertexCount; i ++ )
		{
				glVertex2d( shape->m_vertices[ i ].x, shape->m_vertices[ i ].y );
		}
	glEnd();
}
