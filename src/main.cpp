#include "core/Car.h"
#include "core/global.h"
#include "core/Race.h"
#include <iostream>
#include "env/Environment.h"

int main( int argc, char** argv )
{

	Environment::getEnvironment()->setup();

	Race race;
	race.runRace();

	Environment::getEnvironment()->tearDown();

	return 0;

}
