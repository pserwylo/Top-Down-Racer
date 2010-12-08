#ifndef SDLGLENVIRONMENT_H_
#define SDLGLENVIRONMENT_H_

#include "env/Environment.h"

class SdlInput;

class SdlGlEnvironment : public Environment
{
public:
	SdlGlEnvironment();
	virtual ~SdlGlEnvironment();

	virtual Input* getInput();

	virtual void setup();
	virtual void tearDown();

private:
	SdlInput* input;
};

#endif /* SDLGLENVIRONMENT_H_ */
