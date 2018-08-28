#include "hls_video.h"
#define IMG_WIDTH_OR_COLS 320
#define IMG_HEIGHT_OR_ROWS 240

#define KERNEL_DIM 3

#define INPUT_IMAGE_CORE "E:\\Joshua_BTP\\images\\image_320X240.bmp"
#define OUTPUT_IMAGE_CORE "E:\\Joshua_BTP\\images\\image_320X240_filter.bmp"


// use the axi-stream side channel
#include <ap_axi_sdata.h>
typedef ap_axiu<8,2,5,6> uint8_sidechannel;
typedef ap_axiu<32,2,5,6> int32_sidechannel;

short sumWindow(hls::Window<KERNEL_DIM,KERNEL_DIM,short> *window);
unsigned int CEIL(unsigned int value);

// IP core
void doConv(hls::stream<uint8_sidechannel> &instream, hls::stream<int32_sidechannel> &outstream);



