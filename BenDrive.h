#include <WPILib.h>
#include "Constants.h"

class BenDrive
{
	Victor Lvic, Rvic;
	
	public:
		BenDrive();
		void tankDrive(float left, float right);
		void arcadeDrive(float speedAxis, float turnAxis);
};

