#include "hls_video.h"
#include <hls_stream.h>
#include <hls/hls_video_types.h>
#include <stdint.h>
#include <ap_fixed.h>

// use the axi-stream side channel
#include <ap_axi_sdata.h>
#include <ap_fixed.h>

#define IMG_WIDTH_OR_COLS 638
#define IMG_HEIGHT_OR_ROWS 478

typedef hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC1> GRAY_IMAGE;
typedef hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC3> COLOR_IMAGE;

typedef hls::stream<ap_axiu<24,1,1,1> >			AXI_IN_STREAM;
typedef hls::stream<ap_axiu<24,1,1,1> >			AXI_OUT_STREAM;

void histeq(AXI_IN_STREAM &instream, AXI_OUT_STREAM &outstream);
