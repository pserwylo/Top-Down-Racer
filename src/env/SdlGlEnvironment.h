#ifndef SDLGLENVIRONMENT_H_
#define SDLGLENVIRONMENT_H_

#include "env/Environment.h"

class SdlGlEnvironment : public Environment
{
public:
	SdlGlEnvironment();
	virtual ~SdlGlEnvironment();

	virtual void setup();
	virtual void tearDown();
};

#endif /* SDLGLENVIRONMENT_H_ */
