#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h> 
#include "ansi.h"
#include "charset.h"
char buffer[5][6];
char column;
char display;
char index=0;
int strlength;
char *string;
long flag2;
//K�rer vores interrupt
#pragma interrupt
void timer1int(){
	LEDUpdate();:
	flag2++;
}
//Indl�ser et nyt tegn p� den sidste plads i buffer
void loadNew(){
char j,i;

	for (i=0;i<5;i++){
		for(j=0;j<6;j++){
			if(i<4)
			buffer[i][j]=buffer[i+1][j];
			else
			buffer[i][j]=character_data[*string-0x20][j];

			}
			
	 }
string++;
buffer[4][5]=0;
}

void LEDInit(){
	PEDD = 0x00;
	PGDD = 0x00;	
	DI();
	T1CTL = 0x01; // Prescale value er 1, ingen division
	T1H = 0x00;
	T1L = 0x01;
	T1RH = 0x24; // Reload v�rdi er 9216  = 2400
	T1RL = 0x00;
	SET_VECTOR(TIMER1, timer1int);
	IRQ0ENL |= 0x40; //S�tter priority lav
	T1CTL |= 0x80; //Starter timeren
	EI();
}

void LEDSetString(char *s){
	char i,j;
	strlength = 0;
	string = s;
	//Regner l�ngden p� strengen
	while(* string != '\0'){
	strlength++;
	string++;
	}
	string -= strlength;//S�tter pegeren tilbage til starten p� strengen 
	for(i=0;i <5; i++) string[strlength+i]=' ';
	strlength+=5;
	string[strlength]='\0';
	//L�ser hver karakter
	for(i = 0; i<5; i++){
		//L�ser hver kolonne
		for(j = 0; j < 5; j++){
			buffer[i][j] = character_data[*string-0x20][j];
		}
		buffer[i][5]=0;
		string++;
	}
	display = 0;
	column = 0;
	index = 0;
	printf("%d",strlength);
}

void LEDUpdate(){
		//Opdaterer Vores LED.
		PEOUT = 0x1F;
		PEOUT ^= ( 1 << (4-column));
		
		PGOUT = *(&buffer[0][0] + column + display*6+index);
	
		

		if(display==0){
			PEOUT |=0x80;//D1 clock 
			PEOUT &= ~(1 << 7);
		}
		else if(display==1){
			PGOUT|=0x80; //D2 clock	
			PGOUT &= ~(1 << 7);
		}
		else if(display==2){
			PEOUT|=0x20; //D3 clock
			PEOUT &= ~(1 << 5);
		}
		else if(display==3){
			PEOUT|=0x40; //D4 clock
			PEOUT &= ~(1 << 6);
		}
			
	display++;
	if(display>3){
		display=0;
		column++;
	}
	if(column>4){
		column=0;
	}
	if(flag2 > 150 && strlength>9){
		index++;
		flag2 = 0;
	}
	
	
	if(index>5){
		index=0;
		loadNew();
		
	
}
main(){
	char str2[] = "FEEL THE PUMP!";
	char str3[5] = {'H','E','E','E','\0'};
	init_uart(_UART0,_DEFFREQ,_DEFBAUD);
	flag2=0;

clrscr();
printf("HALLO!ffffffff!");
LEDInit();
display2(str2,str3);

}
