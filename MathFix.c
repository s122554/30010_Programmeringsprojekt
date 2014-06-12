#include <sio.h>
#include "sinLUT.h"
#include "MathFix.h"

void setVec(struct TVector *v, long xin, long yin){
	v->x = xin << FIX14_SHIFT;
	v->y = yin << FIX14_SHIFT;
}

long sin(long x){
	return SIN[x & 0x1FF];
}

long cos(long x){
	return SIN[(x+128) & 0x1FF];
}

void rotate(struct TVector *v, long phi){
	long xVal = v->x;
	long cosPhi = cos(phi);
	long sinPhi = sin(phi);
	v->x = FIX14_MULT(xVal, cosPhi) - FIX14_MULT(v->y, sinPhi);
	v->y = FIX14_MULT(xVal, sinPhi) + FIX14_MULT(v->y, cosPhi);
}

void printFix(long i){
	// prints a signed fixed point number
	if((i & 0x80000000) != 0){
		printf("-");
		i = ~i + 1;
	}
	printf("%ld.%04ld", i >> 16, 10000 * (unsigned long) (i & 0xffff) >> 16);
}

long expand(long i){
	// converts an 18.14 to a 16.16 fixed point
	return i << 2;
}

