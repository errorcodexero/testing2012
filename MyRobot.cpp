// sample robot code
// Steve Tarr - team 1425 mentor - 05-11-2011

// WPILib Includes
#include <WPILib.h>

// Our Includes
#include "MyRobot.h"


MyRobot::MyRobot() :

    joy_left( 1 ),	// driver station left-hand joystick on USB port 1
    joy_right( 2 ),	// driver station right-hand joystick on USB port 2

    motor_left( 1 ),	// left Victor/CIM on PWM 1
    motor_right( 2 ),	// left Victor/CIM on PWM 2

    drive( motor_left, motor_right ),
    
    pressure( 1, 1 ),	// compressor output, sensor input
    
    arm( 2 ),
    grabber( 3 ),
    
    gun( 2, Relay::kForwardOnly )
{
	;
}

void MyRobot::RobotInit()
{
    drive.StopMotor();
    pressure.Start();
    arm.Set(false);
    grabber.Set(false);
    gun.Set(Relay::kOff);
    
    SmartDashboard::Log("Initialized", "Robot State");
    SmartDashboard::Log( 0.0, "Left" );
    SmartDashboard::Log( 0.0, "Right" );
    SmartDashboard::Log( true, "Compressor" );
    SmartDashboard::Log( false, "Arm" );
    SmartDashboard::Log( false, "Grabber" );
    SmartDashboard::Log( false, "Gun" );

    DriverStationLCD *lcd = DriverStationLCD::GetInstance();
    lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Initialized");
    lcd->UpdateLCD();

    m_watchdog.SetEnabled(true);
}

START_ROBOT_CLASS(MyRobot);

