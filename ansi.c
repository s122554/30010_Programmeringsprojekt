#include <sio.h>
#include "helper.h"
#define ESC 0x1B

const char frameChars[2][8] = {
	{218,180,195,191,179,192,196,217},
	{201,185,204,187,186,200,205,188}
//	 ulc,-| ,|- ,urc, | ,llc, - ,lrc
};

// Clear Screen
void clrscr(){
	printf("%c[2J",ESC);
}

// Clear Rest Of Line
void clreol(){
	printf("%c[K",ESC);
}

// Goto row x and column y
void gotoxy(unsigned int x, unsigned int y){
	printf("%c[%u;%uH",ESC,y,x);
}

// Toggle underline
void underline(char on){
	if(on != 0) 
		printf("%c[4m",ESC);
	else
		printf("%c[24m",ESC);
}

// Blink
void blink(char on){
	if(on != 0) 
		printf("%c[5m",ESC);
	else
		printf("%c[25m",ESC);
}

// Reverse - Invert fgbg colors
void reverse(char on){
	if(on != 0) 
		printf("%c[7m",ESC);
	else
		printf("%c[27m",ESC);
}

void window(int x1, int y1, int x2, int y2, char *str, int style){
	int minwidth = strlen(str) + 4;
	int width = x2-x1+1;
	int expandX, i;
	int height = y2-y1;

	if(width < minwidth){
		width = minwidth;
	};
	expandX = width-minwidth;
    
	gotoxy(x1,y1);
	printf("%c%c", frameChars[style][0], frameChars[style][1]);
	reverse(1);
	// blink(1);
	printf("%s", str);
	for(i=0; i<expandX; i++){
		printf(" ");
	};
	reverse(0);
	// blink(0);
	printf("%c%c", frameChars[style][2], frameChars[style][3]);
	
	for(i=1; i<height; i++){
		gotoxy(x1,y1+i);
		printf("%c", frameChars[style][4]);
		gotoxy(x2,y1+i);
		printf("%c", frameChars[style][4]);
	}
	

	gotoxy(x1,y2);
	printf("%c", frameChars[style][5]);
	for(i=0; i<(width-2); i++){
		printf("%c", frameChars[style][6]);
	};
	printf("%c", frameChars[style][7]);
}

void frame(int x1, int y1, int x2, int y2, int style){
	int i, width = x2-x1, height = y2-y1;
	//	{ulc,-| ,|- ,urc, | ,llc, - ,lrc}
	gotoxy(x1,y1);
	printf("%c", frameChars[style][0]);
	for(i=0; i<width-1; i++){
		printf("%c", frameChars[style][6]);
	}
	printf("%c", frameChars[style][3]);
	for(i=1; i<height; i++){
		gotoxy(x1,y1+i);
		printf("%c", frameChars[style][4]);
		gotoxy(x2,y1+i);
		printf("%c", frameChars[style][4]);
	}
	gotoxy(x1,y2);
	printf("%c", frameChars[style][5]);
	for(i=0; i<(width-1); i++){
		printf("%c", frameChars[style][6]);
	};
	printf("%c", frameChars[style][7]);
}

void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color      
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);  
}