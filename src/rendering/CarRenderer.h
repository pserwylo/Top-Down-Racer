#ifndef CARRENDERER_H_
#define CARRENDERER_H_

#include "rendering/Renderer.h"

class Car;

class CarRenderer : public Renderer
{

public:
	CarRenderer( Car* car );
	virtual ~CarRenderer();

	static CarRenderer* create( Car* car );

protected:
	Car* car;

};

#endif /* CARRENDERER_H_ */
