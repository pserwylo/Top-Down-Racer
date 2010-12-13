#include "rendering/gx/WiiGfxRenderer.h"
#include "Box2D/Box2D.h"

WiiGfxRenderer::WiiGfxRenderer()
{
}

WiiGfxRenderer::~WiiGfxRenderer()
{
}

void WiiGfxRenderer::renderShape( b2Shape* shape )
{

	if ( shape->GetType() == b2Shape::e_loop )
	{
		GX_Begin( GX_LINESTRIP, GX_VTXFMT0, ((b2LoopShape*)shape)->GetCount() + 1 );
			for ( int i = 0; i < ((b2LoopShape*)shape)->GetCount() + 1; i ++ )
			{
				int index = i % ((b2LoopShape*)shape)->GetCount();
				GX_Position3f32( ((b2LoopShape*)shape)->GetVertices()[ index ].x, ((b2LoopShape*)shape)->GetVertices()[ index ].y, 0.0f );
				GX_Color3f32( 1.0f, 1.0f, 1.0f );
			}
		GX_End();
	}
	else
	{
		GX_Begin( GX_LINESTRIP, GX_VTXFMT0, ((b2PolygonShape*)shape)->GetVertexCount() + 1 );
			for ( int i = 0; i < ((b2PolygonShape*)shape)->GetVertexCount() + 1; i ++ )
			{
				int index = i % ((b2PolygonShape*)shape)->GetVertexCount();
				GX_Position3f32( ((b2PolygonShape*)shape)->GetVertex( index ).x, ((b2PolygonShape*)shape)->GetVertex( index ).y, 0.0f );
				GX_Color3f32( 1.0f, 1.0f, 1.0f );
			}
		GX_End();
	}
}
