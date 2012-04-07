#include "BenDrive.h"
#include <math.h>

// PID constants for position control 100.0, 0.03, 0.01

void BenDrive::enableSpeedControl()
{
	for(int i = 0; i < 2; i++)
	{
		jaguars[i]->ChangeControlMode( xCANJaguar::kSpeed );
		jaguars[i]->ConfigNeutralMode( xCANJaguar::kNeutralMode_Coast );
		jaguars[i]->SetSpeedReference( xCANJaguar::kSpeedRef_QuadEncoder );
		jaguars[i]->ConfigEncoderCodesPerRev( ENCODER_COUNT );  // or 250, or 300?
		jaguars[i]->SetPID( 0.300, 0.003, 0.001 );
		jaguars[i]->Set( 0.0, 0 );
		jaguars[i]->EnableControl();
	}
	printf("Speed control enabled \n");
}

void BenDrive::enablePositionControl()
{
	for(int i = 0; i < 2; i++)
	{
		jaguars[i]->ChangeControlMode( xCANJaguar::kPosition );
		jaguars[i]->ConfigMaxOutputVoltage(8.0);
		jaguars[i]->ConfigNeutralMode( xCANJaguar::kNeutralMode_Brake );
		jaguars[i]->SetPositionReference( xCANJaguar::kPosRef_QuadEncoder );
		jaguars[i]->ConfigEncoderCodesPerRev( ENCODER_COUNT );  // or 250, or 300?
		jaguars[i]->SetPID( 2400.0, 0.005, 0.001 );
		jaguars[i]->Set( 0.0, 0 );
		jaguars[i]->EnableControl(0.0);
	}
	printf("Position control enabled \n");
}

void BenDrive :: enableVoltageControl()
{
	for(int i = 0; i < 2; i++)
	{
		jaguars[i]->ChangeControlMode( xCANJaguar::kPercentVbus );
		jaguars[i]->ConfigNeutralMode( xCANJaguar::kNeutralMode_Coast );
		jaguars[i]->EnableControl();
		jaguars[i]->Set( 0.0F, 0 );
		jaguars[i]->SetExpiration( 0.5 );
		jaguars[i]->Set( 0.0F, 0 );
	}
	printf("Voltage control enabled \n");
}

BenDrive :: BenDrive() :
#ifdef VICTOR
Lvic(LVIC), Rvic(RVIC)
#endif
#ifdef JAGUAR
lJaguar(LJAGUAR), rJaguar(RJAGUAR)
#endif
{
	jaguars[0] = &lJaguar;
	jaguars[1] = &rJaguar;
	//enableSpeedControl();
}

#ifdef JAGUAR
void BenDrive :: tankDrive(float left, float right)
{
	if(right < 0 && (right + DEADBAND) > 0)
		right = 0;
	if(left < 0 && (left + DEADBAND) >  0)
		left = 0;
	lJaguar.Set((pow((left * LSIDEDIRECTION), TANKCURVE))  * MAX_OUTPUT, 1);
	//blJaguar.Set((pow((left * LSIDEDIRECTION), TANKCURVE))  * MAX_OUTPUT, 1);
	rJaguar.Set((pow((right * RSIDEDIRECTION), TANKCURVE)) * MAX_OUTPUT, 1);
	//brJaguar.Set((pow((right * RSIDEDIRECTION), TANKCURVE)) * MAX_OUTPUT, 1);
	xCANJaguar :: UpdateSyncGroup(1);
}
void BenDrive :: arcadeDrive(float speedAxis, float turnAxis)
{
	if(speedAxis < 0 && (speedAxis + DEADBAND) > 0)
		speedAxis = 0;
	if(turnAxis < 0 && (turnAxis + DEADBAND) >  0)
		turnAxis = 0;
	lJaguar.Set((pow((speedAxis + turnAxis) * LSIDEDIRECTION, TANKCURVE)) * MAX_OUTPUT, 1);
	//blJaguar.Set((pow((speedAxis + turnAxis) * LSIDEDIRECTION, TANKCURVE)) * MAX_OUTPUT, 1);
	//trJaguar.Set((pow((speedAxis - turnAxis) * RSIDEDIRECTION, TANKCURVE)) * MAX_OUTPUT, 1);
	rJaguar.Set((pow((speedAxis - turnAxis) * RSIDEDIRECTION, TANKCURVE)) * MAX_OUTPUT, 1);
	xCANJaguar :: UpdateSyncGroup(1);
}

void BenDrive :: positionDrive(float left, float right)
{
	lJaguar.Set((left * LSIDEDIRECTION), 1);
	//blJaguar.Set((left * LSIDEDIRECTION), 1);
	//trJaguar.Set((right * RSIDEDIRECTION), 1);
	rJaguar.Set((right * RSIDEDIRECTION), 1);
	xCANJaguar :: UpdateSyncGroup(1);
}

int BenDrive :: angleDrive(float angle, float tolerance)
{
	float ratio = ((DISTANCE_BETWEEN_WHEELS / DIAMETER_OF_WHEEL) * GEAR_RATIO) / (2 * pi);
	float lAngle = lJaguar.GetPosition() / ratio;
	float rAngle = rJaguar.GetPosition() / ratio;
	printf("lAngle: %g, rAngle: %g \n", lAngle, rAngle);
	if(fabs(lAngle - angle) < tolerance && fabs(rAngle - angle) < tolerance)
		return 1;
	else
	{
		for(int i = 0; i < 2; i++)
		{
			jaguars[i]->Set((angle * ratio), 1);
		}
		xCANJaguar :: UpdateSyncGroup(1);
		return 0;
	}
}

#endif

#ifdef VICTOR
void BenDrive :: tankDrive(float left, float right)
{
	Lvic.Set(pow((left * LVICDIRECTION), TANKCURVE));
	Rvic.Set(pow((right * RVICDIRECTION), TANKCURVE));
	//SmartDashboard :: Log(pow(left, TANKCURVE), "Left Power");
	//SmartDashboard :: Log(pow(right, TANKCURVE), "Right Power");
}

void BenDrive :: arcadeDrive(float speedAxis, float turnAxis)
{
	Lvic.Set(pow((speedAxis + turnAxis) * LVICDIRECTION, TANKCURVE));
	Rvic.Set(pow((speedAxis - turnAxis) * RVICDIRECTION, TANKCURVE));
	//SmartDashboard :: Log(pow(speedAxis, TANKCURVE), "Speed Axis");
	//SmartDashboard :: Log(pow(turnAxis, TANKCURVE), "Turn Axis");
}
#endif


