/*
 * Race.h
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#ifndef RACE_H_
#define RACE_H_

#include <vector>
#include "io/Input.h"
#include "Car.h"
#include "Track.h"

class CarGlRenderer;
class TrackGlRenderer;

class Race
{

public:
	Race();
	virtual ~Race();

	void runRace();

private:
	bool update( int timeSinceUpdate );
	void draw();
	long int getMilliseconds();

	CarInput input;
	Car* car;
	Car* car2;
	CarGlRenderer* carRenderer;
	CarGlRenderer* car2Renderer;
	TrackGlRenderer* trackRenderer;
	Track* track;
	b2World* world;

};

#endif /* RACE_H_ */
