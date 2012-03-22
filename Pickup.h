#include <WPILib.h>

class benPickup
{
public:
    benPickup();
    ~benPickup();

    void start();
    void reverse();
    void stop();

    void setDirection( int d );
    int getDirection();

    // TBD: add e.g. IsBallInPosition

private:
    // motor controller
    Relay relay;

    // runtime control
    int direction;	// -1 reverse, 0 stopped, 1 forward
};
