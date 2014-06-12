#include "helper.h"

int strlen(char *str){
	int i = 0;
	while(*str++ != '\0')
		i++;
	return i;
}
