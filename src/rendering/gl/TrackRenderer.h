#ifndef TRACKRENDERER_H_
#define TRACKRENDERER_H_

#include "core/Track.h"
#include "GlRenderer.h"

class TrackGlRenderer : public GlRenderer
{

public:
	TrackGlRenderer( Track* track );
	virtual ~TrackGlRenderer();

	void render();

private:
	Track* track;

};

#endif /* TRACKRENDERER_H_ */
