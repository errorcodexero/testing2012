#include "BenDrive.h"

BenDrive :: BenDrive() :
Lvic(LVIC), Rvic(RVIC)
{

}

void BenDrive :: tankDrive(float left, float right)
{
	Lvic.Set(left * LVICDIRECTION);
	Rvic.Set(right * RVICDIRECTION);
	SmartDashboard :: Log(left, "Left Power");
	SmartDashboard :: Log(right, "Right Power");
}

void BenDrive :: arcadeDrive(float speedAxis, float turnAxis)
{
	Lvic.Set((speedAxis + turnAxis) * LVICDIRECTION);
	Rvic.Set((speedAxis - turnAxis) *RVICDIRECTION);
	SmartDashboard :: Log(speedAxis, "Speed Axis");
	SmartDashboard :: Log(turnAxis, "Turn Axis");
}


