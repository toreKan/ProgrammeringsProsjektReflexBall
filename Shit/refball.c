#include <eZ8.h>
#include <sio.h>
#include <stdlib.h>
#include "refball.h"
#include "math.h"
#include "graphics.h"
#include "ansi.h"

void moveBall(Ball * ball){
  ball->x += (ball->xdir);
  ball->y += (ball->ydir);
}

void moveStriker(long * x,char direction){
    if(direction && ((*x + STRIKER_WIDTH + 2) < R_EDGE_COORD))
        * x += STRIKER_SPEED;

    else if(!direction && ((*x - STRIKER_WIDTH - 2) > (L_EDGE_COORD)))
        * x -= STRIKER_SPEED;
}

unsigned char checkBall(Ball * ball,Box * box,  int x){
  char right;
  int angle;
  char nextPosX, nextPosY;
  unsigned char j;
  unsigned char xt = toTerminalCoordinates(ball->x); // Defineres så vi undgår at kalde funktionen flere gange
  unsigned char yt = toTerminalCoordinates(ball->y); // Defineres så vi undgår at kalde funktionen den flere gange
  nextPosX = toTerminalCoordinates(ball->x + ball->xdir); 
  nextPosY = toTerminalCoordinates(ball->y + ball->ydir); 
    if((nextPosY == STRIKER_Y) && (nextPosX >= (x - STRIKER_WIDTH)) && nextPosX <= (x + STRIKER_WIDTH)){


      if(ball->xdir > 0){
        right = 1;
      }else{
        right = 0;
      }

		
		
	  	//Left part of striker
		if(nextPosX >= x - STRIKER_WIDTH && nextPosX < (x - 1)){
        	if(right){
				if(ball->ydir > (7 << 11)){//0.875
					angle = -20;
				}else if ( ball->ydir > (1 << 13)){//0.5
					angle = -30;
				}else{
					angle = -80;
				}
			}else{
				if(ball->ydir > (7 << 11)){
					angle = -20;
				}else if ( ball->ydir > (1 << 13)){
					angle = -30;
				}else{
					angle = 80;
				}
			}
			rotate(ball,angle);
			
      	//Middle part of striker
      	}else if (nextPosX <= x -1 || nextPosX >= x + 1){

      	//Right part of striker
      	}else{
       		if(right){
				if(ball->ydir > (7 << 11)){
					angle = -20;
				}else if ( ball->ydir > (1 << 13)){
					angle = -30;
				}else{
					angle = 80;
				}
			}else{
				if(ball->ydir > (7 << 11)){
					angle = -20;
				}else if ( ball->ydir > (1 << 13)){
					angle = -30;
				}else{
					angle = -80;
				}
			}
			rotate(ball,angle);
		}
		
		ball->ydir *= -1;
		


    }
    else if(nextPosX >= R_EDGE_COORD || nextPosX <= L_EDGE_COORD){
      ball->xdir *= -1;
    }
    else if(nextPosY <= TOP_EDGE_COORD){
      ball->ydir *= -1;
      }
    else if(nextPosY >= OUT_OF_BOUNDS){
		ball->outOfBounds = 1;
    }

    else{

        for(j=0; j < box->size; j++){

          if((box->durability[j] > 0) && (nextPosX >= box->x[j] && nextPosX < box->x[j]+BOXSIZE) && (box->y[j] == nextPosY || box->y[j]+1 == nextPosY))// Boksene har en bredde på 3, vi tester alle koordinater
              {
				
			    if(!(ball->powerActivated)){
	                if((xt >= box->x[j]) && (xt < box->x[j]+BOXSIZE))
	                ball->ydir *= -1;
	
	                else if(yt == box->y[j] || yt == box->y[j]+1)
	                ball->xdir *= -1;
	
	                else{
	                  ball->xdir *= -1;
	                  ball->ydir *= -1;
	                }
				}
				
				//Kills the box instantly when high power
				if(ball->powerActivated && ball->power){
					box->boxesLeft--;
					box->durability[j] = 0;
					ball->power --;
					if(ball->power <= 0){ ball->powerActivated = 0;}
					
				}else{
					if(--box->durability[j] == 0){
						box->boxesLeft--;
						ball->power ++;
						if(ball->power > 9) ball->power = 9;	
					}
					
				}
				drawBox(box->x[j],box->y[j],7-box->durability[j],BOXSIZE);
				
				
            }
        }

      }
    if (xt == L_EDGE_COORD || xt == R_EDGE_COORD){
      return EDGE;
    }
    else if(yt == TOP_EDGE_COORD){
      return TOP_EDGE;
    }
    else if(xt == x && yt ==STRIKER_Y){
      return STRIKER;
    }
    else
      return BLANK;

}
	long toTerminalCoordinates(long x){
  	long o = x >> FIX14_SHIFT;
	o += (x >> (FIX14_SHIFT-1)) & 0x1;
	return o;

}

