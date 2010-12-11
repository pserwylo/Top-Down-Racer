#ifndef WIIENVIRONMENT_H_
#define WIIENVIRONMENT_H_

#include "env/Environment.h"
#include "gccore.h"
#include "rendering/wiigfx/WiiGfxRenderer.h"

class WiiInput;


class WiiEnvironment : public Environment, public WiiGfxRenderer
{

public:
	WiiEnvironment();
	virtual ~WiiEnvironment();

	virtual void setup();
	virtual void tearDown();

	virtual void startDraw();
	virtual void endDraw();

	virtual Input* getInput();

	void getView( Mtx v );

protected:
	WiiInput* input;

	void* frameBuffer[2];
	GXRModeObj* rmode;
	f32 yscale;
	u32 xfbHeight;
	Mtx44 perspective;
	u32	fb;


};

#endif /* WIIENVIRONMENT_H_ */
