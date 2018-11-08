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
//
//
//
//	    /*
//	        kappa = 30
//	        lambda = 1/7
//	        expArray[x] = (x*exp(-(x/kappa)^2))*lambda
//	    */
//

	fixed7 expArray[256];

	expArray[ 0 ]= 0.0 ;
	expArray[ 1 ]= 0.1428571404160793 ;
	expArray[ 2 ]= 0.28571426618577783 ;
	expArray[ 3 ]= 0.42857136266271717 ;
	expArray[ 4 ]= 0.5714284152005242 ;
	expArray[ 5 ]= 0.714285409152833 ;
	expArray[ 6 ]= 0.857142329873288 ;
	expArray[ 7 ]= 0.9999991627155456 ;
	expArray[ 8 ]= 1.1428558930332777 ;
	expArray[ 9 ]= 1.2857125061801737 ;
	expArray[ 10 ]= 1.4285689875099428 ;
	expArray[ 11 ]= 1.5714253223763168 ;
	expArray[ 12 ]= 1.7142814961330524 ;
	expArray[ 13 ]= 1.8571374941339343 ;
	expArray[ 14 ]= 1.999993301732777 ;
	expArray[ 15 ]= 2.1428489042834267 ;
	expArray[ 16 ]= 2.285704287139766 ;
	expArray[ 17 ]= 2.4285594356557145 ;
	expArray[ 18 ]= 2.5714143351852314 ;
	expArray[ 19 ]= 2.714268971082319 ;
	expArray[ 20 ]= 2.8571233287010243 ;
	expArray[ 21 ]= 2.9999773933954423 ;
	expArray[ 22 ]= 3.1428311505197177 ;
	expArray[ 23 ]= 3.285684585428047 ;
	expArray[ 24 ]= 3.428537683474684 ;
	expArray[ 25 ]= 3.5713904300139374 ;
	expArray[ 26 ]= 3.7142428104001772 ;
	expArray[ 27 ]= 3.8570948099878377 ;
	expArray[ 28 ]= 3.9999464141314145 ;
	expArray[ 29 ]= 4.142797608185473 ;
	expArray[ 30 ]= 4.285648377504651 ;
	expArray[ 31 ]= 4.428498707443652 ;
	expArray[ 32 ]= 4.571348583357263 ;
	expArray[ 33 ]= 4.714197990600343 ;
	expArray[ 34 ]= 4.857046914527831 ;
	expArray[ 35 ]= 4.999895340494753 ;
	expArray[ 36 ]= 5.1427432538562154 ;
	expArray[ 37 ]= 5.285590639967414 ;
	expArray[ 38 ]= 5.428437484183635 ;
	expArray[ 39 ]= 5.571283771860259 ;
	expArray[ 40 ]= 5.714129488352755 ;
	expArray[ 41 ]= 5.856974619016699 ;
	expArray[ 42 ]= 5.99981914920776 ;
	expArray[ 43 ]= 6.142663064281714 ;
	expArray[ 44 ]= 6.285506349594436 ;
	expArray[ 45 ]= 6.428348990501917 ;
	expArray[ 46 ]= 6.57119097236025 ;
	expArray[ 47 ]= 6.714032280525648 ;
	expArray[ 48 ]= 6.856872900354432 ;
	expArray[ 49 ]= 6.999712817203046 ;
	expArray[ 50 ]= 7.142552016428053 ;
	expArray[ 51 ]= 7.285390483386137 ;
	expArray[ 52 ]= 7.428228203434108 ;
	expArray[ 53 ]= 7.571065161928901 ;
	expArray[ 54 ]= 7.7139013442275886 ;
	expArray[ 55 ]= 7.8567367356873685 ;
	expArray[ 56 ]= 7.9995713216655755 ;
	expArray[ 57 ]= 8.142405087519682 ;
	expArray[ 58 ]= 8.285238018607306 ;
	expArray[ 59 ]= 8.428070100286199 ;
	expArray[ 60 ]= 8.570901317914265 ;
	expArray[ 61 ]= 8.713731656849548 ;
	expArray[ 62 ]= 8.856561102450248 ;
	expArray[ 63 ]= 8.999389640074723 ;
	expArray[ 64 ]= 9.142217255081473 ;
	expArray[ 65 ]= 9.285043932829163 ;
	expArray[ 66 ]= 9.427869658676617 ;
	expArray[ 67 ]= 9.570694417982825 ;
	expArray[ 68 ]= 9.713518196106937 ;
	expArray[ 69 ]= 9.856340978408273 ;
	expArray[ 70 ]= 9.999162750246324 ;
	expArray[ 71 ]= 10.141983496980751 ;
	expArray[ 72 ]= 10.284803203971395 ;
	expArray[ 73 ]= 10.427621856578266 ;
	expArray[ 74 ]= 10.570439440161563 ;
	expArray[ 75 ]= 10.713255940081664 ;
	expArray[ 76 ]= 10.856071341699133 ;
	expArray[ 77 ]= 10.99888563037472 ;
	expArray[ 78 ]= 11.141698791469366 ;
	expArray[ 79 ]= 11.284510810344205 ;
	expArray[ 80 ]= 11.427321672360566 ;
	expArray[ 81 ]= 11.570131362879978 ;
	expArray[ 82 ]= 11.712939867264167 ;
	expArray[ 83 ]= 11.855747170875059 ;
	expArray[ 84 ]= 11.998553259074793 ;
	expArray[ 85 ]= 12.141358117225709 ;
	expArray[ 86 ]= 12.284161730690359 ;
	expArray[ 87 ]= 12.42696408483151 ;
	expArray[ 88 ]= 12.569765165012143 ;
	expArray[ 89 ]= 12.712564956595454 ;
	expArray[ 90 ]= 12.85536344494486 ;
	expArray[ 91 ]= 12.998160615424009 ;
	expArray[ 92 ]= 13.140956453396756 ;
	expArray[ 93 ]= 13.283750944227204 ;
	expArray[ 94 ]= 13.426544073279672 ;
	expArray[ 95 ]= 13.569335825918719 ;
	expArray[ 96 ]= 13.712126187509138 ;
	expArray[ 97 ]= 13.854915143415951 ;
	expArray[ 98 ]= 13.997702679004437 ;
	expArray[ 99 ]= 14.140488779640103 ;
	expArray[ 100 ]= 14.283273430688707 ;
	expArray[ 101 ]= 14.426056617516254 ;
	expArray[ 102 ]= 14.568838325489 ;
	expArray[ 103 ]= 14.711618539973454 ;
	expArray[ 104 ]= 14.854397246336376 ;
	expArray[ 105 ]= 14.99717442994479 ;
	expArray[ 106 ]= 15.139950076165974 ;
	expArray[ 107 ]= 15.282724170367475 ;
	expArray[ 108 ]= 15.425496697917097 ;
	expArray[ 109 ]= 15.568267644182923 ;
	expArray[ 110 ]= 15.711036994533293 ;
	expArray[ 111 ]= 15.853804734336832 ;
	expArray[ 112 ]= 15.99657084896243 ;
	expArray[ 113 ]= 16.139335323779257 ;
	expArray[ 114 ]= 16.28209814415677 ;
	expArray[ 115 ]= 16.424859295464707 ;
	expArray[ 116 ]= 16.567618763073078 ;
	expArray[ 117 ]= 16.7103765323522 ;
	expArray[ 118 ]= 16.85313258867267 ;
	expArray[ 119 ]= 16.99588691740537 ;
	expArray[ 120 ]= 17.138639503921492 ;
	expArray[ 121 ]= 17.281390333592523 ;
	expArray[ 122 ]= 17.42413939179024 ;
	expArray[ 123 ]= 17.566886663886734 ;
	expArray[ 124 ]= 17.709632135254388 ;
	expArray[ 125 ]= 17.852375791265914 ;
	expArray[ 126 ]= 17.99511761729431 ;
	expArray[ 127 ]= 18.137857598712902 ;
	expArray[ 128 ]= 18.280595720895324 ;
	expArray[ 129 ]= 18.423331969215536 ;
	expArray[ 130 ]= 18.566066329047807 ;
	expArray[ 131 ]= 18.70879878576674 ;
	expArray[ 132 ]= 18.85152932474725 ;
	expArray[ 133 ]= 18.994257931364594 ;
	expArray[ 134 ]= 19.13698459099435 ;
	expArray[ 135 ]= 19.279709289012427 ;
	expArray[ 136 ]= 19.42243201079508 ;
	expArray[ 137 ]= 19.565152741718887 ;
	expArray[ 138 ]= 19.707871467160775 ;
	expArray[ 139 ]= 19.850588172498018 ;
	expArray[ 140 ]= 19.99330284310823 ;
	expArray[ 141 ]= 20.136015464369358 ;
	expArray[ 142 ]= 20.27872602165973 ;
	expArray[ 143 ]= 20.421434500357993 ;
	expArray[ 144 ]= 20.564140885843184 ;
	expArray[ 145 ]= 20.706845163494666 ;
	expArray[ 146 ]= 20.849547318692178 ;
	expArray[ 147 ]= 20.992247336815826 ;
	expArray[ 148 ]= 21.13494520324607 ;
	expArray[ 149 ]= 21.277640903363736 ;
	expArray[ 150 ]= 21.420334422550035 ;
	expArray[ 151 ]= 21.56302574618653 ;
	expArray[ 152 ]= 21.70571485965518 ;
	expArray[ 153 ]= 21.84840174833831 ;
	expArray[ 154 ]= 21.991086397618627 ;
	expArray[ 155 ]= 22.133768792879216 ;
	expArray[ 156 ]= 22.276448919503558 ;
	expArray[ 157 ]= 22.41912676287551 ;
	expArray[ 158 ]= 22.561802308379328 ;
	expArray[ 159 ]= 22.704475541399656 ;
	expArray[ 160 ]= 22.84714644732153 ;
	expArray[ 161 ]= 22.989815011530396 ;
	expArray[ 162 ]= 23.132481219412085 ;
	expArray[ 163 ]= 23.275145056352834 ;
	expArray[ 164 ]= 23.417806507739293 ;
	expArray[ 165 ]= 23.56046555895851 ;
	expArray[ 166 ]= 23.703122195397953 ;
	expArray[ 167 ]= 23.845776402445495 ;
	expArray[ 168 ]= 23.98842816548942 ;
	expArray[ 169 ]= 24.131077469918445 ;
	expArray[ 170 ]= 24.273724301121693 ;
	expArray[ 171 ]= 24.41636864448871 ;
	expArray[ 172 ]= 24.559010485409477 ;
	expArray[ 173 ]= 24.70164980927439 ;
	expArray[ 174 ]= 24.844286601474288 ;
	expArray[ 175 ]= 24.98692084740043 ;
	expArray[ 176 ]= 25.129552532444514 ;
	expArray[ 177 ]= 25.272181641998685 ;
	expArray[ 178 ]= 25.414808161455515 ;
	expArray[ 179 ]= 25.557432076208023 ;
	expArray[ 180 ]= 25.70005337164968 ;
	expArray[ 181 ]= 25.84267203317438 ;
	expArray[ 182 ]= 25.985288046176503 ;
	expArray[ 183 ]= 26.127901396050863 ;
	expArray[ 184 ]= 26.270512068192712 ;
	expArray[ 185 ]= 26.41312004799779 ;
	expArray[ 186 ]= 26.555725320862283 ;
	expArray[ 187 ]= 26.69832787218283 ;
	expArray[ 188 ]= 26.840927687356555 ;
	expArray[ 189 ]= 26.983524751781033 ;
	expArray[ 190 ]= 27.126119050854317 ;
	expArray[ 191 ]= 27.268710569974928 ;
	expArray[ 192 ]= 27.411299294541863 ;
	expArray[ 193 ]= 27.553885209954597 ;
	expArray[ 194 ]= 27.69646830161309 ;
	expArray[ 195 ]= 27.839048554917774 ;
	expArray[ 196 ]= 27.98162595526957 ;
	expArray[ 197 ]= 28.124200488069892 ;
	expArray[ 198 ]= 28.266772138720633 ;
	expArray[ 199 ]= 28.409340892624193 ;
	expArray[ 200 ]= 28.55190673518345 ;
	expArray[ 201 ]= 28.69446965180179 ;
	expArray[ 202 ]= 28.837029627883094 ;
	expArray[ 203 ]= 28.979586648831752 ;
	expArray[ 204 ]= 29.122140700052654 ;
	expArray[ 205 ]= 29.264691766951188 ;
	expArray[ 206 ]= 29.407239834933275 ;
	expArray[ 207 ]= 29.54978488940532 ;
	expArray[ 208 ]= 29.692326915774263 ;
	expArray[ 209 ]= 29.834865899447557 ;
	expArray[ 210 ]= 29.977401825833173 ;
	expArray[ 211 ]= 30.119934680339604 ;
	expArray[ 212 ]= 30.26246444837586 ;
	expArray[ 213 ]= 30.404991115351486 ;
	expArray[ 214 ]= 30.547514666676566 ;
	expArray[ 215 ]= 30.690035087761704 ;
	expArray[ 216 ]= 30.83255236401803 ;
	expArray[ 217 ]= 30.975066480857233 ;
	expArray[ 218 ]= 31.11757742369153 ;
	expArray[ 219 ]= 31.26008517793368 ;
	expArray[ 220 ]= 31.402589728996976 ;
	expArray[ 221 ]= 31.54509106229528 ;
	expArray[ 222 ]= 31.68758916324299 ;
	expArray[ 223 ]= 31.830084017255064 ;
	expArray[ 224 ]= 31.972575609747 ;
	expArray[ 225 ]= 32.11506392613487 ;
	expArray[ 226 ]= 32.25754895183529 ;
	expArray[ 227 ]= 32.40003067226546 ;
	expArray[ 228 ]= 32.54250907284311 ;
	expArray[ 229 ]= 32.68498413898657 ;
	expArray[ 230 ]= 32.82745585611473 ;
	expArray[ 231 ]= 32.96992420964703 ;
	expArray[ 232 ]= 33.11238918500353 ;
	expArray[ 233 ]= 33.25485076760482 ;
	expArray[ 234 ]= 33.397308942872094 ;
	expArray[ 235 ]= 33.53976369622711 ;
	expArray[ 236 ]= 33.682215013092254 ;
	expArray[ 237 ]= 33.82466287889044 ;
	expArray[ 238 ]= 33.967107279045216 ;
	expArray[ 239 ]= 34.1095481989807 ;
	expArray[ 240 ]= 34.2519856241216 ;
	expArray[ 241 ]= 34.39441953989325 ;
	expArray[ 242 ]= 34.53684993172155 ;
	expArray[ 243 ]= 34.67927678503302 ;
	expArray[ 244 ]= 34.82170008525477 ;
	expArray[ 245 ]= 34.964119817814534 ;
	expArray[ 246 ]= 35.106535968140655 ;
	expArray[ 247 ]= 35.24894852166207 ;
	expArray[ 248 ]= 35.39135746380835 ;
	expArray[ 249 ]= 35.53376278000966 ;
	expArray[ 250 ]= 35.67616445569681 ;
	expArray[ 251 ]= 35.8185624763012 ;
	expArray[ 252 ]= 35.9609568272549 ;
	expArray[ 253 ]= 36.10334749399056 ;
	expArray[ 254 ]= 36.24573446194149 ;
	expArray[ 255 ]= 36.3881177165416 ;

	//	fixed2 expArray[256];

