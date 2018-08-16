#include "core.h"

void doConv(hls::stream<uint8_sidechannel> &instream, hls::stream<int8_sidechannel> &outstream, char kernel[KERNEL_DIM*KERNEL_DIM])
{
#pragma HLS INTERFACE axis port=instream
#pragma HLS INTERFACE axis port=outstream
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=operation bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=kernel bundle=KERNEL_BUS


	//defining line buffer
	hls::LineBuffer<KERNEL_DIM,IMG_WIDTH_OR_COLS,unsigned char> lineBuff;
	hls::Window<KERNEL_DIM,KERNEL_DIM,short> window;
	//hls::Window<KERNEL_DIM,KERNEL_DIM,short> left_window;

	//index used to keep track of row,col
	int idxCol = 0;
	int idxRow = 0;
	int pixConvolved = 0;
	// calculate delay to fix line-buffer offset
	int waitTicks = (IMG_WIDTH_OR_COLS*(KERNEL_DIM-1)+KERNEL_DIM)/2;
	int countWait = 0;
	int sentPixels = 0;

	int8_sidechannel dataoutsidechannel;
	uint8_sidechannel currpixelsidechannel;
	//iterate on all pixels
	for (int idxpixel = 0;idxpixel< (IMG_WIDTH_OR_COLS*IMG_HEIGHT_OR_ROWS);idxpixel++)
	{
#pragma HLS PIPELINE
		//read and cache
		currpixelsidechannel = instream.read();

		//get the pixel data
		unsigned char pixelin = currpixelsidechannel.data;


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
							//idxWinCol + pixConvolved will slide the window
							//as the row changes, the windows jumps down
							short pix_val = (short)lineBuff.getval(idxWinRow,idxWinCol+pixConvolved);

							//multiply kernel by the sampled window
							short val = (short)kernel[(idxWinRow*KERNEL_DIM)+idxWinCol]*pix_val;
							window.insert(val,idxWinRow,idxWinCol);
						}
					}
		}

		short valOutput = 0;
		if ((idxRow>=KERNEL_DIM-1) && (idxCol >= KERNEL_DIM-1) && idxCol<IMG_WIDTH_OR_COLS-2 && idxRow<IMG_HEIGHT_OR_ROWS-2)
		{

				//convolution
				valOutput = sumWindow(&window);
				if (valOutput<0)
					valOutput=0;

		}
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
		countWait++;
		if (countWait>waitTicks)
		{
			//put data on output stream
			dataoutsidechannel.data = valOutput;
			dataoutsidechannel.keep = currpixelsidechannel.keep;
			dataoutsidechannel.strb = currpixelsidechannel.strb;
			dataoutsidechannel.user = currpixelsidechannel.user;
			dataoutsidechannel.last = 0;
			dataoutsidechannel.id = currpixelsidechannel.id;
			dataoutsidechannel.dest = currpixelsidechannel.dest;
			outstream.write(dataoutsidechannel);
			sentPixels++;
		}
	}
		for (countWait=0;countWait<waitTicks;countWait++)
		{
			dataoutsidechannel.data = 0;
			dataoutsidechannel.keep = currpixelsidechannel.keep;
			dataoutsidechannel.strb = currpixelsidechannel.strb;
			dataoutsidechannel.user = currpixelsidechannel.user;
			if (countWait<waitTicks-1)
				dataoutsidechannel.last = 0;
			else
				dataoutsidechannel.last = 1;
			dataoutsidechannel.id = currpixelsidechannel.id;
			dataoutsidechannel.dest = currpixelsidechannel.dest;
			outstream.write(dataoutsidechannel);
			sentPixels++;
		}

		//send to the stream (block if FIFO receiver is full)

}


short sumWindow(hls::Window<KERNEL_DIM,KERNEL_DIM,short> *window)
{
	short accumulator=0;
	for (int idxsRow=0;idxsRow<KERNEL_DIM;idxsRow++)
	{
		for(int idxsCol=0;idxsCol<KERNEL_DIM;idxsCol++)
		{
			accumulator = accumulator + (short)window->getval(idxsRow,idxsCol);
		}
	}
	return accumulator;
}
