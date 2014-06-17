// =====================================================================
//	  Look-Up Tables
//		ARCSIN: asin(x/128)
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#include "asin.h"
// -----------------------------------------------------------------------
// ARCSIN: a 129 long LUT of 16bit values in 2.14 format
// asin(x/128)
const signed short ARCSIN[129]=
{
	0x0000,0x0080,0x0100,0x0180,0x0200,0x0280,0x0300,0x0380,
	0x0401,0x0481,0x0501,0x0582,0x0602,0x0683,0x0704,0x0784,
	0x0805,0x0886,0x0908,0x0989,0x0A0B,0x0A8C,0x0B0E,0x0B90,
	0x0C12,0x0C95,0x0D17,0x0D9A,0x0E1D,0x0EA1,0x0F24,0x0FA8,
	0x102C,0x10B0,0x1135,0x11BA,0x123F,0x12C5,0x134A,0x13D1,
	0x1457,0x14DE,0x1565,0x15ED,0x1675,0x16FE,0x1787,0x1810,
	0x189A,0x1924,0x19AF,0x1A3A,0x1AC6,0x1B53,0x1BDF,0x1C6D,
	0x1CFB,0x1D8A,0x1E19,0x1EA9,0x1F39,0x1FCB,0x205D,0x20EF,

	0x2183,0x2217,0x22AC,0x2342,0x23D8,0x2470,0x2508,0x25A2,
	0x263C,0x26D7,0x2774,0x2811,0x28AF,0x294F,0x29F0,0x2A92,
	0x2B35,0x2BDA,0x2C80,0x2D27,0x2DD0,0x2E7B,0x2F27,0x2FD4,
	0x3084,0x3135,0x31E8,0x329D,0x3354,0x340D,0x34C9,0x3586,
	0x3647,0x3709,0x37CF,0x3897,0x3963,0x3A32,0x3B04,0x3BD9,
	0x3CB3,0x3D91,0x3E73,0x3F5A,0x4045,0x4137,0x422E,0x432B,
	0x4430,0x453C,0x4651,0x4770,0x4899,0x49CE,0x4B11,0x4C63,
	0x4DC9,0x4F44,0x50DC,0x5295,0x547D,0x56A6,0x5934,0x5C87,

	0x6488,
};
