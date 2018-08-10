#include <stdio.h>
#include "core.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <hls_opencv.h>

// image file path
#define INPUT_IMAGE_CORE "C:\\Users\\Joshua\\Downloads\\image_320X240.jpg"
#define FILE_HISTOGRAM "histogram.txt"
char outimage[320][240];
int histo[256];
int lutMult[256];

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
	imagesrc = cv::imread(INPUT_IMAGE_CORE,1);
	printf("Image rows:%d Cols:%d\n",imagesrc.rows,imagesrc.cols);
	// convert to grayscale
	cv::cvtColor(imagesrc,imagesrc,CV_BGR2GRAY);


	// define streams for input and output
	hls::stream<uint8_sidechannel> inputstream;

	//iterate on all elements of the image

	//populate the input stream with the image bytes
	for (int idxrows=0;idxrows<imagesrc.rows;idxrows++)
	{
		for(int idxcols=0;idxcols<imagesrc.cols;idxcols++)
		{
			uint8_sidechannel valin;
			valin.data = imagesrc.at<unsigned char>(idxrows,idxcols);
			valin.keep = 1;
			valin.strb=1;
			valin.user=1;
			valin.id=0;
			valin.dest=1;
			inputstream << valin;

		}
	}

	// call the to-be-synthesized function
	doHist(inputstream,histo);

	// save the histogram
	saveHistogram(FILE_HISTOGRAM,histo);
}
