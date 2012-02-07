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

void benCamera :: refreshProcessedImage()
{
		printf("I has image\n");
		MonoImage * mono = image->GetLuminancePlane();
		img = mono->GetImaqImage();
		imaqThreshold(img, img, 200, 255, 1, 255);
    	imaqRejectBorder(img, img, 0);
    	imaqConvexHull(img, img, 0);
    	imaqSizeFilter(img, img, 1, 2, IMAQ_KEEP_LARGE, NULL);
    	writeImage(img, "Processed_Image.bmp", 1);
}
	
void benCamera :: setParticles()
{
	int k = 0;
	particle tempParticle;
	errorCheck(imaqCountParticles(img, 1, &numParticles));
	printf("numParticles: %d\n", numParticles);
	for(int i = 0; i < (numParticles - 1); i++)
	{
		imaqMeasureParticle(img, i, 0, IMAQ_MT_AREA, &tempParticle.area);
		for(int j = 0; j < 4; j++)
		{
			if(hoopParticle[k].area > tempParticle.area)
			{
				hoopParticle[k].area = tempParticle.area;
				imaqMeasureParticle(img, i, 0, IMAQ_MT_CENTER_OF_MASS_X, &hoopParticle[k].xCenter);
				imaqMeasureParticle(img, i, 0, IMAQ_MT_CENTER_OF_MASS_Y, &hoopParticle[k].yCenter);		
			}
			k = (k < 4) ? k + 1 : 0;
		}
	}
	qsort(hoopParticle, 4, sizeof(particle), compareHeight); //x-axis is normal, y-axis is inverted
	if(hoopParticle[1].xCenter < hoopParticle[2].xCenter)
	{
		tempParticle = hoopParticle[1];
		hoopParticle[1] = hoopParticle[2];
		hoopParticle[2] = tempParticle;
	}
	else
	{
		tempParticle = hoopParticle[2];
		hoopParticle[2] = hoopParticle[1];
		hoopParticle[1] = tempParticle;
	}
	for(int i = 0; i < 4; i++)
		printf("hoopParticle %d: %g \n", i, hoopParticle[i].yCenter);
	delete mono;
}

