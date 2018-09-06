#include "core.h"

void doConv(AXI_IN_STREAM &instream, AXI_OUT_STREAM &outstream)
{
#pragma HLS INTERFACE axis port=instream
#pragma HLS INTERFACE axis port=outstream
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS

//set_directive_dependence -variable buffer -type inter -dependent false "core/doConv"

	const char kernel_coeff[KERNEL_DIM][KERNEL_DIM]={
			{0,0,0},
			{1,-1,0},
			{0,0,0},
	};



	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC3> img_in(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> grayMat_1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> img_out(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> histeq(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> histeq_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> histeq_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> histeq_copy1a(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> histeq_copy2a(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> histeq_copy1b(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> histeq_copy2b(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> left_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> right_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> up_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> down_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> left_right(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

#pragma HLS dataflow


	//defining line buffer
	hls::Window<KERNEL_DIM,KERNEL_DIM,char> left_kernel;
	hls::Window<KERNEL_DIM,KERNEL_DIM,char> right_kernel;
	hls::Window<KERNEL_DIM,KERNEL_DIM,char> up_kernel;
	hls::Window<KERNEL_DIM,KERNEL_DIM,char> down_kernel;

	hls::Point_<int> anchor = hls::Point_<int>(-1,-1);

	for (int i=0;i<KERNEL_DIM;i++)
	{
	  for (int j=0;j<KERNEL_DIM;j++)
	  {
		  left_kernel.val[i][j]=kernel_coeff[i][j];
		  right_kernel.val[i][j]=kernel_coeff[i][KERNEL_DIM-1-j];
		  up_kernel.val[i][j]=kernel_coeff[j][i];
		  down_kernel.val[i][j]=kernel_coeff[j][KERNEL_DIM-1-i];
	  }
	}
    //take in the video stream
    hls::AXIvideo2Mat(instream, img_in);
	hls::CvtColor<HLS_BGR2GRAY, HLS_8UC3, HLS_8UC1>(img_in, grayMat_1);

    //Apply histogram equalization
    hls::EqualizeHist( grayMat_1,histeq );
    hls::Duplicate(histeq,histeq_copy1,histeq_copy2);
    hls::Duplicate(histeq_copy2,histeq_copy2a,histeq_copy2b);
    hls::Duplicate(histeq_copy1,histeq_copy1a,histeq_copy1b);
//    // convolve to find difference matrices
    hls::Filter2D(histeq_copy1a,left_diff,left_kernel,anchor);

    hls::Filter2D(histeq_copy1b,right_diff,right_kernel,anchor);
    hls::Filter2D(histeq_copy2a,up_diff,up_kernel,anchor);
    hls::Filter2D(histeq_copy2b,down_diff,down_kernel,anchor);
    hls::Mat2AXIvideo(img_out, outstream);




}

