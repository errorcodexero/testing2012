// sample robot code
// Steve Tarr - team 1425 mentor - 05-11-2011

// WPILib Includes
#include "IterativeRobot.h"

// Our Includes
#include "MyRobot.h"

void MyRobot::AutonomousInit()
{
    drive.StopMotor();
    pressure.Stop();
    arm.Set(false);
    grabber.Set(false);
    gun.Set(Relay::kOff);
    
    SmartDashboard::Log("Autonomous", "Robot State");
    SmartDashboard::Log( 0.0, "Left" );
    SmartDashboard::Log( 0.0, "Right" );
    SmartDashboard::Log( false, "Compressor" );
    SmartDashboard::Log( false, "Arm" );
    SmartDashboard::Log( false, "Grabber" );
    SmartDashboard::Log( false, "Gun" );

    DriverStationLCD *lcd = DriverStationLCD::GetInstance();
    lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Autonomous Mode");
    lcd->UpdateLCD();
}

void MyRobot::AutonomousPeriodic()
{
    m_watchdog.Feed();
}

void MyRobot::AutonomousContinuous()
{
    taskDelay(1);		// be nice to other tasks
}

