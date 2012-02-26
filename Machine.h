#include <WPILib.h>
#include "BenDrive.h"
#include "benCamera.h"
#include "benShooter.h"
#include "Pickup.h"

#define pi 3.14159265

class Machine : public IterativeRobot
{
	Joystick lStick, rStick;
	BenDrive drive;
	benCamera camera;
	SendableChooser lParam, rParam;
	DriverStation *pDS;
	Solenoid cowcatcher, plunger;
	Compressor compressor;
	benPickup pickup;
	benShooter shooter;
	int stickToggle;
	int triggerState;

public:
    Machine();
    ~Machine();

    void RobotInit();

    void DisabledInit();
    void AutonomousInit();
    void TeleopInit();

    void DisabledPeriodic();
    void AutonomousPeriodic();
    void TeleopPeriodic();

    void DisabledContinuous();
    void AutonomousContinuous();
    void TeleopContinuous();
    
    void init();
    void start();
    void run();
    void stop();
    
    void track();
private:
    int running;
    unsigned long int runTime;
    unsigned long int offset;
};
