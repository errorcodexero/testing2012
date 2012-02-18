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
#define RSIDEDIRECTION -1
#define LSIDEDIRECTION 1
#define RVICDIRECTION 1
#define LVICDIRECTION -1
#define DEADBAND 0.05
#define MAX_OUTPUT 300
#define PARTICLE_THRESHOLD 10

#ifdef SIXWHEEL
#define JAGUAR
//#define VICTOR
#endif
