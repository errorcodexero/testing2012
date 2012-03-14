#include "Machine.h"

int convertOutput(float voltage)
{
	if(voltage > 0.6)
		return 1;
	if (voltage > 0.4)
		return 0;
	return -1;	
}

void Machine :: TeleopInit()
{
    DriverStationLCD *lcd = DriverStationLCD::GetInstance();
    lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Ben is here");
    lcd->UpdateLCD();
    drive.enableVoltageControl();
    //drive.enableSpeedControl();
}

void Machine :: DisabledInit()
{
	compressor.Start();
}

void Machine :: AutonomousInit()
{
	compressor.Start();
	autoTimer.Start();
	shooter.start(1); 
	if(autoSwitch.GetVoltage() < 1.0)
		autoMode = 0;
	else if(autoSwitch.GetVoltage() < 2.0)
		autoMode = 1;
	else
		autoMode = 2;
	/*
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
	*/ 
}

void Machine :: AutonomousPeriodic()
{
	/*
	switch(autoMode)
	{
		case 0: shooter.run(0);
		case 1: shooter.run(CENTER);
		case 2: shooter.run(CORNER);
	}
	*/
	shooter.run(CORNER);
	if(autoTimer.Get() > 6.0 && autoTimer.Get() < 7)
	{
		shooter.stop();
		//drive.tankDrive(-0.6, -0.6);
	}
	/*
	if(autoTimer.Get() > 7)
	{
		shooter.stop();
		drive.tankDrive(0.0, 0.0);
	}
	*/
	if(autoTimer.Get() > 2.0 && (!isTime))
	{
		shooter.shoot();
		isTime = true;
	}
	if(autoTimer.Get() > 4.0)
		isTime = 0;
	
}

void Machine :: TeleopPeriodic()
{	
	SmartDashboard :: Log(autoSwitch.GetVoltage(), "AutoMode");
	//camera.refreshImage();
	if(rStick.GetTop())
		topState = 1;
	else if(topState)
	{
		if(stickToggle < 2)
			stickToggle++;
		else
			stickToggle = 0;
		topState = 0;
	}
	
	/*
	if(rStick.GetTrigger())
		rTriggerState = 1;
	else if(rTriggerState)
	{
		cowcatcherState = !cowcatcherState;
		cowcatcher.Set(cowcatcherState);
		rTriggerState = 0;
	}
	*/
	
	if(rStick.GetTrigger())
		cowcatcher.Set(1);
	else
		cowcatcher.Set(0);
	/*
	if(lStick.GetRawButton(3) && (!turning))
	{
		turning = true;
		ticks = 0;
		fudge = 1;
		drive.tankDrive(0.3, -0.3);
	}
	else if(lStick.GetRawButton(4) && (!turning))
	{
		turning = true;
		ticks = 0;
		fudge = 1;
		drive.tankDrive(-0.3, 0.3);
	}
	else if(lStick.GetRawButton(5) && (!turning))
	{
		turning = true;
		ticks = 0;
		fudge = 0;
		drive.tankDrive(0.3, -0.3);
	}
	else if(lStick.GetRawButton(6) && (!turning))
	{
		turning = true;
		ticks = 0;
		fudge = 0;
		drive.tankDrive(-0.3, 0.3);
	}
	
	if(turning)
	{
		printf("running");
		if(fudge)
		{
			if(ticks > 160)
			{
				drive.tankDrive(0.0, 0.0);
				turning = false;
			}
		}
		else
		{
			if(ticks > 80)
			{
				drive.tankDrive(0.0, 0.0);
				turning = false;
			}
		}
	}
	*/
	
	/*
	if(convertOutput(pIO->GetAnalogInRatio(7)) && (!turning))
		extraSwitch = 1;
	else if(extraSwitch)
	{
		turning = true;
		camera.refreshImage();
		drive.enablePositionControl();
		extraSwitch = 0;
	}
	*/
	
	if(specialTurning)
	{
		printf("running /n");
		//if(drive.angleDrive( (float)camera.getAngle(), (pi / 360.0)))
		if(drive.angleDrive((pi / 4), (pi / 360)))
		{
			drive.enableVoltageControl();
			specialTurning = false;
		}
	}
	
	if(pIO->GetDigital(ILLUMINATOR_SWITCH))
		illuminator.Set(Relay::kOn );
	else
		illuminator.Set(Relay::kOff);
	/*
	switch (convertOutput(pIO->GetAnalogInRatio(COWCATCHER_SWITCH)))
	{
		case -1: cowcatcher.Set(1); break;
		case 0: break;
		case 1: cowcatcher.Set(0); break;
		default: printf("Things are seriously wrong. \n");
	}
	*/
	switch (convertOutput(pIO->GetAnalogInRatio(PICKUP_SWITCH)))
	{
		case -1: pickup.reverse(); break;
		case 0: pickup.stop(); break;
		case 1: pickup.start(); break;
		default: printf("Things are seriously wrong. \n");
	}
	int shooterSwitch = convertOutput(pIO->GetAnalogInRatio(SHOOTER_SWITCH));
	if(shooterSwitch != lastCase)
	{
		switch (shooterSwitch)
		{
			case -1: shooter.stop(); lastCase = -1; break;
			case 0: lastCase = 0; break;
			case 1: shooter.start(1); lastCase = 1; break;
			default: printf("Things are seriously wrong. \n");
		}
	}
	shooter.run( pIO->GetAnalogInRatio(ADJUST_SWITCH) + 0.2);
	if(pIO->GetDigital(PLUNGER_SWITCH) && shooter.shootEnable)
		shooter.shoot();
	
	//float sensitivity = 1.0 / (10 * rStick.GetRawButton(3));

	if(1)
	{
		switch(/*stickToggle*/ 2)
		{
			case 0: 
				drive.tankDrive(rStick.GetY() , lStick.GetY());
				break;
			case 1:
				drive.arcadeDrive(rStick.GetY() , rStick.GetX() );
				break;
			case 2:
				drive.arcadeDrive(rStick.GetY() , rStick.GetTwist() );
				break;
			default:
				SmartDashboard :: Log(stickToggle, "stickToggle has exceeded its bounds");
				break;
		}	
	}
	ticks++;
	
	//DriverStation::GetInstance()->GetDigitalIn( 6 )
}
void Machine :: DisabledPeriodic()
{
	
}

void Machine :: TeleopContinuous()
{
	//long start = GetFPGATime();
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

