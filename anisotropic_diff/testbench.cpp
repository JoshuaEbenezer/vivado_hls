#include<stdio.h>
#include<opencv2/core/core.hpp>
#include <hls_video.h>
#include "core.h"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <hls_opencv.h>



void saveImage(const std::string path, cv::InputArray inArr)
{
	double min;
	double max;
	cv::minMaxIdx(inArr,&min,&max);
	cv::Mat adjMap;
	cv::convertScaleAbs(inArr,adjMap,255/max);
	cv::imwrite(path,adjMap);
}
char outimage[IMG_HEIGHT_OR_ROWS][IMG_WIDTH_OR_COLS];

int main()
{
	for(int iter_count=0;iter_count<5;iter_count++)
	{
		//read input image
		printf("Load image %s in iteration %d\n", INPUT_IMAGE_CORE,iter_count);
		cv::Mat imagesrc;
		imagesrc = cv::imread(INPUT_IMAGE_CORE);
		// convert to grayscale
		cv::cvtColor(imagesrc,imagesrc,CV_BGR2GRAY);
		printf("Image Rows:%d Cols:%d\n", imagesrc.rows,imagesrc.cols);

		//define streams for input and output
		hls::stream<uint8_sidechannel> inputstream;
		hls::stream<int32_sidechannel> outputstream;

		// OpenCV mat that points to a array
		cv::Mat imgCvOut (cv::Size(imagesrc.cols,imagesrc.rows),CV_8UC1, outimage, cv::Mat::AUTO_STEP);

		for(int idxRows=0;idxRows<imagesrc.rows;idxRows++)
		{
			for(int idxCols=0;idxCols<imagesrc.cols;idxCols++)
			{
				uint8_sidechannel valin;
				valin.data = imagesrc.at<unsigned char>(idxRows,idxCols);
				valin.keep = 1;
				valin.keep = 1;
				valin.strb=1;
				valin.user=1;
				valin.id=0;
				valin.dest=0;
				inputstream << valin;
			}
		}
		printf("Calling core function\n");
		doConv(inputstream,outputstream);
		printf("Core function ended\n");

		for (int idxRows=0;idxRows<imagesrc.rows;idxRows++)
		{
			for (int idxCols=0;idxCols<imagesrc.cols;idxCols++)
			{
				int32_sidechannel valout;
				outputstream.read(valout);
				outimage[idxRows][idxCols]=valout.data;
			}
		}

		//save image out file
		printf("Saving image\n");
		saveImage(std::string(INPUT_IMAGE_CORE),imgCvOut);
	}
	return 0;
}
