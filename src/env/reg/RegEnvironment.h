#ifndef SDLGLENVIRONMENT_H_
#define SDLGLENVIRONMENT_H_

#include "env/Environment.h"

class RegInput;

class SdlGlEnvironment : public Environment
{
public:
	SdlGlEnvironment();
	virtual ~SdlGlEnvironment();

	virtual Input* getInput();

	virtual void setup();
	virtual void tearDown();

	virtual void startDraw( Race* race );
	virtual void endDraw();


private:
	RegInput* input;
};

#endif /* SDLGLENVIRONMENT_H_ */
