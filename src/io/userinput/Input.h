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
	virtual float getSteeringAngle();
	virtual bool isQuitting();

protected:
	static const int ACCEL = 0;
	static const int DECEL = 1;
	static const int SHOOT = 2;
	static const int LEFT = 3;
	static const int RIGHT = 4;
	static const int NUM_FLAGS = 5;
	bool flags[ NUM_FLAGS ];
	bool quit;

protected:
	void setSteeringAngle( float angle );

private:
	float steeringAngle;

};

#endif /* INPUT_H_ */
