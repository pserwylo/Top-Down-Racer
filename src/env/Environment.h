#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

class Environment
{
public:
	Environment() {};
	virtual ~Environment() {};

	virtual void setup() {};
	virtual void tearDown() {};

	static Environment* getEnvironment();

private:
	static Environment* environment;
	static bool singletonExists;

};

#endif /* ENVIRONMENT_H_ */
