#ifndef INPUT_H_
#define INPUT_H_

/**
 * Deals with obtaining input from the user and presenting it as actions which
 * need to be applied to the car.
 */
class Input
{
public:
	Input();
	virtual ~Input();

	virtual void readInput() = 0;

	virtual bool isAccelarating();
	virtual bool isDecelarating();
	virtual bool isShooting();
	virtual bool isTurningLeft();
	virtual bool isTurningRight();
	virtual bool isQuitting();

protected:
	static const int ACCEL = 0;
	static const int DECEL = 1;
	static const int LEFT = 2;
	static const int RIGHT = 3;
	static const int SHOOT = 4;
	static const int NUM_KEYS = 5;
	bool flags[ NUM_KEYS ];
	bool quit;

};

#endif /* INPUT_H_ */