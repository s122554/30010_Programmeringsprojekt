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
volatile char ball_updateFLAG;
volatile char striker_updateFLAG;


char gameState=0, ballMoving=0;

struct TVector ball_p;
struct TVector ball_v;
unsigned char strikerPos, strikerLen, striker_v;

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


void update_ball(){
	int xPos = ball_p.x >> FIX14_SHIFT;
	int yPos = ball_p.y >> FIX14_SHIFT;
	int next_xPos = (ball_p.x + ball_v.x) >> FIX14_SHIFT;
	int next_yPos = (ball_p.y + ball_v.y) >> FIX14_SHIFT;
	long incidenceAngle = angle();
	int rotation=0, caseSelect;
	int strikerCen = (strikerLen/2);

	if(ball_v.x == 0 && ball_v.y == 0 ){
		setVec(&ball_p, strikerPos+(strikerLen/2), frameBounds[3]-2);
	}
	else {
		if(next_yPos == frameBounds[3]-1){
			if( (next_xPos >= strikerPos) && (next_xPos <= strikerPos+strikerLen) ){
				// Set caseSelect to reflect ball direction
				if(ball_v.x >= 0){
					caseSelect = next_xPos - strikerPos;
				}
				else {
					caseSelect = strikerPos+strikerLen - next_xPos;
				}
	
				// Rotation on different sections of the striker
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
		else if(next_yPos <= frameBounds[1]){
			ball_v.y = -ball_v.y;
		}
		else if(next_yPos >= frameBounds[3]){
			// You are dead !
			// setGameState(0);
		}
	
		// reflect ball on side walls !
		if(next_xPos <= frameBounds[0] || next_xPos >= frameBounds[2]){
			ball_v.x = -ball_v.x;
		}
	
		ball_p.x += ball_v.x;
		ball_p.y += ball_v.y;	
	}
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

void init_ball(){
	setVec(&ball_p, strikerPos+(strikerLen/2), frameBounds[3]-2);
	setVec(&ball_v, 0, 0);
	// rotate(&ball_v, 40);
	drawBall();
}

void printStatus(unsigned char x, unsigned char y){
	gotoxy(x,y);
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
	gotoxy(x,y+1);
	printf("StrikerPos: %03d", strikerPos);
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
	striker_v = 0;

	if(movex < 0 && strikerPos > frameBounds[0]+1){
		gotoxy(strikerPos, y);
		printf("%c",223);
		gotoxy(strikerPos+strikerLen, y);
		printf(" ");
		strikerPos--;
		striker_v = -1;
	}
	else if(movex > 0 && strikerPos+strikerLen < frameBounds[2]-1) {		
		gotoxy(strikerPos, y);
		printf(" ");
		strikerPos++;
		striker_v = 1;
		gotoxy(strikerPos+strikerLen-1, y);
		printf("%c",223);
	}

	if(ball_v.x == 0 && ball_v.y == 0 ){
		drawBall();
	}
}

void drawStriker(){
	char i;
	for (i=0; i<strikerLen;i++){
		printf("%c",223);
	}
}

void initGame(){
	setVec(&ball_v, 0, 0);
	strikerLen = 9;
	strikerPos = (frameBounds[2]-frameBounds[0])/2 - strikerLen/2;
	init_ball();
	gotoxy(strikerPos,frameBounds[3]-1);
}

void setGameState(int state){
	/*	0: Ball is on striker
		1: Game is on
	*/
	switch(state){
		case 0:
			// startGame();
			break;
		case 1:
			setVec(&ball_v, 1, 0);
			rotate(&ball_v, -128 - striker_v * 51);
			break;
		default:
			break;
	}
	gameState = state;
}

void main(){
	char tick_ball,tick_ball_last, tick_striker, tick_striker_last;
	int b_last, b;
	long mul;
	init();
	clrscr();	
	frame(frameBounds[0], frameBounds[1], frameBounds[2], frameBounds[3], 1);


	//setGameState(0);
		
	while(1){
		b = getB();
		tick_ball = (milis & 0x40);
		tick_striker  = (milis & 0x20);

		if(tick_striker != tick_striker_last){
			if(b == 0x02){
				moveStriker(-1);
			}
			else if(b == 0x04){
				moveStriker(1);
			}
			if(gameState == 0 && (b & 0x01) == 1){
				setGameState(1);
			}
			tick_striker_last = tick_striker;
			printStatus(2,frameBounds[3]+2);
		}

		if(gameState == 1 && tick_ball != tick_ball_last && (ball_v.x != 0 || ball_v.y != 0) ){
			drawBall();
			// printStatus(2,frameBounds[3]+2);
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
