#include "Machine.h"

int convertOutput(float voltage)
{
	if(voltage < 1)
		return -1;
	if (voltage < 2)
		return 0;
	return 1;	
}

void Machine :: TeleopInit()
{
    DriverStationLCD *lcd = DriverStationLCD::GetInstance();
    lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Ben is here");
    lcd->UpdateLCD();
    drive.enableSpeedControl();
    compressor.Start();
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
	switch (convertOutput(pDS->GetAnalogIn(COWCATCHER_SWITCH)))
	{
		case -1: cowcatcher.Set(0); break;
		case 0: break;
		case 1: cowcatcher.Set(1); break;
		default: printf("Things are seriously wrong. \n");
	}
	switch (convertOutput(pDS->GetAnalogIn(PICKUP_SWITCH)))
	{
		case -1: pickup.reverse(); break;
		case 0: pickup.stop(); break;
		case 1: pickup.start(); break;
		default: printf("Things are seriously wrong. \n");
	}
	plunger.Set(pDS->GetDigitalIn(PLUNGER_SWITCH));
	shooter.multiplier = pDS->GetAnalogIn(ADJUST_SWITCH) / 3.3;
	switch (convertOutput(pDS->GetAnalogIn(SHOOTER_SWITCH)))
	{
		case -1: shooter.reverse();
		case 0: shooter.stop();
		case 1: shooter.start();
		default: printf("Things are seriously wrong. \n");
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

