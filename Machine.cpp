#include "Machine.h"
#include "Constants.h"

Machine :: Machine() :
lStick(LSTICK), rStick(RSTICK), drive(), camera()
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

START_ROBOT_CLASS(Machine);



