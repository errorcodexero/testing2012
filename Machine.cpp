#include "Machine.h"
#include "Constants.h"

Machine :: Machine() :
lStick(LSTICK), rStick(RSTICK)
{
	//m_watchdog.SetEnabled(false);
	stickToggle = 0;
	triggerState = 0;
}

Machine :: ~Machine() 
{

}

void Machine :: RobotInit()
{
	
}

void Machine :: init()
{
	running = 0;
	runTime = 0;
	offset = GetFPGATime();
}

void Machine :: start()
{
	if(running)
		return;
	running = 1;
}

void Machine :: run()
{
	if(runTime < 300000)
		drive.tankDrive(0.8, -0.8);
	else
		drive.tankDrive(0.0, 0.0);
}

void Machine :: stop()
{
	drive.tankDrive(0.0, 0.0);
	running = 0;
}

START_ROBOT_CLASS(Machine);



