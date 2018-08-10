#include "core.h"

void doHist(hls::stream<uint8_sidechannel> &instream,int histo[256])
{
#pragma HLS INTERFACE axis port=instream
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS INTERFACE bram port=histo

	//Initialize to zero
	for (int idxhist=0;idxhist<256;idxhist++)
	{
	#pragma HLS PIPELINE
		histo[idxhist]=0;
	}
	
	//iterate over stream
	for (int idxpixel=0;idxpixel<(320*240);idxpixel++)
	{
		//read and cache
		uint8_sidechannel currpixelsidechannel = instream.read();
		
		//calculate histogram
		histo[currpixelsidechannel.data]+=1;
	}
	
}		
	
	