void setBallOverStriker( Ball * ball, long st){
	ball->x = (st << FIX14_SHIFT);
	ball->y = ((STRIKER_Y-OVER_STRIKER) << FIX14_SHIFT);
	
	ball->xdir = 0;
	ball->ydir = (-1) << FIX14_SHIFT;
	rotate(ball, -(int) 40);
/*
  ball->xdir = (11 << (FIX14_SHIFT - 4));
  ball->ydir = (-11 << (FIX14_SHIFT - 4));
*/

}

Box * newBoxStack() {
    Box * stackContents;
    stackContents = malloc(sizeof(Box));
    stackContents-> size = 0;
    stackContents->x= malloc(sizeof(char)*MAX_BOXES);
    stackContents->y = malloc(sizeof(char)*MAX_BOXES);
    stackContents->durability = malloc(sizeof(char)*MAX_BOXES);
    return stackContents;
}

void createBoxes( Box * box,char level){ //Creates and draws boxes
	unsigned char j,i;
  unsigned char * xtemp, * ytemp, * dtemp;
				box->size = 0;
				if(level == 1){
				     for(j=0;j<1;j++){
					        for(i = L_EDGE_COORD + 5; i < (R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        box->x[box->size] = i;
	                      	box->y[box->size] = TOP_EDGE_COORD+20+j*2;
	                      	box->durability[box->size] = 1;
	                      	box->size++;
							
	                      }
	         		 }
				 }else if(level == 2){
				     for(j=0;j<2;j++){
					         for(i = L_EDGE_COORD + 5; i < (R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        	box->x[box->size] = i;
	                      		box->y[box->size] = TOP_EDGE_COORD+20+j*2;
	                      		box->durability[box->size] = j+1;
	                      		box->size++;
	
	                      }
	         		 }

				}else if(level == 3){
					/*for(i = 0; i < 16; i++){
						box->x[box->size] = 20 + 4*i;
						if(i < 8) box->y[box->size] = 5 + i;
						else box->y[box->size] = 19 - (i-8);
						
						box->durability[box->size] = 3;
						box->size++;
					}
					
					*/
					
				     for(j=0;j<3;j++){
					         for(i = L_EDGE_COORD + 5; i < (R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        	box->x[box->size] = i;
	                      		box->y[box->size] = TOP_EDGE_COORD+20+j*2;
	                      		box->durability[box->size] = j+1;
	                      		box->size++;
	
	                      }
	         		 }
					 

				}else if(level == 4){
				     for(j=2;j<4;j++){
					         for(i = L_EDGE_COORD + 5; i < (R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        	box->x[box->size] = i;
	                      		box->y[box->size] = TOP_EDGE_COORD+20+j*2;
	                      		box->durability[box->size] = j+1;
	                      		box->size++;
	
	                      }
	         		 }

				}else if(level == 5){
				     for(j=3;j<5;j++){
					         for(i = L_EDGE_COORD + 5; i < (R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        	box->x[box->size] = i;
	                      		box->y[box->size] = TOP_EDGE_COORD+25+j*2;
	                      		box->durability[box->size] = j+1;
	                      		box->size++;
	
	                      }
	         		 }

				}
				box->boxesLeft = box->size;
}
