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
	//SmartDashboard :: Log(autoSwitch.GetVoltage(), "AutoMode");
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
	
	two = rStick.GetRawButton(2);
	three = rStick.GetRawButton(3);
	four = rStick.GetRawButton(4);
	five = rStick.GetRawButton(5);
	six = rStick.GetRawButton(6);
	
	if(two || three || four || five || six)
	{
		if(!fudge)
		{
			if(two)
			{
				camera.refreshImage();
				camAngle = camera.getAngle();
				turnType = 9;
			}
			else if(three)
				turnType = -2;
			else if(four)
				turnType = 1;
			else if(five)
				turnType = -1;
			else
				turnType = 2;
			turnTimer.Start();
			turnTimer.Reset();
			fudge = 1;
			printf("Adjusting \n");
			turning = true;
			drive.enablePositionControl();
		}
	}
	else
	{
		fudge = 0;
	}
	

	if(turning)
	{
		switch(turnType)
		{
			case -2: angle = -(pi / 18.0); break;
			case -1: angle = -(pi / 54.0); break;
			case 0: angle = 0.0; break;
			case 1: angle = (pi / 18.0); break;
			case 2: angle = (pi / 54.0); break;
			case 9: angle = camAngle; break;
			default: printf("Things are seriously wrong \n"); break;
		}
		printf("Turn_Type: %d, angle: %g, camAngle: %g \n", turnType, angle, camAngle);
		if(drive.angleDrive(angle, pi / 360) || turnTimer.Get() > TURN_TIME)
		{
			drive.enableVoltageControl();
			turning = false;
		}
	}
	
	/*
	if(rStick.GetRawButton(2))
	{
		if(lastDriveMode)
		{
			drive.enableSpeedControl();
			lastDriveMode = true;
		}
	}
	else if(lastDriveMode)
	{
		drive.enableVoltageControl();
		lastDriveMode = false;
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
	/*
	if(lStick.GetTrigger())
	{
		if(!lTriggerState)
		{
			lTriggerState = 1;
			printf("angle drive enabled \n");
			specialTurning = true;
			drive.enablePositionControl();
		}
	}
	else
	{
		lTriggerState = 0;
	}
	
	if(specialTurning)
	{
		//if(drive.angleDrive( (float)camera.getAngle(), (pi / 360.0)))
		if(drive.angleDrive((pi / 4), (pi / 360)))
		{
			drive.enableVoltageControl();
			specialTurning = false;
		}
	}
	*/
	
	if(pIO->GetDigital(ILLUMINATOR_SWITCH))
		illuminator.Set(Relay::kOn );
	else
		illuminator.Set(Relay::kOff);
	
	if(lightSensor.Get())
		pIO->SetDigitalOutput(RAMP_LIGHT, 1);
	else
		pIO->SetDigitalOutput(RAMP_LIGHT, 0);
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
	switch(convertOutput(pIO->GetAnalogInRatio(TIPPER_SWITCH)))
	{
		case -1: tipper.Set(0); break;
		case 0: break;
		case 1: tipper.Set(1); break;
	}
	shooter.run( 0.3 + 0.750 * pIO->GetAnalogInRatio(ADJUST_SWITCH));
	if(pIO->GetDigital(PLUNGER_SWITCH) && shooter.shootEnable)
		shooter.shoot();
	
	//float sensitivity = 1.0 / (10 * rStick.GetRawButton(3));

	if(!turning)
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
	taskDelay(1);
	//long start = GetFPGATime();
	//long end = GetFPGATime();
	//printf("%ld \n", (end - start) / 1000);
}

void Machine :: AutonomousContinuous()
{
	taskDelay(1);
	//track();
}

void Machine :: DisabledContinuous()
{
	taskDelay(1);
}

