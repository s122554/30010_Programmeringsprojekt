#ifndef _MATHFIX_H_
#define _MATHFIX_H_

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a,b)  ( ((a) << FIX14_SHIFT) / (b))
#define FIX14_KONST (1 << 14)
#define FIX14_PI 51472
#define FIX14_PI_256 1335088


struct TVector {
	long x, y;
};

long FIX14_POW(long x, int n);
long FIX14_SQRT(long x);
void setVec(struct TVector *v, long xin, long yin);
long sin(long x);
long cos(long x);
long arcsin(long x);
long arccos(long x);
void rotate(struct TVector *v, long phi);
void printFix(long i);
long expand(long i);
long dotP(struct TVector *v1, struct TVector *v2);
long vecMagSquared(struct TVector *v1);
long vecMag(struct TVector *v1);
long vecAngle(struct TVector *v1, struct TVector *v2);

unsigned long rand(unsigned long min, unsigned long max);

#endif // _MATHFIX_H_
