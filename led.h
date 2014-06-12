#ifndef _LED_H_
#define _LED_H_

void LEDinit();
void clockLed(char index);
void LEDsetString(char *string, char startIndex);
void LEDupdate();

#endif
