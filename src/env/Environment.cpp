#include "env/Environment.h"

#ifdef WII
#include "env/wii/WiiEnvironment.h"
#else
#include "env/reg/RegEnvironment.h"
#endif

Environment* Environment::environment = 0;
bool Environment::singletonExists = false;

Environment* Environment::getEnvironment()
{
	if ( !Environment::singletonExists )
	{
		Environment::singletonExists = true;

#ifdef WII
		Environment::environment = new WiiEnvironment();
#else
		Environment::environment = new SdlGlEnvironment();
#endif

	}
	return Environment::environment;
}
