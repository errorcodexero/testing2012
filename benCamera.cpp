#include "benCamera.h"

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
	axisCamera(AxisCamera::GetInstance()), img()
{
	image = new HSLImage();
	numParticles = 0;
	axisCamera.WriteResolution(AxisCamera::kResolution_640x480);
	axisCamera.WriteCompression(20);
	axisCamera.WriteBrightness(50);
}

void benCamera :: errorCheck(int val)
{
	if(!val)
	{
		char *err = imaqGetErrorText(imaqGetLastError());
		printf(err);
		imaqDispose(err);
	}
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
		axisCamera.GetImage(image);
		image->Write("/images/Image.bmp");
	}
}

void benCamera :: setParticles()
{
		printf("I has image\n");
		MonoImage * mono = image->GetLuminancePlane();
		img = mono->GetImaqImage();
		imaqThreshold(img, img, 200, 255, 1, 255);
    	imaqRejectBorder(img, img, 0);
    	imaqConvexHull(img, img, 0);
    	imaqSizeFilter(img, img, 1, 2, IMAQ_KEEP_LARGE, NULL);
    	writeImage(img, "Processed_Image.bmp", 1);
    	particle allParticles[256];
    	imaqCountParticles(img, 1, &numParticles);
    	if(numParticles > 256)//truncating amount of particles to 256 so memory won't die
    		numParticles = 256;
    	for(int i = 0; i < numParticles; i++)
    	{
    		particle* p = & allParticles[i];
       		imaqMeasureParticle(img, i, 0, IMAQ_MT_AREA, &(p->area));
			imaqMeasureParticle(img, i, 0, IMAQ_MT_CENTER_OF_MASS_X, &(p->xCenter));
			imaqMeasureParticle(img, i, 0, IMAQ_MT_CENTER_OF_MASS_Y, &(p->yCenter));	
    	}
    	qsort(allParticles, numParticles, sizeof(particle), compareArea);
    	for(int i = 0; i < 4; i++)
    		hoopParticles[i] = allParticles[i];
    	qsort(hoopParticles, 4, sizeof(particle), compareHeight);
    	if(hoopParticles[1].xCenter > hoopParticles[2].xCenter)
    	{
    		allParticles[0] = hoopParticles[1];
    		hoopParticles[1] = hoopParticles[2];
    		hoopParticles[2] = allParticles[0];
    	}
    	for(int i = 0; i < 4; i++)
    		printf("hoopParticle %d: %g, %g, %g \n", i, hoopParticles[i].area, hoopParticles[i].xCenter, hoopParticles[i].yCenter);
    		
    	delete mono;
}
