#include<stdio.h>
#include<opencv2/core/core.hpp>
#include <hls_video.h>
#include "core.h"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <hls_opencv.h>
#include "opencv2/opencv.hpp"


int main()
{

    cv::VideoCapture cap(INPUT_IMAGE_CORE); // open the video
    cv::VideoWriter video(OUTPUT_IMAGE_CORE,CV_FOURCC('M','J','P','G'),15, cv::Size(IMG_WIDTH_OR_COLS,IMG_HEIGHT_OR_ROWS),false);
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    char outimage[IMG_HEIGHT_OR_ROWS][IMG_WIDTH_OR_COLS];
	// OpenCV mat that points to a array

    for(;;)
    {
        cv::Mat imagesrc(IMG_HEIGHT_OR_ROWS,IMG_WIDTH_OR_COLS,CV_8UC3);
    	cv::Mat imgCvOut(IMG_HEIGHT_OR_ROWS,IMG_WIDTH_OR_COLS,CV_8UC1);

		cap>>imagesrc;
	    // If the frame is empty, break immediately
	    if (imagesrc.empty())
	      break;


		//define streams for input and output
		AXI_IN_STREAM inputstream("input_stream");
		AXI_OUT_STREAM outputstream("output_stream");

		cvMat2AXIvideo(imagesrc,inputstream);

		doConv(inputstream,outputstream);
		AXIvideo2cvMat(outputstream, imgCvOut);

		// Write the frame into the file 'outcpp.avi'
		video.write(imgCvOut);
		printf("Finished writing a frame\n");

    }
		//save image out file
	  //release cap and video
      printf("Finished\n");
	  cap.release();
	  video.release();


	return 0;
}
