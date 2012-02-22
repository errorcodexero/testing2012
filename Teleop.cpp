#include "Machine.h"

void Machine :: TeleopInit()
{
    DriverStationLCD *lcd = DriverStationLCD::GetInstance();
    lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Ben is here");
    lcd->UpdateLCD();
    drive.enableSpeedControl();
}

void Machine :: DisabledInit()
{

}

void Machine :: AutonomousInit()
{
	drive.enablePositionControl();
	//drive.enableSpeedControl();
	camera.refreshImage();
	double direction = camera.getHoopDirection();
	if(direction)
	{
		direction = camera.getHoopDirection();
		drive.positionDrive(0.3 * direction, -0.3 * direction);
		camera.refreshImage();
	}
	Wait(1.0);
	double angle = camera.getAngle();
	angle = angle * ((DISTANCE_BETWEEN_WHEELS / DIAMETER_OF_WHEEL) * GEAR_RATIO) / (2 * pi);
	drive.positionDrive(-angle, angle); 
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
	
	float ly = lStick.GetY();
	float ry = rStick.GetY();
	printf("Right: %f \n Left: %f \n", ly, ry);
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
	
	//DriverStation::GetInstance()->GetDigitalIn( 6 )
}
void Machine :: DisabledPeriodic()
{
	
}

void Machine :: TeleopContinuous()
{
	//long start = GetFPGATime();
	//camera.refreshImage();
	//long end = GetFPGATime();
	//printf("%ld \n", (end - start) / 1000);
}

void Machine :: AutonomousContinuous()
{
	//track();
}

void Machine :: DisabledContinuous()
{
	
}

