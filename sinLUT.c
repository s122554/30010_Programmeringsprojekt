// =====================================================================
//	  Look-Up Tables
//		SIN: sin(x*pi/256)
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#include "sinLUT.h"
// -----------------------------------------------------------------------
// SIN: a 512 long LUT of 16bit values in 2.14 format
// sin(x*pi/256)
const signed short SIN[512]=
{
	0x0000,0x00C9,0x0192,0x025B,0x0324,0x03ED,0x04B5,0x057E,
	0x0646,0x070E,0x07D6,0x089D,0x0964,0x0A2B,0x0AF1,0x0BB7,
	0x0C7C,0x0D41,0x0E06,0x0ECA,0x0F8D,0x1050,0x1112,0x11D3,
	0x1294,0x1354,0x1413,0x14D2,0x1590,0x164C,0x1709,0x17C4,
	0x187E,0x1937,0x19EF,0x1AA7,0x1B5D,0x1C12,0x1CC6,0x1D79,
	0x1E2B,0x1EDC,0x1F8C,0x203A,0x20E7,0x2193,0x223D,0x22E7,
	0x238E,0x2435,0x24DA,0x257E,0x2620,0x26C1,0x2760,0x27FE,
	0x289A,0x2935,0x29CE,0x2A65,0x2AFB,0x2B8F,0x2C21,0x2CB2,

	0x2D41,0x2DCF,0x2E5A,0x2EE4,0x2F6C,0x2FF2,0x3076,0x30F9,
	0x3179,0x31F8,0x3274,0x32EF,0x3368,0x33DF,0x3453,0x34C6,
	0x3537,0x35A5,0x3612,0x367D,0x36E5,0x374B,0x37B0,0x3812,
	0x3871,0x38CF,0x392B,0x3984,0x39DB,0x3A30,0x3A82,0x3AD3,
	0x3B21,0x3B6D,0x3BB6,0x3BFD,0x3C42,0x3C85,0x3CC5,0x3D03,
	0x3D3F,0x3D78,0x3DAF,0x3DE3,0x3E15,0x3E45,0x3E72,0x3E9D,
	0x3EC5,0x3EEB,0x3F0F,0x3F30,0x3F4F,0x3F6B,0x3F85,0x3F9C,
	0x3FB1,0x3FC4,0x3FD4,0x3FE1,0x3FEC,0x3FF5,0x3FFB,0x3FFF,

	0x4000,0x3FFF,0x3FFB,0x3FF5,0x3FEC,0x3FE1,0x3FD4,0x3FC4,
	0x3FB1,0x3F9C,0x3F85,0x3F6B,0x3F4F,0x3F30,0x3F0F,0x3EEB,
	0x3EC5,0x3E9D,0x3E72,0x3E45,0x3E15,0x3DE3,0x3DAF,0x3D78,
	0x3D3F,0x3D03,0x3CC5,0x3C85,0x3C42,0x3BFD,0x3BB6,0x3B6D,
	0x3B21,0x3AD3,0x3A82,0x3A30,0x39DB,0x3984,0x392B,0x38CF,
	0x3871,0x3812,0x37B0,0x374B,0x36E5,0x367D,0x3612,0x35A5,
	0x3537,0x34C6,0x3453,0x33DF,0x3368,0x32EF,0x3274,0x31F8,
	0x3179,0x30F9,0x3076,0x2FF2,0x2F6C,0x2EE4,0x2E5A,0x2DCF,

	0x2D41,0x2CB2,0x2C21,0x2B8F,0x2AFB,0x2A65,0x29CE,0x2935,
	0x289A,0x27FE,0x2760,0x26C1,0x2620,0x257E,0x24DA,0x2435,
	0x238E,0x22E7,0x223D,0x2193,0x20E7,0x203A,0x1F8C,0x1EDC,
	0x1E2B,0x1D79,0x1CC6,0x1C12,0x1B5D,0x1AA7,0x19EF,0x1937,
	0x187E,0x17C4,0x1709,0x164C,0x1590,0x14D2,0x1413,0x1354,
	0x1294,0x11D3,0x1112,0x1050,0x0F8D,0x0ECA,0x0E06,0x0D41,
	0x0C7C,0x0BB7,0x0AF1,0x0A2B,0x0964,0x089D,0x07D6,0x070E,
	0x0646,0x057E,0x04B5,0x03ED,0x0324,0x025B,0x0192,0x00C9,

	0x0000,0xFF37,0xFE6E,0xFDA5,0xFCDC,0xFC13,0xFB4B,0xFA82,
	0xF9BA,0xF8F2,0xF82A,0xF763,0xF69C,0xF5D5,0xF50F,0xF449,
	0xF384,0xF2BF,0xF1FA,0xF136,0xF073,0xEFB0,0xEEEE,0xEE2D,
	0xED6C,0xECAC,0xEBED,0xEB2E,0xEA70,0xE9B4,0xE8F7,0xE83C,
	0xE782,0xE6C9,0xE611,0xE559,0xE4A3,0xE3EE,0xE33A,0xE287,
	0xE1D5,0xE124,0xE074,0xDFC6,0xDF19,0xDE6D,0xDDC3,0xDD19,
	0xDC72,0xDBCB,0xDB26,0xDA82,0xD9E0,0xD93F,0xD8A0,0xD802,
	0xD766,0xD6CB,0xD632,0xD59B,0xD505,0xD471,0xD3DF,0xD34E,

	0xD2BF,0xD231,0xD1A6,0xD11C,0xD094,0xD00E,0xCF8A,0xCF07,
	0xCE87,0xCE08,0xCD8C,0xCD11,0xCC98,0xCC21,0xCBAD,0xCB3A,
	0xCAC9,0xCA5B,0xC9EE,0xC983,0xC91B,0xC8B5,0xC850,0xC7EE,
	0xC78F,0xC731,0xC6D5,0xC67C,0xC625,0xC5D0,0xC57E,0xC52D,
	0xC4DF,0xC493,0xC44A,0xC403,0xC3BE,0xC37B,0xC33B,0xC2FD,
	0xC2C1,0xC288,0xC251,0xC21D,0xC1EB,0xC1BB,0xC18E,0xC163,
	0xC13B,0xC115,0xC0F1,0xC0D0,0xC0B1,0xC095,0xC07B,0xC064,
	0xC04F,0xC03C,0xC02C,0xC01F,0xC014,0xC00B,0xC005,0xC001,

	0xC000,0xC001,0xC005,0xC00B,0xC014,0xC01F,0xC02C,0xC03C,
	0xC04F,0xC064,0xC07B,0xC095,0xC0B1,0xC0D0,0xC0F1,0xC115,
	0xC13B,0xC163,0xC18E,0xC1BB,0xC1EB,0xC21D,0xC251,0xC288,
	0xC2C1,0xC2FD,0xC33B,0xC37B,0xC3BE,0xC403,0xC44A,0xC493,
	0xC4DF,0xC52D,0xC57E,0xC5D0,0xC625,0xC67C,0xC6D5,0xC731,
	0xC78F,0xC7EE,0xC850,0xC8B5,0xC91B,0xC983,0xC9EE,0xCA5B,
	0xCAC9,0xCB3A,0xCBAD,0xCC21,0xCC98,0xCD11,0xCD8C,0xCE08,
	0xCE87,0xCF07,0xCF8A,0xD00E,0xD094,0xD11C,0xD1A6,0xD231,

	0xD2BF,0xD34E,0xD3DF,0xD471,0xD505,0xD59B,0xD632,0xD6CB,
	0xD766,0xD802,0xD8A0,0xD93F,0xD9E0,0xDA82,0xDB26,0xDBCB,
	0xDC72,0xDD19,0xDDC3,0xDE6D,0xDF19,0xDFC6,0xE074,0xE124,
	0xE1D5,0xE287,0xE33A,0xE3EE,0xE4A3,0xE559,0xE611,0xE6C9,
	0xE782,0xE83C,0xE8F7,0xE9B4,0xEA70,0xEB2E,0xEBED,0xECAC,
	0xED6C,0xEE2D,0xEEEE,0xEFB0,0xF073,0xF136,0xF1FA,0xF2BF,
	0xF384,0xF449,0xF50F,0xF5D5,0xF69C,0xF763,0xF82A,0xF8F2,
	0xF9BA,0xFA82,0xFB4B,0xFC13,0xFCDC,0xFDA5,0xFE6E,0xFF37,
};

