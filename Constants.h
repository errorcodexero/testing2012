//Robots
#define SIXWHEEL
#define MECANUM

#define TANKCURVE 3.0

//Ports Numbers
#define RSTICK 1
#define LSTICK 2
#define RVIC 1
#define LVIC 2

#ifdef SIXWHEEL
#define RVICDIRECTION 1
#define LVICDIRECTION -1
#define DEADBAND 0.05
#endif
