/*
 * CarRenderer.h
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#ifndef CARRENDERER_H_
#define CARRENDERER_H_

class Car;

class CarGlRenderer
{

public:
	CarGlRenderer( Car* car );
	virtual ~CarGlRenderer();

	void render();

private:
	Car* car;

};

#endif /* CARRENDERER_H_ */
