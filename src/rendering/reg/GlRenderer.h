/*
 * GlRenderer.h
 *
 *  Created on: 03/12/2010
 *      Author: pete
 */

#ifndef GLRENDERER_H_
#define GLRENDERER_H_

class b2Shape;
class b2Body;

class GlRenderer
{
public:
	GlRenderer();
	virtual ~GlRenderer();

protected:
	void renderShape( b2Shape* shape );
	void renderBody( b2Body* body );
	void renderAxis();

};

#endif /* GLRENDERER_H_ */
