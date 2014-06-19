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

#define MAX_SHOTS 5
unsigned char shots;


struct Bullit {
	unsigned char x, y, v;
}; 
struct Bullit bullits[MAX_SHOTS];

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

void addPoints(int p){
	points += p;
	gotoxy((frameBounds[2]-frameBounds[0])/2,frameBounds[1]-1);
	printf("%c%05d", 36, points);
}

void addLives(int l){
	int i;
	if(l > 0){
		gotoxy(frameBounds[0]+lives,frameBounds[1]-1);
		for(i=0; i<l; i++){
			printf("%c", 33);
		}
	}
	else {
		gotoxy(frameBounds[0]+lives+l,frameBounds[1]-1);
		for(i=0; i>l; i--){
			printf(" ");
		}
	}
	lives +=l;
}

void addShots(int s){
	int i;
	shots += s;
	if(s > 0){
		gotoxy(frameBounds[2]-shots,frameBounds[1]-1);
		for(i=0; i<shots; i++){
			printf("%c", 248);
		}
	}
	else {
		gotoxy(frameBounds[2]-shots+s, frameBounds[1]-1);
		for(i=0; i>s; i--){
			printf(" ");
		}
	}
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
	fgcolor(15);
}

void drawBall(){
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

	gotoxy(ball_p.x >> FIX14_SHIFT, ball_p.y >> FIX14_SHIFT);
	printf(" ");

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
				if(nextAngle > 122 ){
					rotation = (115 - (incidenceAngle >> FIX14_SHIFT)) ;
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
			addLives(-1);
			if(lives > 0){ 
				gameState = 0;
				setVec(&ball_v ,0 ,0);
				
			}
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
					addPoints(10);
				}
			}
		}

		if(next_yPos <= frameBounds[1]){
			ball_v.y = -ball_v.y;
		}

		ball_p.x += ball_v.x;
		ball_p.y += ball_v.y;
	}
	
	gotoxy(ball_p.x >> FIX14_SHIFT, ball_p.y >> FIX14_SHIFT);
	printf("O");
}

void drawBullits(){
	// Bullits are NOT in FIX14
	unsigned char i, n, column, row;
	for(i=0; i<MAX_SHOTS; i++){
		if(bullits[i].v != 0){
			if(bullits[i].y <= frameBounds[1]+1){
				bullits[i].v = 0;
				gotoxy(bullits[i].x, bullits[i].y );
				printf(" ");
			}
			else {
				column = (bullits[i].x - frameBounds[0]-1) / blocklen;
				row = (bullits[i].y - frameBounds[1] - 1) / blockh;
				gotoxy(bullits[i].x, bullits[i].y );
				printf(" ");
				bullits[i].y = bullits[i].y - bullits[i].v;
				gotoxy(bullits[i].x, bullits[i].y);
				printf("%c",248);
		
				if(row < tileRows && !Tiles[column][row].destroyed){
					bullits[i].v = 0;
					Tiles[column][row].destroyed = 1;
					drawTile(frameBounds[0]+1+column*blocklen,frameBounds[1]+1+row*3, blocklen, blockh, 79); // Delete Tile
					addPoints(10);

				}
			}
		}
	}
}

void drawStriker(){
	char i;
	for (i=0; i<strikerLen;i++){
		printf("%c",223);
	}
}


void initGame(){
	unsigned char i;
	
	fgcolor(15);
	frame(frameBounds[0], frameBounds[1], frameBounds[2], frameBounds[3], 1);
	
	
	// Init Striker
	strikerLen = 9;
	fgcolor(15);
	strikerPos = (frameBounds[2]-frameBounds[0])/2 - strikerLen/2;

	// Init Ball
	setVec(&ball_p, strikerPos+(strikerLen/2), frameBounds[3]-2);
	setVec(&ball_v, 0, 0);

	// Init Bullit
	for(i=0;i<MAX_SHOTS;i++){
		bullits[i].y = frameBounds[3]-2 -(i*2);
		bullits[i].x = strikerPos+(strikerLen/2);
		bullits[i].v = 0;
	}
	
	// Draw Stuff
	gotoxy(strikerPos,frameBounds[3]-1);
	drawStriker();
	drawBall();
	drawBullits();
	addShots(5);
	addLives(5);
	addPoints(0);
	drawTiles();
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
	// printf(" - %d", sizeof(bullits)/sizeof(struct Bullit));
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
	gameState = 0;
	if(level == 1){
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

void newBall(){
	
	setVec(&ball_v, 0, 0);

}

void updateGameState(){
	/*	0: Ball is on striker
		1: Game is on
	*/
	if(gameState != gameState_last){
		switch(gameState){
			case 0: // Reload LvL
				LEDsetString("Play",0);
				break;
			case 1: // GamePlay
				setVec(&ball_v, 1, 0);
				rotate(&ball_v, -128 - striker_v * 19);
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


void fireBullit(){
	
	if(shots > 0){
		addShots(-1);
		bullits[shots].x = strikerPos + (strikerLen/2);
		bullits[shots].v = 1;
	
		
	//	gotoxy(frameBounds[2]-shots-1,frameBounds[1]-1);
	//	printf(" ");
	}
}

void fireButtonAction(unsigned char val){
		// Fire Button
		if(gameState == 0 && val == 1){
			gameState = 1;
		}
		else if(gameState == 1 && shots > 0 && val == 1){
			fireBullit();	
		}
}

void main(){
	unsigned int ball_milis, striker_milis, print_milis;
	int b_last, b, i, n;
	unsigned char fire_button_last, fire_button;
	long mul;
	init();
	clrscr();
	newGame(1);
	initGame();
	updateGameState();
	LEDsetString("HEJS", 0);

	while(1){
		b = getB();
		updateGameState();

		// Fire Button Actions
		fire_button = (b & 0x01);
		if(fire_button != fire_button_last){
			fireButtonAction(fire_button);
			fire_button_last = fire_button;
		}
		

		
		// Move striker buttons
		if(striker_milis == 0){
			if(b & 0x02){
				moveStriker(-1);
			}
			else if(b & 0x04){
				moveStriker(1);
			}
		}

		if(gameState == 1 && ball_milis == 0 && (ball_v.x != 0 || ball_v.y != 0) ){
			drawBall();
			drawBullits();
		}

		// clock dividers!
		if(++ball_milis == 100){ ball_milis = 0; }
		if(++striker_milis == 61){ striker_milis = 0; }
	//	if(++print_milis == 203) 
	//		print_milis = 0;
		//	printStatus(2,frameBounds[3]+2);
		
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
