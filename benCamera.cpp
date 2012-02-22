#include "benCamera.h"

#define CHECK(x) {if(!x){errorCheck(x); printf("Imaq image function failed at line %d \n", __LINE__); return 1;}}

//Constants used for calculation of position
static double pi = 3.14159265;
static double FOV = pi / 4;
static double xResolution = 640;
//static double yResolution = 480;
static double hoopWidthHalf = 39 + 3/8;

int compareHeight(const void * x1, const void * x2)
{
		benCamera :: particle *p1 = (benCamera :: particle *) x1;
		benCamera :: particle *p2 = (benCamera :: particle *) x2;
		if(p1->yCenter < p2->yCenter)
			return 1;
		else if(p1->yCenter == p2->yCenter)
			return 0;
		else
			return -1;
}

int compareArea(const void * x1, const void * x2)
{
		benCamera :: particle *p1 = (benCamera :: particle *) x1;
		benCamera :: particle *p2 = (benCamera :: particle *) x2;
		if(p1->area < p2->area)
			return 1;
		else if(p1->area == p2->area)
			return 0;
		else
			return -1;
}

benCamera :: benCamera() :
	axisCamera(AxisCamera::GetInstance())
{
	angle = 0;
	distance = 0;
	hoopDirection = 0;
	axisCamera.WriteResolution(AxisCamera::kResolution_640x480);
	axisCamera.WriteCompression(20);
	axisCamera.WriteBrightness(50);
}

void errorCheck(int val)
{
	if(!val)
	{
		char *err = imaqGetErrorText(imaqGetLastError());
		printf(err);
		imaqDispose(err);
	}
}

int benCamera :: getHoopDirection()
{
	return hoopDirection;
}

double benCamera :: getDistance()
{
	return distance;
}

double benCamera :: getAngle()
{
	return angle;
}

void benCamera :: writeImage(Image* img, const char *file, int usepalette)
{
    // GACK...
    char path[255];
    // TODO: check string fits... 
    sprintf(path, "%s%s", "/images/", file);

    int width, height;
    imaqGetImageSize(img, &width, &height);
    printf("Writing file %s, width %d heigh %d\n", path, width, height);

    if (usepalette) {
        RGBValue colorTable[256];
        // Priv_SetWriteFileAllowed(1);
        memset(colorTable, 0, sizeof(colorTable));
        colorTable[0].R = 0;
        colorTable[1].R = 255;
        colorTable[0].G = colorTable[1].G = 0;
        colorTable[0].B = colorTable[1].B = 0;
        colorTable[0].alpha = colorTable[1].alpha = 0;

        errorCheck(imaqWriteFile(img, path, colorTable));
    }
    else
        errorCheck(imaqWriteFile(img, path, NULL));
}

void benCamera :: refreshImage()
{
	if (axisCamera.IsFreshImage())
	{
		axisCamera.GetImage(&image);
		//image.LuminanceEqualize();
		//image.Write("/images/Image.bmp");
		setParticles();
	}
}

int benCamera :: setParticles()
{
		int numParticles = 0;
		printf("I has image\n");		
		MonoImage * mono = image.GetBluePlane();
		if(!mono)
			return 1;
		Image* img = mono->GetImaqImage();
		CHECK(imaqThreshold(img, img, 200, 255, 1, 255));
		//BinaryImage* bi = image.ThresholdHSL(0, 255, 0, 255, 180, 255);
		//img = bi->GetImaqImage();
    	//imaqRejectBorder(img, img, 0);
    	CHECK(imaqConvexHull(img, img, 1));
    	CHECK(imaqSizeFilter(img, img, 1, 2, IMAQ_KEEP_LARGE, NULL));
    	//writeImage(img, "Processed_Image.bmp", 1);
    	
    	particle allParticles[256];
    	CHECK(imaqCountParticles(img, 1, &numParticles));
    	if(numParticles > 256)//truncating amount of particles to 256 so memory won't die
    		numParticles = 256;
    	for(int i = 0; i < numParticles; i++)
    	{
    		particle* p = & allParticles[i];
       		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_AREA, &(p->area)));
       		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_CENTER_OF_MASS_X, &(p->xCenter)));
       		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_CENTER_OF_MASS_Y, &(p->yCenter)));
       		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_BOUNDING_RECT_LEFT, &(p->leftBound)));
       		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_BOUNDING_RECT_RIGHT , &(p->rightBound)));
       		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_BOUNDING_RECT_TOP, &(p->topBound))); 
       		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_BOUNDING_RECT_BOTTOM, &(p->bottomBound)));
       		p->height = p->bottomBound - p->topBound;
       		p->width = p->rightBound - p->leftBound;
    	}
    	qsort(allParticles, numParticles, sizeof(particle), compareArea);
    	for(int i = 0; i < 4; i++)
    		hoopParticles[i] = allParticles[i];
    	if((((hoopParticles[2].height - hoopParticles[3].height) / 2) > PARTICLE_THRESHOLD) || (((hoopParticles[2].width - hoopParticles[3].width) / 2) > PARTICLE_THRESHOLD))
    	{
    		if(((hoopParticles[0].xCenter + hoopParticles[1].xCenter + hoopParticles[2].xCenter) / 3) < (xResolution / 2))
    			hoopDirection = -1;
    		else
    			hoopDirection = 1;
    		printf("4th Particle not in field of view. Direction: %d \n", hoopDirection);
    		return 0;
    	}
    	else
    	{
    		hoopDirection = 0;
    		qsort(hoopParticles, 4, sizeof(particle), compareHeight);
    		if(hoopParticles[1].xCenter > hoopParticles[2].xCenter)
    			swap(hoopParticles[1], hoopParticles[2]);	
    		for(int i = 0; i < 4; i++)
    			printf("hoopParticle %d: %g, %g, %g \n", i, hoopParticles[i].area, hoopParticles[i].xCenter, hoopParticles[i].yCenter);
    		//delete bi;
    		setPosition();
    	}
    	delete mono;
    	return 0;
}