//	expArray[ 0 ]= 0.00 ;
//	expArray[ 1 ]= 0.14 ;
//	expArray[ 2 ]= 0.28 ;
//	expArray[ 3 ]= 0.42 ;
//	expArray[ 4 ]= 0.56 ;
//	expArray[ 5 ]= 0.69 ;
//	expArray[ 6 ]= 0.82 ;
//	expArray[ 7 ]= 0.95 ;
//	expArray[ 8 ]= 1.06 ;
//	expArray[ 9 ]= 1.18 ;
//	expArray[ 10 ]= 1.28 ;
//	expArray[ 11 ]= 1.37 ;
//	expArray[ 12 ]= 1.46 ;
//	expArray[ 13 ]= 1.54 ;
//	expArray[ 14 ]= 1.61 ;
//	expArray[ 15 ]= 1.67 ;
//	expArray[ 16 ]= 1.72 ;
//	expArray[ 17 ]= 1.76 ;
//	expArray[ 18 ]= 1.79 ;
//	expArray[ 19 ]= 1.82 ;
//	expArray[ 20 ]= 1.83 ;
//	expArray[ 21 ]= 1.84 ;
//	expArray[ 22 ]= 1.84 ;
//	expArray[ 23 ]= 1.83 ;
//	expArray[ 24 ]= 1.81 ;
//	expArray[ 25 ]= 1.78 ;
//	expArray[ 26 ]= 1.75 ;
//	expArray[ 27 ]= 1.72 ;
//	expArray[ 28 ]= 1.67 ;
//	expArray[ 29 ]= 1.63 ;
//	expArray[ 30 ]= 1.58 ;
//	expArray[ 31 ]= 1.52 ;
//	expArray[ 32 ]= 1.47 ;
//	expArray[ 33 ]= 1.41 ;
//	expArray[ 34 ]= 1.34 ;
//	expArray[ 35 ]= 1.28 ;
//	expArray[ 36 ]= 1.22 ;
//	expArray[ 37 ]= 1.15 ;
//	expArray[ 38 ]= 1.09 ;
//	expArray[ 39 ]= 1.03 ;
//	expArray[ 40 ]= 0.97 ;
//	expArray[ 41 ]= 0.90 ;
//	expArray[ 42 ]= 0.85 ;
//	expArray[ 43 ]= 0.79 ;
//	expArray[ 44 ]= 0.73 ;
//	expArray[ 45 ]= 0.68 ;
//	expArray[ 46 ]= 0.63 ;
//	expArray[ 47 ]= 0.58 ;
//	expArray[ 48 ]= 0.53 ;
//	expArray[ 49 ]= 0.49 ;
//	expArray[ 50 ]= 0.44 ;
//	expArray[ 51 ]= 0.40 ;
//	expArray[ 52 ]= 0.37 ;
//	expArray[ 53 ]= 0.33 ;
//	expArray[ 54 ]= 0.30 ;
//	expArray[ 55 ]= 0.27 ;
//	expArray[ 56 ]= 0.25 ;
//	expArray[ 57 ]= 0.22 ;
//	expArray[ 58 ]= 0.20 ;
//	expArray[ 59 ]= 0.18 ;
//	expArray[ 60 ]= 0.16 ;
//	expArray[ 61 ]= 0.14 ;
//	expArray[ 62 ]= 0.12 ;
//	expArray[ 63 ]= 0.11 ;
//	expArray[ 64 ]= 0.10 ;
//	expArray[ 65 ]= 0.08 ;
//	expArray[ 66 ]= 0.07 ;
//	expArray[ 67 ]= 0.07 ;
//	expArray[ 68 ]= 0.06 ;
//	expArray[ 69 ]= 0.05 ;
//	expArray[ 70 ]= 0.04 ;
//	expArray[ 71 ]= 0.04 ;
//	expArray[ 72 ]= 0.03 ;
//	expArray[ 73 ]= 0.03 ;
//	expArray[ 74 ]= 0.02 ;
//	expArray[ 75 ]= 0.02 ;
//	expArray[ 76 ]= 0.02 ;
//	expArray[ 77 ]= 0.02 ;
//	expArray[ 78 ]= 0.01 ;
//	expArray[ 79 ]= 0.01 ;
//	expArray[ 80 ]= 0.01 ;
//	expArray[ 81 ]= 0.01 ;
//	expArray[ 82 ]= 0.01 ;
//	expArray[ 83 ]= 0.01 ;
//	expArray[ 84 ]= 0.00 ;
//	expArray[ 85 ]= 0.00 ;
//	expArray[ 86 ]= 0.00 ;
//	expArray[ 87 ]= 0.00 ;
//	expArray[ 88 ]= 0.00 ;
//	expArray[ 89 ]= 0.00 ;
//	expArray[ 90 ]= 0.00 ;
//	expArray[ 91 ]= 0.00 ;
//	expArray[ 92 ]= 0.00 ;
//	expArray[ 93 ]= 0.00 ;
//	expArray[ 94 ]= 0.00 ;
//	expArray[ 95 ]= 0.00 ;
//	expArray[ 96 ]= 0.00 ;
//	expArray[ 97 ]= 0.00 ;
//	expArray[ 98 ]= 0.00 ;
//	expArray[ 99 ]= 0.00 ;
//	expArray[ 100 ]= 0.00 ;
//	expArray[ 101 ]= 0.00 ;
//	expArray[ 102 ]= 0.00 ;
//	expArray[ 103 ]= 0.00 ;
//	expArray[ 104 ]= 0.00 ;
//	expArray[ 105 ]= 0.00 ;
//	expArray[ 106 ]= 0.00 ;
//	expArray[ 107 ]= 0.00 ;
//	expArray[ 108 ]= 0.00 ;
//	expArray[ 109 ]= 0.00 ;
//	expArray[ 110 ]= 0.00 ;
//	expArray[ 111 ]= 0.00 ;
//	expArray[ 112 ]= 0.00 ;
//	expArray[ 113 ]= 0.00 ;
//	expArray[ 114 ]= 0.00 ;
//	expArray[ 115 ]= 0.00 ;
//	expArray[ 116 ]= 0.00 ;
//	expArray[ 117 ]= 0.00 ;
//	expArray[ 118 ]= 0.00 ;
//	expArray[ 119 ]= 0.00 ;
//	expArray[ 120 ]= 0.00 ;
//	expArray[ 121 ]= 0.00 ;
//	expArray[ 122 ]= 0.00 ;
//	expArray[ 123 ]= 0.00 ;
//	expArray[ 124 ]= 0.00 ;
//	expArray[ 125 ]= 0.00 ;
//	expArray[ 126 ]= 0.00 ;
//	expArray[ 127 ]= 0.00 ;
//	expArray[ 128 ]= 0.00 ;
//	expArray[ 129 ]= 0.00 ;
//	expArray[ 130 ]= 0.00 ;
//	expArray[ 131 ]= 0.00 ;
//	expArray[ 132 ]= 0.00 ;
//	expArray[ 133 ]= 0.00 ;
//	expArray[ 134 ]= 0.00 ;
//	expArray[ 135 ]= 0.00 ;
//	expArray[ 136 ]= 0.00 ;
//	expArray[ 137 ]= 0.00 ;
//	expArray[ 138 ]= 0.00 ;
//	expArray[ 139 ]= 0.00 ;
//	expArray[ 140 ]= 0.00 ;
//	expArray[ 141 ]= 0.00 ;
//	expArray[ 142 ]= 0.00 ;
//	expArray[ 143 ]= 0.00 ;
//	expArray[ 144 ]= 0.00 ;
//	expArray[ 145 ]= 0.00 ;
//	expArray[ 146 ]= 0.00 ;
//	expArray[ 147 ]= 0.00 ;
//	expArray[ 148 ]= 0.00 ;
//	expArray[ 149 ]= 0.00 ;
//	expArray[ 150 ]= 0.00 ;
//	expArray[ 151 ]= 0.00 ;
//	expArray[ 152 ]= 0.00 ;
//	expArray[ 153 ]= 0.00 ;
//	expArray[ 154 ]= 0.00 ;
//	expArray[ 155 ]= 0.00 ;
//	expArray[ 156 ]= 0.00 ;
//	expArray[ 157 ]= 0.00 ;
//	expArray[ 158 ]= 0.00 ;
//	expArray[ 159 ]= 0.00 ;
//	expArray[ 160 ]= 0.00 ;
//	expArray[ 161 ]= 0.00 ;
//	expArray[ 162 ]= 0.00 ;
//	expArray[ 163 ]= 0.00 ;
//	expArray[ 164 ]= 0.00 ;
//	expArray[ 165 ]= 0.00 ;
//	expArray[ 166 ]= 0.00 ;
//	expArray[ 167 ]= 0.00 ;
//	expArray[ 168 ]= 0.00 ;
//	expArray[ 169 ]= 0.00 ;
//	expArray[ 170 ]= 0.00 ;
//	expArray[ 171 ]= 0.00 ;
//	expArray[ 172 ]= 0.00 ;
//	expArray[ 173 ]= 0.00 ;
//	expArray[ 174 ]= 0.00 ;
//	expArray[ 175 ]= 0.00 ;
//	expArray[ 176 ]= 0.00 ;
//	expArray[ 177 ]= 0.00 ;
//	expArray[ 178 ]= 0.00 ;
//	expArray[ 179 ]= 0.00 ;
//	expArray[ 180 ]= 0.00 ;
//	expArray[ 181 ]= 0.00 ;
//	expArray[ 182 ]= 0.00 ;
//	expArray[ 183 ]= 0.00 ;
//	expArray[ 184 ]= 0.00 ;
//	expArray[ 185 ]= 0.00 ;
//	expArray[ 186 ]= 0.00 ;
//	expArray[ 187 ]= 0.00 ;
//	expArray[ 188 ]= 0.00 ;
//	expArray[ 189 ]= 0.00 ;
//	expArray[ 190 ]= 0.00 ;
//	expArray[ 191 ]= 0.00 ;
//	expArray[ 192 ]= 0.00 ;
//	expArray[ 193 ]= 0.00 ;
//	expArray[ 194 ]= 0.00 ;
//	expArray[ 195 ]= 0.00 ;
//	expArray[ 196 ]= 0.00 ;
//	expArray[ 197 ]= 0.00 ;
//	expArray[ 198 ]= 0.00 ;
//	expArray[ 199 ]= 0.00 ;
//	expArray[ 200 ]= 0.00 ;
//	expArray[ 201 ]= 0.00 ;
//	expArray[ 202 ]= 0.00 ;
//	expArray[ 203 ]= 0.00 ;
//	expArray[ 204 ]= 0.00 ;
//	expArray[ 205 ]= 0.00 ;
//	expArray[ 206 ]= 0.00 ;
//	expArray[ 207 ]= 0.00 ;
//	expArray[ 208 ]= 0.00 ;
//	expArray[ 209 ]= 0.00 ;
//	expArray[ 210 ]= 0.00 ;
//	expArray[ 211 ]= 0.00 ;
//	expArray[ 212 ]= 0.00 ;
//	expArray[ 213 ]= 0.00 ;
//	expArray[ 214 ]= 0.00 ;
//	expArray[ 215 ]= 0.00 ;
//	expArray[ 216 ]= 0.00 ;
//	expArray[ 217 ]= 0.00 ;
//	expArray[ 218 ]= 0.00 ;
//	expArray[ 219 ]= 0.00 ;
//	expArray[ 220 ]= 0.00 ;
//	expArray[ 221 ]= 0.00 ;
//	expArray[ 222 ]= 0.00 ;
//	expArray[ 223 ]= 0.00 ;
//	expArray[ 224 ]= 0.00 ;
//	expArray[ 225 ]= 0.00 ;
//	expArray[ 226 ]= 0.00 ;
//	expArray[ 227 ]= 0.00 ;
//	expArray[ 228 ]= 0.00 ;
//	expArray[ 229 ]= 0.00 ;
//	expArray[ 230 ]= 0.00 ;
//	expArray[ 231 ]= 0.00 ;
//	expArray[ 232 ]= 0.00 ;
//	expArray[ 233 ]= 0.00 ;
//	expArray[ 234 ]= 0.00 ;
//	expArray[ 235 ]= 0.00 ;
//	expArray[ 236 ]= 0.00 ;
//	expArray[ 237 ]= 0.00 ;
//	expArray[ 238 ]= 0.00 ;
//	expArray[ 239 ]= 0.00 ;
//	expArray[ 240 ]= 0.00 ;
//	expArray[ 241 ]= 0.00 ;
//	expArray[ 242 ]= 0.00 ;
//	expArray[ 243 ]= 0.00 ;
//	expArray[ 244 ]= 0.00 ;
//	expArray[ 245 ]= 0.00 ;
//	expArray[ 246 ]= 0.00 ;
//	expArray[ 247 ]= 0.00 ;
//	expArray[ 248 ]= 0.00 ;
//	expArray[ 249 ]= 0.00 ;
//	expArray[ 250 ]= 0.00 ;
//	expArray[ 251 ]= 0.00 ;
//	expArray[ 252 ]= 0.00 ;
//	expArray[ 253 ]= 0.00 ;
//	expArray[ 254 ]= 0.00 ;
//	expArray[ 255 ]= 0.00 ;

