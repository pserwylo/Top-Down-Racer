#include "core/Car.h"
#include "core/Bullet.h"
#include "rendering/reg/RegCarRenderer.h"
#include <GL/gl.h>

RegCarRenderer::RegCarRenderer( Car* car ) : CarRenderer( car )
{
}

RegCarRenderer::~RegCarRenderer()
{
}

void RegCarRenderer::render()
{
	this->renderBody( this->car->carBody );
	this->renderBody( this->car->frontLeftWheel );
	this->renderBody( this->car->frontRightWheel );
	this->renderBody( this->car->backLeftWheel );
	this->renderBody( this->car->backRightWheel );

	for ( std::vector<Gun*>::iterator it = this->car->getGuns().begin(); it != this->car->getGuns().end(); it ++ )
	{
		this->renderBody( (*it)->getBody() );
		for ( std::vector<Bullet*>::iterator bIt = (*it)->getBullets().begin(); bIt != (*it)->getBullets().end(); bIt ++ )
		{
			this->renderBody( (*bIt)->getBody() );
		}

		// DEBUGGING:
		// Simply draw a line from the tip of the gun, indicating the firing direction and speed...
		b2Vec2 shootPos = (*it)->getShootPosition();
		b2Vec2 endPos = shootPos + (*it)->getShootVelocity();

		glPointSize( 3 );
		glBegin( GL_POINTS );
			glVertex2d( shootPos.x, shootPos.y );
			glVertex2d( endPos.x, endPos.y );
		glEnd();
	};

	this->renderAxis();

}
