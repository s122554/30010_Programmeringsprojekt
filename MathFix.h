#ifndef _MATHFIX_H_
#define _MATHFIX_H_

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a,b)  ( (a) << FIX14_SHIFT / (b))

struct TVector {
	long x,y;
};

void setVec(struct TVector *v, long xin, long yin);
long sin(long x);
long cos(long x);
void rotate(struct TVector *v, long phi);
void printFix(long i);
long expand(long i);

#endif // _MATHFIX_H_
