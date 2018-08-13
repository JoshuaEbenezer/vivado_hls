// the class stream
#include <hls_stream.h>

// axis side channel stream
#include <ap_axi_sdata.h>
typedef ap_axiu<8,2,5,6> uint8_sidechannel;

void doHiststretch(hls::stream<uint8_sidechannel> &instream,hls::stream<uint8_sidechannel> &outstream, unsigned char xMin, unsigned char xMax);
