#ifndef _ANSI_H_
#define _ANSI_H_

void clrscr(); // Clear Screen
void clreol(); // Clear Rest Of Line
void gotoxy(unsigned int x, unsigned int y); // Goto row x and column y
void underline(char on); // Toggle underline
void blink(char on); // Blink
void reverse(char on); // Reverse - Invert fgbg colors
int strlen(char *str); // Return length of string
void window(int x1, int y1, int x2, int y2, char *str, int style); // Draw window

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();

#endif // _ANSI_H_
