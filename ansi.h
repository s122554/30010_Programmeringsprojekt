#ifndef _ANSI_H_
#define _ANSI_H_

/*
struct TILE {
	unsigned char x, y, w, h;
	unsigned char hits, maxhits;
};
*/

void clrscr(); // Clear Screen
void clreol(); // Clear Rest Of Line
void gotoxy(unsigned int x, unsigned int y); // Goto row x and column y
void underline(char on); // Toggle underline
void blink(char on); // Blink
void reverse(char on); // Reverse - Invert fgbg colors
void window(int x1, int y1, int x2, int y2, char *str, int style); // Draw window
void frame(int x1, int y1, int x2, int y2, int style);
void drawTile(unsigned char x, unsigned char y, unsigned char w, unsigned char h, char myChar);
void drawStriker(int len);

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();

#endif // _ANSI_H_
