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
#define RVIC 2
#define LVIC 1
#define RSIDEDIRECTION -1.0
#define LSIDEDIRECTION 1.0
#define RVICDIRECTION 1.0
#define LVICDIRECTION -1.0
#define DEADBAND 0.05
#define MAX_OUTPUT 300
#define PARTICLE_THRESHOLD 10
#define DISTANCE_BETWEEN_WHEELS 19.0 // in inches
#define DIAMETER_OF_WHEEL 8.0 // in inches
#define GEAR_RATIO (36.0 / 16.0)

#ifdef SIXWHEEL
#define JAGUAR
//#define VICTOR
#endif
