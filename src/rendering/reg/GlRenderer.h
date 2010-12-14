/*
 * GlRenderer.h
 *
 *  Created on: 03/12/2010
 *      Author: pete
 */

#ifndef GLRENDERER_H_
#define GLRENDERER_H_

#include "Box2D.h"

class GlRenderer
{
public:
	GlRenderer();
	virtual ~GlRenderer();

protected:
	void renderShape( b2Shape* shape );
	void renderAxis();

};

#endif /* GLRENDERER_H_ */
