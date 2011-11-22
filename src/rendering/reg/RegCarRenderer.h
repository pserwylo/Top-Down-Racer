#ifndef GLCARRENDERER_H_
#define GLCARRENDERER_H_

class Car;

#include "rendering/reg/GlRenderer.h"
#include "rendering/CarRenderer.h"

class RegCarRenderer : public GlRenderer, public CarRenderer
{
public:
	RegCarRenderer( Car* car );
	virtual ~RegCarRenderer();

	virtual void render();

};

#endif /* GLCARRENDERER_H_ */
