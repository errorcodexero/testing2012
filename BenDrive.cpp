#include "BenDrive.h"
#include <math.h>

// PID constants 100.0, 0.03, 0.01

BenDrive :: BenDrive() :
#ifdef VICTOR
Lvic(LVIC), Rvic(RVIC)
#endif
#ifdef JAGUAR
tlJaguar(TLJAGUAR), trJaguar(TRJAGUAR), blJaguar(BLJAGUAR), brJaguar(BRJAGUAR)
#endif
{

}

#ifdef JAGUAR
void BenDrive :: tankDrive(float left, float right)
{
	tlJaguar.Set(((pow((left * LSIDEDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))), 1);
	blJaguar.Set(((pow((left * LSIDEDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))), 1);
	trJaguar.Set(((pow((right * RSIDEDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))), 1);
	brJaguar.Set(((pow((right * RSIDEDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))), 1);
	CANJaguar :: UpdateSyncGroup(1);
}
void BenDrive :: arcadeDrive(float speedAxis, float turnAxis)
{
	tlJaguar.Set(((pow((speedAxis + turnAxis) * LSIDEDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))), 1);
	blJaguar.Set(((pow((speedAxis + turnAxis) * LSIDEDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))), 1);
	trJaguar.Set(((pow((speedAxis - turnAxis) * RSIDEDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))), 1);
	brJaguar.Set(((pow((speedAxis - turnAxis) * RSIDEDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))), 1);
	CANJaguar :: UpdateSyncGroup(1);
}

#endif

#ifdef VICTOR
void BenDrive :: tankDrive(float left, float right)
{
	Lvic.Set((pow((left * LVICDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND)));
	Rvic.Set((pow((right * RVICDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND)));
	//SmartDashboard :: Log(pow(left, TANKCURVE), "Left Power");
	//SmartDashboard :: Log(pow(right, TANKCURVE), "Right Power");
}

void BenDrive :: arcadeDrive(float speedAxis, float turnAxis)
{
	Lvic.Set((pow((speedAxis + turnAxis) * LVICDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND)));
	Rvic.Set((pow((speedAxis - turnAxis) * RVICDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND)));
	//SmartDashboard :: Log(pow(speedAxis, TANKCURVE), "Speed Axis");
	//SmartDashboard :: Log(pow(turnAxis, TANKCURVE), "Turn Axis");
}
#endif


