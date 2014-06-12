#include <eZ8.h>
#include <sio.h>
#include "time.h"

extern volatile unsigned long milis;
extern volatile char LEDupdateFLAG;


#pragma interrupt
void timer0int() {
	milis++;
	LEDupdateFLAG = 1;
}
void init_time(){
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


void printTime(){
	struct TIME T;
	T.milis = milis;
	T.hour = T.milis/3600000;
	T.milis = T.milis - T.hour*3600000;
	T.min = T.milis/60000;
	T.milis = T.milis - T.min*60000;
	T.sec = T.milis/1000;
	T.milis = T.milis - T.sec*1000;
	printf("%d:%d:%d:%d\n",T.hour,T.min,T.sec,T.milis);
}


