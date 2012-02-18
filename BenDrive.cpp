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
	jaguars[0] = &tlJaguar;
	jaguars[1] = &trJaguar;
	jaguars[2] = &blJaguar;
	jaguars[3] = &brJaguar;
	EnableSpeedControl();
}

void BenDrive::EnableSpeedControl()
{
	for(int i = 0; i < 4; i++)
	{
		jaguars[i]->ChangeControlMode( CANJaguar::kSpeed );
		jaguars[i]->ConfigNeutralMode( CANJaguar::kNeutralMode_Coast );
		jaguars[i]->SetSpeedReference( CANJaguar::kSpeedRef_QuadEncoder );
		jaguars[i]->ConfigEncoderCodesPerRev( 360 );  // or 250, or 300?
		jaguars[i]->SetPID( 100.0, 0.003, 0.001 );
		jaguars[i]->Set( 0.0, 0 );
		jaguars[i]->EnableControl();
	}
}

#ifdef JAGUAR
void BenDrive :: tankDrive(float left, float right)
{
	tlJaguar.Set(((pow((left * LSIDEDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))) * MAX_OUTPUT, 1);
	blJaguar.Set(((pow((left * LSIDEDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))) * MAX_OUTPUT, 1);
	trJaguar.Set(((pow((right * RSIDEDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))) * MAX_OUTPUT, 1);
	brJaguar.Set(((pow((right * RSIDEDIRECTION), TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))) * MAX_OUTPUT, 1);
	CANJaguar :: UpdateSyncGroup(1);
}
void BenDrive :: arcadeDrive(float speedAxis, float turnAxis)
{
	tlJaguar.Set(((pow((speedAxis + turnAxis) * LSIDEDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))) * MAX_OUTPUT, 1);
	blJaguar.Set(((pow((speedAxis + turnAxis) * LSIDEDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))) * MAX_OUTPUT, 1);
	trJaguar.Set(((pow((speedAxis - turnAxis) * RSIDEDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))) * MAX_OUTPUT, 1);
	brJaguar.Set(((pow((speedAxis - turnAxis) * RSIDEDIRECTION, TANKCURVE) + DEADBAND) * (1.0 / (1.0 + DEADBAND))) * MAX_OUTPUT, 1);
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


