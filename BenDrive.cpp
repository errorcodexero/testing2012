#include "BenDrive.h"
#include <cmath>

BenDrive :: BenDrive() :
Lvic(LVIC), Rvic(RVIC)
{

}

void BenDrive :: tankDrive(float left, float right)
{
	Lvic.Set((pow((left * LVICDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND)));
	Rvic.Set((pow((right * RVICDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND)));
	SmartDashboard :: Log(pow(left, TANKCURVE), "Left Power");
	SmartDashboard :: Log(pow(right, TANKCURVE), "Right Power");
}

void BenDrive :: arcadeDrive(float speedAxis, float turnAxis)
{
	Lvic.Set((pow((speedAxis + turnAxis) * LVICDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND)));
	Rvic.Set((pow((speedAxis - turnAxis) *RVICDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND)));
	SmartDashboard :: Log(pow(speedAxis, TANKCURVE), "Speed Axis");
	SmartDashboard :: Log(pow(turnAxis, TANKCURVE), "Turn Axis");
}


