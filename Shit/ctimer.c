#include <ez8.h>
#include "ctimer.h"
unsigned long time;
int timeWait;
void resetTimer(){
time = 0;
timeWait = 0;
}
#pragma interrupt
void timer0int(){
time++;
timeWait--;
}

int getDelay(){
return timeWait;
}

void setDelay(int input){
timeWait = input;
}


void setTimer(){
	DI();
	T0CTL = 0x01;
	T0H = 0x00;
	T0L = 0x01;
	T0RH = 0x48; //0x05
	T0RL = 0x00; //0xA0
	SET_VECTOR(TIMER0, timer0int);
	IRQ0ENH |= 0x20;
	IRQ0ENL |= 0x20;
	T0CTL |= 0x80;

	EI();
}

unsigned long getCentis(){
	return time;
}
