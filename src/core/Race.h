/*
 * Race.h
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#ifndef RACE_H_
#define RACE_H_

#include <vector>
#include "Input.h"
#include "Car.h"

class CarGlRenderer;
class Track;

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
	CarGlRenderer* carRenderer;
	Track* track;
	b2World* world;

};

#endif /* RACE_H_ */