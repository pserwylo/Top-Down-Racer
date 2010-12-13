#ifndef WIIGFXTRACKRENDERER_H_
#define WIIGFXTRACKRENDERER_H_

#include "core/Track.h"
#include "rendering/gx/WiiGfxRenderer.h"
#include "rendering/TrackRenderer.h"

class WiiGfxTrackRenderer : public WiiGfxRenderer, public TrackRenderer
{

public:
	WiiGfxTrackRenderer( Track* track );
	virtual ~WiiGfxTrackRenderer();
	void render();

};

#endif /* WIIGFXTRACKRENDERER_H_ */
