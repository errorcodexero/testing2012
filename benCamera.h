#include <WPILib.h>

class benCamera
{
public:
	benCamera();
	void writeImage(Image* img, const char *file, int usepalette);
	void refreshImage();
	void refreshProcessedImage();
	void setParticles();
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
		particle& operator = (const particle& p)
		{
			area = p.area;
			yCenter = p.yCenter;
			xCenter = p.xCenter;
			return *this;
		}		
	};
	
private:
	void errorCheck(int val);
	particle hoopParticle[4];
	AxisCamera &axisCamera;
	HSLImage *image;
	Image* img;
	MonoImage *mono;
	int numParticles;
};
