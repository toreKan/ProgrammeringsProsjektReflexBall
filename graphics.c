#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "ansi.h"
#include "graphics.h"
#include "refball.h"

void drawBox(unsigned char x, unsigned char y,unsigned char color){
	fgcolor(color);
	drawBounds(x,y,x+2,y+1);
	//draws last line
	gotoxy(x,y+1);
	printf("%c%c%c",192,196,217);
	fgcolor(0);
}
void drawBall(unsigned char x, unsigned char y, unsigned char color){
	fgcolor(color);
	gotoxy(x,y);
	printf("%c", 111);
	fgcolor(0);
}
void moveDrawStriker(unsigned char x, unsigned char direction){
	fgcolor(0);
	if(direction==1){
		gotoxy(x-3,STRIKER_Y);
		printf(" ");
		gotoxy(x+2,STRIKER_Y);
		printf("%c",220);
	}else{
		gotoxy(x+3,STRIKER_Y);
		printf(" ");
		gotoxy(x-2,STRIKER_Y);
		printf("%c",220);
	}
}
void drawStriker(unsigned char x, unsigned char color){
	unsigned char i;
	fgcolor(color);
	gotoxy(x-2,STRIKER_Y);
	for(i=0;i<5;i++)
		printf("%c",220);
	fgcolor(0);
}
void drawBounds(int x1,int y1, int x2, int y2){
	int i,j;
	char hs,vs,h1,h2,h3,h4;
	int height = y2 - y1+1;
	int width = x2 - x1+1;
	fgcolor(0);
	hs=196;
	vs=179;
	h1=218;
	h2=191;
	h3=217;
	h4=192;
	gotoxy(x1,y1);
	printf("%c",h1);

	for(i=1;i<=width-2;i++){
		printf("%c",hs);
	}

	printf("%c",h2);

	for(i=1;i<=height-2;i++){
		gotoxy(x1,y1+i);
		printf("%c",vs);
		gotoxy(x2,y1+i);
		printf("%c",vs);
	}

}

void drawLogo(){
	gotoxy(2,2);
	printf("||******************************************||\n");

	printf(" _____       __ _             ____        _ _ \n");
	printf("|  __ \     / _| |           |  _ \      | | |\n");
	printf("| |__) |___| |_| | _____  __ | |_) | __ _| | |\n");
	printf("|  _  // _ \  _| |/ _ \ \/ / |  _ < / _` | | |\n");
	printf("| | \ \  __/ | | |  __/>  <  | |_) | (_| | | |\n");
	printf("|_|  \_\___|_| |_|\___/_/\_\ |____/ \__,_|_|_|\n");

	printf("||******************************************||\n");

	printf("Group 3, s144012, s144045, s144021, June 2015   ");
	//printf("Ver. 0.2.0.3 Beta\n                             ");
	
}

void drawGameOver(){
	gotoxy(2,2);
	printf(" .----------------.  .----------------.  .----------------.  .----------------.  \n");
	printf("| .--------------. || .--------------. || .--------------. || .--------------. |\n");
	printf("| |    ______    | || |      __      | || | ____    ____ | || |  _________   | | \n");
	printf("| |  .' ___  |   | || |     /  \     | || ||_   \  /   _|| || | |_   ___  |  | | \n");
	printf("| | / .'   \_|   | || |    / /\ \    | || |  |   \/   |  | || |   | |_  \_|  | | \n");
	printf("| | | |    ____  | || |   / ____ \   | || |  | |\  /| |  | || |   |  _|  _   | | \n");
	printf("| |              | || |              | || |              | || |              | | \n");
	printf("| '--------------' || '--------------' || '--------------' || '--------------' | \n");
	printf(" '----------------'  '----------------'  '----------------'  '----------------' \n");
	printf("\n");
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

void printDifficulty(short diff){
	fgcolor(1);
	bgcolor(7);
	
	gotoxy(25,LINE_NUMBER + 1);
	
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

