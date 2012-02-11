#include <WPILib.h>
#include <math.h>

class benCamera
{
public:
	benCamera();
	void writeImage(Image* img, const char *file, int usepalette);
	void refreshImage();
	void setParticles();
	void setPosition();
	class particle
	{
	public:
		double yCenter;
		double xCenter;
		double area;
		double leftBound;
		double rightBound;
		particle()
		{
			area = 0;
			yCenter = 0;
			xCenter = 0;
			leftBound = 0;
			rightBound = 0;
		}
		particle& operator = (const particle& p)
		{
			area = p.area;
			yCenter = p.yCenter;
			xCenter = p.xCenter;
			leftBound = p.leftBound;
			rightBound = p.rightBound;
			return *this;
		}
	};
	
private:
	void errorCheck(int val);
	particle hoopParticles[4];
	AxisCamera &axisCamera;
	HSLImage image;
	Image* img;
	MonoImage *mono;
	int numParticles;
};
