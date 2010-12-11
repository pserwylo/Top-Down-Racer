#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

class Input;

class Environment
{
public:
	Environment() {};
	virtual ~Environment() {};

	virtual void setup() {};
	virtual void tearDown() {};

	virtual void startDraw() {};
	virtual void endDraw() {};

	virtual Input* getInput() = 0;

	static Environment* getEnvironment();

private:
	static Environment* environment;
	static bool singletonExists;

};

#endif /* ENVIRONMENT_H_ */
