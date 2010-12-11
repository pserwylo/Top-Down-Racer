#include "core/Car.h"
#include "core/Race.h"
#include <iostream>
#include "env/Environment.h"
#include <stdio.h>

int main( int argc, char** argv )
{

	Environment::getEnvironment()->setup();
	Race race;
	race.runRace();
	Environment::getEnvironment()->tearDown();

	return 0;

}
