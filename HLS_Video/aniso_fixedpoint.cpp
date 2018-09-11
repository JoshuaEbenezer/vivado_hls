#include "core.h"

void doConv(AXI_IN_STREAM &instream, AXI_OUT_STREAM &outstream)
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


	fixed7 expArray[256];

	    /*
	        kappa = 30
	        lambda = 1/7
	        expArray[x] = (x*exp(-(x/kappa)^2))*lambda
	    */

	expArray[ 0 ]= 0.0000000 ;
	expArray[ 1 ]= 0.1426985 ;
	expArray[ 2 ]= 0.2844473 ;
	expArray[ 3 ]= 0.4243071 ;
	expArray[ 4 ]= 0.5613596 ;
	expArray[ 5 ]= 0.6947175 ;
	expArray[ 6 ]= 0.8235338 ;
	expArray[ 7 ]= 0.9470111 ;
	expArray[ 8 ]= 1.0644096 ;
	expArray[ 9 ]= 1.1750544 ;
	expArray[ 10 ]= 1.2783419 ;
	expArray[ 11 ]= 1.3737451 ;
	expArray[ 12 ]= 1.4608179 ;
	expArray[ 13 ]= 1.5391979 ;
	expArray[ 14 ]= 1.6086083 ;
	expArray[ 15 ]= 1.6688588 ;
	expArray[ 16 ]= 1.7198449 ;
	expArray[ 17 ]= 1.7615464 ;
	expArray[ 18 ]= 1.7940248 ;
	expArray[ 19 ]= 1.8174196 ;
	expArray[ 20 ]= 1.8319440 ;
	expArray[ 21 ]= 1.8378792 ;
	expArray[ 22 ]= 1.8355690 ;
	expArray[ 23 ]= 1.8254130 ;
	expArray[ 24 ]= 1.8078597 ;
	expArray[ 25 ]= 1.7833992 ;
	expArray[ 26 ]= 1.7525560 ;
	expArray[ 27 ]= 1.7158811 ;
	expArray[ 28 ]= 1.6739452 ;
	expArray[ 29 ]= 1.6273310 ;
	expArray[ 30 ]= 1.5766262 ;
	expArray[ 31 ]= 1.5224171 ;
	expArray[ 32 ]= 1.4652824 ;
	expArray[ 33 ]= 1.4057872 ;
	expArray[ 34 ]= 1.3444781 ;
	expArray[ 35 ]= 1.2818788 ;
	expArray[ 36 ]= 1.2184856 ;
	expArray[ 37 ]= 1.1547648 ;
	expArray[ 38 ]= 1.0911493 ;
	expArray[ 39 ]= 1.0280373 ;
	expArray[ 40 ]= 0.9657904 ;
	expArray[ 41 ]= 0.9047326 ;
	expArray[ 42 ]= 0.8451505 ;
	expArray[ 43 ]= 0.7872933 ;
	expArray[ 44 ]= 0.7313730 ;
	expArray[ 45 ]= 0.6775664 ;
	expArray[ 46 ]= 0.6260157 ;
	expArray[ 47 ]= 0.5768304 ;
	expArray[ 48 ]= 0.5300896 ;
	expArray[ 49 ]= 0.4858440 ;
	expArray[ 50 ]= 0.4441180 ;
	expArray[ 51 ]= 0.4049124 ;
	expArray[ 52 ]= 0.3682067 ;
	expArray[ 53 ]= 0.3339616 ;
	expArray[ 54 ]= 0.3021215 ;
	expArray[ 55 ]= 0.2726168 ;
	expArray[ 56 ]= 0.2453663 ;
	expArray[ 57 ]= 0.2202793 ;
	expArray[ 58 ]= 0.1972576 ;
	expArray[ 59 ]= 0.1761974 ;
	expArray[ 60 ]= 0.1569912 ;
	expArray[ 61 ]= 0.1395293 ;
	expArray[ 62 ]= 0.1237011 ;
	expArray[ 63 ]= 0.1093966 ;
	expArray[ 64 ]= 0.0965072 ;
	expArray[ 65 ]= 0.0849267 ;
	expArray[ 66 ]= 0.0745522 ;
	expArray[ 67 ]= 0.0652848 ;
	expArray[ 68 ]= 0.0570299 ;
	expArray[ 69 ]= 0.0496974 ;
	expArray[ 70 ]= 0.0432024 ;
	expArray[ 71 ]= 0.0374653 ;
	expArray[ 72 ]= 0.0324114 ;
	expArray[ 73 ]= 0.0279717 ;
	expArray[ 74 ]= 0.0240820 ;
	expArray[ 75 ]= 0.0206834 ;
	expArray[ 76 ]= 0.0177219 ;
	expArray[ 77 ]= 0.0151481 ;
	expArray[ 78 ]= 0.0129171 ;
	expArray[ 79 ]= 0.0109885 ;
	expArray[ 80 ]= 0.0093256 ;
	expArray[ 81 ]= 0.0078955 ;
	expArray[ 82 ]= 0.0066689 ;
	expArray[ 83 ]= 0.0056195 ;
	expArray[ 84 ]= 0.0047240 ;
	expArray[ 85 ]= 0.0039619 ;
	expArray[ 86 ]= 0.0033149 ;
	expArray[ 87 ]= 0.0027670 ;
	expArray[ 88 ]= 0.0023042 ;
	expArray[ 89 ]= 0.0019143 ;
	expArray[ 90 ]= 0.0015867 ;
	expArray[ 91 ]= 0.0013121 ;
	expArray[ 92 ]= 0.0010824 ;
	expArray[ 93 ]= 0.0008909 ;
	expArray[ 94 ]= 0.0007315 ;
	expArray[ 95 ]= 0.0005993 ;
	expArray[ 96 ]= 0.0004898 ;
	expArray[ 97 ]= 0.0003994 ;
	expArray[ 98 ]= 0.0003249 ;
	expArray[ 99 ]= 0.0002637 ;
	expArray[ 100 ]= 0.0002135 ;
	expArray[ 101 ]= 0.0001725 ;
	expArray[ 102 ]= 0.0001390 ;
	expArray[ 103 ]= 0.0001118 ;
	expArray[ 104 ]= 0.0000897 ;
	expArray[ 105 ]= 0.0000718 ;
	expArray[ 106 ]= 0.0000573 ;
	expArray[ 107 ]= 0.0000457 ;
	expArray[ 108 ]= 0.0000363 ;
	expArray[ 109 ]= 0.0000288 ;
	expArray[ 110 ]= 0.0000228 ;
	expArray[ 111 ]= 0.0000180 ;
	expArray[ 112 ]= 0.0000142 ;
	expArray[ 113 ]= 0.0000111 ;
	expArray[ 114 ]= 0.0000087 ;
	expArray[ 115 ]= 0.0000068 ;
	expArray[ 116 ]= 0.0000053 ;
	expArray[ 117 ]= 0.0000041 ;
	expArray[ 118 ]= 0.0000032 ;
	expArray[ 119 ]= 0.0000025 ;
	expArray[ 120 ]= 0.0000019 ;
	expArray[ 121 ]= 0.0000015 ;
	expArray[ 122 ]= 0.0000011 ;
	expArray[ 123 ]= 0.0000009 ;
	expArray[ 124 ]= 0.0000007 ;
	expArray[ 125 ]= 0.0000005 ;
	expArray[ 126 ]= 0.0000004 ;
	expArray[ 127 ]= 0.0000003 ;
	expArray[ 128 ]= 0.0000000 ;
	expArray[ 129 ]= 0.0000000 ;
	expArray[ 130 ]= 0.0000000 ;
	expArray[ 131 ]= 0.0000000 ;
	expArray[ 132 ]= 0.0000000 ;
	expArray[ 133 ]= 0.0000000 ;
	expArray[ 134 ]= 0.0000000 ;
	expArray[ 135 ]= 0.0000000 ;
	expArray[ 136 ]= 0.0000000 ;
	expArray[ 137 ]= 0.0000000 ;
	expArray[ 138 ]= 0.0000000 ;
	expArray[ 139 ]= 0.0000000 ;
	expArray[ 140 ]= 0.0000000 ;
	expArray[ 141 ]= 0.0000000 ;
	expArray[ 142 ]= 0.0000000 ;
	expArray[ 143 ]= 0.0000000 ;
	expArray[ 144 ]= 0.0000000 ;
	expArray[ 145 ]= 0.0000000 ;
	expArray[ 146 ]= 0.0000000 ;
	expArray[ 147 ]= 0.0000000 ;
	expArray[ 148 ]= 0.0000000 ;
	expArray[ 149 ]= 0.0000000 ;
	expArray[ 150 ]= 0.0000000 ;
	expArray[ 151 ]= 0.0000000 ;
	expArray[ 152 ]= 0.0000000 ;
	expArray[ 153 ]= 0.0000000 ;
	expArray[ 154 ]= 0.0000000 ;
	expArray[ 155 ]= 0.0000000 ;
	expArray[ 156 ]= 0.0000000 ;
	expArray[ 157 ]= 0.0000000 ;
	expArray[ 158 ]= 0.0000000 ;
	expArray[ 159 ]= 0.0000000 ;
	expArray[ 160 ]= 0.0000000 ;
	expArray[ 161 ]= 0.0000000 ;
	expArray[ 162 ]= 0.0000000 ;
	expArray[ 163 ]= 0.0000000 ;
	expArray[ 164 ]= 0.0000000 ;
	expArray[ 165 ]= 0.0000000 ;
	expArray[ 166 ]= 0.0000000 ;
	expArray[ 167 ]= 0.0000000 ;
	expArray[ 168 ]= 0.0000000 ;
	expArray[ 169 ]= 0.0000000 ;
	expArray[ 170 ]= 0.0000000 ;
	expArray[ 171 ]= 0.0000000 ;
	expArray[ 172 ]= 0.0000000 ;
	expArray[ 173 ]= 0.0000000 ;
	expArray[ 174 ]= 0.0000000 ;
	expArray[ 175 ]= 0.0000000 ;
	expArray[ 176 ]= 0.0000000 ;
	expArray[ 177 ]= 0.0000000 ;
	expArray[ 178 ]= 0.0000000 ;
	expArray[ 179 ]= 0.0000000 ;
	expArray[ 180 ]= 0.0000000 ;
	expArray[ 181 ]= 0.0000000 ;
	expArray[ 182 ]= 0.0000000 ;
	expArray[ 183 ]= 0.0000000 ;
	expArray[ 184 ]= 0.0000000 ;
	expArray[ 185 ]= 0.0000000 ;
	expArray[ 186 ]= 0.0000000 ;
	expArray[ 187 ]= 0.0000000 ;
	expArray[ 188 ]= 0.0000000 ;
	expArray[ 189 ]= 0.0000000 ;
	expArray[ 190 ]= 0.0000000 ;
	expArray[ 191 ]= 0.0000000 ;
	expArray[ 192 ]= 0.0000000 ;
	expArray[ 193 ]= 0.0000000 ;
	expArray[ 194 ]= 0.0000000 ;
	expArray[ 195 ]= 0.0000000 ;
	expArray[ 196 ]= 0.0000000 ;
	expArray[ 197 ]= 0.0000000 ;
	expArray[ 198 ]= 0.0000000 ;
	expArray[ 199 ]= 0.0000000 ;
	expArray[ 200 ]= 0.0000000 ;
	expArray[ 201 ]= 0.0000000 ;
	expArray[ 202 ]= 0.0000000 ;
	expArray[ 203 ]= 0.0000000 ;
	expArray[ 204 ]= 0.0000000 ;
	expArray[ 205 ]= 0.0000000 ;
	expArray[ 206 ]= 0.0000000 ;
	expArray[ 207 ]= 0.0000000 ;
	expArray[ 208 ]= 0.0000000 ;
	expArray[ 209 ]= 0.0000000 ;
	expArray[ 210 ]= 0.0000000 ;
	expArray[ 211 ]= 0.0000000 ;
	expArray[ 212 ]= 0.0000000 ;
	expArray[ 213 ]= 0.0000000 ;
	expArray[ 214 ]= 0.0000000 ;
	expArray[ 215 ]= 0.0000000 ;
	expArray[ 216 ]= 0.0000000 ;
	expArray[ 217 ]= 0.0000000 ;
	expArray[ 218 ]= 0.0000000 ;
	expArray[ 219 ]= 0.0000000 ;
	expArray[ 220 ]= 0.0000000 ;
	expArray[ 221 ]= 0.0000000 ;
	expArray[ 222 ]= 0.0000000 ;
	expArray[ 223 ]= 0.0000000 ;
	expArray[ 224 ]= 0.0000000 ;
	expArray[ 225 ]= 0.0000000 ;
	expArray[ 226 ]= 0.0000000 ;
	expArray[ 227 ]= 0.0000000 ;
	expArray[ 228 ]= 0.0000000 ;
	expArray[ 229 ]= 0.0000000 ;
	expArray[ 230 ]= 0.0000000 ;
	expArray[ 231 ]= 0.0000000 ;
	expArray[ 232 ]= 0.0000000 ;
	expArray[ 233 ]= 0.0000000 ;
	expArray[ 234 ]= 0.0000000 ;
	expArray[ 235 ]= 0.0000000 ;
	expArray[ 236 ]= 0.0000000 ;
	expArray[ 237 ]= 0.0000000 ;
	expArray[ 238 ]= 0.0000000 ;
	expArray[ 239 ]= 0.0000000 ;
	expArray[ 240 ]= 0.0000000 ;
	expArray[ 241 ]= 0.0000000 ;
	expArray[ 242 ]= 0.0000000 ;
	expArray[ 243 ]= 0.0000000 ;
	expArray[ 244 ]= 0.0000000 ;
	expArray[ 245 ]= 0.0000000 ;
	expArray[ 246 ]= 0.0000000 ;
	expArray[ 247 ]= 0.0000000 ;
	expArray[ 248 ]= 0.0000000 ;
	expArray[ 249 ]= 0.0000000 ;
	expArray[ 250 ]= 0.0000000 ;
	expArray[ 251 ]= 0.0000000 ;
	expArray[ 252 ]= 0.0000000 ;
	expArray[ 253 ]= 0.0000000 ;
	expArray[ 254 ]= 0.0000000 ;
	expArray[ 255 ]= 0.0000000 ;


	fixed7 divArray[256];
	/*
	 * divArray[index] = 1/(255-index)
	*/
	divArray[ 0 ]= 0.0039216 ;
	divArray[ 1 ]= 0.0039370 ;
	divArray[ 2 ]= 0.0039526 ;
	divArray[ 3 ]= 0.0039683 ;
	divArray[ 4 ]= 0.0039841 ;
	divArray[ 5 ]= 0.0040000 ;
	divArray[ 6 ]= 0.0040161 ;
	divArray[ 7 ]= 0.0040323 ;
	divArray[ 8 ]= 0.0040486 ;
	divArray[ 9 ]= 0.0040650 ;
	divArray[ 10 ]= 0.0040816 ;
	divArray[ 11 ]= 0.0040984 ;
	divArray[ 12 ]= 0.0041152 ;
	divArray[ 13 ]= 0.0041322 ;
	divArray[ 14 ]= 0.0041494 ;
	divArray[ 15 ]= 0.0041667 ;
	divArray[ 16 ]= 0.0041841 ;
	divArray[ 17 ]= 0.0042017 ;
	divArray[ 18 ]= 0.0042194 ;
	divArray[ 19 ]= 0.0042373 ;
	divArray[ 20 ]= 0.0042553 ;
	divArray[ 21 ]= 0.0042735 ;
	divArray[ 22 ]= 0.0042918 ;
	divArray[ 23 ]= 0.0043103 ;
	divArray[ 24 ]= 0.0043290 ;
	divArray[ 25 ]= 0.0043478 ;
	divArray[ 26 ]= 0.0043668 ;
	divArray[ 27 ]= 0.0043860 ;
	divArray[ 28 ]= 0.0044053 ;
	divArray[ 29 ]= 0.0044248 ;
	divArray[ 30 ]= 0.0044444 ;
	divArray[ 31 ]= 0.0044643 ;
	divArray[ 32 ]= 0.0044843 ;
	divArray[ 33 ]= 0.0045045 ;
	divArray[ 34 ]= 0.0045249 ;
	divArray[ 35 ]= 0.0045455 ;
	divArray[ 36 ]= 0.0045662 ;
	divArray[ 37 ]= 0.0045872 ;
	divArray[ 38 ]= 0.0046083 ;
	divArray[ 39 ]= 0.0046296 ;
	divArray[ 40 ]= 0.0046512 ;
	divArray[ 41 ]= 0.0046729 ;
	divArray[ 42 ]= 0.0046948 ;
	divArray[ 43 ]= 0.0047170 ;
	divArray[ 44 ]= 0.0047393 ;
	divArray[ 45 ]= 0.0047619 ;
	divArray[ 46 ]= 0.0047847 ;
	divArray[ 47 ]= 0.0048077 ;
	divArray[ 48 ]= 0.0048309 ;
	divArray[ 49 ]= 0.0048544 ;
	divArray[ 50 ]= 0.0048780 ;
	divArray[ 51 ]= 0.0049020 ;
	divArray[ 52 ]= 0.0049261 ;
	divArray[ 53 ]= 0.0049505 ;
	divArray[ 54 ]= 0.0049751 ;
	divArray[ 55 ]= 0.0050000 ;
	divArray[ 56 ]= 0.0050251 ;
	divArray[ 57 ]= 0.0050505 ;
	divArray[ 58 ]= 0.0050761 ;
	divArray[ 59 ]= 0.0051020 ;
	divArray[ 60 ]= 0.0051282 ;
	divArray[ 61 ]= 0.0051546 ;
	divArray[ 62 ]= 0.0051813 ;
	divArray[ 63 ]= 0.0052083 ;
	divArray[ 64 ]= 0.0052356 ;
	divArray[ 65 ]= 0.0052632 ;
	divArray[ 66 ]= 0.0052910 ;
	divArray[ 67 ]= 0.0053191 ;
	divArray[ 68 ]= 0.0053476 ;
	divArray[ 69 ]= 0.0053763 ;
	divArray[ 70 ]= 0.0054054 ;
	divArray[ 71 ]= 0.0054348 ;
	divArray[ 72 ]= 0.0054645 ;
	divArray[ 73 ]= 0.0054945 ;
	divArray[ 74 ]= 0.0055249 ;
	divArray[ 75 ]= 0.0055556 ;
	divArray[ 76 ]= 0.0055866 ;
	divArray[ 77 ]= 0.0056180 ;
	divArray[ 78 ]= 0.0056497 ;
	divArray[ 79 ]= 0.0056818 ;
	divArray[ 80 ]= 0.0057143 ;
	divArray[ 81 ]= 0.0057471 ;
	divArray[ 82 ]= 0.0057803 ;
	divArray[ 83 ]= 0.0058140 ;
	divArray[ 84 ]= 0.0058480 ;
	divArray[ 85 ]= 0.0058824 ;
	divArray[ 86 ]= 0.0059172 ;
	divArray[ 87 ]= 0.0059524 ;
	divArray[ 88 ]= 0.0059880 ;
	divArray[ 89 ]= 0.0060241 ;
	divArray[ 90 ]= 0.0060606 ;
	divArray[ 91 ]= 0.0060976 ;
	divArray[ 92 ]= 0.0061350 ;
	divArray[ 93 ]= 0.0061728 ;
	divArray[ 94 ]= 0.0062112 ;
	divArray[ 95 ]= 0.0062500 ;
	divArray[ 96 ]= 0.0062893 ;
	divArray[ 97 ]= 0.0063291 ;
	divArray[ 98 ]= 0.0063694 ;
	divArray[ 99 ]= 0.0064103 ;
	divArray[ 100 ]= 0.0064516 ;
	divArray[ 101 ]= 0.0064935 ;
	divArray[ 102 ]= 0.0065359 ;
	divArray[ 103 ]= 0.0065789 ;
	divArray[ 104 ]= 0.0066225 ;
	divArray[ 105 ]= 0.0066667 ;
	divArray[ 106 ]= 0.0067114 ;
	divArray[ 107 ]= 0.0067568 ;
	divArray[ 108 ]= 0.0068027 ;
	divArray[ 109 ]= 0.0068493 ;
	divArray[ 110 ]= 0.0068966 ;
	divArray[ 111 ]= 0.0069444 ;
	divArray[ 112 ]= 0.0069930 ;
	divArray[ 113 ]= 0.0070423 ;
	divArray[ 114 ]= 0.0070922 ;
	divArray[ 115 ]= 0.0071429 ;
	divArray[ 116 ]= 0.0071942 ;
	divArray[ 117 ]= 0.0072464 ;
	divArray[ 118 ]= 0.0072993 ;
	divArray[ 119 ]= 0.0073529 ;
	divArray[ 120 ]= 0.0074074 ;
	divArray[ 121 ]= 0.0074627 ;
	divArray[ 122 ]= 0.0075188 ;
	divArray[ 123 ]= 0.0075758 ;
	divArray[ 124 ]= 0.0076336 ;
	divArray[ 125 ]= 0.0076923 ;
	divArray[ 126 ]= 0.0077519 ;
	divArray[ 127 ]= 0.0078125 ;
	divArray[ 128 ]= 0.0078740 ;
	divArray[ 129 ]= 0.0079365 ;
	divArray[ 130 ]= 0.0080000 ;
	divArray[ 131 ]= 0.0080645 ;
	divArray[ 132 ]= 0.0081301 ;
	divArray[ 133 ]= 0.0081967 ;
	divArray[ 134 ]= 0.0082645 ;
	divArray[ 135 ]= 0.0083333 ;
	divArray[ 136 ]= 0.0084034 ;
	divArray[ 137 ]= 0.0084746 ;
	divArray[ 138 ]= 0.0085470 ;
	divArray[ 139 ]= 0.0086207 ;
	divArray[ 140 ]= 0.0086957 ;
	divArray[ 141 ]= 0.0087719 ;
	divArray[ 142 ]= 0.0088496 ;
	divArray[ 143 ]= 0.0089286 ;
	divArray[ 144 ]= 0.0090090 ;
	divArray[ 145 ]= 0.0090909 ;
	divArray[ 146 ]= 0.0091743 ;
	divArray[ 147 ]= 0.0092593 ;
	divArray[ 148 ]= 0.0093458 ;
	divArray[ 149 ]= 0.0094340 ;
	divArray[ 150 ]= 0.0095238 ;
	divArray[ 151 ]= 0.0096154 ;
	divArray[ 152 ]= 0.0097087 ;
	divArray[ 153 ]= 0.0098039 ;
	divArray[ 154 ]= 0.0099010 ;
	divArray[ 155 ]= 0.0100000 ;
	divArray[ 156 ]= 0.0101010 ;
	divArray[ 157 ]= 0.0102041 ;
	divArray[ 158 ]= 0.0103093 ;
	divArray[ 159 ]= 0.0104167 ;
	divArray[ 160 ]= 0.0105263 ;
	divArray[ 161 ]= 0.0106383 ;
	divArray[ 162 ]= 0.0107527 ;
	divArray[ 163 ]= 0.0108696 ;
	divArray[ 164 ]= 0.0109890 ;
	divArray[ 165 ]= 0.0111111 ;
	divArray[ 166 ]= 0.0112360 ;
	divArray[ 167 ]= 0.0113636 ;
	divArray[ 168 ]= 0.0114943 ;
	divArray[ 169 ]= 0.0116279 ;
	divArray[ 170 ]= 0.0117647 ;
	divArray[ 171 ]= 0.0119048 ;
	divArray[ 172 ]= 0.0120482 ;
	divArray[ 173 ]= 0.0121951 ;
	divArray[ 174 ]= 0.0123457 ;
	divArray[ 175 ]= 0.0125000 ;
	divArray[ 176 ]= 0.0126582 ;
	divArray[ 177 ]= 0.0128205 ;
	divArray[ 178 ]= 0.0129870 ;
	divArray[ 179 ]= 0.0131579 ;
	divArray[ 180 ]= 0.0133333 ;
	divArray[ 181 ]= 0.0135135 ;
	divArray[ 182 ]= 0.0136986 ;
	divArray[ 183 ]= 0.0138889 ;
	divArray[ 184 ]= 0.0140845 ;
	divArray[ 185 ]= 0.0142857 ;
	divArray[ 186 ]= 0.0144928 ;
	divArray[ 187 ]= 0.0147059 ;
	divArray[ 188 ]= 0.0149254 ;
	divArray[ 189 ]= 0.0151515 ;
	divArray[ 190 ]= 0.0153846 ;
	divArray[ 191 ]= 0.0156250 ;
	divArray[ 192 ]= 0.0158730 ;
	divArray[ 193 ]= 0.0161290 ;
	divArray[ 194 ]= 0.0163934 ;
	divArray[ 195 ]= 0.0166667 ;
	divArray[ 196 ]= 0.0169491 ;
	divArray[ 197 ]= 0.0172414 ;
	divArray[ 198 ]= 0.0175439 ;
	divArray[ 199 ]= 0.0178571 ;
	divArray[ 200 ]= 0.0181818 ;
	divArray[ 201 ]= 0.0185185 ;
	divArray[ 202 ]= 0.0188679 ;
	divArray[ 203 ]= 0.0192308 ;
	divArray[ 204 ]= 0.0196078 ;
	divArray[ 205 ]= 0.0200000 ;
	divArray[ 206 ]= 0.0204082 ;
	divArray[ 207 ]= 0.0208333 ;
	divArray[ 208 ]= 0.0212766 ;
	divArray[ 209 ]= 0.0217391 ;
	divArray[ 210 ]= 0.0222222 ;
	divArray[ 211 ]= 0.0227273 ;
	divArray[ 212 ]= 0.0232558 ;
	divArray[ 213 ]= 0.0238095 ;
	divArray[ 214 ]= 0.0243902 ;
	divArray[ 215 ]= 0.0250000 ;
	divArray[ 216 ]= 0.0256410 ;
	divArray[ 217 ]= 0.0263158 ;
	divArray[ 218 ]= 0.0270270 ;
	divArray[ 219 ]= 0.0277778 ;
	divArray[ 220 ]= 0.0285714 ;
	divArray[ 221 ]= 0.0294118 ;
	divArray[ 222 ]= 0.0303030 ;
	divArray[ 223 ]= 0.0312500 ;
	divArray[ 224 ]= 0.0322581 ;
	divArray[ 225 ]= 0.0333333 ;
	divArray[ 226 ]= 0.0344827 ;
	divArray[ 227 ]= 0.0357143 ;
	divArray[ 228 ]= 0.0370370 ;
	divArray[ 229 ]= 0.0384615 ;
	divArray[ 230 ]= 0.0400000 ;
	divArray[ 231 ]= 0.0416666 ;
	divArray[ 232 ]= 0.0434782 ;
	divArray[ 233 ]= 0.0454545 ;
	divArray[ 234 ]= 0.0476190 ;
	divArray[ 235 ]= 0.0500000 ;
	divArray[ 236 ]= 0.0526316 ;
	divArray[ 237 ]= 0.0555555 ;
	divArray[ 238 ]= 0.0588235 ;
	divArray[ 239 ]= 0.0625000 ;
	divArray[ 240 ]= 0.0666666 ;
	divArray[ 241 ]= 0.0714285 ;
	divArray[ 242 ]= 0.0769230 ;
	divArray[ 243 ]= 0.0833333 ;
	divArray[ 244 ]= 0.0909090 ;
	divArray[ 245 ]= 0.0999999 ;
	divArray[ 246 ]= 0.1111110 ;
	divArray[ 247 ]= 0.1249998 ;
	divArray[ 248 ]= 0.1428569 ;
	divArray[ 249 ]= 0.1666664 ;
	divArray[ 250 ]= 0.1999996 ;
	divArray[ 251 ]= 0.2499994 ;
	divArray[ 252 ]= 0.3333322 ;
	divArray[ 253 ]= 0.4999975 ;
	divArray[ 254 ]= 0.9999900 ;
	divArray[ 255 ]= 1.0000000 ;

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

    //Apply histogram equalization
    hls::EqualizeHist( grayMat_1,histeq );
    hls::Duplicate(histeq,histeq_copy1,histeq_copy2);
    //airlight map initial estimation
    initial_estimate(airlight_initial,histeq_copy1);

    //anisotropic diffusion
    anisotropic_diffusion(airlight_initial, img_out1,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
    anisotropic_diffusion(img_out1, img_out2,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
    anisotropic_diffusion(img_out2, img_out3,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
    anisotropic_diffusion(img_out3, img_out4,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
    anisotropic_diffusion(img_out4, airlight,left_kernel,right_kernel,up_kernel,down_kernel,expArray);


    restoration(airlight,histeq_copy2,img_out,divArray);

    hls::Mat2AXIvideo(img_out, outstream);
}



void anisotropic_diffusion(GRAY_IMAGE& img_in, GRAY_IMAGE& img_out,WINDOW left_kernel,WINDOW right_kernel,WINDOW up_kernel,WINDOW down_kernel,fixed7 expArray[256])
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
    hls::Scalar<1,fixed7> iteration_added;
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
    	    iteration_added = (expArray[right_valOutput.val[0]]+expArray[left_valOutput.val[0]]+expArray[down_valOutput.val[0]]+expArray[up_valOutput.val[0]]);
    	    output_val = (unsigned char)(input_val.val[0] + iteration_added.val[0]);
    	    img_out.write(output_val);
    	}
    }
}



