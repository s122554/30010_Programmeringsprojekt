#include <sio.h>
#include <menu.h> 
#include <helper.h>
#include <ansi.h>

extern const unsigned char frameBounds[4];
unsigned char current_index, menu_selected;

void menu_print(){
	unsigned int linespace = 10;
	char indent = 10;
	char strLen = strlen("STREET FIGHTER BALL BUSTER");
	menu_selected = 0;

	gotoxy((frameBounds[2]+frameBounds[1]-strLen)/2, frameBounds[1]+linespace);	
	printf("STREET FIGHTER BALL BUSTER");
	
	if(current_index == 0) reverse(1); else reverse(0);
	gotoxy((frameBounds[2]+frameBounds[1]-strLen)/2+indent, frameBounds[1]+linespace*2);
	printf("EASY");
	
	if(current_index == 1) reverse(1); else reverse(0);
	gotoxy((frameBounds[2]+frameBounds[1]-strLen)/2+indent, frameBounds[1]+linespace*2+1);
	printf("NORMAL");

	if(current_index == 2) reverse(1); else reverse(0);
	gotoxy((frameBounds[2]+frameBounds[1]-strLen)/2+indent, frameBounds[1]+linespace*2+2);
	printf("HARD");

	if(current_index == 3) reverse(1); else reverse(0);
	gotoxy((frameBounds[2]+frameBounds[1]-strLen)/2+indent, frameBounds[1]+linespace*2+3);
	printf("CHUCK NORRIS");

}

void menu_setIndex(unsigned char index){
	current_index = index;
}

void menu_next(){
	current_index++;
	menu_print();
}

void menu_prev(){
	current_index--;
	menu_print();
}

unsigned char menu_isSelected(){
	return menu_selected;
}

unsigned char menu_select(){
	menu_selected = 1;
	return current_index;
}


