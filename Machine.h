#include <WPILib.h>
#include "BenDrive.h"

class Machine : public IterativeRobot
{
	Joystick lStick, rStick;
	BenDrive drive;
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
};
