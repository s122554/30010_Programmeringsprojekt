#include <eZ8.h>
#include <gpio.h>
#include <sio.h>
#include "ansi.h"
#include "MathFix.h"
#include "led.h"
#include "time.h"
#include "asciiart.h"
#include "helper.h"
#include "menu.h"

// Global Vars
volatile unsigned long milis;
volatile char LEDupdateFLAG;

#define defaultTileColor 6
#define MAX_SHOTS 10
#define blocklen 17
#define blockh 3
#define tileColumns 8

const unsigned char frameBounds[4] = {2,2,139,60};

unsigned char tileRows, tiles_left;

char gameState, gameState_last = -1;

struct TVector ball_p;
struct TVector ball_v;

unsigned char strikerPos, strikerLen, striker_v, lives, points, shots;

struct Tile {
	unsigned char type, hits, destroyed, color;
};
struct Tile Tiles[8][15];

struct Bullit {
	unsigned char x, y, v;
}; 
struct Bullit bullits[MAX_SHOTS];

char getB(){
	return	// 0 0 0 0 0 F7 F6 D3
		(~PFIN >> 5 & 0x06) +
		(~PDIN >> 3 & 0x01);
}

char getB_wait(){
	unsigned char b;
	while(b == 0){
		b = getB();
	}
	return b;
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
	unsigned char column = (next_xPos-frameBounds[0]-1) / blocklen;

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
					if(--tiles_left == 0) gameState = 3;
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
					if(--tiles_left == 0) gameState = 3;

				}
			}
		}
	}
}








void gameOver(){
	int b;	
	clrscr();
	printGameOver();
	while(!(b & 0x01) || !(b & 0x02) || !(b & 0x04)){
		b = getB();
		if((b & 0x01) || (b & 0x02) || (b & 0x04)){
			clrscr();
			break;
		}
	}
	clrscr();
	gotoxy((frameBounds[2]-frameBounds[0])/2,(frameBounds[3]+frameBounds[1])/2);
	printf("Want to try again?");
	gotoxy((frameBounds[2]-frameBounds[0])/2,(frameBounds[3]+frameBounds[1]+2)/2);
	printf("    YES     NO");
}


void winScreen(){
	clrscr();
	printStartscreen();
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
	drawStriker(strikerLen);
	drawBall();
	drawBullits();
	addShots(MAX_SHOTS);
	addLives(5);
	addPoints(0);
	drawTiles();
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
	switch(level){
		case 0: // Easy Mode
			tileRows = rand(6,8);
			break;
		case 1: // Normal Mode
			tileRows = rand(8,10);
			break;
		case 2: // Hard Mode
			tileRows = rand(10,12);
			break;
		case 3: // Chuck Mode
			tileRows = rand(12,15);
			break;
		default: // Bogus Mode
			tileRows = 1;
			break;
	}
	for(n=0; n<tileRows; n++){
		for(i=0; i<tileColumns; i++){
			Tiles[i][n].destroyed = 0;
			Tiles[i][n].hits = 0;
			Tiles[i][n].color = defaultTileColor;
		}
	}
	tiles_left = tileColumns*tileRows;

	gameState = 0;
}

void menuScreen(){
	unsigned char b, b_last, item;
	clrscr();
	menu_print();
  	while(!menu_isSelected()){
		b = getB();
		if( b != b_last ){
			if(b & 0x02){
				menu_prev(); 
			}
			else if(b & 0x04){	
				menu_next();
			}
			else if(b & 0x01){
				randSeed(milis);
				item = menu_select();	
			}
			b_last = b;
		}
	}

	newGame(item);
	initGame();
}

void startScreen(){
	int b;
	clrscr();
	printStartscreen();
  	while(!(b & 0x01) || !(b & 0x02) || !(b & 0x04)){
		b = getB();
		if((b & 0x01) || (b & 0x02) || (b & 0x04)){
			clrscr();
			break;
		}
	}
	menuScreen();
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
				gameOver();
				break;
			case 3: //Winner
				LEDsetString("    WINNER",0);
				printStartscreen();
				break;
			case 4: // Startscreen
				LEDsetString("    Wellcome to TILE FIGHTERl",0);
				startScreen();
				break;
			case 5: // Startscreen
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
	unsigned char fire_button_last, fire_button, selected_level;
	long mul;
	init();
	startScreen();

	updateGameState();

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

		LEDupdate();
				
	}
	

	do {} while (1 != 2); // stay here always
}