const signed short ARCSIN[128]=
{
	0x0000,0x0081,0x0102,0x0183,0x0204,0x0285,0x0306,0x0388,
	0x0409,0x048A,0x050B,0x058D,0x060E,0x0690,0x0712,0x0794,
	0x0816,0x0898,0x091A,0x099C,0x0A1F,0x0AA2,0x0B25,0x0BA8,
	0x0C2B,0x0CAE,0x0D32,0x0DB6,0x0E3A,0x0EBF,0x0F43,0x0FC8,
	0x104D,0x10D3,0x1158,0x11DE,0x1265,0x12EC,0x1373,0x13FA,
	0x1482,0x150A,0x1592,0x161B,0x16A5,0x172E,0x17B8,0x1843,
	0x18CE,0x195A,0x19E6,0x1A72,0x1B00,0x1B8D,0x1C1C,0x1CAA,
	0x1D3A,0x1DCA,0x1E5B,0x1EEC,0x1F7E,0x2011,0x20A4,0x2138,

	0x21CD,0x2263,0x22FA,0x2391,0x2429,0x24C2,0x255D,0x25F8,
	0x2694,0x2731,0x27CF,0x286E,0x290F,0x29B1,0x2A53,0x2AF7,
	0x2B9D,0x2C44,0x2CEC,0x2D96,0x2E41,0x2EEE,0x2F9C,0x304C,
	0x30FE,0x31B2,0x3268,0x3320,0x33DA,0x3496,0x3555,0x3616,
	0x36DA,0x37A0,0x3869,0x3936,0x3A05,0x3AD8,0x3BAF,0x3C8A,
	0x3D68,0x3E4B,0x3F33,0x4020,0x4112,0x420A,0x4309,0x440F,
	0x451C,0x4632,0x4752,0x487C,0x49B3,0x4AF7,0x4C4B,0x4DB2,
	0x4F2F,0x50C8,0x5283,0x546D,0x5698,0x5928,0x5C7F,0x6488,
};

