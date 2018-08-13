#include <stdio.h>
#include "core.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <hls_opencv.h>

// image file path
#define INPUT_IMAGE_CORE "C:\\Users\\Joshua\\Downloads\\image_320x240.bmp"
#define OUTPUT_IMAGE_CORE "C:\\Users\\Joshua\\Downloads\\image_320X240_out.bmp"

#define FILE_HISTOGRAM "histogram.txt"
char outimage[240][320];
//int histo[256];
//int lutMult[256];

void saveImage(const std::string path, cv::InputArray inArr)
{
	double min;
	double max;
	cv::minMaxIdx(inArr,&min,&max);
	cv::Mat adjMap;
	cv::convertScaleAbs(inArr,adjMap,255/max);
	cv::imwrite(path,adjMap);
}

void saveHistogram(const char* filename, int *histPointer)
{
	// open file to compare later
	FILE *pfile;
	pfile = fopen(filename,"w");
	if(pfile!=NULL)
	{
		for(int idx=0;idx<256;idx++)
		{
			fprintf(pfile,"Bin[%d]-%d\n",idx,histPointer[idx]);
		}
	}
}

int main()
{
	//Read input image
	printf("Load image %s\n",INPUT_IMAGE_CORE);
	
	cv::Mat imagesrc;
	imagesrc = cv::imread(INPUT_IMAGE_CORE);
	printf("Image rows:%d Cols:%d\n",imagesrc.rows,imagesrc.cols);
	// convert to grayscale
	cv::cvtColor(imagesrc,imagesrc,CV_BGR2GRAY);


	// define streams for input and output
	hls::stream<uint8_sidechannel> inputstream;
	hls::stream<uint8_sidechannel> outputstream;

	//opencv Mat that points to the output array
	cv::Mat imgcvOut(cv::Size(imagesrc.cols,imagesrc.rows),CV_8UC1,outimage,cv::Mat::AUTO_STEP);
	//iterate on all elements of the image

	//populate the input stream with the image bytes
	for (int idxrows=0;idxrows<240;idxrows++)
	{
		for(int idxcols=0;idxcols<320;idxcols++)
		{
			uint8_sidechannel valin;
			valin.data = imagesrc.at<unsigned char>(idxrows,idxcols);
			valin.keep = 1;
			valin.strb=1;
			valin.user=1;
			valin.id=0;
			valin.dest=0;
			inputstream << valin;

		}
	}

	// call the to-be-synthesized function
	doHiststretch(inputstream,outputstream,34,220);

	//populate the output stream with the image bytes
	for (int idxrows=0;idxrows<240;idxrows++)
	{
		for(int idxcols=0;idxcols<320;idxcols++)
		{
			uint8_sidechannel valout;
			outputstream.read(valout);
			outimage[idxrows][idxcols]=valout.data;

		}
	}
	//save image
	saveImage(std::string(OUTPUT_IMAGE_CORE),imgcvOut);
	return 0;
}
