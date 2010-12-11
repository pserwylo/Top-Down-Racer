#include "rendering/reg/RegTrackRenderer.h"
#include "core/Track.h"
#include <GL/gl.h>

GlTrackRenderer::GlTrackRenderer( Track* track ) : TrackRenderer( track )
{
}

GlTrackRenderer::~GlTrackRenderer()
{
}

void GlTrackRenderer::render()
{
	for ( std::vector<b2Shape*>::iterator it = this->track->getBorders().begin(); it != this->track->getBorders().end(); it ++ )
	{
		this->renderShape( *it );
	}
}
