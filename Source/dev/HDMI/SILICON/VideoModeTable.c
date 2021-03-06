/***********************************************************************************/
/*  Copyright (c) 2002-2009, Silicon Image, Inc.  All rights reserved.             */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1060 East Arques Avenue, Sunnyvale, California 94085                           */
/***********************************************************************************/
//#include <stdio.h>
//#include "MCU_Regs.h"
#include "dev.h"
#include "defs.h"
#include "TypeDefs.h"
#include "Constants.h"
#include "Externals.h"
#include "VideoModeTable.h"

//
// These are the VIC codes that we support in a 3D mode
//
#define VIC_FOR_480P_60Hz_4X3			2		// 720p x 480p @ 60Hz
#define VIC_FOR_480P_60Hz_16X9			3		// 720p x 480p @ 60Hz
#define VIC_FOR_720P_60Hz				4		// 1280 x 720p @60Mhz
#define VIC_FOR_1080i_60Hz				5		// 1920 x 1080i @ 6Mhz
#define VIC_FOR_1080p_60Hz				16		// 1920 x 1080i @ 6Mhz
#define VIC_FOR_720P_50Hz				19		// 1280 x 720p @ 5Mhz
#define VIC_FOR_1080i_50Hz				20		// 1920 x 1080i @ 5Mhz
#define VIC_FOR_1080p_50Hz				31		// 1280 x 720p @100Hz
#define VIC_FOR_1080p_24Hz				32		// 1920 x 720p @24Hz


