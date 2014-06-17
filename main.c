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

struct TVector norm;
struct TVector ball_p;
struct TVector ball_v;
long strikerPos, strikerLen;

int frameBounds[4] = {2,2,140,60};

char getB(){
	return	// 0 0 0 0 0 F7 F6 D3
		(~PFIN >> 5 & 0x06) +
		(~PDIN >> 3 & 0x01);
}

void init(){
	// init_uart(_UART0,_DEFFREQ,_DEFBAUD);	// set-up UART0 to 57600, 8n1
	init_uart(_UART0,_DEFFREQ,112000);	// set-up UART0 to 57600, 8n1

	// Set button ports as input
	PFDD |= (1 << 7) | (1 << 6); // Set PF6 & PF7 to input
	PDDD |= (1 << 3); // Set PD3 to input

	init_time();
	init_led();

}

long angle(){
	if(ball_v.y <0)
		return arccos(-ball_v.y);
	 else
	 	return arccos(ball_v.y);
}

void init_ball(){
	setVec(&ball_p, 20, 20);
	setVec(&ball_v, 0, 1);
	rotate(&ball_v, 40);
}

void update_ball(){
	int xPos = ball_p.x >> FIX14_SHIFT;
	int yPos = ball_p.y >> FIX14_SHIFT;
	int next_xPos = (ball_p.x + ball_v.x) >> FIX14_SHIFT;
	int next_yPos = (ball_p.y + ball_v.y) >> FIX14_SHIFT;
	long incidenceAngle = angle();
	int rotation=0, caseSelect;
	int strikerCen = (strikerLen/2);

	if(next_yPos == frameBounds[3]-1){
		if( (next_xPos >= strikerPos) && (next_xPos <= strikerPos + strikerLen) ){
			caseSelect = next_xPos - strikerPos;
			if(caseSelect == 0){
				ball_v.x = -ball_v.x;
				ball_v.y = -ball_v.y;
			}
			else if(caseSelect > 0 && caseSelect < strikerCen){
				ball_v.x = -ball_v.x;
				ball_v.y = -ball_v.y;
				rotation = -(incidenceAngle/2 >> FIX14_SHIFT);
			}
			else if(caseSelect > strikerCen && caseSelect <= strikerLen){
				ball_v.y = -ball_v.y;
				rotation = (incidenceAngle/2 >> FIX14_SHIFT);
			}
			else {
				ball_v.y = -ball_v.y;
			}
			
			if(ball_v.x < 0){
 		    	rotation = -rotation; 
			}
			rotate(&ball_v, rotation);

			


			
		}
	}
	else if(next_yPos <= frameBounds[1] || next_yPos >= frameBounds[3]){
		ball_v.y = -ball_v.y;
	}

	if(next_xPos <= frameBounds[0] || next_xPos >= frameBounds[2]){
		ball_v.x = -ball_v.x;
	}

	ball_p.x += ball_v.x;
	ball_p.y += ball_v.y;	
}

struct TVector nextBallPos(){
	struct TVector nextPos;
	nextPos.x = ball_p.x + ball_v.x;
	nextPos.y = ball_p.y + ball_v.y;
	return nextPos;
}



void drawBall(){
	gotoxy(ball_p.x >> FIX14_SHIFT, ball_p.y >> FIX14_SHIFT);
	printf(" ");
	update_ball();
	gotoxy(ball_p.x >> FIX14_SHIFT, ball_p.y >> FIX14_SHIFT);
	printf("O");
}

void printStatus(){
	printf("BallPos: (");
	printFix(expand(ball_p.x));
	printf(", ");
	printFix(expand(ball_p.y));
	printf(") - BallVelo: (");
	printFix(expand(ball_v.x));
	printf(", ");
	printFix(expand(ball_v.y));
	printf(") - AngleToNorm: ");
	printFix(expand(angle()));
	printf(") - AngleToNorm/2: ");
	printFix(expand(angle()/2));
}

void printBallInfo(){
	printf("BallPos: (");
	printFix(expand(ball_p.x));
	printf(", ");
	printFix(expand(ball_p.y));
	printf(")");
}

void moveStriker(char movex){
	char i, y = frameBounds[3]-1;
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


void main(){
	char tick_ball,tick_ball_last, tick_striker, tick_striker_last;
	int b_last, b;
	long mul;
	init();
	clrscr();

	
	frame(frameBounds[0], frameBounds[1], frameBounds[2], frameBounds[3], 1);
	init_ball();

	strikerPos = 20;
	strikerLen = 9;
	setVec(&norm, 0, 1);
	gotoxy(strikerPos,frameBounds[3]-1);
	drawStriker();


	printf("Sin %ld: ",128);
	printFix(expand(arcsin(1<<14)));
	printf("\n");
	printf("Cos %ld: ",128);
	printFix(expand(arccos(cos(128))));
	printf("\n");

	
	while(1){
		tick_ball = (milis & 0x40);
		tick_striker  = (milis & 0x20);

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
		if(tick_ball != tick_ball_last){
			drawBall();
			gotoxy(2,frameBounds[3]+2);
			printStatus();
			tick_ball_last = tick_ball;
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
