/*
 * CarRenderer.h
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#ifndef WIIGFXCARRENDERER_H_
#define WIIGFXCARRENDERER_H_

#include "rendering/CarRenderer.h"
#include "rendering/wiigfx/WiiGfxRenderer.h"

class WiiGfxCarRenderer : public WiiGfxRenderer, public CarRenderer
{

public:
	WiiGfxCarRenderer( Car* car );
	virtual ~WiiGfxCarRenderer();
	void render();

protected:
	void renderBody( b2Body* body );

};

#endif /* WIIGFXCARRENDERER_H_ */
