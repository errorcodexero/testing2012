#include <WPILib.h>

class benCamera
{
public:
	benCamera();
	void writeImage(Image* img, const char *file, int usepalette);
	void refreshImage();
	void refreshProcessedImage();
	void setParticles();
	
private:
	void errorCheck(int val);
	class particle
	{
	public:
		double yCenter;
		double xCenter;
		double area;
		particle()
		{
			area = 0;
			yCenter = 0;
			xCenter = 0;
		}
	};
	particle hoopParticle[4];
	particle tempParticle;
	AxisCamera &axisCamera;
	HSLImage *image;
	Image* img;
	int numParticles;
	double biggestArea;
};
