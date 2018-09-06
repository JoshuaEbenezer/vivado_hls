#include "core.h"

void doAniso(AXI_IN_STREAM &instream, AXI_OUT_STREAM &outstream)
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


	unsigned int expArray[256];

	    /*
	        kappa = 30
	        delta_t = 1/7
	        expArray[x] = (x*exp(-(x/kappa)^2))/delta_t * (2^20)
	        this has been scaled by 2 ^ 20
	    */

	expArray[0]   = 0;
	expArray[1]   = 149630;
	expArray[2]   = 298265;
	expArray[3]   = 444918;
	expArray[4]   = 588628;
	expArray[5]   = 728464;
	expArray[6]   = 863538;
	expArray[7]   = 993013;
	expArray[8]   = 1116114;
	expArray[9]   = 1232134;
	expArray[10]   = 1340439;
	expArray[11]   = 1440476;
	expArray[12]   = 1531779;
	expArray[13]   = 1613966;
	expArray[14]   = 1686748;
	expArray[15]   = 1749925;
	expArray[16]   = 1803388;
	expArray[17]   = 1847115;
	expArray[18]   = 1881171;
	expArray[19]   = 1905703;
	expArray[20]   = 1920932;
	expArray[21]   = 1927156;
	expArray[22]   = 1924734;
	expArray[23]   = 1914084;
	expArray[24]   = 1895678;
	expArray[25]   = 1870030;
	expArray[26]   = 1837688;
	expArray[27]   = 1799232;
	expArray[28]   = 1755259;
	expArray[29]   = 1706380;
	expArray[30]   = 1653212;
	expArray[31]   = 1596370;
	expArray[32]   = 1536460;
	expArray[33]   = 1474075;
	expArray[34]   = 1409788;
	expArray[35]   = 1344147;
	expArray[36]   = 1277675;
	expArray[37]   = 1210859;
	expArray[38]   = 1144153;
	expArray[39]   = 1077975;
	expArray[40]   = 1012705;
	expArray[41]   = 948681;
	expArray[42]   = 886205;
	expArray[43]   = 825537;
	expArray[44]   = 766900;
	expArray[45]   = 710480;
	expArray[46]   = 656425;
	expArray[47]   = 604851;
	expArray[48]   = 555839;
	expArray[49]   = 509444;
	expArray[50]   = 465692;
	expArray[51]   = 424581;
	expArray[52]   = 386093;
	expArray[53]   = 350184;
	expArray[54]   = 316797;
	expArray[55]   = 285859;
	expArray[56]   = 257285;
	expArray[57]   = 230980;
	expArray[58]   = 206840;
	expArray[59]   = 184756;
	expArray[60]   = 164617;
	expArray[61]   = 146307;
	expArray[62]   = 129710;
	expArray[63]   = 114711;
	expArray[64]   = 101195;
	expArray[65]   = 89052;
	expArray[66]   = 78174;
	expArray[67]   = 68456;
	expArray[68]   = 59800;
	expArray[69]   = 52111;
	expArray[70]   = 45301;
	expArray[71]   = 39285;
	expArray[72]   = 33986;
	expArray[73]   = 29330;
	expArray[74]   = 25252;
	expArray[75]   = 21688;
	expArray[76]   = 18583;
	expArray[77]   = 15884;
	expArray[78]   = 13545;
	expArray[79]   = 11522;
	expArray[80]   = 9779;
	expArray[81]   = 8279;
	expArray[82]   = 6993;
	expArray[83]   = 5892;
	expArray[84]   = 4954;
	expArray[85]   = 4154;
	expArray[86]   = 3476;
	expArray[87]   = 2901;
	expArray[88]   = 2416;
	expArray[89]   = 2007;
	expArray[90]   = 1664;
	expArray[91]   = 1376;
	expArray[92]   = 1135;
	expArray[93]   = 934;
	expArray[94]   = 767;
	expArray[95]   = 628;
	expArray[96]   = 514;
	expArray[97]   = 419;
	expArray[98]   = 341;
	expArray[99]   = 276;
	expArray[100]   = 224;
	expArray[101]   = 181;
	expArray[102]   = 146;
	expArray[103]   = 117;
	expArray[104]   = 94;
	expArray[105]   = 75;
	expArray[106]   = 60;
	expArray[107]   = 48;
	expArray[108]   = 38;
	expArray[109]   = 30;
	expArray[110]   = 24;
	expArray[111]   = 19;
	expArray[112]   = 15;
	expArray[113]   = 12;
	expArray[114]   = 9;
	expArray[115]   = 7;
	expArray[116]   = 6;
	expArray[117]   = 4;
	expArray[118]   = 3;
	expArray[119]   = 3;
	expArray[120]   = 2;
	expArray[121]   = 2;
	expArray[122]   = 1;
	expArray[123]   = 1;
	expArray[124]   = 1;
	expArray[125]   = 1;
	//for(i=126;i<255;i++)
	//expArray[i]=0;
	expArray[126]   = 0;
	expArray[127]   = 0;
	expArray[128]   = 0;
	expArray[129]   = 0;
	expArray[130]   = 0;
	expArray[131]   = 0;
	expArray[132]   = 0;
	expArray[133]   = 0;
	expArray[134]   = 0;
	expArray[135]   = 0;
	expArray[136]   = 0;
	expArray[137]   = 0;
	expArray[138]   = 0;
	expArray[139]   = 0;
	expArray[140]   = 0;
	expArray[141]   = 0;
	expArray[142]   = 0;
	expArray[143]   = 0;
	expArray[144]   = 0;
	expArray[145]   = 0;
	expArray[146]   = 0;
	expArray[147]   = 0;
	expArray[148]   = 0;
	expArray[149]   = 0;
	expArray[150]   = 0;
	expArray[151]   = 0;
	expArray[152]   = 0;
	expArray[153]   = 0;
	expArray[154]   = 0;
	expArray[155]   = 0;
	expArray[156]   = 0;
	expArray[157]   = 0;
	expArray[158]   = 0;
	expArray[159]   = 0;
	expArray[160]   = 0;
	expArray[161]   = 0;
	expArray[162]   = 0;
	expArray[163]   = 0;
	expArray[164]   = 0;
	expArray[165]   = 0;
	expArray[166]   = 0;
	expArray[167]   = 0;
	expArray[168]   = 0;
	expArray[169]   = 0;
	expArray[170]   = 0;
	expArray[171]   = 0;
	expArray[172]   = 0;
	expArray[173]   = 0;
	expArray[174]   = 0;
	expArray[175]   = 0;
	expArray[176]   = 0;
	expArray[177]   = 0;
	expArray[178]   = 0;
	expArray[179]   = 0;
	expArray[180]   = 0;
	expArray[181]   = 0;
	expArray[182]   = 0;
	expArray[183]   = 0;
	expArray[184]   = 0;
	expArray[185]   = 0;
	expArray[186]   = 0;
	expArray[187]   = 0;
	expArray[188]   = 0;
	expArray[189]   = 0;
	expArray[190]   = 0;
	expArray[191]   = 0;
	expArray[192]   = 0;
	expArray[193]   = 0;
	expArray[194]   = 0;
	expArray[195]   = 0;
	expArray[196]   = 0;
	expArray[197]   = 0;
	expArray[198]   = 0;
	expArray[199]   = 0;
	expArray[200]   = 0;
	expArray[201]   = 0;
	expArray[202]   = 0;
	expArray[203]   = 0;
	expArray[204]   = 0;
	expArray[205]   = 0;
	expArray[206]   = 0;
	expArray[207]   = 0;
	expArray[208]   = 0;
	expArray[209]   = 0;
	expArray[210]   = 0;
	expArray[211]   = 0;
	expArray[212]   = 0;
	expArray[213]   = 0;
	expArray[214]   = 0;
	expArray[215]   = 0;
	expArray[216]   = 0;
	expArray[217]   = 0;
	expArray[218]   = 0;
	expArray[219]   = 0;
	expArray[220]   = 0;
	expArray[221]   = 0;
	expArray[222]   = 0;
	expArray[223]   = 0;
	expArray[224]   = 0;
	expArray[225]   = 0;
	expArray[226]   = 0;
	expArray[227]   = 0;
	expArray[228]   = 0;
	expArray[229]   = 0;
	expArray[230]   = 0;
	expArray[231]   = 0;
	expArray[232]   = 0;
	expArray[233]   = 0;
	expArray[234]   = 0;
	expArray[235]   = 0;
	expArray[236]   = 0;
	expArray[237]   = 0;
	expArray[238]   = 0;
	expArray[239]   = 0;
	expArray[240]   = 0;
	expArray[241]   = 0;
	expArray[242]   = 0;
	expArray[243]   = 0;
	expArray[244]   = 0;
	expArray[245]   = 0;
	expArray[246]   = 0;
	expArray[247]   = 0;
	expArray[248]   = 0;
	expArray[249]   = 0;
	expArray[250]   = 0;
	expArray[251]   = 0;
	expArray[252]   = 0;
	expArray[253]   = 0;
	expArray[254]   = 0;
	expArray[255]   = 0;

	hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC3> img_in(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE grayMat_1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE histeq(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE airlight_initial(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	GRAY_IMAGE img_out1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE img_out2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE img_out3(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE img_out4(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	GRAY_IMAGE airlight(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE histeq_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE histeq_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	GRAY_IMAGE img_out(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

#pragma HLS dataflow


	//defining line buffer
	hls::Window<KERNEL_DIM,KERNEL_DIM,char> left_kernel;
	hls::Window<KERNEL_DIM,KERNEL_DIM,char> right_kernel;
	hls::Window<KERNEL_DIM,KERNEL_DIM,char> up_kernel;
	hls::Window<KERNEL_DIM,KERNEL_DIM,char> down_kernel;


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
  
    hls::Duplicate(grayMat_1,histeq_copy1,histeq_copy2);



    //anisotropic diffusion
    anisotropic_diffusion(histeq_copy1, img_out1,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
    anisotropic_diffusion(img_out1, img_out2,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
    anisotropic_diffusion(img_out2, img_out3,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
    anisotropic_diffusion(img_out3, img_out4,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
    anisotropic_diffusion(img_out4, airlight,left_kernel,right_kernel,up_kernel,down_kernel,expArray);

    hls::Mat2AXIvideo(airlight, outstream);

}

void anisotropic_diffusion(GRAY_IMAGE& img_in, GRAY_IMAGE& img_out,WINDOW left_kernel,WINDOW right_kernel,WINDOW up_kernel,WINDOW down_kernel,unsigned int expArray[256])
{
	GRAY_IMAGE histeq_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE histeq_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE histeq_copy3(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	GRAY_IMAGE histeq_copy1a(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE histeq_copy2a(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	GRAY_IMAGE histeq_copy1b(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE histeq_copy2b(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	GRAY_IMAGE histeq_copy1c(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);


	GRAY_IMAGE left_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE right_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE up_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE down_diff(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	hls::Point_<int> anchor = hls::Point_<int>(-1,-1);

    // anisotropic diffusion
    hls::Duplicate(img_in,histeq_copy1,histeq_copy2);
    hls::Duplicate(histeq_copy2,histeq_copy2a,histeq_copy2b);
    hls::Duplicate(histeq_copy1,histeq_copy1c,histeq_copy1b);
    hls::Duplicate(histeq_copy1c,histeq_copy1a,histeq_copy3);

    // convolve to find difference matrices
    hls::Filter2D(histeq_copy1a,left_diff,left_kernel,anchor);
    hls::Filter2D(histeq_copy1b,right_diff,right_kernel,anchor);
    hls::Filter2D(histeq_copy2a,up_diff,up_kernel,anchor);
    hls::Filter2D(histeq_copy2b,down_diff,down_kernel,anchor);

    hls::Scalar<1,unsigned char> input_val;
    hls::Scalar<1,unsigned char> output_val;

    hls::Scalar<1,unsigned char> left_valOutput;
    hls::Scalar<1,unsigned char> right_valOutput;
    hls::Scalar<1,unsigned char> down_valOutput;
    hls::Scalar<1,unsigned char> up_valOutput;
    hls::Scalar<1,unsigned char> iteration_added;
    ROW: for(int row = 0; row < IMG_HEIGHT_OR_ROWS; row++)
    {
#pragma HLS LOOP_TRIPCOUNT min=1 max=478

    	COL: for(int col = 0; col < IMG_WIDTH_OR_COLS; col++)
    	{
#pragma HLS LOOP_TRIPCOUNT min=1 max=638
#pragma HLS PIPELINE
//#pragma HLS DEPENDENCE

    		histeq_copy3.read(input_val);
    		left_diff.read(left_valOutput);
    		right_diff.read(right_valOutput);
    		down_diff.read(down_valOutput);
    		up_diff.read(up_valOutput);
    	    iteration_added = (expArray[right_valOutput.val[0]]>>20+expArray[left_valOutput.val[0]]>> 20+expArray[down_valOutput.val[0]]>> 20+expArray[up_valOutput.val[0]]>> 20);
    	    output_val = input_val + iteration_added;
    	    img_out.write(output_val);
    	}
    }
}


