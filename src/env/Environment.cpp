#include "env/Environment.h"

#ifdef WII
#include "env/WiiEnvironment.h"
#else
#include "env/SdlGlEnvironment.h"
#endif

Environment* Environment::environment = 0;
bool Environment::singletonExists = false;

Environment* Environment::getEnvironment()
{
	if ( !Environment::singletonExists )
	{
		Environment::singletonExists = true;

#ifdef WII
		envrinoment = new WiiEnvironment();
#else
		Environment::environment = new SdlGlEnvironment();
#endif

	}
	return Environment::environment;
}