//	unsigned int expArray[256];
//	  expArray[0] = 0;
//	  expArray[1] = 149630;
//	  expArray[2] = 298265;
//	  expArray[3] = 444918;
//	  expArray[4] = 588628;
//	  expArray[5] = 728464;
//	  expArray[6] = 863538;
//	  expArray[7] = 993013;
//	  expArray[8] = 1116114;
//	  expArray[9] = 1232134;
//	  expArray[10] = 1340439;
//	  expArray[11] = 1440476;
//	  expArray[12] = 1531779;
//	  expArray[13] = 1613966;
//	  expArray[14] = 1686748;
//	  expArray[15] = 1749925;
//	  expArray[16] = 1803388;
//	  expArray[17] = 1847115;
//	  expArray[18] = 1881171;
//	  expArray[19] = 1905703;
//	  expArray[20] = 1920932;
//	  expArray[21] = 1927156;
//	  expArray[22] = 1924734;
//	  expArray[23] = 1914084;
//	  expArray[24] = 1895678;
//	  expArray[25] = 1870030;
//	  expArray[26] = 1837688;
//	  expArray[27] = 1799232;
//	  expArray[28] = 1755259;
//	  expArray[29] = 1706380;
//	  expArray[30] = 1653212;
//	  expArray[31] = 1596370;
//	  expArray[32] = 1536460;
//	  expArray[33] = 1474075;
//	  expArray[34] = 1409788;
//	  expArray[35] = 1344147;
//	  expArray[36] = 1277675;
//	  expArray[37] = 1210859;
//	  expArray[38] = 1144153;
//	  expArray[39] = 1077975;
//	  expArray[40] = 1012705;
//	  expArray[41] = 948681;
//	  expArray[42] = 886205;
//	  expArray[43] = 825537;
//	  expArray[44] = 766900;
//	  expArray[45] = 710480;
//	  expArray[46] = 656425;
//	  expArray[47] = 604851;
//	  expArray[48] = 555839;
//	  expArray[49] = 509444;
//	  expArray[50] = 465692;
//	  expArray[51] = 424581;
//	  expArray[52] = 386093;
//	  expArray[53] = 350184;
//	  expArray[54] = 316797;
//	  expArray[55] = 285859;
//	  expArray[56] = 257285;
//	  expArray[57] = 230980;
//	  expArray[58] = 206840;
//	  expArray[59] = 184756;
//	  expArray[60] = 164617;
//	  expArray[61] = 146307;
//	  expArray[62] = 129710;
//	  expArray[63] = 114711;
//	  expArray[64] = 101195;
//	  expArray[65] = 89052;
//	  expArray[66] = 78174;
//	  expArray[67] = 68456;
//	  expArray[68] = 59800;
//	  expArray[69] = 52111;
//	  expArray[70] = 45301;
//	  expArray[71] = 39285;
//	  expArray[72] = 33986;
//	  expArray[73] = 29330;
//	  expArray[74] = 25252;
//	  expArray[75] = 21688;
//	  expArray[76] = 18583;
//	  expArray[77] = 15884;
//	  expArray[78] = 13545;
//	  expArray[79] = 11522;
//	  expArray[80] = 9779;
//	  expArray[81] = 8279;
//	  expArray[82] = 6993;
//	  expArray[83] = 5892;
//	  expArray[84] = 4954;
//	  expArray[85] = 4154;
//	  expArray[86] = 3476;
//	  expArray[87] = 2901;
//	  expArray[88] = 2416;
//	  expArray[89] = 2007;
//	  expArray[90] = 1664;
//	  expArray[91] = 1376;
//	  expArray[92] = 1135;
//	  expArray[93] = 934;
//	  expArray[94] = 767;
//	  expArray[95] = 628;
//	  expArray[96] = 514;
//	  expArray[97] = 419;
//	  expArray[98] = 341;
//	  expArray[99] = 276;
//	  expArray[100] = 224;
//	  expArray[101] = 181;
//	  expArray[102] = 146;
//	  expArray[103] = 117;
//	  expArray[104] = 94;
//	  expArray[105] = 75;
//	  expArray[106] = 60;
//	  expArray[107] = 48;
//	  expArray[108] = 38;
//	  expArray[109] = 30;
//	  expArray[110] = 24;
//	  expArray[111] = 19;
//	  expArray[112] = 15;
//	  expArray[113] = 12;
//	  expArray[114] = 9;
//	  expArray[115] = 7;
//	  expArray[116] = 6;
//	  expArray[117] = 4;
//	  expArray[118] = 3;
//	  expArray[119] = 3;
//	  expArray[120] = 2;
//	  expArray[121] = 2;
//	  expArray[122] = 1;
//	  expArray[123] = 1;
//	  expArray[124] = 1;
//	  expArray[125] = 1;
//	  //for(i=126;i<255;i++)
//	  //expArray[i]=0;
//	  expArray[126] = 0;
//	  expArray[127] = 0;
//	  expArray[128] = 0;
//	  expArray[129] = 0;
//	  expArray[130] = 0;
//	  expArray[131] = 0;
//	  expArray[132] = 0;
//	  expArray[133] = 0;
//	  expArray[134] = 0;
//	  expArray[135] = 0;
//	  expArray[136] = 0;
//	  expArray[137] = 0;
//	  expArray[138] = 0;
//	  expArray[139] = 0;
//	  expArray[140] = 0;
//	  expArray[141] = 0;
//	  expArray[142] = 0;
//	  expArray[143] = 0;
//	  expArray[144] = 0;
//	  expArray[145] = 0;
//	  expArray[146] = 0;
//	  expArray[147] = 0;
//	  expArray[148] = 0;
//	  expArray[149] = 0;
//	  expArray[150] = 0;
//	  expArray[151] = 0;
//	  expArray[152] = 0;
//	  expArray[153] = 0;
//	  expArray[154] = 0;
//	  expArray[155] = 0;
//	  expArray[156] = 0;
//	  expArray[157] = 0;
//	  expArray[158] = 0;
//	  expArray[159] = 0;
//	  expArray[160] = 0;
//	  expArray[161] = 0;
//	  expArray[162] = 0;
//	  expArray[163] = 0;
//	  expArray[164] = 0;
//	  expArray[165] = 0;
//	  expArray[166] = 0;
//	  expArray[167] = 0;
//	  expArray[168] = 0;
//	  expArray[169] = 0;
//	  expArray[170] = 0;
//	  expArray[171] = 0;
//	  expArray[172] = 0;
//	  expArray[173] = 0;
//	  expArray[174] = 0;
//	  expArray[175] = 0;
//	  expArray[176] = 0;
//	  expArray[177] = 0;
//	  expArray[178] = 0;
//	  expArray[179] = 0;
//	  expArray[180] = 0;
//	  expArray[181] = 0;
//	  expArray[182] = 0;
//	  expArray[183] = 0;
//	  expArray[184] = 0;
//	  expArray[185] = 0;
//	  expArray[186] = 0;
//	  expArray[187] = 0;
//	  expArray[188] = 0;
//	  expArray[189] = 0;
//	  expArray[190] = 0;
//	  expArray[191] = 0;
//	  expArray[192] = 0;
//	  expArray[193] = 0;
//	  expArray[194] = 0;
//	  expArray[195] = 0;
//	  expArray[196] = 0;
//	  expArray[197] = 0;
//	  expArray[198] = 0;
//	  expArray[199] = 0;
//	  expArray[200] = 0;
//	  expArray[201] = 0;
//	  expArray[202] = 0;
//	  expArray[203] = 0;
//	  expArray[204] = 0;
//	  expArray[205] = 0;
//	  expArray[206] = 0;
//	  expArray[207] = 0;
//	  expArray[208] = 0;
//	  expArray[209] = 0;
//	  expArray[210] = 0;
//	  expArray[211] = 0;
//	  expArray[212] = 0;
//	  expArray[213] = 0;
//	  expArray[214] = 0;
//	  expArray[215] = 0;
//	  expArray[216] = 0;
//	  expArray[217] = 0;
//	  expArray[218] = 0;
//	  expArray[219] = 0;
//	  expArray[220] = 0;
//	  expArray[221] = 0;
//	  expArray[222] = 0;
//	  expArray[223] = 0;
//	  expArray[224] = 0;
//	  expArray[225] = 0;
//	  expArray[226] = 0;
//	  expArray[227] = 0;
//	  expArray[228] = 0;
//	  expArray[229] = 0;
//	  expArray[230] = 0;
//	  expArray[231] = 0;
//	  expArray[232] = 0;
//	  expArray[233] = 0;
//	  expArray[234] = 0;
//	  expArray[235] = 0;
//	  expArray[236] = 0;
//	  expArray[237] = 0;
//	  expArray[238] = 0;
//	  expArray[239] = 0;
//	  expArray[240] = 0;
//	  expArray[241] = 0;
//	  expArray[242] = 0;
//	  expArray[243] = 0;
//	  expArray[244] = 0;
//	  expArray[245] = 0;
//	  expArray[246] = 0;
//	  expArray[247] = 0;
//	  expArray[248] = 0;
//	  expArray[249] = 0;
//	  expArray[250] = 0;
//	  expArray[251] = 0;
//	  expArray[252] = 0;
//	  expArray[253] = 0;
//	  expArray[254] = 0;
//	  expArray[255] = 0;

