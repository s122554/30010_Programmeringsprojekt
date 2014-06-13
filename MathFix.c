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

long arcsin(long x){
	if(x >=0){ 
		return ARCSIN[x & 0x7F];
	}
	else {
		return -ARCSIN[x & 0x7F];
	}
}



long arccos(long x){
	if(x >=0){ 
		return ARCSIN[x & 0x7F] - (128 << FIX14_SHIFT);
	}
	else {
		return -(ARCSIN[x & 0x7F] - (128 << FIX14_SHIFT));
	}
}

long dotP(struct TVector *v1, struct TVector *v2){
	return (FIX14_MULT(v1->x, v2->x) + FIX14_MULT(v1->y, v2->y));
}

long vecMagSquared(struct TVector *v1){
	return FIX14_MULT(v1->x, v1->x) + FIX14_MULT(v1->y, v1->y);
}

long vecAngle(struct TVector *v1, struct TVector *v2){
	long cosPhi = FIX14_DIV(dotP(v1,v2),23170);
	return arccos(cosPhi);
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

