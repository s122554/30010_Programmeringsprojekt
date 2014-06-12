#include <eZ8.h>
#include "led.h"
#include <gpio.h>

void clockLed(char index){
	switch(index){
		case 0:
			PEOUT |=  (1 << 7);
			PEOUT &= ~(1 << 7);
			break;
		case 1:
			PGOUT |=  (1 << 7);
			PGOUT &= ~(1 << 7);
			break;
		case 2:
			PEOUT |=  (1 << 5);
			PEOUT &= ~(1 << 5);
			break;
		case 3:
			PEOUT |=  (1 << 6);
			PEOUT &= ~(1 << 6);
			break;
		 default:
		 	break;
	}
}

void LEDsetString(char *string, char startIndex){
	char i, c;
	char restlen = strlen(string)-startIndex;

	pString = string;

	for(i=0; i < 5; i++){
		for(c=0; c<5; c++){
			if(i < restlen){
				videoBuf[i][c] = character_data[string[i+startIndex] - 0x20][c];
			}
			else{
				videoBuf[i][c] = character_data[0][c];
			}
		}	
	}
}


void LEDupdate(){
	unsigned int index = (LEDdigit*6 + 4-LEDcolumn + (LEDscrollCount>>2));
	char x, slen = strlen(pString);

	if(LEDupdateFLAG){
		x = *(&videoBuf[0][0] + index);
		PGOUT = x & 0x7F;
		PEOUT = 0x1F & ~(1 << LEDcolumn);
		clockLed(LEDdigit);

		if(++LEDdigit == 4) {
			LEDdigit = 0;
			if(++LEDcolumn == 5) {
				LEDcolumn = 0;
				if(slen > 4){
					if(++LEDscrollCount == (6<<2)){
						LEDscrollCount = 0;
						if(++LEDcharNum == slen){
							LEDcharNum = 0;
						}
						LEDsetString(pString, LEDcharNum);
					}
				}
			}
		}
	}
	LEDupdateFLAG = 0;
}

void LEDinit(){
	// Set LED ports as output
	PEDD = 0x00;
	PGDD = 0x00;
	
	// Turn Off All LEDs and Reset all Clocks
	PEOUT = 0x0F; // set cathodes = 1
	PGOUT = 0x00; // set anodes = 0
}



