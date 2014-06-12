#include <eZ8.h>
#include <gpio.h>
#include <sio.h>
#include "ansi.h"
#include "MathFix.h"
#include "led.h"
#include "time.h"

// Global Vars
volatile unsigned long milis;
volatile char LEDupdateFLAG;

struct TVector ball_p;
struct TVector ball_v;
long strikerPos, strikerLen;

int frameBounds[4] = {2,2,140,70};

char getB(){
	return	// 0 0 0 0 0 F7 F6 D3
		(~PFIN >> 5 & 0x06) +
		(~PDIN >> 3 & 0x01);
}

void init(){
	init_uart(_UART0,_DEFFREQ,_DEFBAUD);	// set-up UART0 to 57600, 8n1

	// Set button ports as input
	PFDD |= (1 << 7) | (1 << 6); // Set PF6 & PF7 to input
	PDDD |= (1 << 3); // Set PD3 to input

	init_time();
	init_led();
}

void init_ball(){
	setVec(&ball_p, 20, 20);
	setVec(&ball_v, 1, 1);
}

void update_ball(){
	int xPos = ball_p.x >> 14;
	int yPos = ball_p.y >> 14;

	if(xPos <= frameBounds[0]+1 || xPos >= frameBounds[2]-1){
		ball_v.x = -ball_v.x;
	}
	if(yPos <= frameBounds[1]+1 || yPos >= frameBounds[3]-1){
		ball_v.y = -ball_v.y;
	}

	ball_p.x += ball_v.x;
	ball_p.y += ball_v.y;
}

void printBallInfo(){
	printf("BallPos: (");
	printFix(expand(ball_p.x));
	printf(", ");
	printFix(expand(ball_p.y));
	printf(")");
}

void moveStriker(char movex){
	char i, y = frameBounds[1]+1;
		if(movex < 0 && strikerPos > frameBounds[0]+1){
			gotoxy(strikerPos, y);
			printf("%c",223);
			gotoxy(strikerPos+strikerLen, y);
			printf(" ");
			strikerPos--;
		}
		else if(movex > 0 && strikerPos+strikerLen < frameBounds[2]-1) {		
			gotoxy(strikerPos, y);
			printf(" ");
			strikerPos++;
			gotoxy(strikerPos+strikerLen-1, y);
			printf("%c",223);
		}

}

void drawStriker(){
	char i;
	for (i=0; i<strikerLen;i++){
		printf("%c",223);
	}
}

void drawBall(){
	gotoxy(ball_p.x >> FIX14_SHIFT, ball_p.y >> FIX14_SHIFT);
	printf(" ");
	update_ball();
	gotoxy(ball_p.x >> FIX14_SHIFT, ball_p.y >> FIX14_SHIFT);
	printf("O");
}

void main(){
	char tick_ball,tick_ball_last, tick_striker,tick_striker_last;
	int b_last, b;
	init();
	clrscr();

	frame(frameBounds[0], frameBounds[1], frameBounds[2], frameBounds[3], 1);
	init_ball();

	strikerPos = 20;
	strikerLen = 7;
	// drawStriker();

	while(1){
		

		tick_ball = (milis & 0x40);
		tick_striker  = (milis & 0x20);

		if(tick_ball != tick_ball_last){
			drawBall();
			tick_ball_last = tick_ball;
		}

		if(tick_striker != tick_striker_last){
			b = getB();
			if(b == 0x02){
				moveStriker(-1);
			}
			else if(b == 0x04){
				moveStriker(1);
			}
			tick_striker_last = tick_striker;
		}

	

	}
	



	do {} while (1 != 2); // stay here always
}



	// LEDsetString("    Hvordan sker det nu ????", 0);

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

	while(1){
		LEDupdate();
		long count=0, last_count=0;
		int b_last, b;

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
			printf("%d\n",count);
			printTime();
			PEOUT &= ~(1 << 7);
			// PGOUT = count & 0x7F;
			PGOUT = 1 << ((count & 0x7F)%7);
			PEOUT |= (1 << 7);
			last_count = count;
		}
	}

*/
