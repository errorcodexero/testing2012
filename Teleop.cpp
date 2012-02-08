#include "Machine.h"

void Machine :: TeleopInit()
{
    DriverStationLCD *lcd = DriverStationLCD::GetInstance();
    lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Ben is here");
    lcd->UpdateLCD();
}

void Machine :: DisabledInit()
{

}

void Machine :: AutonomousInit()
{

}

void Machine :: AutonomousPeriodic()
{

}

void Machine :: TeleopPeriodic()
{	
	if(rStick.GetTop())
		triggerState = 1;
	else if(triggerState)
	{
		if(stickToggle < 2)
			stickToggle++;
		else
			stickToggle = 0;
		triggerState = 0;
	}
	
	SmartDashboard :: Log(stickToggle, "stickToggle");
	
	switch(stickToggle)
	{
		case 0: 
		drive.tankDrive(rStick.GetY(), lStick.GetY());
		break;
		case 1:
		drive.arcadeDrive(rStick.GetY(), rStick.GetX());
		break;
		case 2:
		drive.arcadeDrive(rStick.GetY(), rStick.GetTwist());
		break;
		default:
		SmartDashboard :: Log(stickToggle, "stickToggle has exceeded its bounds");
		break;
	}	
	
	camera.refreshImage();
	camera.setParticles();
	//camera.setParticles();
	
	//DriverStation::GetInstance()->GetDigitalIn( 6 )
}
void Machine :: DisabledPeriodic()
{
	
}

void Machine :: TeleopContinuous()
{
	
}

void Machine :: AutonomousContinuous()
{
	
}

void Machine :: DisabledContinuous()
{
	
}

