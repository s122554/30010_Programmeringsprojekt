#ifndef _LED_H_
#define _LED_H_

void init_led();
void clockLed(char index);
void LEDsetString(char *string, char startIndex);
void LEDupdate();

#endif
