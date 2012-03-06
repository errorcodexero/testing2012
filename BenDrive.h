#include <WPILib.h>
#include "xCanJaguar.h"
#include "Constants.h"

class BenDrive
{
#ifdef VICTOR
	Victor Lvic, Rvic;
#endif
#ifdef JAGUAR
	xCANJaguar tlJaguar, trJaguar, blJaguar, brJaguar;
#endif
	
public:
	BenDrive();
	void tankDrive(float left, float right);
	void arcadeDrive(float speedAxis, float turnAxis);
	void positionDrive(float left, float right); // old, use angleDrive instead
	int angleDrive(float angle, float tolerance);
	void enableSpeedControl();
	void enablePositionControl();
private:
	xCANJaguar* jaguars[4];
};

