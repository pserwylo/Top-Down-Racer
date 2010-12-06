#include "TrackRenderer.h"
#include "core/Track.h"
#include "GL/gl.h"
#include <iostream>

TrackGlRenderer::TrackGlRenderer( Track* track ) : track( track )
{

}

TrackGlRenderer::~TrackGlRenderer()
{

}

void TrackGlRenderer::render()
{
	for ( std::vector<b2Shape*>::iterator it = this->track->getBorders().begin(); it != this->track->getBorders().end(); it ++ )
	{
		this->renderShape( *it );
	}
}