//	unsigned int div[256];
//	/*
//	 * div[index] = 1/(255-index)
//	*/
//	  div[0] = 257;
//	  div[1] = 258;
//	  div[2] = 259;
//	  div[3] = 260;
//	  div[4] = 261;
//	  div[5] = 262;
//	  div[6] = 263;
//	  div[7] = 264;
//	  div[8] = 265;
//	  div[9] = 266;
//	  div[10] = 267;
//	  div[11] = 268;
//	  div[12] = 269;
//	  div[13] = 270;
//	  div[14] = 271;
//	  div[15] = 273;
//	  div[16] = 274;
//	  div[17] = 275;
//	  div[18] = 276;
//	  div[19] = 277;
//	  div[20] = 278;
//	  div[21] = 280;
//	  div[22] = 281;
//	  div[23] = 282;
//	  div[24] = 283;
//	  div[25] = 284;
//	  div[26] = 286;
//	  div[27] = 287;
//	  div[28] = 288;
//	  div[29] = 289;
//	  div[30] = 291;
//	  div[31] = 292;
//	  div[32] = 293;
//	  div[33] = 295;
//	  div[34] = 296;
//	  div[35] = 297;
//	  div[36] = 299;
//	  div[37] = 300;
//	  div[38] = 302;
//	  div[39] = 303;
//	  div[40] = 304;
//	  div[41] = 306;
//	  div[42] = 307;
//	  div[43] = 309;
//	  div[44] = 310;
//	  div[45] = 312;
//	  div[46] = 313;
//	  div[47] = 315;
//	  div[48] = 316;
//	  div[49] = 318;
//	  div[50] = 319;
//	  div[51] = 321;
//	  div[52] = 322;
//	  div[53] = 324;
//	  div[54] = 326;
//	  div[55] = 327;
//	  div[56] = 329;
//	  div[57] = 330;
//	  div[58] = 332;
//	  div[59] = 334;
//	  div[60] = 336;
//	  div[61] = 337;
//	  div[62] = 339;
//	  div[63] = 341;
//	  div[64] = 343;
//	  div[65] = 344;
//	  div[66] = 346;
//	  div[67] = 348;
//	  div[68] = 350;
//	  div[69] = 352;
//	  div[70] = 354;
//	  div[71] = 356;
//	  div[72] = 358;
//	  div[73] = 360;
//	  div[74] = 362;
//	  div[75] = 364;
//	  div[76] = 366;
//	  div[77] = 368;
//	  div[78] = 370;
//	  div[79] = 372;
//	  div[80] = 374;
//	  div[81] = 376;
//	  div[82] = 378;
//	  div[83] = 381;
//	  div[84] = 383;
//	  div[85] = 385;
//	  div[86] = 387;
//	  div[87] = 390;
//	  div[88] = 392;
//	  div[89] = 394;
//	  div[90] = 397;
//	  div[91] = 399;
//	  div[92] = 402;
//	  div[93] = 404;
//	  div[94] = 407;
//	  div[95] = 409;
//	  div[96] = 412;
//	  div[97] = 414;
//	  div[98] = 417;
//	  div[99] = 420;
//	  div[100] = 422;
//	  div[101] = 425;
//	  div[102] = 428;
//	  div[103] = 431;
//	  div[104] = 434;
//	  div[105] = 436;
//	  div[106] = 439;
//	  div[107] = 442;
//	  div[108] = 445;
//	  div[109] = 448;
//	  div[110] = 451;
//	  div[111] = 455;
//	  div[112] = 458;
//	  div[113] = 461;
//	  div[114] = 464;
//	  div[115] = 468;
//	  div[116] = 471;
//	  div[117] = 474;
//	  div[118] = 478;
//	  div[119] = 481;
//	  div[120] = 485;
//	  div[121] = 489;
//	  div[122] = 492;
//	  div[123] = 496;
//	  div[124] = 500;
//	  div[125] = 504;
//	  div[126] = 508;
//	  div[127] = 512;
//	  div[128] = 516;
//	  div[129] = 520;
//	  div[130] = 524;
//	  div[131] = 528;
//	  div[132] = 532;
//	  div[133] = 537;
//	  div[134] = 541;
//	  div[135] = 546;
//	  div[136] = 550;
//	  div[137] = 555;
//	  div[138] = 560;
//	  div[139] = 564;
//	  div[140] = 569;
//	  div[141] = 574;
//	  div[142] = 579;
//	  div[143] = 585;
//	  div[144] = 590;
//	  div[145] = 595;
//	  div[146] = 601;
//	  div[147] = 606;
//	  div[148] = 612;
//	  div[149] = 618;
//	  div[150] = 624;
//	  div[151] = 630;
//	  div[152] = 636;
//	  div[153] = 642;
//	  div[154] = 648;
//	  div[155] = 655;
//	  div[156] = 661;
//	  div[157] = 668;
//	  div[158] = 675;
//	  div[159] = 682;
//	  div[160] = 689;
//	  div[161] = 697;
//	  div[162] = 704;
//	  div[163] = 712;
//	  div[164] = 720;
//	  div[165] = 728;
//	  div[166] = 736;
//	  div[167] = 744;
//	  div[168] = 753;
//	  div[169] = 762;
//	  div[170] = 771;
//	  div[171] = 780;
//	  div[172] = 789;
//	  div[173] = 799;
//	  div[174] = 809;
//	  div[175] = 819;
//	  div[176] = 829;
//	  div[177] = 840;
//	  div[178] = 851;
//	  div[179] = 862;
//	  div[180] = 873;
//	  div[181] = 885;
//	  div[182] = 897;
//	  div[183] = 910;
//	  div[184] = 923;
//	  div[185] = 936;
//	  div[186] = 949;
//	  div[187] = 963;
//	  div[188] = 978;
//	  div[189] = 992;
//	  div[190] = 1008;
//	  div[191] = 1024;
//	  div[192] = 1040;
//	  div[193] = 1057;
//	  div[194] = 1074;
//	  div[195] = 1092;
//	  div[196] = 1110;
//	  div[197] = 1129;
//	  div[198] = 1149;
//	  div[199] = 1170;
//	  div[200] = 1191;
//	  div[201] = 1213;
//	  div[202] = 1236;
//	  div[203] = 1260;
//	  div[204] = 1285;
//	  div[205] = 1310;
//	  div[206] = 1337;
//	  div[207] = 1365;
//	  div[208] = 1394;
//	  div[209] = 1424;
//	  div[210] = 1456;
//	  div[211] = 1489;
//	  div[212] = 1524;
//	  div[213] = 1560;
//	  div[214] = 1598;
//	  div[215] = 1638;
//	  div[216] = 1680;
//	  div[217] = 1724;
//	  div[218] = 1771;
//	  div[219] = 1820;
//	  div[220] = 1872;
//	  div[221] = 1927;
//	  div[222] = 1985;
//	  div[223] = 2048;
//	  div[224] = 2114;
//	  div[225] = 2184;
//	  div[226] = 2259;
//	  div[227] = 2340;
//	  div[228] = 2427;
//	  div[229] = 2520;
//	  div[230] = 2621;
//	  div[231] = 2730;
//	  div[232] = 2849;
//	  div[233] = 2978;
//	  div[234] = 3120;
//	  div[235] = 3276;
//	  div[236] = 3449;
//	  div[237] = 3640;
//	  div[238] = 3855;
//	  div[239] = 4096;
//	  div[240] = 4369;
//	  div[241] = 4681;
//	  div[242] = 5041;
//	  div[243] = 5461;
//	  div[244] = 5957;
//	  div[245] = 6553;
//	  div[246] = 7281;
//	  div[247] = 8192;
//	  div[248] = 9362;
//	  div[249] = 10922;
//	  div[250] = 13107;
//	  div[251] = 16384;
//	  div[252] = 21845;
//	  div[253] = 32768;
//	  div[254] = 65536;
//	  div[255] = 65536;

	  fixed7 div[256];
	  div[ 0 ]= 1.0 ;
	  div[ 1 ]= 1.0039370078740157 ;
	  div[ 2 ]= 1.007905138339921 ;
	  div[ 3 ]= 1.0119047619047619 ;
	  div[ 4 ]= 1.0159362549800797 ;
	  div[ 5 ]= 1.02 ;
	  div[ 6 ]= 1.0240963855421688 ;
	  div[ 7 ]= 1.028225806451613 ;
	  div[ 8 ]= 1.0323886639676114 ;
	  div[ 9 ]= 1.0365853658536586 ;
	  div[ 10 ]= 1.0408163265306123 ;
	  div[ 11 ]= 1.0450819672131149 ;
	  div[ 12 ]= 1.0493827160493827 ;
	  div[ 13 ]= 1.0537190082644627 ;
	  div[ 14 ]= 1.058091286307054 ;
	  div[ 15 ]= 1.0625 ;
	  div[ 16 ]= 1.0669456066945606 ;
	  div[ 17 ]= 1.0714285714285714 ;
	  div[ 18 ]= 1.0759493670886076 ;
	  div[ 19 ]= 1.0805084745762712 ;
	  div[ 20 ]= 1.0851063829787233 ;
	  div[ 21 ]= 1.0897435897435896 ;
	  div[ 22 ]= 1.094420600858369 ;
	  div[ 23 ]= 1.0991379310344827 ;
	  div[ 24 ]= 1.103896103896104 ;
	  div[ 25 ]= 1.108695652173913 ;
	  div[ 26 ]= 1.1135371179039302 ;
	  div[ 27 ]= 1.118421052631579 ;
	  div[ 28 ]= 1.1233480176211454 ;
	  div[ 29 ]= 1.1283185840707965 ;
	  div[ 30 ]= 1.1333333333333333 ;
	  div[ 31 ]= 1.1383928571428572 ;
	  div[ 32 ]= 1.1434977578475336 ;
	  div[ 33 ]= 1.1486486486486487 ;
	  div[ 34 ]= 1.1538461538461537 ;
	  div[ 35 ]= 1.1590909090909092 ;
	  div[ 36 ]= 1.1643835616438356 ;
	  div[ 37 ]= 1.1697247706422018 ;
	  div[ 38 ]= 1.1751152073732718 ;
	  div[ 39 ]= 1.1805555555555556 ;
	  div[ 40 ]= 1.186046511627907 ;
	  div[ 41 ]= 1.191588785046729 ;
	  div[ 42 ]= 1.1971830985915493 ;
	  div[ 43 ]= 1.2028301886792452 ;
	  div[ 44 ]= 1.2085308056872037 ;
	  div[ 45 ]= 1.2142857142857142 ;
	  div[ 46 ]= 1.2200956937799043 ;
	  div[ 47 ]= 1.2259615384615385 ;
	  div[ 48 ]= 1.2318840579710144 ;
	  div[ 49 ]= 1.2378640776699028 ;
	  div[ 50 ]= 1.2439024390243902 ;
	  div[ 51 ]= 1.25 ;
	  div[ 52 ]= 1.2561576354679802 ;
	  div[ 53 ]= 1.2623762376237624 ;
	  div[ 54 ]= 1.2686567164179106 ;
	  div[ 55 ]= 1.275 ;
	  div[ 56 ]= 1.2814070351758795 ;
	  div[ 57 ]= 1.2878787878787878 ;
	  div[ 58 ]= 1.2944162436548223 ;
	  div[ 59 ]= 1.3010204081632653 ;
	  div[ 60 ]= 1.3076923076923077 ;
	  div[ 61 ]= 1.3144329896907216 ;
	  div[ 62 ]= 1.3212435233160622 ;
	  div[ 63 ]= 1.328125 ;
	  div[ 64 ]= 1.3350785340314135 ;
	  div[ 65 ]= 1.3421052631578947 ;
	  div[ 66 ]= 1.3492063492063493 ;
	  div[ 67 ]= 1.3563829787234043 ;
	  div[ 68 ]= 1.3636363636363635 ;
	  div[ 69 ]= 1.3709677419354838 ;
	  div[ 70 ]= 1.3783783783783783 ;
	  div[ 71 ]= 1.3858695652173914 ;
	  div[ 72 ]= 1.3934426229508197 ;
	  div[ 73 ]= 1.401098901098901 ;
	  div[ 74 ]= 1.408839779005525 ;
	  div[ 75 ]= 1.4166666666666667 ;
	  div[ 76 ]= 1.4245810055865922 ;
	  div[ 77 ]= 1.4325842696629214 ;
	  div[ 78 ]= 1.4406779661016949 ;
	  div[ 79 ]= 1.4488636363636365 ;
	  div[ 80 ]= 1.457142857142857 ;
	  div[ 81 ]= 1.4655172413793103 ;
	  div[ 82 ]= 1.4739884393063585 ;
	  div[ 83 ]= 1.4825581395348837 ;
	  div[ 84 ]= 1.4912280701754386 ;
	  div[ 85 ]= 1.5 ;
	  div[ 86 ]= 1.5088757396449703 ;
	  div[ 87 ]= 1.5178571428571428 ;
	  div[ 88 ]= 1.526946107784431 ;
	  div[ 89 ]= 1.536144578313253 ;
	  div[ 90 ]= 1.5454545454545454 ;
	  div[ 91 ]= 1.5548780487804879 ;
	  div[ 92 ]= 1.5644171779141105 ;
	  div[ 93 ]= 1.5740740740740742 ;
	  div[ 94 ]= 1.5838509316770186 ;
	  div[ 95 ]= 1.59375 ;
	  div[ 96 ]= 1.6037735849056605 ;
	  div[ 97 ]= 1.6139240506329113 ;
	  div[ 98 ]= 1.624203821656051 ;
	  div[ 99 ]= 1.6346153846153846 ;
	  div[ 100 ]= 1.6451612903225807 ;
	  div[ 101 ]= 1.655844155844156 ;
	  div[ 102 ]= 1.6666666666666667 ;
	  div[ 103 ]= 1.6776315789473684 ;
	  div[ 104 ]= 1.6887417218543046 ;
	  div[ 105 ]= 1.7 ;
	  div[ 106 ]= 1.7114093959731544 ;
	  div[ 107 ]= 1.722972972972973 ;
	  div[ 108 ]= 1.7346938775510203 ;
	  div[ 109 ]= 1.7465753424657535 ;
	  div[ 110 ]= 1.7586206896551724 ;
	  div[ 111 ]= 1.7708333333333333 ;
	  div[ 112 ]= 1.7832167832167831 ;
	  div[ 113 ]= 1.795774647887324 ;
	  div[ 114 ]= 1.8085106382978724 ;
	  div[ 115 ]= 1.8214285714285714 ;
	  div[ 116 ]= 1.8345323741007193 ;
	  div[ 117 ]= 1.8478260869565217 ;
	  div[ 118 ]= 1.8613138686131387 ;
	  div[ 119 ]= 1.875 ;
	  div[ 120 ]= 1.8888888888888888 ;
	  div[ 121 ]= 1.9029850746268657 ;
	  div[ 122 ]= 1.9172932330827068 ;
	  div[ 123 ]= 1.9318181818181819 ;
	  div[ 124 ]= 1.9465648854961832 ;
	  div[ 125 ]= 1.9615384615384615 ;
	  div[ 126 ]= 1.9767441860465116 ;
	  div[ 127 ]= 1.9921875 ;
	  div[ 128 ]= 2.0078740157480315 ;
	  div[ 129 ]= 2.0238095238095237 ;
	  div[ 130 ]= 2.04 ;
	  div[ 131 ]= 2.056451612903226 ;
	  div[ 132 ]= 2.073170731707317 ;
	  div[ 133 ]= 2.0901639344262297 ;
	  div[ 134 ]= 2.1074380165289255 ;
	  div[ 135 ]= 2.125 ;
	  div[ 136 ]= 2.142857142857143 ;
	  div[ 137 ]= 2.1610169491525424 ;
	  div[ 138 ]= 2.1794871794871793 ;
	  div[ 139 ]= 2.1982758620689653 ;
	  div[ 140 ]= 2.217391304347826 ;
	  div[ 141 ]= 2.236842105263158 ;
	  div[ 142 ]= 2.256637168141593 ;
	  div[ 143 ]= 2.2767857142857144 ;
	  div[ 144 ]= 2.2972972972972974 ;
	  div[ 145 ]= 2.3181818181818183 ;
	  div[ 146 ]= 2.3394495412844036 ;
	  div[ 147 ]= 2.361111111111111 ;
	  div[ 148 ]= 2.383177570093458 ;
	  div[ 149 ]= 2.4056603773584904 ;
	  div[ 150 ]= 2.4285714285714284 ;
	  div[ 151 ]= 2.451923076923077 ;
	  div[ 152 ]= 2.4757281553398056 ;
	  div[ 153 ]= 2.5 ;
	  div[ 154 ]= 2.5247524752475248 ;
	  div[ 155 ]= 2.55 ;
	  div[ 156 ]= 2.5757575757575757 ;
	  div[ 157 ]= 2.6020408163265305 ;
	  div[ 158 ]= 2.6288659793814433 ;
	  div[ 159 ]= 2.65625 ;
	  div[ 160 ]= 2.6842105263157894 ;
	  div[ 161 ]= 2.7127659574468086 ;
	  div[ 162 ]= 2.7419354838709675 ;
	  div[ 163 ]= 2.7717391304347827 ;
	  div[ 164 ]= 2.802197802197802 ;
	  div[ 165 ]= 2.8333333333333335 ;
	  div[ 166 ]= 2.865168539325843 ;
	  div[ 167 ]= 2.897727272727273 ;
	  div[ 168 ]= 2.9310344827586206 ;
	  div[ 169 ]= 2.9651162790697674 ;
	  div[ 170 ]= 3.0 ;
	  div[ 171 ]= 3.0357142857142856 ;
	  div[ 172 ]= 3.072289156626506 ;
	  div[ 173 ]= 3.1097560975609757 ;
	  div[ 174 ]= 3.1481481481481484 ;
	  div[ 175 ]= 3.1875 ;
	  div[ 176 ]= 3.2278481012658227 ;
	  div[ 177 ]= 3.269230769230769 ;
	  div[ 178 ]= 3.311688311688312 ;
	  div[ 179 ]= 3.3552631578947367 ;
	  div[ 180 ]= 3.4 ;
	  div[ 181 ]= 3.445945945945946 ;
	  div[ 182 ]= 3.493150684931507 ;
	  div[ 183 ]= 3.5416666666666665 ;
	  div[ 184 ]= 3.591549295774648 ;
	  div[ 185 ]= 3.642857142857143 ;
	  div[ 186 ]= 3.6956521739130435 ;
	  div[ 187 ]= 3.75 ;
	  div[ 188 ]= 3.8059701492537314 ;
	  div[ 189 ]= 3.8636363636363638 ;
	  div[ 190 ]= 3.923076923076923 ;
	  div[ 191 ]= 3.984375 ;
	  div[ 192 ]= 4.0476190476190474 ;
	  div[ 193 ]= 4.112903225806452 ;
	  div[ 194 ]= 4.180327868852459 ;
	  div[ 195 ]= 4.25 ;
	  div[ 196 ]= 4.322033898305085 ;
	  div[ 197 ]= 4.396551724137931 ;
	  div[ 198 ]= 4.473684210526316 ;
	  div[ 199 ]= 4.553571428571429 ;
	  div[ 200 ]= 4.636363636363637 ;
	  div[ 201 ]= 4.722222222222222 ;
	  div[ 202 ]= 4.811320754716981 ;
	  div[ 203 ]= 4.903846153846154 ;
	  div[ 204 ]= 5.0 ;
	  div[ 205 ]= 5.1 ;
	  div[ 206 ]= 5.204081632653061 ;
	  div[ 207 ]= 5.3125 ;
	  div[ 208 ]= 5.425531914893617 ;
	  div[ 209 ]= 5.543478260869565 ;
	  div[ 210 ]= 5.666666666666667 ;
	  div[ 211 ]= 5.795454545454546 ;
	  div[ 212 ]= 5.930232558139535 ;
	  div[ 213 ]= 6.071428571428571 ;
	  div[ 214 ]= 6.219512195121951 ;
	  div[ 215 ]= 6.375 ;
	  div[ 216 ]= 6.538461538461538 ;
	  div[ 217 ]= 6.7105263157894735 ;
	  div[ 218 ]= 6.891891891891892 ;
	  div[ 219 ]= 7.083333333333333 ;
	  div[ 220 ]= 7.285714285714286 ;
	  div[ 221 ]= 7.5 ;
	  div[ 222 ]= 7.7272727272727275 ;
	  div[ 223 ]= 7.96875 ;
	  div[ 224 ]= 8.225806451612904 ;
	  div[ 225 ]= 8.5 ;
	  div[ 226 ]= 8.793103448275861 ;
	  div[ 227 ]= 9.107142857142858 ;
	  div[ 228 ]= 9.444444444444445 ;
	  div[ 229 ]= 9.807692307692308 ;
	  div[ 230 ]= 10.2 ;
	  div[ 231 ]= 10.625 ;
	  div[ 232 ]= 11.08695652173913 ;
	  div[ 233 ]= 11.590909090909092 ;
	  div[ 234 ]= 12.142857142857142 ;
	  div[ 235 ]= 12.75 ;
	  div[ 236 ]= 13.421052631578947 ;
	  div[ 237 ]= 14.166666666666666 ;
	  div[ 238 ]= 15.0 ;
	  div[ 239 ]= 15.9375 ;
	  div[ 240 ]= 17.0 ;
	  div[ 241 ]= 18.214285714285715 ;
	  div[ 242 ]= 19.615384615384617 ;
	  div[ 243 ]= 21.25 ;
	  div[ 244 ]= 23.181818181818183 ;
	  div[ 245 ]= 25.5 ;
	  div[ 246 ]= 28.333333333333332 ;
	  div[ 247 ]= 31.875 ;
	  div[ 248 ]= 36.42857142857143 ;
	  div[ 249 ]= 42.5 ;
	  div[ 250 ]= 51.0 ;
	  div[ 251 ]= 63.75 ;
	  div[ 252 ]= 85.0 ;
	  div[ 253 ]= 127.5 ;
	  div[ 254 ]= 255.0 ;
	  div[ 255 ]= 255.0 ;




		hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC3> img_in(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	//	GRAY_IMAGE grayMat_1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE blue(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE green(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE red(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE histeq_blue(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE histeq_green(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE histeq_red(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE histeq(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE airlight_initial(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE img_out1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE img_out2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE img_out3(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE img_out4(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE airlight(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE airlight_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE airlight_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE airlight_copy1a(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE airlight_copy3(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	//	GRAY_IMAGE histeq_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	//	GRAY_IMAGE histeq_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE histeq_min(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE blue_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE blue_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE green_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE green_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE red_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE red_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		GRAY_IMAGE restored_image_b(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE restored_image_g(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE restored_image_r(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	//	GRAY_IMAGE restored_image(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE img_out_b(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE img_out_g(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
		GRAY_IMAGE img_out_r(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

		hls::Mat<IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS, HLS_8UC3> img_out(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	//	GRAY_IMAGE img_out(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

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
	    hls::Split(img_in,blue,green,red);
//
	    hls::Duplicate(blue,blue_copy1,blue_copy2);
	    hls::Duplicate(green,green_copy1,green_copy2);
	    hls::Duplicate(red,red_copy1,red_copy2);

	//	hls::CvtColor<HLS_BGR2GRAY, HLS_8UC3, HLS_8UC1>(img_in, grayMat_1);

	    hls::EqualizeHist( blue_copy1,histeq_blue );
	    hls::EqualizeHist( green_copy1,histeq_green );
	    hls::EqualizeHist( red_copy1,histeq_red );

	    dark_channel_prior(histeq_min,histeq_blue,histeq_green,histeq_red);
	    //Apply histogram equalization
	//    hls::EqualizeHist( grayMat_1,histeq );
	//    hls::Duplicate(histeq,histeq_copy1,histeq_copy2);
	//    //airlight map initial estimation
	    initial_estimate(airlight_initial,histeq_min);
//	    normalize(airlight_initial_norm,airlight_initial);
	//	hls::AddWeighted(histeq_copy2, 1, airlight_initial, -1, 0, img_out);

	    //anisotropic diffusion
	    anisotropic_diffusion(airlight_initial, img_out1,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
	    anisotropic_diffusion(img_out1, img_out2,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
	    anisotropic_diffusion(img_out2, img_out3,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
	    anisotropic_diffusion(img_out3, img_out4,left_kernel,right_kernel,up_kernel,down_kernel,expArray);
	    anisotropic_diffusion(img_out4, airlight,left_kernel,right_kernel,up_kernel,down_kernel,expArray);

//	    hls::Duplicate(airlight,airlight_copy1,airlight_copy1a);
//	    hls::Duplicate(airlight_copy1a,airlight_copy2,airlight_copy3);
////
//////	    hls::AddWeighted(histeq_copy2, 1, img_out1, -1, 0, img_out);
//	    restoration(airlight_copy1,blue_copy2,restored_image_b,div);
//	    restoration(airlight_copy2,green_copy2,restored_image_g,div);
//	    restoration(airlight_copy3,red_copy2,restored_image_r,div);
//
//
//
//	    doHiststretch( restored_image_b, img_out_b,10,108);
//	    doHiststretch( restored_image_g, img_out_g,10,108);
//	    doHiststretch( restored_image_r, img_out_r,10,108);
//
//	    hls::Merge(restored_image_b,restored_image_g,restored_image_r,img_out);

	    hls::Mat2AXIvideo(airlight, outstream);
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
    hls::Scalar<1,fixed8> iteration_added;
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
    	    output_val = clip(input_val.val[0] + iteration_added.val[0]) ;
    	    img_out.write(output_val);
    	}
    }
}

unsigned char clip(unsigned int val)
{
	unsigned char out;
	if (val>255)
	{
		out =(unsigned char)255;
	}
	else if (val<0)
	{
		out = (unsigned char)0;

	}
	else
		out = (unsigned char)val;
	return out;
}

void restoration(GRAY_IMAGE& airlight,GRAY_IMAGE& img_in, GRAY_IMAGE& img_out,fixed7 div[256])
{
	GRAY_IMAGE intermed_difference(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE airlight_copy1(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);
	GRAY_IMAGE airlight_copy2(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	hls::Duplicate(airlight,airlight_copy1,airlight_copy2);
//	hls::AddWeighted(img_in, 1, airlight_copy1, -1, 0, intermed_difference);
	find_modulus(img_in, airlight_copy1,intermed_difference);

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
    		airlight_copy2.read(input_val);
    	    output_val.val[0] = clip(diff_val.val[0]*div[input_val.val[0]]);
    	    img_out.write(output_val);
    	}
    }

}

void initial_estimate(GRAY_IMAGE& airlight,GRAY_IMAGE& img_in)
{
    hls::Scalar<1,unsigned char> input_val;
    hls::Scalar<1,unsigned char> output_val;
    fixed7 beta = 0.9000000;

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
void dark_channel_prior(GRAY_IMAGE& histeq_min, GRAY_IMAGE& blue, GRAY_IMAGE& green, GRAY_IMAGE& red)
{
	GRAY_IMAGE bg_min(IMG_HEIGHT_OR_ROWS, IMG_WIDTH_OR_COLS);

	hls::Min(blue,green,bg_min);
	hls::Min(bg_min,red,histeq_min);

}

void find_modulus(GRAY_IMAGE& img_in_copy1, GRAY_IMAGE& airlight,GRAY_IMAGE& intermed_difference)
{
    hls::Scalar<1,unsigned char> intensity_val;
    hls::Scalar<1,unsigned char> airlight_val;
    hls::Scalar<1,unsigned char> modulo_val;

    ROW: for(int row = 0; row < IMG_HEIGHT_OR_ROWS; row++)
    {
#pragma HLS LOOP_TRIPCOUNT min=1 max=478

    	COL: for(int col = 0; col < IMG_WIDTH_OR_COLS; col++)
    	{
#pragma HLS LOOP_TRIPCOUNT min=1 max=638
#pragma HLS PIPELINE
//#pragma HLS DEPENDENCE

    		img_in_copy1.read(intensity_val);
    		airlight.read(airlight_val);
    		modulo_val = (intensity_val.val[0]>=airlight_val.val[0])?(intensity_val.val[0]-airlight_val.val[0]):(airlight_val.val[0]-intensity_val.val[0]);
    		intermed_difference.write(modulo_val);
    	}
    }
}

void doHiststretch( GRAY_IMAGE& restored_image, GRAY_IMAGE& out_image, unsigned char xMin, unsigned char xMax)
{

    hls::Scalar<1,unsigned char> restored_val;
    hls::Scalar<1,unsigned char> out_val;

    float pixel_val;
	float xMax_minus_xMin = xMax-xMin;

    ROW: for(int row = 0; row < IMG_HEIGHT_OR_ROWS; row++)
    {
#pragma HLS LOOP_TRIPCOUNT min=1 max=478

    	COL: for(int col = 0; col < IMG_WIDTH_OR_COLS; col++)
    	{
#pragma HLS LOOP_TRIPCOUNT min=1 max=638
#pragma HLS PIPELINE
//#pragma HLS DEPENDENCE

		//read
		restored_image.read(restored_val);

		//get the pixel data
		pixel_val = restored_val.val[0];

		//calculate the histogram stretch
		if (pixel_val>xMax)
		{
			out_val = clip((pixel_val-xMax)/2+242);
		}
		else if(pixel_val>xMin)
		{
			out_val = clip((pixel_val-xMin)/xMax_minus_xMin*230+13);
		}
		else
		{
			out_val = clip(pixel_val/xMin*13);
		}

		//send to the stream (block if FIFO receiver is full)
		out_image.write(out_val);
	}
}
}

void doHist(GRAY_IMAGE &input,int histo[256])
{
    hls::Scalar<1,unsigned char> intensity_val;
    hls::Scalar<1,unsigned char> airlight_val;
    hls::Scalar<1,unsigned char> modulo_val;

	//Initialize to zero
	for (int idxhist=0;idxhist<256;idxhist++)
	{
	#pragma HLS PIPELINE
		histo[idxhist]=0;
	}

	//iterate over stream
	for (int idxpixel=0;idxpixel<(638*478);idxpixel++)
	{
		//read and cache
		intensity_val = input.read();

		//calculate histogram
		histo[intensity_val.val[0]]+=1;
	}

}
