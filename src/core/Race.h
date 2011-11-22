#ifndef RACE_H_
#define RACE_H_

#include <vector>
#include "Car.h"
#include "Track.h"

#include <sys/time.h>
#include <ctime>

class Input;
class CarRenderer;
class TrackRenderer;

double myDifftime( timeval& start, timeval& end );

/**
 * The race class depicts one single race. 
 * It begins with the countdown, 
 * then the actual racing,
 * keeping track of which cars cross checkpoints,
 * how many laps each car has completed,
 * when the race is over,
 * and then a bit of time after the race is finished.
 */
class Race
{

public:
	Race();
	virtual ~Race();

	void runRace();
	Car* getCar() { return this->car; }

private:
	bool update( double timeSinceUpdate );
	bool updateRace( double timeSinceUpdate );
	void draw();
	long int getMilliseconds();

	Input* input;
	Car* car;
	CarRenderer* carRenderer;
	TrackRenderer* trackRenderer;
	Track* track;
	b2World* world;

	// We need to use these states to decide what to do in the game loop...
	enum { STATE_WAITING, STATE_STARTING, STATE_RACING, STATE_FINISHED_WAITING, STATE_FINISHED };
	int state;

};

#endif /* RACE_H_ */
