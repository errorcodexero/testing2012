#include <WPILib.h>
#include "Constants.h"

class BenDrive
{
#ifdef VICTOR
	Victor Lvic, Rvic;
#endif
#ifdef JAGUAR
	CANJaguar tlJaguar, trJaguar, blJaguar, brJaguar;
#endif
	
public:
	BenDrive();
	void tankDrive(float left, float right);
	void arcadeDrive(float speedAxis, float turnAxis);
};

