//Robots
#define SIXWHEEL
//#define MECANUM

#define TANKCURVE 3.0

//Port Numbers
#define RSTICK 1
#define LSTICK 2
#define TLJAGUAR 7 
#define TRJAGUAR 6 
#define BLJAGUAR 5
#define BRJAGUAR 8
#define LJAGUAR 5
#define RJAGUAR 6
#define RVIC 2
#define LVIC 1
#define RSIDEDIRECTION -1.0
#define LSIDEDIRECTION 1.0
#define RVICDIRECTION 1.0
#define LVICDIRECTION -1.0
#define DEADBAND 0.005
#define MAX_OUTPUT 1.0 //300
#define PARTICLE_THRESHOLD 10
#define DISTANCE_BETWEEN_WHEELS 19.0 // in inches
#define DIAMETER_OF_WHEEL 8.0 // in inches
#define GEAR_RATIO (36.0 / 17.0)
#define COWCATCHER 1
#define PLUNGER 2
#define PICKUP_RELAY 2
#define PICKUP_SWITCH 1
#define COWCATCHER_SWITCH 2
#define SHOOTER_SWITCH 4
#define PLUNGER_SWITCH 1
#define SHOOTER_TOP_VICTOR 2
#define SHOOTER_BOTTOM_VICTOR 1
#define SHOOTER_TOP_SENSOR 4 // 3
#define SHOOTER_BOTTOM_SENSOR 3 // 4
#define COMPRESSOR_SWITCH 1
#define COMPRESSOR_RELAY 1
#define ADJUST_SWITCH 3
#define SHOOTER_P 0.01
#define SHOOTER_I 0.001
#define SHOOTER_D 0.0
#define SHOOTER_DRIVE_RATIO 0.7
#define SHOOTER_TOLERANCE 3.0 // in percent
#define SHOOTER_PID_CONTROLLER 2
#define MAX_GEARTOOTH_PPS 1200 // maximum number of pulses the geartooth will give in a second
#define SHOT_TIME 0.8
#define TURN_TIME 0.3
#define ILLUMINATOR 3
#define ILLUMINATOR_SWITCH 8
#define AUTONOMOUS_SWITCH 2
#define pi 3.14159265
#define CORNER 0.810
#define CENTER 0.795
#define TIPPER 3
#define TIPPER_SWITCH 6
#define LIGHT_SENSOR 2
#define RAMP_LIGHT 9
#define SHOOTER_LIGHT 10
#define ENCODER_COUNT 250
//9, 10, enhancedio.setdigitaloutput(value), digital input 2 for light sensor
// .3 + 0.650

#ifdef SIXWHEEL
#define JAGUAR
//#define VICTOR
#endif
