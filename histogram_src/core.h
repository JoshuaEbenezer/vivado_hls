// the class stream
#include <hls_stream.h>

// axis side channel stream
#include <ap_axi_sdata.h>
typedef ap_axiu<8,2,5,6> uint8_sidechannel;

void doHist(hls::stream<uint8_sidechannel> &instream, int histo[256]);