//code const VModeInfoType VModesTable[] =
const VModeInfoType VModesTable[] =
{
	//===================================================================================================================================================================================================================================
	//		   VIC					Refresh type Refresh-Rate Pixel-Totals	Position	 Active 	Aspect	 Int  Length		  Hbit	Vbit  Field  Pixel			Vact Space/Blank
	//		  1   2  SubM	PixClk	V/H Position	   VFreq   H	  V 	 H	  V 	  H    V	Ratio	 Adj  H   V  Top  Dly HSync VSync Offset Repl  Space1 Space2 Blank1 Blank2 Blank3  3D
	//===================================================================================================================================================================================================================================
	{{		  1,  0, NSM},	2517,  {ProgrVNegHNeg,	   6000, { 800,  525}}, {144, 35}, { 640, 480}, R_4,	 {0,  96, 2, 33,  48,  16,	10,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 0 - 1.	   640	x 480p @ 60 VGA
	{{		  2,  3, NSM},	2700,  {ProgrVNegHNeg,	   6000, { 858,  525}}, {122, 36}, { 720, 480}, R_4or16, {0,  62, 6, 30,  60,  19,	 9,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 1 - 2,3	   720	x 480p
	{{		  4,  0, NSM},	7425,  {ProgrVPosHPos,	   6000, {1650,  750}}, {260, 25}, {1280, 720}, R_16,	 {0,  40, 5, 20, 220, 110,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 2 - 4 	   1280 x 720p@60Hz
	{{		  5,  0, NSM},	7425,  {InterlaceVPosHPos, 6000, {2200,  562}}, {192, 20}, {1920,1080}, R_16,	 {0,  44, 5, 15, 148,  88,	 2, 1100},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 3 - 5 	   1920 x 1080i
	{{		  6,  7, NSM},	2700,  {InterlaceVNegHNeg, 6000, {1716,  264}}, {119, 18}, { 720, 480}, R_4or16, {3,  62, 3, 15, 114,  17,	 5,  429},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 4 - 6,7	   1440 x 480i,pix repl
	{{		  8,  9,   1},	2700,  {ProgrVNegHNeg,	   6000, {1716,  262}}, {119, 18}, {1440, 240}, R_4or16, {0, 124, 3, 15, 114,  38,	 4,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 5 - 8,9(1)   1440 x 240p
	{{		  8,  9,   2},	2700,  {ProgrVNegHNeg,	   6000, {1716,  263}}, {119, 18}, {1440, 240}, R_4or16, {0, 124, 3, 15, 114,  38,	 4,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 6 - 8,9(2)   1440 x 240p
	{{		 10, 11, NSM},	5400,  {InterlaceVNegHNeg, 6000, {3432,  525}}, {238, 18}, {2880, 480}, R_4or16, {0, 248, 3, 15, 228,  76,	 4, 1716},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 7 - 10,11    2880 x 480i
	{{		 12, 13,   1},	5400,  {ProgrVNegHNeg,	   6000, {3432,  262}}, {238, 18}, {2880, 240}, R_4or16, {0, 248, 3, 15, 228,  76,	 4,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 8 - 12,13(1) 2880 x 240p
	{{		 12, 13,   2},	5400,  {ProgrVNegHNeg,	   6000, {3432,  263}}, {238, 18}, {2880, 240}, R_4or16, {0, 248, 3, 15, 228,  76,	 4,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 9 - 12,13(2) 2880 x 240p
	{{		 14, 15, NSM},	5400,  {ProgrVNegHNeg,	   6000, {1716,  525}}, {244, 36}, {1440, 480}, R_4or16, {0, 124, 6, 30, 120,  32,	 9,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 10 - 14,15	1440 x 480p
//	{{		 16,  0, NSM}, 14835,  {ProgrVPosHPos,	   6000, {2200, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148,  88,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 11 - 16		1920 x 1080p
	{{		 16,  0, NSM}, 14850,  {ProgrVPosHPos,	   6000, {2200, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148,  88,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 11 - 16		1920 x 1080p
	{{		 17, 18, NSM},	2700,  {ProgrVNegHNeg,	   5000, { 864,  625}}, {132, 44}, { 720, 576}, R_4or16, {0,  64, 5, 39,  68,  12,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 12 - 17,18	720  x 576p
	{{		 19,  0, NSM},	7425,  {ProgrVPosHPos,	   5000, {1980,  750}}, {260, 25}, {1280, 720}, R_16,	 {0,  40, 5, 20, 220, 440,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 13 - 19		1280 x 720p@50Hz
	{{		 20,  0, NSM},	7425,  {InterlaceVPosHPos, 5000, {2640, 1125}}, {192, 20}, {1920,1080}, R_16,	 {0,  44, 5, 15, 148, 528,	 2, 1320},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 14 - 20		1920 x 1080i
	{{		 21, 22, NSM},	2700,  {InterlaceVNegHNeg, 5000, {1728,  625}}, {132, 22}, { 720, 576}, R_4,	 {3,  63, 3, 19, 138,  24,	 2,  432},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 15 - 21,22	1440 x 576i
	{{		 23, 24,   1},	2700,  {ProgrVNegHNeg,	   5000, {1728,  312}}, {132, 22}, {1440, 288}, R_4or16, {0, 126, 3, 19, 138,  24,	 2,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 16 - 23,24(1) 1440 x 288p
	{{		 23, 24,   2},	2700,  {ProgrVNegHNeg,	   5000, {1728,  313}}, {132, 22}, {1440, 288}, R_4or16, {0, 126, 3, 19, 138,  24,	 2,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 17 - 23,24(2) 1440 x 288p
	{{		 23, 24,   3},	2700,  {ProgrVNegHNeg,	   5000, {1728,  314}}, {132, 22}, {1440, 288}, R_4or16, {0, 126, 3, 19, 138,  24,	 2,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 18 - 23,24(3) 1440 x 288p
	{{		 25, 26, NSM},	5400,  {InterlaceVNegHNeg, 5000, {3456,  625}}, {264, 22}, {2880, 576}, R_4or16, {0, 252, 3, 19, 276,  48,	 2, 1728},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 19 - 25,26	2880 x 576i
	{{		 27, 28,   1},	5400,  {ProgrVNegHNeg,	   5000, {3456,  312}}, {264, 22}, {2880, 288}, R_4or16, {0, 252, 3, 19, 276,  48,	 2,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 20 - 27,28(1) 2880 x 288p
	{{		 27, 28,   2},	5400,  {ProgrVNegHNeg,	   5000, {3456,  313}}, {264, 22}, {2880, 288}, R_4or16, {0, 252, 3, 19, 276,  48,	 3,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 21 - 27,28(2) 2880 x 288p
	{{		 27, 28,   3},	5400,  {ProgrVNegHNeg,	   5000, {3456,  314}}, {264, 22}, {2880, 288}, R_4or16, {0, 252, 3, 19, 276,  48,	 4,    0},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 22 - 27,28(3) 2880 x 288p
	{{		 29, 30, NSM},	5400,  {ProgrVPosHNeg,	   5000, {1728,  625}}, {264, 44}, {1440, 576}, R_4or16, {0, 128, 5, 39, 136,  24,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 23 - 29,30	1440 x 576p
	{{		 31,  0, NSM}, 14850,  {ProgrVPosHPos,	   5000, {2640, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148, 528,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 24 - 31(1)	1920 x 1080p
	{{		 32,  0, NSM},	7417,  {ProgrVPosHPos,	   2400, {2750, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148, 638,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 25 - 32(2)	1920 x 1080p@24Hz
	{{		 33,  0, NSM},	7425,  {ProgrVPosHPos,	   2500, {2640, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148, 528,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 26 - 33(3)	1920 x 1080p
	{{		 34,  0, NSM},	7417,  {ProgrVPosHPos,	   3000, {2200, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148, 528,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 27 - 34(4)	1920 x 1080p
	{{		 35, 36, NSM}, 10800,  {ProgrVNegHNeg,	   5994, {3432,  525}}, {488, 36}, {2880, 480}, R_4or16, {0, 248, 6, 30, 240,  64,	10,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 28 - 35, 36	2880 x 480p@59.94/60Hz
	{{		 37, 38, NSM}, 10800,  {ProgrVNegHNeg,	   5000, {3456,  625}}, {272, 39}, {2880, 576}, R_4or16, {0, 256, 5, 40, 272,  48,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 29 - 37, 38	2880 x 576p@50Hz
	{{		 39,  0, NSM},	7200,  {InterlaceVNegHNeg, 5000, {2304, 1250}}, {352, 62}, {1920,1080}, R_16,	 {0, 168, 5, 87, 184,  32,	24,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 30 - 39		1920 x 1080i@50Hz
	{{		 40,  0, NSM}, 14850,  {InterlaceVPosHPos, 10000,{2640, 1125}}, {192, 20}, {1920,1080}, R_16,	 {0,  44, 5, 15, 148, 528,	 2, 1320},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 31 - 40		1920 x 1080i@100Hz
	{{		 41,  0, NSM}, 14850,  {InterlaceVPosHPos, 10000,{1980,  750}}, {260, 25}, {1280, 720}, R_16,	 {0,  40, 5, 20, 220, 400,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 32 - 41		1280 x 720p@100Hz
	{{		 42, 43, NSM},	5400,  {ProgrVNegHNeg,	   10000,{ 864,  144}}, {132, 44}, { 720, 576}, R_4or16, {0,  64, 5, 39,  68,  12,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 33 - 42, 43,	720p x 576p@100Hz
	{{		 44, 45, NSM},	5400,  {InterlaceVNegHNeg, 10000,{ 864,  625}}, {132, 22}, { 720, 576}, R_4or16, {0,  63, 3, 19,  69,  12,	 2,  432},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 34 - 44, 45,	720p x 576i@100Hz, pix repl
	{{		 46,  0, NSM}, 14835,  {InterlaceVPosHPos, 11988,{2200, 1125}}, {192, 20}, {1920,1080}, R_16,	 {0,  44, 5, 15, 149,  88,	 2, 1100},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 35 - 46,		1920 x 1080i@119.88/120Hz
	{{		 47,  0, NSM}, 14835,  {ProgrVPosHPos,	   11988,{1650,  750}}, {260, 25}, {1280, 720}, R_16,	 {0,  40, 5, 20, 220, 110,	 5, 1100},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 36 - 47,		1280 x 720p@119.88/120Hz
	{{		 48, 49, NSM},	5400,  {ProgrVNegHNeg,	   11988,{ 858,  525}}, {122, 36}, { 720, 480}, R_4or16, {0,  62, 6, 30,  60,  16,	10,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 37 - 48, 49	720  x 480p@119.88/120Hz
	{{		 50, 51, NSM},	5400,  {InterlaceVNegHNeg, 11988,{ 858,  525}}, {119, 18}, { 720, 480}, R_4or16, {0,  62, 3, 15,  57,  19,	 4,  429},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 38 - 50, 51	720  x 480i@119.88/120Hz
	{{		 52, 53, NSM}, 10800,  {ProgrVNegHNeg,	   20000,{ 864,  625}}, {132, 44}, { 720, 576}, R_4or16, {0,  64, 5, 39,  68,  12,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 39 - 52, 53,	720  x 576p@200Hz
	{{		 54, 55, NSM}, 10800,  {InterlaceVNegHNeg, 20000,{ 864,  625}}, {132, 22}, { 720, 576}, R_4or16, {0,  63, 3, 19,  69,  12,	 2,  432},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 40 - 54, 55,	1440 x 576i @200Hz, pix repl
	{{		 56, 57, NSM}, 10800,  {ProgrVNegHNeg,	   24000,{ 858,  525}}, {122, 42}, { 720, 480}, R_4or16, {0,  62, 6, 30,  60,  16,	 9,    0},	  0,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 41 - 56, 57,	720  x 480p @239.76/240Hz
	{{		 58, 59, NSM}, 10800,  {InterlaceVNegHNeg, 24000,{ 858,  525}}, {119, 18}, { 720, 480}, R_4or16, {0,  62, 3, 15,  57,  19,	 4,  429},	  1,	{0, 	0,	   0,	  0,	0},    NO_3D_SUPPORT}, // 42 - 58, 59,	1440 x 480i @239.76/240Hz, pix repl

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 4K x 2K Modes:
	//===================================================================================================================================================================================================================================
	//																											  Pulse
	//		   VIC					Refresh type Refresh-Rate Pixel-Totals	 Position	  Active	Aspect	 Int  Width 		  Hbit	Vbit  Field  Pixel			Vact Space/Blank
	//		  1   2  SubM	PixClk	V/H Position	   VFreq   H	  V 	 H	  V 	  H    V	Ratio	 Adj  H   V  Top  Dly HSync VSync Offset Repl  Space1 Space2 Blank1 Blank2 Blank3  3D
	//===================================================================================================================================================================================================================================
	{{		  1,  0, NSM}, 29700, {ProgrVPosHPos,	  30000,{4400, 2250}}, {384, 82}, {3840,2160}, R_16,	{0,  88, 10, 72, 296, 176,	8,	  0},	0,	   {0,	   0,	  0,	 0,    0},	  NO_3D_SUPPORT}, // 43 - 4k x 2k 29.97/30Hz (297.000 MHz)
	{{		  2,  0, NSM}, 29700, {ProgrVNegHNeg,	  29700,{5280, 2250}}, {384, 82}, {3840,2160}, R_16,	{0,  88, 10, 72, 296,1056,	8,	  0},	0,	   {0,	   0,	  0,	 0,    0},	  NO_3D_SUPPORT}, // 44 - 4k x 2k 25Hz
	{{		  3,  0, NSM}, 29700, {ProgrVNegHNeg,	  24000,{5500, 2250}}, {384, 82}, {3840,2160}, R_16,	{0,  88, 10, 72, 296,1276,	8,	  0},	0,	   {0,	   0,	  0,	 0,    0},	  NO_3D_SUPPORT}, // 45 - 4k x 2k 24Hz (297.000 MHz)
	{{		  4  ,0, NSM}, 29700, {ProgrVNegHNeg,	  24000,{6500, 2250}}, {384, 82}, {4096,2160}, R_16,	{0,  88, 10, 72, 296,1020,	8,	  0},	0,	   {0,	   0,	  0,	 0,    0},	  NO_3D_SUPPORT}, // 46 - 4k x 2k 24Hz (SMPTE)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 3D Modes:
	//===================================================================================================================================================================================================================================
	//																											  Pulse
	//		   VIC					Refresh type Refresh-Rate Pixel-Totals	Position	  Active	Aspect	 Int  Width 		  Hbit	Vbit  Field  Pixel			Vact Space/Blank
	//		  1   2  SubM	PixClk	V/H Position	   VFreq   H	  V 	 H	  V 	  H    V	Ratio	 Adj  H   V  Top  Dly HSync VSync Offset Repl  Space1 Space2 Blank1 Blank2 Blank3  3D
	//===================================================================================================================================================================================================================================
	{{		  2,  3, NSM},	2700,  {ProgrVPosHPos,	   6000, {858,	 525}}, {122, 36}, { 720, 480}, R_4or16, {0,  62, 6, 30,  60,  16,	 9,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	8}, // 47 - 3D, 2,3 720p x 480p /60Hz, Side-by-Side (Half)
	{{		  4,  0, NSM}, 14850,  {ProgrVPosHPos,	   6000, {1650,  750}}, {260, 25}, {1280, 720}, R_16,	 {0,  40, 5, 20, 220, 110,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	0}, // 48 - 3D	4	1280 x 720p@60Hz,  Frame Packing
	{{		  5,  0, NSM}, 14850,  {InterlaceVPosHPos, 6000, {2200,  562}}, {192, 20}, {1920, 540}, R_16,	 {0,  44, 5, 15, 148,  88,	 2, 1100},	  0,	{23,   22,	   0,	  0,	0}, 	0}, // 49 - 3D, 5,	1920 x 1080i/60Hz, Frame Packing
	{{		  5,  0, NSM}, 14850,  {InterlaceVPosHPos, 6000, {2200,  562}}, {192, 20}, {1920, 540}, R_16,	 {0,  44, 5, 15, 148,  88,	 2, 1100},	  0,	{0, 	0,	  22,	 22,   23}, 	1}, // 50 - 3D, 5,	1920 x 1080i/60Hz, Field Alternative
	{{		 16,  0, NSM}, 29700,  {ProgrVPosHPos,	   6000, {2200, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148,  88,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	0}, // 51 - 3D, 16, 1920 x 1080p/60Hz, Frame Packing
	{{		 16,  0, NSM}, 29700,  {ProgrVPosHPos,	   6000, {2200, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148,  88,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	2}, // 52 - 3D, 16, 1920 x 1080p/60Hz, Line Alternative
	{{		 16,  0, NSM}, 29700,  {ProgrVPosHPos,	   6000, {2200, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148,  88,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	3}, // 53 - 3D, 16, 1920 x 1080p/60Hz, Side-by-Side (Full)
	{{		 16,  0, NSM}, 14850,  {ProgrVPosHPos,	   6000, {2200, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148,  88,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	8}, // 54 - 3D, 16, 1920 x 1080p/60Hz, Side-by-Side (Half)
	{{		 19,  0, NSM}, 14850,  {ProgrVPosHPos,	   5000, {1980,  750}}, {260, 25}, {1280, 720}, R_16,	 {0,  40, 5, 20, 220, 440,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	0}, // 55 - 3D, 19, 1280 x 720p@50Hz,  Frame Packing
	{{		 19,  0, NSM}, 14850,  {ProgrVPosHPos,	   5000, {1980,  750}}, {260, 25}, {1280, 720}, R_16,	 {0,  40, 5, 20, 220, 440,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	4}, // 56 - 3D, 19, 1280 x 720p/50Hz,  (L + depth)
	{{		 19,  0, NSM}, 29700,  {ProgrVPosHPos,	   5000, {1980,  750}}, {260, 25}, {1280, 720}, R_16,	 {0,  40, 5, 20, 220, 440,	 5,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	5}, // 57 - 3D, 19, 1280 x 720p/50Hz,  (L + depth + Gfx + G-depth)
	{{		 20,  0, NSM}, 14850,  {InterlaceVPosHPos, 5000, {2640,  562}}, {192, 20}, {1920, 540}, R_16,	 {0,  44, 5, 15, 148, 528,	 2, 1220},	  0,	{23,   22,	   0,	  0,	0}, 	0}, // 58 - 3D, 20, 1920 x 1080i/50Hz, Frame Packing
	{{		 20,  0, NSM}, 14850,  {InterlaceVPosHPos, 5000, {2640,  562}}, {192, 20}, {1920, 540}, R_16,	 {0,  44, 5, 15, 148, 528,	 2, 1220},	  0,	{0, 	0,	  22,	 22,   23}, 	1}, // 59 - 3D, 20, 1920 x 1080i/50Hz, Field Alternative
	{{		 31,  0, NSM}, 29700,  {ProgrVPosHPos,	   5000, {2640, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148, 528,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	0}, // 60 - 3D, 31, 1920 x 1080p/50Hz, Frame Packing
	{{		 31,  0, NSM}, 29700,  {ProgrVPosHPos,	   5000, {2640, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148, 528,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	2}, // 61 - 3D, 31, 1920 x 1080p/50Hz, Line Alternative
	{{		 31,  0, NSM}, 29700,  {ProgrVPosHPos,	   5000, {2650, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148, 528,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	3}, // 62 - 3D, 31, 1920 x 1080p/50Hz, Side-by-Side (Full)
	{{		 32,  0, NSM}, 14850,  {ProgrVPosHPos,	   2400, {2750, 1125}}, {192, 41}, {1920,1080}, R_16,	 {0,  44, 5, 36, 148, 638,	 4,    0},	  0,	{0, 	0,	   0,	  0,	0}, 	0}, // 63 - 3D, 32, 1920 x 1080p@24Hz, Frame Packing

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NOTE: DO NOT ATTEMPT INPUT RESOLUTIONS THAT REQUIRE PIXEL CLOCK FREQUENCIES HIGHER THAN THOSE SUPPORTED BY THE TRANSMITTER CHIP

	//===================================================================================================================================================================================================================================
	//																												Sync Pulse
	//	VIC 						 Refresh type	fresh-Rate	Pixel-Totals	Position	Active	   Aspect	Int  Width			  Hbit	Vbit  Field  Pixel			Vact Space/Blank
	// 1   2  SubM		   PixClk	 V/H Position		VFreq	H	   V		H	 V		 H	  V 	Ratio	{Adj  H   V  Top  Dly HSync VSync Offset} Repl	Space1 Space2 Blank1 Blank2 Blank3	3D
	//===================================================================================================================================================================================================================================
	{{PC_BASE  , 0,NSM},	3150,	{ProgrVNegHPos, 	8508,	{832, 445}},	{160,63},	{640,350},	 R_16,	{0,  64,  3,  60,  96,	32,  32,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 64 - 640x350@85.08
	{{PC_BASE+1, 0,NSM},	3150,	{ProgrVPosHNeg, 	8508,	{832, 445}},	{160,44},	{640,400},	 R_16,	{0,  64,  3,  41,  96,	32,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 65 - 640x400@85.08
	{{PC_BASE+2, 0,NSM},	2700,	{ProgrVPosHNeg, 	7008,	{900, 449}},	{0,0},		{720,400},	 R_16,	{0,   0,  0,   0,	0,	 0,   0,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 66 - 720x400@70.08
	{{PC_BASE+3, 0,NSM},	3500,	{ProgrVPosHNeg, 	8504,	{936, 446}},	{20,45},	{720,400},	 R_16,	{0,  72,  3,  42, 108,	36,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 67 - 720x400@85.04
	{{PC_BASE+4, 0,NSM},	2517,	{ProgrVNegHNeg, 	5994,	{800, 525}},	{144,35},	{640,480},	 R_4,	{0,  96,  2,  33,  48,	16,  10,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 68 - 640x480@59.94
	{{PC_BASE+5, 0,NSM},	3150,	{ProgrVNegHNeg, 	7281,	{832, 520}},	{144,31},	{640,480},	 R_4,	{0,  40,  3,  28, 128, 128,   9,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 69 - 640x480@72.80
	{{PC_BASE+6, 0,NSM},	3150,	{ProgrVNegHNeg, 	7500,	{840, 500}},	{21,19},	{640,480},	 R_4,	{0,  64,  3,  28, 128,	24,   9,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 70 - 640x480@75.00
	{{PC_BASE+7,0,NSM}, 	3600,	{ProgrVNegHNeg, 	8500,	{832, 509}},	{168,28},	{640,480},	 R_4,	{0,  56,  3,  25, 128,	24,   9,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 71 - 640x480@85.00
	{{PC_BASE+8,0,NSM}, 	3600,	{ProgrVPosHPos, 	5625,	{1024, 625}},	{200,24},	{800,600},	 R_4,	{0,  72,  2,  22, 128,	24,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 72 - 800x600@56.25
	{{PC_BASE+9,0,NSM}, 	4000,	{ProgrVPosHPos, 	6032,	{1056, 628}},	{216,27},	{800,600},	 R_4,	{0, 128,  4,  23,  88,	40,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 73 - 800x600@60.317
	{{PC_BASE+10,0,NSM},	5000,	{ProgrVPosHPos, 	7219,	{1040, 666}},	{184,29},	{800,600},	 R_4,	{0, 120,  6,  23,  64,	56,  37,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 74 - 800x600@72.19
	{{PC_BASE+11,0,NSM},	4950,	{ProgrVPosHPos, 	7500,	{1056, 625}},	{240,24},	{800,600},	 R_4,	{0,  80,  3,  21, 160,	16,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 75 - 800x600@75
	{{PC_BASE+12,0,NSM},	5625,	{ProgrVPosHPos, 	8506,	{1048, 631}},	{216,30},	{800,600},	 R_4,	{0,  64,  3,  27, 152,	32,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 76 - 800x600@85.06
	{{PC_BASE+13,0,NSM},	6500,	{ProgrVNegHNeg, 	6000,	{1344, 806}},	{296,35},	{1024,768},  R_4,	{0, 136,  6,  29, 160,	24,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 77 - 1024x768@60
	{{PC_BASE+14,0,NSM},	7500,	{ProgrVNegHNeg, 	7007,	{1328, 806}},	{280,35},	{1024,768},  R_4,	{0, 136,  6,  19, 144,	24,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 78 - 1024x768@70.07
	{{PC_BASE+15,0,NSM},	7875,	{ProgrVPosHPos, 	7503,	{1312, 800}},	{272,31},	{1024,768},  R_4,	{0,  96,  3,  28, 176,	16,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 79 - 1024x768@75.03
	{{PC_BASE+16,0,NSM},	9450,	{ProgrVPosHPos, 	8500,	{1376, 808}},	{304,39},	{1024,768},  R_4,	{0,  96,  3,  36, 208,	48,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 80 - 1024x768@85
	{{PC_BASE+17,0,NSM},   10800,	{ProgrVPosHPos, 	7500,	{1600, 900}},	{384,35},	{1152,864},  R_4,	{0, 128,  3,  32, 256,	64,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 81 - 1152x864@75
	{{PC_BASE+18,0,NSM},   16200,	{ProgrVPosHPos, 	6000,	{2160, 1250}},	{496,49},	{1600,1200}, R_4,	{0, 304,  3,  46, 304,	64,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 82 - 1600x1200@60
	{{PC_BASE+19,0,NSM},	6825,	{ProgrVNegHPos, 	6000,	{1440, 790}},	{112,19},	{1280,768},  R_16,	{0,  32,  7,  12,  80,	48,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 83 - 1280x768@59.95
	{{PC_BASE+20,0,NSM},	7950,	{ProgrVPosHNeg, 	5987,	{1664, 798}},	{320,27},	{1280,768},  R_16,	{0, 128,  7,  20, 192,	64,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 84 - 1280x768@59.87
	{{PC_BASE+21,0,NSM},   10220,	{ProgrVPosHNeg, 	6029,	{1696, 805}},	{320,27},	{1280,768},  R_16,	{0, 128,  7,  27, 208,	80,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 85 - 1280x768@74.89
	{{PC_BASE+22,0,NSM},   11750,	{ProgrVPosHNeg, 	8484,	{1712, 809}},	{352,38},	{1280,768},  R_16,	{0, 136,  7,  31, 216,	80,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 86 - 1280x768@85
	{{PC_BASE+23,0,NSM},   10800,	{ProgrVPosHPos, 	6000,	{1800, 1000}},	{424,39},	{1280,960},  R_4,	{0, 112,  3,  36, 312,	96,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 87 - 1280x960@60
	{{PC_BASE+24,0,NSM},   14850,	{ProgrVPosHPos, 	8500,	{1728, 1011}},	{384,50},	{1280,960},  R_4,	{0, 160,  3,  47, 224,	64,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 88 - 1280x960@85
	{{PC_BASE+25,0,NSM},   10800,	{ProgrVPosHPos, 	6002,	{1688, 1066}},	{360,41},	{1280,1024}, R_4,	{0, 112,  3,  38, 248,	48,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 89 - 1280x1024@60
	{{PC_BASE+26,0,NSM},   13500,	{ProgrVPosHPos, 	7502,	{1688, 1066}},	{392,41},	{1280,1024}, R_4,	{0, 144,  3,  38, 248,	16,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 90 - 1280x1024@75
	{{PC_BASE+27,0,NSM},   15750,	{ProgrVPosHPos, 	8502,	{1728, 1072}},	{384,47},	{1280,1024}, R_4,	{0, 160,  3,   4, 224,	64,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 91 - 1280x1024@85
	{{PC_BASE+28,0,NSM},	8550,	{ProgrVPosHPos, 	6002,	{1792, 795}},	{368,24},	{1360,768},  R_16,	{0, 112,  6,  18, 256,	64,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 92 - 1360x768@60
	{{PC_BASE+29,0,NSM},   10100,	{ProgrVNegHPos, 	5995,	{1560, 1080}},	{112,27},	{1400,1050}, R_4,	{0,  32,  4,  23,  80,	48,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 93 - 1400x105@59.95
	{{PC_BASE+30,0,NSM},   12175,	{ProgrVPosHNeg, 	5998,	{1864, 1089}},	{376,36},	{1400,1050}, R_4,	{0, 144,  4,  32, 232,	88,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 94 - 1400x105@59.98
	{{PC_BASE+31,0,NSM},   15600,	{ProgrVPosHNeg, 	7487,	{1896, 1099}},	{392,46},	{1400,1050}, R_4,	{0, 144,  4,  22, 248, 104,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 95 - 1400x105@74.87
	{{PC_BASE+32,0,NSM},   17950,	{ProgrVPosHNeg, 	8496,	{1912, 1105}},	{408,52},	{1400,1050}, R_4,	{0, 152,  4,  48, 256, 104,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 96 - 1400x105@84.96
	{{PC_BASE+33,0,NSM},   17550,	{ProgrVPosHPos, 	6500,	{2160, 1250}},	{496,49},	{1600,1200}, R_4,	{0, 192,  3,  46, 304,	64,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 97 - 1600x1200@65
	{{PC_BASE+34,0,NSM},   18900,	{ProgrVPosHPos, 	7000,	{2160, 1250}},	{496,49},	{1600,1200}, R_4,	{0, 192,  3,  46, 304,	64,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 98 - 1600x1200@70
	{{PC_BASE+35,0,NSM},   20250,	{ProgrVPosHPos, 	7500,	{2160, 1250}},	{496,49},	{1600,1200}, R_4,	{0, 192,  3,  46, 304,	64,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 99 - 1600x1200@75
	{{PC_BASE+36,0,NSM},   22950,	{ProgrVPosHPos, 	8500,	{2160, 1250}},	{496,49},	{1600,1200}, R_4,	{0, 192,  3,  46, 304,	64,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 100 - 1600x1200@85
	{{PC_BASE+37,0,NSM},   20475,	{ProgrVPosHNeg, 	6000,	{2448, 1394}},	{528,49},	{1792,1344}, R_4,	{0, 200,  3,  46, 328, 128,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 101 - 1792x1344@60
	{{PC_BASE+38,0,NSM},   26100,	{ProgrVPosHNeg, 	7500,	{2456, 1417}},	{568,72},	{1792,1344}, R_4,	{0, 216,  3,  69, 352,	96,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 102 - 1792x1344@74.997
	{{PC_BASE+39,0,NSM},   21825,	{ProgrVPosHNeg, 	6000,	{2528, 1439}},	{576,46},	{1856,1392}, R_4,	{0, 224,  3,  43, 352,	96,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 103 - 1856x1392@60
	{{PC_BASE+40,0,NSM},   28800,	{ProgrVPosHNeg, 	7500,	{2560, 1500}},	{576,107},	{1856,1392}, R_4,	{0, 224,  3, 104, 352, 128,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 104 - 1856x1392@75
	{{PC_BASE+41,0,NSM},   15400,	{ProgrVNegHPos, 	5995,	{2080, 1235}},	{112,32},	{1920,1200}, R_16,	{0,  32,  6,  26,  80,	48,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 106 - 1920x1200@59.95
	{{PC_BASE+42,0,NSM},   19325,	{ProgrVPosHNeg, 	5988,	{2592, 1245}},	{536,42},	{1920,1200}, R_16,	{0, 200,  6,  36, 336, 136,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 107 - 1920x1200@59.88
	{{PC_BASE+43,0,NSM},   24525,	{ProgrVPosHNeg, 	7493,	{2608, 1255}},	{552,52},	{1920,1200}, R_16,	{0, 208,  6,  46, 344, 136,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 108 - 1920x1200@74.93
	{{PC_BASE+44,0,NSM},   28125,	{ProgrVPosHNeg, 	8493,	{2624, 1262}},	{560,59},	{1920,1200}, R_16,	{0, 208,  6,  53, 352, 144,   3,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 109 - 1920x1200@84.93
	{{PC_BASE+45,0,NSM},   23400,	{ProgrVPosHNeg, 	6000,	{2600, 1500}},	{552,59},	{1920,1440}, R_4,	{0, 208,  3,  56, 344, 128,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 110 - 1920x1440@60
	{{PC_BASE+46,0,NSM},   29700,	{ProgrVPosHNeg, 	7500,	{2640, 1500}},	{576,59},	{1920,1440}, R_4,	{0, 224,  3,  56, 352, 144,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 111 - 1920x1440@75
	{{PC_BASE+47,0,NSM},   24150,	{ProgrVPosHNeg, 	6000,	{2720, 1481}},	{48,  3},	{2560,1440}, R_16,	{0,  32,  5,  56, 352, 144,   1,	   0},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 112 - 2560x1440@60 // %%% need work
	{{PC_BASE+48,0,NSM},	2700,	{InterlaceVNegHNeg, 6000,	{1716,	264}},	{244,18},	{1440, 480},R_4or16,{3, 124,  3,  15, 114,	17,   5,	 429},	0,	{0, 	0,	   0,	  0,	0},   NO_3D_SUPPORT}, // 113 - 1440 x 480i
};



/////////////////////////////////////////////////////////////////////////////////////
//
// Aspect Ratio table defines the aspect ratio as function of VIC. This table
// should be used in conjunction with the 861-D part of VModeInfoType VModesTable[]
// (formats 0 - 59) because some formats that differ only in their AR are grouped
// together (e.g., formats 2 and 3).
//
/////////////////////////////////////////////////////////////////////////////////////
//code const byte AspectRatioTable[] =
const byte AspectRatioTable[] =
{
	R_4,  R_4, R_16, R_16, R_16,  R_4, R_16,  R_4, R_16,  R_4,
	R_16,  R_4, R_16,  R_4, R_16, R_16,  R_4, R_16, R_16, R_16,
	R_4, R_16,	R_4, R_16,	R_4, R_16,	R_4, R_16,	R_4, R_16,
	R_16, R_16, R_16, R_16,  R_4, R_16,  R_4, R_16, R_16, R_16,
	R_16,  R_4, R_16,  R_4, R_16, R_16, R_16,  R_4, R_16,  R_4,
	R_16,  R_4, R_16,  R_4, R_16,  R_4, R_16,  R_4, R_16
};



/////////////////////////////////////////////////////////////////////////////////////
//
// VIC to Indexc table defines which VideoModeTable entry is appropreate for this
// VIC code.
// Note:
// This table is valid ONLY for VIC codes in 861-D formats, NOT for HDMI_VIC codes
// or 3D codes!
/////////////////////////////////////////////////////////////////////////////////////
//code const byte VIC2Index[] =
const byte VIC2Index[] =
{
	0,	0,	1,	1,	2,	3,	4,	4,	5,	5,
	7,	7,	8,	8, 10, 10, 11, 12, 12, 13,
	14, 15, 15, 16, 16, 19, 19, 20, 20, 23,
	23, 24, 25, 26, 27, 28, 28, 29, 29, 30,
	31, 32, 33, 33, 34, 34, 35, 36, 37, 37,
	38, 38, 39, 39, 40, 40, 41, 41, 42, 42
};

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION      :	ConvertVIC_To_VM_Index()
//
// PURPOSE       :  Convert Video Identification Code to the corresponding
//                  index of VModesTable[]. Conversion also depends on the
//					value of the 3D_Structure parameter in the case of
//                  3D video format.
//
// INPUT PARAMS  :	VIC to be converted; 3D_Structure value
//
// OUTPUT PARAMS :	None
//
// GLOBALS USED  :	VModesTable[]
// 					VideoModeDescription
//
// RETURNS       :	Index into VModesTable[] corrsponding to VIC
//
// Note          :	Conversion is for 861-D formats, HDMI_VIC or 3D
//
//////////////////////////////////////////////////////////////////////////////


int ConvertVIC_To_VM_Index(void)
{
	int	index;

	//
	// The global VideoModeDescription contains all the information we need about
	// the Video mode for use to find its entry in the Videio mode table.
	//
	// The first issue.  The "VIC" may be a 891-D VIC code, or it might be an
	// HDMI_VIC code, or it might be a 3D code.  Each require different handling
	// to get the proper video mode table index.
	//
	if (VideoModeDescription.HDMIVideoFormat == VMD_HDMIFORMAT_CEA_VIC)
	{
		//
		// This is a regular 861-D format VIC, so we use the VIC to Index
		// table to look up the index.
		//
        index = VIC2Index[VideoModeDescription.VIC];
	}
	else if (VideoModeDescription.HDMIVideoFormat == VMD_HDMIFORMAT_HDMI_VIC)
	{
		//
		// HDMI_VIC conversion is simple.  We need to subtract one because the codes start
		// with one instead of zero.  These values are from HDMI 1.4 Spec Table 8-13.
		//
		if ((VideoModeDescription.VIC < 1) || (VideoModeDescription.VIC > 4))
		{
			index = DEFAULT_VIDEO_MODE;
		}
		else
		{
			index = (HDMI_VIC_BASE - 1) + VideoModeDescription.VIC;
		}
	}
	else if (VideoModeDescription.HDMIVideoFormat == VMD_HDMIFORMAT_3D)
	{
		//
		// Currently there are only a few VIC modes that we can do in 3D.  If the VIC code is not
		// one of these OR if the packing type is not supported for that VIC code, then it is an
		// error and we go to the default video mode.  See HDMI Spec 1.4 Table H-6.
		//
		switch (VideoModeDescription.VIC)
		{
			case VIC_FOR_480P_60Hz_4X3:
			case VIC_FOR_480P_60Hz_16X9:
				// We only support Side-by-Side (Half) for these modes
				if (VideoModeDescription.ThreeDStructure == SIDE_BY_SIDE_HALF)
					index = VIC_3D_BASE + 0;
				else
					index = DEFAULT_VIDEO_MODE;
				break;

			case VIC_FOR_720P_60Hz:
				switch(VideoModeDescription.ThreeDStructure)
				{
					case FRAME_PACKING:
						index = VIC_3D_BASE + 1;
						break;
					default:
						index = DEFAULT_VIDEO_MODE;
						break;
				}
				break;

			case VIC_FOR_1080i_60Hz:
				switch(VideoModeDescription.ThreeDStructure)
				{
					case FRAME_PACKING:
						index = VIC_3D_BASE + 2;
						break;
					case VMD_3D_FIELDALTERNATIVE:
						index = VIC_3D_BASE + 3;
						break;
					default:
						index = DEFAULT_VIDEO_MODE;
						break;
				}
				break;

			case VIC_FOR_1080p_60Hz:
				switch(VideoModeDescription.ThreeDStructure)
				{
					case FRAME_PACKING:
						index = VIC_3D_BASE + 4;
						break;
					case VMD_3D_LINEALTERNATIVE:
						index = VIC_3D_BASE + 5;
						break;
					case SIDE_BY_SIDE_FULL:
						index = VIC_3D_BASE + 6;
						break;
					case SIDE_BY_SIDE_HALF:
						index = VIC_3D_BASE + 7;
						break;
					default:
						index = DEFAULT_VIDEO_MODE;
						break;
				}
				break;

			case VIC_FOR_720P_50Hz:
				switch(VideoModeDescription.ThreeDStructure)
				{
					case FRAME_PACKING:
						index = VIC_3D_BASE + 8;
						break;
					case VMD_3D_LDEPTH:
						index = VIC_3D_BASE + 9;
						break;
					case VMD_3D_LDEPTHGRAPHICS:
						index = VIC_3D_BASE + 10;
						break;
					default:
						index = DEFAULT_VIDEO_MODE;
						break;
				}
				break;

			case VIC_FOR_1080i_50Hz:
				switch(VideoModeDescription.ThreeDStructure)
				{
					case FRAME_PACKING:
						index = VIC_3D_BASE + 11;
						break;
					case VMD_3D_FIELDALTERNATIVE:
						index = VIC_3D_BASE + 12;
						break;
					default:
						index = DEFAULT_VIDEO_MODE;
						break;
				}
			break;

			case VIC_FOR_1080p_50Hz:
				switch(VideoModeDescription.ThreeDStructure)
				{
					case FRAME_PACKING:
						index = VIC_3D_BASE + 13;
						break;
					case VMD_3D_LINEALTERNATIVE:
						index = VIC_3D_BASE + 14;
						break;
					case SIDE_BY_SIDE_FULL:
						index = VIC_3D_BASE + 15;
						break;
					default:
						index = DEFAULT_VIDEO_MODE;
						break;
				}
				break;

			case VIC_FOR_1080p_24Hz:
				switch(VideoModeDescription.ThreeDStructure)
				{
					case FRAME_PACKING:
						index = VIC_3D_BASE + 16;
						break;
					default:
						index = DEFAULT_VIDEO_MODE;
						break;
				}
				break;

			default:
				index = DEFAULT_VIDEO_MODE;
				break;
		}
	}
	else
	{
		// This should never happen!  If so, default to first table entry
		index = DEFAULT_VIDEO_MODE;
	}

    return index;
}

