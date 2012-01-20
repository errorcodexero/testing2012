// sample robot code
// Steve Tarr - team 1425 mentor - 05-11-2011

// WPILib Includes
#include "IterativeRobot.h"

// Our Includes
#include "MyRobot.h"

void MyRobot::TeleopInit()
{
    drive.StopMotor();
    pressure.Start();
    arm.Set(false);
    grabber.Set(false);
    gun.Set(Relay::kOff);
    
    SmartDashboard::Log("Autonomous", "Robot State");
    SmartDashboard::Log( 0.0, "Left" );
    SmartDashboard::Log( 0.0, "Right" );
    SmartDashboard::Log( true, "Compressor" );
    SmartDashboard::Log( false, "Arm" );
    SmartDashboard::Log( false, "Grabber" );
    SmartDashboard::Log( false, "Gun" );

    DriverStationLCD *lcd = DriverStationLCD::GetInstance();
    lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Teleop Mode");
    lcd->UpdateLCD();
}

void MyRobot::TeleopPeriodic()
{
    float left, right;
    bool trigger;
    
    left = joy_left.GetY() / 2.0F;
    right = joy_right.GetY() / 2.0F;
    drive.TankDrive( left, right );
    SmartDashboard::Log( left, "Left");
    SmartDashboard::Log( right, "Right" );
    
    // analog input 1
    trigger = ( DriverStation::GetInstance()->GetAnalogIn(1) < 0.5F );
    arm.Set( trigger );
    SmartDashboard::Log( trigger, "Arm" );

    // grab/release digital input 6
    
    trigger = DriverStation::GetInstance()->GetDigitalIn( 6 );
    grabber.Set( trigger );
    SmartDashboard::Log( trigger, "Grabber" );
    
    // gun digital input 1
    
    trigger = ! DriverStation::GetInstance()->GetDigitalIn( 1 );
    gun.Set( trigger ? Relay::kOn : Relay::kOff );
    SmartDashboard::Log( trigger, "Grabber" );
    
    m_watchdog.Feed();
}

void MyRobot::TeleopContinuous()
{
    taskDelay(1);		// be nice to other tasks
}
