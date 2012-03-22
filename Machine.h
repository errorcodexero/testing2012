#include <WPILib.h>
#include "BenDrive.h"
#include "benCamera.h"
#include "benShooter.h"
#include "Pickup.h"
#include "Constants.h"

#define pi 3.14159265

class Machine : public IterativeRobot
{
	Joystick lStick, rStick;
	BenDrive drive;
	benCamera camera;
	SendableChooser lParam, rParam;
	DriverStation *pDS;
	DriverStationEnhancedIO *pIO;
	Solenoid cowcatcher;
	Relay illuminator;
	Compressor compressor;
	benPickup pickup;
	benShooter shooter;
	Timer autoTimer;
	AnalogChannel autoSwitch;
	DigitalInput lightSensor;
	Solenoid tipper;
	bool cowcatcherState;
	int stickToggle;
	int lTriggerState, rTriggerState;
	bool turning;
	bool specialTurning;
	int topState;
	int lastCase;
	bool isTime;
	unsigned int ticks;
	bool fudge;
	int extraSwitch;
	int autoMode;
	int turnType;
	float angle;
	float camAngle;

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
    
    void setShooterLight(bool setting);
private:
    int running;
    unsigned long int runTime;
    unsigned long int offset;
};
