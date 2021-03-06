#include <eZ8.h>
#include <sio.h>
#include "ansi.h"
#include "menu.h"
#include "graphics.h"

	

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


void printDifficulty(short diff){
	fgcolor(1);
	bgcolor(7);

	gotoxy(40,LINE_NUMBER + 1);

	if(diff == 1){
		printf(" [Easy]   ");
	}else if(diff == 2){
		printf(" [Medium] ");
	}else if(diff == 3){
		printf(" [Hard]   ");
	}else{
		printf(" [Error]  ");
	}
}

void printHelp(){
	gotoxy(LEFT_BORDER,35);
	printf("Instructions:");
	gotoxy(LEFT_BORDER,37);
	printf("Use the left and middle button on the board to control the striker.\n");
	gotoxy(LEFT_BORDER,39);
	printf("Hit the right button to shoot the ball.");
	gotoxy(LEFT_BORDER,41);
	printf("Your mission is to stay alive and eliminate all the boxes.\n");
	gotoxy(LEFT_BORDER,43);
	printf("If you loose the ball you will loose a life.\n");
	gotoxy(LEFT_BORDER,45);
	printf("When you earn enough power time 5, you can activate High Power! (left and middle button)\n");
	gotoxy(LEFT_BORDER,46);
	printf("Then your ball turns red and you can smash boxes.");
	gotoxy(LEFT_BORDER,48);
	printf("The LED display shows number of balls left and earned power.");
	gotoxy(LEFT_BORDER,50);
	printf("If your boss turns up, hit all three buttons.");
	
}

	
	
