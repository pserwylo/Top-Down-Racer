#include "rendering/reg/RegTrackRenderer.h"
#include "core/Track.h"
#include "core/Waypoint.h"
#include <GL/gl.h>
#include <GL/glu.h>

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

	for ( std::vector<Waypoint*>::iterator it = this->track->getWaypoints().begin(); it != this->track->getWaypoints().end(); it ++ )
	{
		this->renderBody( (*it)->getBody() );
	}

	for ( std::vector<b2Shape*>::iterator it = this->track->getHazards().begin(); it != this->track->getHazards().end(); it ++ )
	{
		this->renderShape( *it );
	}
}
