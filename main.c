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
unsigned char column;
char frameColor = 15;
char strikerColor = 4;
char defaultTileColor = 6;

char blocklen = 17;
char blockh = 3;
unsigned char tileRows = 10;

char gameState, gameState_last = -1, ballMoving=0;
unsigned int strikerHitPos;

struct TVector ball_p;
struct TVector ball_v;
unsigned char strikerPos, strikerLen, striker_v;

struct Tile {
	unsigned char type, hits, destroyed, color;
};

struct GameState {
	unsigned char lives, points;
};

unsigned char lives;
unsigned int points;

struct Tile Tiles[8][12];
struct GameState Game;

int frameBounds[4] = {2,2,139,60};

char getB(){
	return	// 0 0 0 0 0 F7 F6 D3
		(~PFIN >> 5 & 0x06) +
		(~PDIN >> 3 & 0x01);
}

long angle(){
	if(ball_v.y < 0)
		return arccos(-ball_v.y);
	 else
	 	return arccos(ball_v.y);
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

void drawTiles(){
	int n,i;

// Draw Tiles
	for(n=0; n<tileRows; n++){
		for(i=0; i<8; i++){
			fgcolor(Tiles[i][n].color);
			if(!Tiles[i][n].destroyed){
				drawTile(frameBounds[0]+1+i*blocklen,frameBounds[1]+1+n*blockh, blocklen, blockh, (n+i+1)%2);
			}
		}
	}
}

void update_ball(){
	int xPos = ball_p.x >> FIX14_SHIFT;
	int yPos = ball_p.y >> FIX14_SHIFT;
	int next_xPos = (ball_p.x + ball_v.x) >> FIX14_SHIFT;
	int next_yPos = (ball_p.y + ball_v.y) >> FIX14_SHIFT;
	long incidenceAngle = angle();
	long xAngle = (128 << 14) - incidenceAngle;
	int rotation=0, caseSelect;
	int strikerCen = (strikerLen/2);
	long nextAngle;
	column = (next_xPos-frameBounds[0]-1) / blocklen;

	if(column > 7) column = 7;

	if(ball_v.x == 0 && ball_v.y == 0 ){
		setVec(&ball_p, strikerPos+(strikerLen/2), frameBounds[3]-2);
	}
	else {
		if(next_yPos == frameBounds[3]-1){
			if( (next_xPos >= strikerPos) && (next_xPos <= strikerPos+strikerLen) ){
				// Set caseSelect to reflect ball direction
				if(ball_v.x >= 0){
					caseSelect = next_xPos-strikerPos;
				}
				else {
					caseSelect = strikerPos+strikerLen-next_xPos;
				}

				// Where on striker ??
				if(caseSelect == 0){
					ball_v.x = -ball_v.x;
					ball_v.y = -ball_v.y;
					rotation = (xAngle/2) >> FIX14_SHIFT ;
				}
				else if(caseSelect == 1){
					ball_v.x = -ball_v.x;
					ball_v.y = -ball_v.y;	
				}
				else if(caseSelect == 2 || caseSelect == 3){
					ball_v.x = -ball_v.x;
					ball_v.y = -ball_v.y;
					rotation = -(incidenceAngle/(4-caseSelect) >> FIX14_SHIFT);
				}
				else if(caseSelect == strikerCen){
					ball_v.y = -ball_v.y;
				}
				else if(caseSelect > strikerCen && caseSelect <= strikerLen){
					ball_v.y = -ball_v.y;
					rotation = (xAngle/(1+strikerLen-caseSelect)) >> FIX14_SHIFT;
				}
				
				nextAngle = ((incidenceAngle >> FIX14_SHIFT) + rotation) & 0x1FF;
				if(nextAngle > 120 ){
					rotation = (110 - (incidenceAngle >> FIX14_SHIFT)) ;
				}
				
				// Compensate for ball direction !
				if(ball_v.x < 0){
	 		    	rotation = -rotation; 
				}
				rotate(&ball_v, rotation);
			}
		}
		else if(next_yPos >= frameBounds[3]){
			// You are dead !
			if(--lives > 0) 
				gameState = 0;
			else 
				gameState = 2;
		}
	
		// reflect ball on side walls !
		if(next_xPos <= frameBounds[0] || next_xPos >= frameBounds[2]){
			ball_v.x = -ball_v.x;
		}

		// Faster, working, but but more spacious way to check
		if(next_xPos >= frameBounds[0]+1+column*blocklen && next_xPos <= frameBounds[0]+1+(column+1)*blocklen){
			int n;
			for(n=0; n<tileRows; n++){
				if((next_yPos <= frameBounds[1]+3+n*3 && next_yPos >= frameBounds[1]+1+n*3) && !Tiles[column][n].destroyed){
					if(next_yPos == frameBounds[1]+2+n*3) ball_v.x = -ball_v.x;
					else ball_v.y = -ball_v.y;
					Tiles[column][n].destroyed = 1;
					drawTile(frameBounds[0]+1+column*blocklen,frameBounds[1]+1+n*3, blocklen, blockh, 79);
					points += 10;
				}
			}
		}
		
		if(next_yPos <= frameBounds[1]){
			ball_v.y = -ball_v.y;
		}

		ball_p.x += ball_v.x;
		ball_p.y += ball_v.y;	
	}
}

void drawBall(){
	fgcolor(frameColor);
	gotoxy(ball_p.x >> FIX14_SHIFT, ball_p.y >> FIX14_SHIFT);
	printf(" ");
	update_ball();
	gotoxy(ball_p.x >> FIX14_SHIFT, ball_p.y >> FIX14_SHIFT);
	printf("O");
}

void drawStriker(){
	char i;
	fgcolor(frameColor);
	for (i=0; i<strikerLen;i++){
		printf("%c",223);
	}
}

void initGame(){

	drawTiles();

	// Init Striker
	strikerLen = 9;
	fgcolor(frameColor);
	strikerPos = (frameBounds[2]-frameBounds[0])/2 - strikerLen/2;

	// Init Ball
	setVec(&ball_p, strikerPos+(strikerLen/2), frameBounds[3]-2);
	setVec(&ball_v, 0, 0);
	
	// Draw Stuff
	gotoxy(strikerPos,frameBounds[3]-1);
	drawStriker();
	drawBall();
}

void printStatus(unsigned char x, unsigned char y){
	/*
	gotoxy(x,y);
	printf("BallPos: (");
	printFix(expand(ball_p.x));
	printf(", ");
	printFix(expand(ball_p.y));
	printf(") - BallVelo: (");
	printFix(expand(ball_v.x));
	printf(", ");
	printFix(expand(ball_v.y));
	
	
	gotoxy(x,y+1);
	printf("StrikerPos: %03d", strikerPos);
	printf(" - GameState: %03d", gameState);
	printf(" - Column: %03d", column);
	*/
	gotoxy(x,y);
	printf("Lives: %d - Points: %05d", lives, points);
	printf(") - AngleToNorm: ");
	printFix(expand(angle()));
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


void newGame(unsigned char level){
	int n,i;
	if(level == 1){
		lives = 50;
		tileRows = 8;
	}

	for(n=0; n<tileRows; n++){
		for(i=0; i<8; i++){
			Tiles[i][n].destroyed = 0;
			Tiles[i][n].hits = 0;
			Tiles[i][n].color = defaultTileColor;
		}
	}
}

void updateGameState(){
	/*	0: Ball is on striker
		1: Game is on
	*/
	if(gameState != gameState_last){
		switch(gameState){
			case 0: // Reload LvL
				clrscr();
				fgcolor(frameColor);
				frame(frameBounds[0], frameBounds[1], frameBounds[2], frameBounds[3], 1);
				initGame();
				LEDsetString("Play",0);
				break;
			case 1: // GamePlay
				setVec(&ball_v, 1, 0);
				rotate(&ball_v, -128 - striker_v * 51);
				LEDsetString("    ",0);
				break;
			case 2: // Game Over
				LEDsetString("    Game Over", 0);
				break;
			default:
				break;
		}
		gameState_last = gameState;
	}
}

void main(){
	unsigned int ball_milis, striker_milis, print_milis;
	int b_last, b, i, n;
	long mul;
	init();
	clrscr();
	
	newGame(1);
	updateGameState();
	LEDsetString("HEJS", 0);

	while(1){
		b = getB();
		updateGameState();
		
		if(striker_milis == 0){
			if(b == 0x02){
				moveStriker(-1);
			}
			else if(b == 0x04){
				moveStriker(1);
			}
			if(gameState == 0 && (b & 0x01) == 1){
				gameState = 1;
			}
		}

		if(gameState == 1 && ball_milis == 0 && (ball_v.x != 0 || ball_v.y != 0) ){
			drawBall();
		}

		// clock dividers!
		if(++ball_milis == 100){ ball_milis = 0; }
		if(++striker_milis == 61){ striker_milis = 0; }
		if(++print_milis == 203){ 
			print_milis = 0;
			printStatus(2,frameBounds[3]+2);
		}
		LEDupdate();
		
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
