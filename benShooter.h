#include <WPILib.h>
#include "Constants.h"
#include "xCounter.h"
#include "xGearTooth.h"
#include "xPIDController.h"

class benShooter
{
public:
	benShooter();
	void adjustSpeed(float distance); // must be in inches
	void start(int direction);
	void stop();
	void shoot();
	void run();
	void setMultiplier(float n);
private:
	const float p, i, d;
	const float driveRatio;
	const float tolerance;
	float multiplier;
	float speed;
	int running;
	Solenoid plunger;
	Victor topMotor, bottomMotor;
	xGearTooth topSensor, bottomSensor;
	xPIDController topPID, bottomPID;
	Timer shotTimer;
/*
public:
	benShooter();
	void start();
	void reverse();
	void stop();
	float multiplier;
private:
	Victor top;
	Victor bottom;
*/
};
