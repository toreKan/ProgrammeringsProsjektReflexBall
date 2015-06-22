#include <eZ8.h>
#include <sio.h>
#include "ansi.h"
#include "menu.h"
#include "graphics.h"



//char selectedOption = 0;

	

void initiateMenu(){
	clrscr();
	fgcolor(0);
	bgcolor(7);
	drawLogo();
	gotoxy(LEFT_BORDER,24);
	printf("Welcome to ReflexBall");
	gotoxy(LEFT_BORDER,25);
	printf("Move up / down in the menu with the left / middle button.");
	gotoxy(LEFT_BORDER,27);
	printf("Select with right button.");
	gotoxy(LEFT_BORDER,28);
	printf("  1. Start game.\n");
	gotoxy(LEFT_BORDER,29);
	printf("  2. Change difficulty:\n");
	gotoxy(LEFT_BORDER,30);
	printf("  3. Show instructions.\n");
	gotoxy(LEFT_BORDER,31);

	//Prints the menu-select marker
	moveMarker(1);

}

void moveMarker (int selectedOption){
	int i;
	fgcolor(1);
	bgcolor(7);
	//Clears the first column
	for(i = 0;i < 3; i++){
		gotoxy(LEFT_BORDER,LINE_NUMBER + i);
		printf(" ");
	}
	gotoxy(LEFT_BORDER, LINE_NUMBER + selectedOption - 1);
	printf("*");
	
}



/*
//Moves the menu-select
void moveMarker(char up){
	int i;
	fgcolor(1);
	bgcolor(7);
	//Clears the first column
	gotoxy(1,LINE_NUMBER + selectedOption - 1);
	printf(" ");
	if(up){
		selectedOption --;
		if(selectedOption == 0){
			selectedOption = 3;
		}
	}else{
		selectedOption ++;
		if(selectedOption == 4){
			selectedOption = 1;
		}
	}
	//Prints marker
	gotoxy(1, LINE_NUMBER + selectedOption - 1);
	printf("*");

}

char getChoice(){
	return selectedOption;
}
*/


		
	
	
	
