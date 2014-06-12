#include <eZ8.h>
#include <gpio.h>
#include <sio.h>
#include "ansi.h"
#include "MathFix.h"
#include "charset.h"
#include "led.h"

typedef unsigned char volatile far *IORegInt8;
#define IO_ADDR(addr) *((IORegInt8) addr)

// Global Vars
unsigned long milis = 0;

struct TIME {
	unsigned long hour, min, sec, milis;
};

#pragma interrupt
void timer0int() {
	milis++;
	LEDupdateFLAG = 1;
}

char getB(){
	return	// 0 0 0 0 0 F7 F6 D3
		(~PFIN >> 5 & 0x06) +
		(~PDIN >> 3 & 0x01);
}

void setup(){
	
	init_uart(_UART0,_DEFFREQ,_DEFBAUD);	// set-up UART0 to 57600, 8n1

	// Set button ports as input
	PFDD |= (1 << 7) | (1 << 6); // Set PF6 & PF7 to input
	PDDD |= (1 << 3); // Set PD3 to input

	//  --- Timer ---
	DI(); // Disable Interrupts
	
	// Set 
	T0CTL &= ~((1 << 7) | (1 << 2) | (1 << 1)); // Reset bits
	T0CTL |= (1 << 0); // Set Bit 0
	
	// Set prescaler = 0
	T0CTL &= ~((1 << 5) | (1 << 4) | (1 << 3)); //Reset bits
	
	//Set time & reload values
	T0H = 0x00; // Set timer high byte
	T0L = 0x01; // Set timer low byte
	T0RH = 0x48; // Set timer reload high byte
	T0RL = 0x00; // Set timer reload low byte

	SET_VECTOR(TIMER0, timer0int);
	IRQ0ENH &= ~(1 << 5); // Enable timer0 interrupt, and set low priority
	IRQ0ENL |= (1 << 5);

	T0CTL |= (1 << 7); // Enable Timer0

	EI(); // Enable Interrupts
}


void main(){
	long count=0, last_count=0;
	struct TVector v;
	struct TIME T;
	int b_last, b;

	setup();
	LEDinit();
	//LEDscrollStr = "Hej Med Dig !!!";

	LEDsetString("    Hvordan sker det nu ????", 0);

	clrscr();
	
	while(1){
		LEDupdate();
		T.milis = milis;
		T.hour = T.milis/3600000;
		T.milis = T.milis - T.hour*3600000;
		T.min = T.milis/60000;
		T.milis = T.milis - T.min*60000;
		T.sec = T.milis/1000;
		T.milis = T.milis - T.sec*1000;
		b = getB();
		if(b != b_last){
			if(b == 0x01){ 
				count = 0;
			}
			else if(b == 0x02){
				count--;
			}
			else if(b == 0x04){
				count++;
			}
		}
		b_last = b;
		if(count != last_count){
			printf("%d:%d:%d:%d\n",T.hour,T.min,T.sec,T.milis);
			printf("%d\n",count);
			PEOUT &= ~(1 << 7);
			// PGOUT = count & 0x7F;
			PGOUT = 1 << ((count & 0x7F)%7);
			PEOUT |= (1 << 7);
			last_count = count;
		}
	}

	do {} while (1 != 2); // stay here always
}





/*
	window(20,5,80,10,"Hejsa",0);
	window(20,20,50,25,"Yiir mayn",1);

	printf("Sin %ld: ",43);
	printFix(expand(sin(43)));
	printf("\n");
	printf("Cos %ld: ",43);
	printFix(expand(cos(43)));
	printf("\n");
	
	setVec(&v, -4, -4);
	rotate(&v,1280);
	printf("Vec: [");
	printFix(expand(v.x));
	printf(",");
	printFix(expand(v.y));
	printf("]\n");
*/
