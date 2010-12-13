#include "rendering/gx/WiiGfxTrackRenderer.h"
#include "core/Track.h"

WiiGfxTrackRenderer::WiiGfxTrackRenderer( Track* track ) : TrackRenderer( track )
{

}

WiiGfxTrackRenderer::~WiiGfxTrackRenderer()
{

}

void WiiGfxTrackRenderer::render()
{
	for ( std::vector<b2Shape*>::iterator it = this->track->getBorders().begin(); it != this->track->getBorders().end(); it ++ )
	{
		this->renderShape( *it );
	}
}
