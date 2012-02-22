#include <WPILib.h>
#include <math.h>
#include <vision/RGBImage.h>
#include "Constants.h"

class benCamera
{
public:
	benCamera();
	void writeImage(Image* img, const char *file, int usepalette);
	void refreshImage();
	int setParticles();
	int fastSetParticles();
	void setPosition();
	int getHoopDirection();
	double getDistance();
	double getAngle();
	class particle
	{
	public:
		double yCenter;
		double xCenter;
		double area;
		double leftBound;
		double rightBound;
		double topBound;
		double bottomBound;
		double height;
		double width;
		particle()
		{
			area = 0;
			yCenter = 0;
			xCenter = 0;
			leftBound = 0;
			rightBound = 0;
			topBound = 0;
			bottomBound = 0;
			height = 0;
			width = 0;
		}
		particle& operator = (const particle& p)
		{
			area = p.area;
			yCenter = p.yCenter;
			xCenter = p.xCenter;
			leftBound = p.leftBound;
			rightBound = p.rightBound;
			topBound = p.topBound;
			bottomBound = p.bottomBound;
			height = p.height;
			width = p.width;
			return *this;
		}
	};
	
private:
	int hoopDirection;
	particle hoopParticles[4];
	RGBImage image;
	AxisCamera &axisCamera;
	double distance;
	double angle;
};
