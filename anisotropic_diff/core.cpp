#include "core.h"

void doConv(hls::stream<uint8_sidechannel> &instream, hls::stream<int32_sidechannel> &outstream)
{
#pragma HLS INTERFACE axis port=instream
#pragma HLS INTERFACE axis port=outstream
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
//set_directive_dependence -variable buffer -type inter -dependent false "core/doConv"

	char left_kernel[KERNEL_DIM*KERNEL_DIM]={
			0,0,0,
			-1,1,0,
			0,0,0,
	};
	char right_kernel[KERNEL_DIM*KERNEL_DIM]={
			0,0,0,
			0,1,-1,
			0,0,0,
	};
	char up_kernel[KERNEL_DIM*KERNEL_DIM]={
			0,-1,0,
			0,1,0,
			0,0,0,
	};
	char down_kernel[KERNEL_DIM*KERNEL_DIM]={
			0,0,0,
			0,1,0,
			0,-1,0,
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


	//defining line buffer
	hls::LineBuffer<KERNEL_DIM,IMG_WIDTH_OR_COLS,unsigned char> lineBuff;
	hls::Window<KERNEL_DIM,KERNEL_DIM,short> left_window;
	hls::Window<KERNEL_DIM,KERNEL_DIM,short> right_window;
	hls::Window<KERNEL_DIM,KERNEL_DIM,short> up_window;
	hls::Window<KERNEL_DIM,KERNEL_DIM,short> down_window;
	//hls::Window<KERNEL_DIM,KERNEL_DIM,short> left_window;

	//index used to keep track of row,col
	int idxCol = 0;
	int idxRow = 0;
	int pixConvolved = 0;
	// calculate delay to fix line-buffer offset


	int32_sidechannel dataoutsidechannel;
	uint8_sidechannel currpixelsidechannel;
	unsigned int valOutput = 0;
	//iterate on all pixels
	for (int idxpixel = 0;idxpixel< (IMG_WIDTH_OR_COLS*IMG_HEIGHT_OR_ROWS);idxpixel++)
	{
#pragma HLS PIPELINE

		//read and cache
		currpixelsidechannel = instream.read();

		//get the pixel data
		unsigned char pixelin = currpixelsidechannel.data;
		valOutput = 0;

		short left_valOutput = 0;
		short right_valOutput = 0;
		short up_valOutput = 0;
		short down_valOutput = 0;
		//put data on the line-buffer
		lineBuff.shift_up(idxCol);
		lineBuff.insert_top(pixelin,idxCol);

		if ((idxRow>=KERNEL_DIM-1) && (idxCol >= KERNEL_DIM-1) && idxCol<IMG_WIDTH_OR_COLS-2 && idxRow<IMG_HEIGHT_OR_ROWS-2)
		{
			//put data on the window and multiply it with the kernel
			for (int idxWinRow=0;idxWinRow<KERNEL_DIM;idxWinRow++)
			{
				for (int idxWinCol=0;idxWinCol<KERNEL_DIM;idxWinCol++)
				{
//#pragma HLS DEPENDENCE variable=lineBuff inter false

					//idxWinCol + pixConvolved will slide the window
					//as the row changes, the windows jumps down
					short pix_val = (short)lineBuff.getval(idxWinRow,idxWinCol+pixConvolved);

					//multiply kernel by the sampled window
					short left_val = (short)left_kernel[(idxWinRow*KERNEL_DIM)+idxWinCol]*pix_val;
					short right_val = (short)right_kernel[(idxWinRow*KERNEL_DIM)+idxWinCol]*pix_val;
					short up_val = (short)up_kernel[(idxWinRow*KERNEL_DIM)+idxWinCol]*pix_val;
					short down_val = (short)down_kernel[(idxWinRow*KERNEL_DIM)+idxWinCol]*pix_val;

					left_window.insert(left_val,idxWinRow,idxWinCol);
					right_window.insert(right_val,idxWinRow,idxWinCol);
					up_window.insert(up_val,idxWinRow,idxWinCol);
					down_window.insert(down_val,idxWinRow,idxWinCol);
				}
			}
		//convolution
		left_valOutput = sumWindow(&left_window);
		right_valOutput = sumWindow(&right_window);
		up_valOutput = sumWindow(&up_window);
		down_valOutput = sumWindow(&down_window);

		if (left_valOutput<0)
			left_valOutput=-left_valOutput;
		if (right_valOutput<0)
			right_valOutput=-right_valOutput;
		if (up_valOutput<0)
			up_valOutput=-up_valOutput;
		if (down_valOutput<0)
			down_valOutput=-down_valOutput;
		}

		unsigned int iteration_added = expArray[right_valOutput]+expArray[left_valOutput]+expArray[down_valOutput]+expArray[up_valOutput];
		valOutput = CEIL(pixelin + (iteration_added >> 20));

		pixConvolved++;
		//row and pixel index for line buffer
		if (idxCol<IMG_WIDTH_OR_COLS-1)
		{
			idxCol++;
		}
		//next row
		else
		{

			idxCol=0;
			idxRow++;
			pixConvolved = 0;
		}
		//put data on output stream
		dataoutsidechannel.data = valOutput;
		dataoutsidechannel.keep = currpixelsidechannel.keep;
		dataoutsidechannel.strb = currpixelsidechannel.strb;
		dataoutsidechannel.user = currpixelsidechannel.user;
		dataoutsidechannel.last = currpixelsidechannel.last;
		dataoutsidechannel.id = currpixelsidechannel.id;
		dataoutsidechannel.dest = currpixelsidechannel.dest;
		outstream.write(dataoutsidechannel);

	}


}


unsigned int CEIL(unsigned int value)
{
	if(value>255)
		return 255;
	else
		return value;
}
short sumWindow(hls::Window<KERNEL_DIM,KERNEL_DIM,short> *window)
{
	short accumulator=0;
	for (int idxsRow=0;idxsRow<KERNEL_DIM;idxsRow++)
	{
		for(int idxsCol=0;idxsCol<KERNEL_DIM;idxsCol++)
		{
//#pragma HLS PIPELINE
			accumulator = accumulator + (short)window->getval(idxsRow,idxsCol);
		}
	}
	return accumulator;
}