void restoration(GRAY_IMAGE& airlight,GRAY_IMAGE& img_in, GRAY_IMAGE& img_out,fixed7 divArray[256])
{
	GRAY_IMAGE intermed_difference(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE img_in_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE img_in_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	hls::Duplicate(img_in,img_in_copy1,img_in_copy2);
	hls::AddWeighted(img_in_copy1, 1, airlight, -1, 0, intermed_difference);

	hls::Scalar<1,unsigned char> diff_val;
    hls::Scalar<1,unsigned char> input_val;
    hls::Scalar<1,unsigned char> output_val;

    ROW: for(int row = 0; row < IMG_HEIGHT_OR_ROWS; row++)
    {
#pragma HLS LOOP_TRIPCOUNT min=1 max=478

    	COL: for(int col = 0; col < IMG_WIDTH_OR_COLS; col++)
    	{
#pragma HLS LOOP_TRIPCOUNT min=1 max=638
#pragma HLS PIPELINE
//#pragma HLS DEPENDENCE

    		intermed_difference.read(diff_val);
    		img_in_copy2.read(input_val);
    	    output_val = (unsigned char)(diff_val.val[0]*divArray[input_val.val[0]]);
    	    img_out.write(output_val);
    	}
    }

}

void initial_estimate(GRAY_IMAGE& airlight,GRAY_IMAGE& img_in)
{
    hls::Scalar<1,unsigned char> input_val;
    hls::Scalar<1,unsigned char> output_val;
    fixed7 beta = 0.9500000;

    ROW: for(int row = 0; row < IMG_HEIGHT_OR_ROWS; row++)
    {
#pragma HLS LOOP_TRIPCOUNT min=1 max=478

    	COL: for(int col = 0; col < IMG_WIDTH_OR_COLS; col++)
    	{
#pragma HLS LOOP_TRIPCOUNT min=1 max=638
#pragma HLS PIPELINE
//#pragma HLS DEPENDENCE

    		img_in.read(input_val);
    	    output_val = (unsigned char)(input_val.val[0]*beta);
    	    airlight.write(output_val);
    	}
    }
}
