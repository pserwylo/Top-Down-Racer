#include "rendering/TrackRenderer.h"
#include "core/Track.h"

#ifdef WII
#include "rendering/gx/WiiGfxTrackRenderer.h"
#else
#include "rendering/reg/RegTrackRenderer.h"
#endif

TrackRenderer::TrackRenderer( Track* track ) : track( track )
{

}

TrackRenderer::~TrackRenderer()
{

}

TrackRenderer* TrackRenderer::create( Track* track )
{

#ifdef WII
	return new WiiGfxTrackRenderer( track );
#else
	return new GlTrackRenderer( track );
#endif

}
