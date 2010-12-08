#ifndef WIIENVIRONMENT_H_
#define WIIENVIRONMENT_H_

#include "env/Environment.h"

class WiiEnvironment : public Environment
{
public:
	WiiEnvironment();
	virtual ~WiiEnvironment();

	virtual void setup();
	virtual void tearDown();
};

#endif /* WIIENVIRONMENT_H_ */
