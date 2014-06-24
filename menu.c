#include <sio.h>
#include <menu.h> 
#include <helper.h>
#include <ansi.h>
#include <MathFix.h>

#define MENU_ITEM_COUNT 4
extern const unsigned char frameBounds[4];
unsigned char current_index, menu_selected;

void menu_print(){
	unsigned int linespace = 5;
	char indent = 3;
	char strLen = strlen("TILE FIGHTER");

	menu_selected = 0;

	reverse(0);
	gotoxy((frameBounds[2]+frameBounds[1]-strLen)/2, frameBounds[1]+linespace);	
	printf("TILE FIGHTER");
	
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
	printf("CHUCKLE NORRIS");

	if(current_index == 3) reverse(0);
}

void menu_setIndex(unsigned char index){
	if(index >= 0 && index < MENU_ITEM_COUNT){
		current_index = index;
	}
}

void menu_next(){
	if(current_index < MENU_ITEM_COUNT-1){
		current_index++;
	}
	menu_print();
}

void menu_prev(){
	if(current_index > 0){
		current_index--;
	}
	menu_print();
}

unsigned char menu_isSelected(){
	return menu_selected;
}

unsigned char menu_select(){
	menu_selected = 1;
	return current_index;
}


