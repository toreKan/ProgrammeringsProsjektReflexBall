#ifndef _REFBALL_H_
#define _REFBALL_H_
#define STRIKER_SPEED 2
#define L_EDGE_COORD 2
#define R_EDGE_COORD 120
#define STRIKER_WIDTH 4
#define OUT_OF_BOUNDS 65
#define GAMESPEED 5
#define OVER_STRIKER 20
#define STRIKER_Y  60
#define STRIKER_START  20
#define TOP_EDGE_COORD 2
#define BLANK 32
#define EDGE 180
#define TOP_EDGE 196
#define STRIKER 220
#define BOXSIZE 6
#define MAX_BOXES 50
#define KEY_LEFT 4
#define KEY_MIDDLE 2
#define KEY_RIGHT 1
  typedef struct{
  long x,y,xdir, ydir;
  unsigned char power, outOfBounds;
  } Ball;

  typedef struct{
    unsigned char *x, *y;
	unsigned char * durability;
    unsigned char size,boxesLeft;
  } Box;

  void moveBall(Ball * ball);
  void moveStriker(long * x, char direction);
  unsigned char checkBall(Ball * ball,Box * box, int x);
  long toTerminalCoordinates(long x);
  void setBallOverStriker( Ball * ball,  long st);

  Box * newBoxStack(void);
  void createBoxes( Box * box,char level);
  void checkBoxes( Ball * ball,  Box * box);
#endif
