#ifndef GLTRACKRENDERER_H_
#define GLTRACKRENDERER_H_

#include "core/Track.h"
#include "rendering/reg/GlRenderer.h"
#include "rendering/TrackRenderer.h"

class GlTrackRenderer : public GlRenderer, public TrackRenderer
{

public:
	GlTrackRenderer( Track* track );
	virtual ~GlTrackRenderer();
	void render();

};

#endif /* TRACKRENDERER_H_ */
