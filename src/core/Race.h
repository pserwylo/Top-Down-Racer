/*
 * Race.h
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#ifndef RACE_H_
#define RACE_H_

#include <vector>
#include "Car.h"
#include "Track.h"

class Input;
class CarRenderer;
class TrackRenderer;

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

	Input* input;
	Car* car;
	CarRenderer* carRenderer;
	TrackRenderer* trackRenderer;
	Track* track;
	b2World* world;

};

#endif /* RACE_H_ */