int benCamera :: fastSetParticles()
{
	int numParticles = 0;
	printf("I has image\n");		
	MonoImage * mono = image.GetBluePlane();
	if(!mono)
		return 1;
	Image* img = mono->GetImaqImage();
	CHECK(imaqThreshold(img, img, 200, 255, 1, 255));
	//BinaryImage* bi = image.ThresholdHSL(0, 255, 0, 255, 180, 255);
	//img = bi->GetImaqImage();
	//imaqRejectBorder(img, img, 0);
	CHECK(imaqConvexHull(img, img, 1));
	CHECK(imaqSizeFilter(img, img, 1, 2, IMAQ_KEEP_LARGE, NULL));
	//writeImage(img, "Processed_Image.bmp", 1);
	
	double particleArea[256];
	CHECK(imaqCountParticles(img, 1, &numParticles));
	if(numParticles > 256)//truncating amount of particles to 256 so memory won't die
		numParticles = 256;
	for(int i = 0; i < numParticles; i++)
	{
   		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_AREA, &particleArea[i]));
	}
	qsort(particleArea, numParticles, sizeof(double), compareArea);
	for(int i = 0; i < 4; i++)
	{
		hoopParticles[i].area = particleArea[i];
		particle* p = & hoopParticles[i];
   		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_CENTER_OF_MASS_X, &(p->xCenter)));
   		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_CENTER_OF_MASS_Y, &(p->yCenter)));
   		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_BOUNDING_RECT_LEFT, &(p->leftBound)));
   		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_BOUNDING_RECT_RIGHT , &(p->rightBound)));
   		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_BOUNDING_RECT_TOP, &(p->topBound))); 
   		CHECK(imaqMeasureParticle(img, i, 0, IMAQ_MT_BOUNDING_RECT_BOTTOM, &(p->bottomBound)));
   		p->height = p->bottomBound - p->topBound;
   		p->width = p->rightBound - p->leftBound;
	}
	if((((hoopParticles[2].height - hoopParticles[3].height) / 2) > PARTICLE_THRESHOLD) || (((hoopParticles[2].width - hoopParticles[3].width) / 2) > PARTICLE_THRESHOLD))
	{
		if(((hoopParticles[0].xCenter + hoopParticles[1].xCenter + hoopParticles[2].xCenter) / 3) < (xResolution / 2))
			hoopDirection = -1;
		else
			hoopDirection = 1;
		printf("4th Particle not in field of view. Direction: %d \n", hoopDirection);
		return 0;
	}
	else
	{
		hoopDirection = 0;
		qsort(hoopParticles, 4, sizeof(particle), compareHeight);
		if(hoopParticles[1].xCenter > hoopParticles[2].xCenter)
			swap(hoopParticles[1], hoopParticles[2]);	
		for(int i = 0; i < 4; i++)
			printf("hoopParticle %d: %g, %g, %g \n", i, hoopParticles[i].area, hoopParticles[i].xCenter, hoopParticles[i].yCenter);
		//delete bi;
		setPosition();
	}
	delete mono;
	return 0;
}

void benCamera :: setPosition()
{
	double pCenter = ((hoopParticles[0].xCenter + hoopParticles[3].xCenter) / 2);
	double angleLeft = (pCenter - hoopParticles[1].leftBound) * (FOV / xResolution);
	double angleRight = (hoopParticles[2].rightBound - pCenter) * (FOV / xResolution);
	angle = ((xResolution / 2) - pCenter) * (FOV / xResolution);
	printf("values: %g, %g, %g \n", angleLeft, angleRight, angle);
	double leftmostAngle = (pi / 2) - (angleLeft - angle);
	double rightmostAngle = (pi / 2) - (angleRight - angle);
	double calcDistanceLeft = sin(leftmostAngle) * (hoopWidthHalf / sin(angleLeft));
	double calcDistanceRight = sin(rightmostAngle) * (hoopWidthHalf / sin(angleRight));
	distance = (calcDistanceLeft + calcDistanceRight) / 2;
	printf("distances: %g, %g %g \n", calcDistanceLeft, calcDistanceRight, distance);
}
