/*
 * Input.h
 *
 *  Created on: 19/10/2010
 *      Author: pete
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "SDL/SDL.h"

/**
 * Deals with obtaining input from the user and presenting it as actions which
 * need to be applied to the car.
 */
class CarInput
{
public:
	CarInput();
	virtual ~CarInput();

	void readInput();
	bool isAccelarating();
	bool isDecelarating();
	bool isTurningLeft();
	bool isTurningRight();
	bool isQuitting();

private:
	static const int ACCEL = 0;
	static const int DECEL = 1;
	static const int LEFT = 2;
	static const int RIGHT = 3;
	bool flags[4];
	SDLKey keyFlagMap[4];
	bool quit;

};

#endif /* INPUT_H_ */
