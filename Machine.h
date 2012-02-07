#include <WPILib.h>
#include "BenDrive.h"
#include "benCamera.h"

class Machine : public IterativeRobot
{
	Joystick lStick, rStick;
	BenDrive drive;
	benCamera camera;
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
