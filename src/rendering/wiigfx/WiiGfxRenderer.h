#ifndef WIIGFXRENDERER_H_
#define WIIGFXRENDERER_H_

#include "gccore.h"
class b2Shape;

class WiiGfxRenderer
{
public:
	WiiGfxRenderer();
	virtual ~WiiGfxRenderer();

protected:
	void renderShape( b2Shape* shape );
	Mtx view;

};

#endif /* WIIGFXRENDERER_H_ */
