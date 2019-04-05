#include "hist_core.h"

void histeq(AXI_IN_STREAM &instream, AXI_OUT_STREAM &outstream)
{
#pragma HLS INTERFACE axis port=instream
#pragma HLS INTERFACE axis port=outstream
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS


#pragma HLS dataflow

		COLOR_IMAGE img_in(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		COLOR_IMAGE img_out(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE img_Y(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE img_Cb(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE img_Cr(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE img_out_Y(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);



 //take in the video stream
	    hls::AXIvideo2Mat(instream, img_in);
	    hls::Split(img_in, img_Y, img_Cb,img_Cr);

	    hls::EqualizeHist( img_Y,img_out_Y );

	    hls::Merge(img_out_Y,img_Cb,img_Cr,img_out);

	    hls::Mat2AXIvideo(img_out, outstream);
	}


