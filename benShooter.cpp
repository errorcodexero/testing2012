#include "benShooter.h"

benShooter :: benShooter() :
p(SHOOTER_P), i(SHOOTER_I), d(SHOOTER_D),
driveRatio(SHOOTER_DRIVE_RATIO),
tolerance(SHOOTER_TOLERANCE),
plunger(PLUNGER),
topMotor(SHOOTER_TOP_VICTOR), bottomMotor(SHOOTER_BOTTOM_VICTOR),
topSensor(SHOOTER_BOTTOM_SENSOR), bottomSensor(SHOOTER_TOP_SENSOR),
topPID(p, i, d, &topSensor, &topMotor),
bottomPID(p, i, d, &bottomSensor, &bottomMotor)

{
	multiplier = 1.0;
	autoHax = false;
	shootEnable = true;
	running = 0;
	speed = 0.010825 * (109.5 * 109.5) + 5.02778 * 109.5 + 265;
    topPID.SetInputRange(0.0, MAX_GEARTOOTH_PPS);
    bottomPID.SetInputRange(0.0, MAX_GEARTOOTH_PPS);
    topPID.SetOutputRange(0.0, 0.98);
    bottomPID.SetOutputRange(0.0, 0.98);
    topPID.SetTolerance(tolerance);
    bottomPID.SetTolerance(tolerance);
    topPID.SetPID(p, i, d);
    bottomPID.SetPID(p, i, d);
    topSensor.SetAverageSize(8);
    bottomSensor.SetAverageSize(8);   
	topSensor.Start();
	bottomSensor.Start();
}

void benShooter :: adjustSpeed(float distance)
{
	speed = 0.010825 * (distance * distance) + 5.02778 * distance + 265;
	speed = (float) (speed * MAX_GEARTOOTH_PPS);
}

void benShooter :: start(int direction)
{
	speed *= direction;
	running = 1;
	topPID.Enable();
	bottomPID.Enable();
	run();
}

void benShooter :: stop()
{
	running = 0;
	topPID.Reset();
	bottomPID.Reset();
	topMotor.PIDWrite(0.0);
	bottomMotor.PIDWrite(0.0);
	topSensor.Stop();
	bottomSensor.Stop();
}

void benShooter :: shoot()
{
	if(/*topPID.OnTarget() && bottomPID.OnTarget()*/ 1)
	{
		shotTimer.Start();
		shotTimer.Reset();
		shootEnable = false;
		printf("roger, roger \n");
		plunger.Set(1);
	}
}

void benShooter :: run()
{
	if(running)
	{
		topPID.SetSetpoint(speed * driveRatio);
		bottomPID.SetSetpoint(speed);
	}
	if(shotTimer.Get() > SHOT_TIME)
	{
		plunger.Set(0);
		shootEnable = true;
		autoHax = 1;
	}
}

void benShooter :: setMultiplier(float n)
{
	multiplier = n;
}

/*
benShooter :: benShooter() : 
top(TOP_SHOOTER_VICTOR), bottom(BOTTOM_SHOOTER_VICTOR)
{
	multiplier = 0;
}

void benShooter :: start()
{
	top.Set(1.0 * multiplier);
	bottom.Set(1.0 * multiplier);
}

void benShooter :: reverse()
{
	top.Set(-(1.0) * multiplier);
	bottom.Set(-(1.0) * multiplier);
}

void benShooter :: stop()
{
	top.Set(0.0);
	bottom.Set(0.0);
}
*/
