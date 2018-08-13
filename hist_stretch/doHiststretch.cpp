#include "core.h"

void doHiststretch(hls::stream<uint8_sidechannel> &instream,hls::stream<uint8_sidechannel> &outstream, unsigned char xMin, unsigned char xMax)
{
#pragma HLS INTERFACE axis port=instream
#pragma HLS INTERFACE axis port=outstream
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=xMin bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=xMax bundle=CTRL_BUS

	float xMax_minus_xMin = xMax-xMin;

	for (int idxpixel=0;idxpixel<(320*240);idxpixel++)
	{
#pragma HLS PIPELINE
		//read and cache (block here if FIFO sender is empty)
		uint8_sidechannel currpixelsidechannel = instream.read();
		uint8_sidechannel dataoutsidechannel;

		//get the pixel data
		unsigned char x_t = currpixelsidechannel.data;
		float y_t_float;
		//calculate the histogram stretch
		if (x_t>xMax)
		{
			y_t_float = (x_t-xMax)/2+242;
		}
		else if(x_t>xMin)
		{
			y_t_float = (x_t-xMin)/xMax_minus_xMin*230+13;
		}
		else
		{
			y_t_float = x_t/xMin*13;
		}

		unsigned char y_t =y_t_float;

		//put data on output stream
		dataoutsidechannel.data = y_t;
		dataoutsidechannel.keep = currpixelsidechannel.keep;
		dataoutsidechannel.strb = currpixelsidechannel.strb;
		dataoutsidechannel.user = currpixelsidechannel.user;
		dataoutsidechannel.last = currpixelsidechannel.last;
		dataoutsidechannel.id = currpixelsidechannel.id;
		dataoutsidechannel.dest = currpixelsidechannel.dest;

		//send to the stream (block if FIFO receiver is full)
		outstream.write(dataoutsidechannel);
	}
}