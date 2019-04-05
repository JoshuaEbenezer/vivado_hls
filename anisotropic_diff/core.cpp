#include "core.h"


void aniso_filter(GRAY_IMAGE& imgin_copy1,GRAY_IMAGE& left_diff,GRAY_IMAGE& right_diff,GRAY_IMAGE& up_diff,GRAY_IMAGE& down_diff)
{
#pragma HLS inline region recursive

	#pragma HLS DATAFLOW





	//defining line buffer
	unsigned char lineBuff[IMG_WIDTH_OR_COLS];



	hls::Scalar<1,unsigned char> in_val;

	hls::Scalar<1,unsigned char> left_val;
	hls::Scalar<1,unsigned char> right_val;
	hls::Scalar<1,unsigned char> up_val;
	hls::Scalar<1,unsigned char> down_val;


	unsigned char hwin[3]={0,0,0};

	// convolution
	// go through this carefully to understand this
	HConvRow:for(int row = 0; row < 478; row++)
		{
#pragma HLS LOOP_TRIPCOUNT min=478 max=478

			HconvCol:for(int col = 0; col < 638; col++)
			{
#pragma HLS LOOP_TRIPCOUNT min=638 max=638

				#pragma HLS PIPELINE
				#pragma HLS loop_flatten

				#pragma HLS DEPENDENCE variable=lineBuff inter false
				#pragma HLS DEPENDENCE variable=down_diff inter false
				#pragma HLS DEPENDENCE variable=up_diff inter false
				#pragma HLS DEPENDENCE variable=right_diff inter false
				#pragma HLS DEPENDENCE variable=left_diff inter false

				in_val = imgin_copy1.read();

				// vertical convolution




//				lineBuff[0][col]=lineBuff[1][col];
//				lineBuff[1][col] = in_val.val[0];

				if(row==0)
				{
					lineBuff[col]=in_val.val[0];
					up_val = 0;
				}
				else
				{
					up_val = (in_val.val[0]-lineBuff[col])>0?(in_val.val[0]-lineBuff[col]):(lineBuff[col]-in_val.val[0]);
					down_val = up_val;
					down_diff.write(down_val);
					lineBuff[col]=in_val.val[0];
				}
				up_diff.write(up_val);
					// horizontal convolution

				if(col==0)
				{
					left_val = 0;
				}
				else
				{
					left_val = (in_val.val[0]-lineBuff[col-1])>0?in_val.val[0]-lineBuff[col-1]:-in_val.val[0]+lineBuff[col-1];
					right_val = left_val;
					right_diff.write(right_val);

					if(col==637)
					{
						right_val = 0;
						right_diff.write(right_val);
					}

				}
				left_diff.write(left_val);


			}
		}

}

void anisotropic_diffusion(GRAY_IMAGE& img_in, GRAY_IMAGE& img_out,const fixed_exp expArray5[])
{


	GRAY_IMAGE left_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE right_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE up_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE down_diff(IMG_HEIGHT_OR_ROWS-1, IMG_WIDTH_OR_COLS);

	GRAY_IMAGE imgin_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE imgin_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

    hls::Duplicate(img_in,imgin_copy1,imgin_copy2);

	aniso_filter(imgin_copy1,left_diff,right_diff,up_diff,down_diff);


    hls::Scalar<1,unsigned char> input_val;
    hls::Scalar<1,unsigned char> output_val;

    hls::Scalar<1,unsigned char> left_valOutput;
    hls::Scalar<1,unsigned char> right_valOutput;
    hls::Scalar<1,unsigned char> down_valOutput;
    hls::Scalar<1,unsigned char> up_valOutput;
    hls::Scalar<1,fixed_exp_sum> iteration_added;

#pragma HLS dataflow
    ROW: for(int row = 0; row < IMG_HEIGHT_OR_ROWS; row++)
    {
#pragma HLS LOOP_TRIPCOUNT min=478 max=478

    	COL: for(int col = 0; col < IMG_WIDTH_OR_COLS; col++)
    	{
#pragma HLS LOOP_TRIPCOUNT min=638 max=638
#pragma HLS PIPELINE
#pragma HLS dependence variable=imgin_copy2 inter false
#pragma HLS dependence variable=left_diff inter false
#pragma HLS dependence variable=right_diff inter false
#pragma HLS dependence variable=down_diff inter false
#pragma HLS dependence variable=up_diff inter false
#pragma HLS dependence variable=iteration_added inter false
#pragma HLS dependence variable=output_val inter false
#pragma HLS dependence variable=img_out inter false


    		imgin_copy2.read(input_val);
    		left_diff.read(left_valOutput);
    		right_diff.read(right_valOutput);
    		if(row==IMG_HEIGHT_OR_ROWS-1)
    		{
    			down_valOutput = 0;
    		}
    		else
    		{
        		down_diff.read(down_valOutput);
    		}
    		up_diff.read(up_valOutput);

    	    iteration_added = (expArray5[right_valOutput.val[0]]+expArray5[left_valOutput.val[0]]+expArray5[down_valOutput.val[0]]+expArray5[up_valOutput.val[0]]);
    	    output_val = (unsigned char)(input_val.val[0] + (unsigned char)(iteration_added.val[0])) ;
    	    img_out.write(output_val);
    	}
    }
}
