#include "core.h"

const fixed_exp expArray[256] = {0.0 ,0.14143569053559543 ,0.27451126832923517 ,0.3916847936876692 ,0.4869393079806922 ,0.556286273622432 ,0.5980082794894551 ,0.6126263941844161 ,0.6026199131920554 ,0.5719603708580671 ,0.5255420588163461 ,0.46859572481839434 ,0.40616187202649445 ,0.34267911598698 ,0.28171684184209006 ,0.22585548120399498 ,0.17669654958468506 ,0.13497080205645892 ,0.10070715882596673 ,0.07342644149437969 ,0.052330396824954786 ,0.03646553498974481 ,0.024850741305007938 ,0.01656578371041323 ,0.010803811194666656 ,0.0068944790579561046 ,0.004305708360217049 ,0.0026318367749174503 ,0.0015746761626203145 ,0.0009223236929496827 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};

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
