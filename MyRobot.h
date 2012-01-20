// sample robot code
// Steve Tarr - team 1425 mentor - 05-11-2011

#include <WPILib.h>

class MyRobot : public IterativeRobot
{
private:
    // This example assumes tank drive with 2 CIM motors.
    //
    // TBD: Change from Tank to Mecanum drive.
    //
    // TBD: Use shaft encoders for motor rate feedback.
    //
    // TBD: Use accelerometers and gyros for robot motion feedback,
    // instead of or in addition to the shaft encoders.
    //
    // TBD: Add light sensors for line tracking, either during
    // autonomous mode or as directed by a "line lock" switch or
    // a "follow line" button in teleop mode.

    // driver station inputs
    Joystick joy_left,
    	     joy_right;

    // robot outputs
    Victor motor_left,
    	   motor_right;

    // robot control
    RobotDrive drive;
    
    // compressor control
    Compressor pressure;
    
    // pneumatic controls
    Solenoid arm, grabber;
    
    // gun control (PWM output connector to Spike relay)
    Relay gun;
    
public:
    MyRobot();

    void RobotInit();

    void DisabledInit();
    void AutonomousInit();
    void TeleopInit();

    void DisabledPeriodic();
    void AutonomousPeriodic();
    void TeleopPeriodic();

    void DisabledContinuous();
    void AutonomousContinuous();
    void TeleopContinuous();

};

