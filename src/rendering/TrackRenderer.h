#ifndef TRACKRENDERER_H_
#define TRACKRENDERER_H_

#include "rendering/Renderer.h"

class Track;

class TrackRenderer : public Renderer
{

public:
	TrackRenderer( Track* track );
	virtual ~TrackRenderer();

	static TrackRenderer* create( Track* track );

protected:
	Track* track;

};

#endif /* TRACKRENDERER_H_ */
