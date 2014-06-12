#ifndef _LED_H_
#define _LED_H_


// Global LED Vars

unsigned int LEDupdateCount = 0;
unsigned int LEDscrollCount = 0;
unsigned int LEDscrollDiv = 2;

char *pString;

char LEDcharNum = 0;
unsigned int LEDdigit=0, LEDcolumn=0;
char videoBuf[5][6]; 
volatile char LEDupdateFLAG = 0;

void clockLed(char index);
void LEDsetString(char *string, char startIndex);
void LEDupdate();
void LEDinit();

#endif // _LED_H_
