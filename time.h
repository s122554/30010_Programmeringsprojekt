#ifndef _TIME_H_
#define _TIME_H_

void init_time();


struct TIME {
	unsigned long hour, min, sec, milis;
};

void printTime();

#endif
