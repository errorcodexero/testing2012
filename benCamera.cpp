#include "benCamera.h"

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
    	writeImage(img, "Processed_Image.bmp", 1);
    	delete mono;
}
	
void benCamera :: setParticles()
{
	biggestArea = 0.0;
	imaqSizeFilter(img, img, 1, 2, IMAQ_KEEP_LARGE, NULL);
	imaqCountParticles(img, 1, &numParticles);
	printf("%d\n", numParticles);
	for(int i = 0; i < (numParticles - 1); i++)
	{
		imaqMeasureParticle(img, i, 0, IMAQ_MT_AREA, &tempParticle.area);
		if(1)
		{
			
		}
	}
}

