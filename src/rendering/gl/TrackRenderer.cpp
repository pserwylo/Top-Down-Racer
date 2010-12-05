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
	this->renderShape( this->track->getBorders()[ 0 ] );
}
