#include <WPILib.h>
#include "Pickup.h"
#include "Constants.h"

benPickup::benPickup() :
    relay(PICKUP_RELAY, Relay::kBothDirections)
{
	direction = 0;
    stop();
}

benPickup::~benPickup()
{
    stop();
}

void benPickup::setDirection( int d )
{
    direction = d;
    switch (direction) {
    case -1:
	relay.Set(Relay::kReverse);
	break;
    case 0:
	relay.Set(Relay::kOff);
	break;
    case 1:
	relay.Set(Relay::kForward);
	break;
    }
}

int benPickup::getDirection()
{
    return direction;
}

void benPickup::start()
{
    setDirection( 1 );
}

void benPickup::reverse()
{
    setDirection( -1 );
}

void benPickup::stop()
{
    setDirection( 0 );
}

