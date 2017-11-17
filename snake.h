/*
 * snake.h
 *
 *  Created on: 3 Nov 2017
 *      Author: lrolo
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include "DataTypeDefinitions.h"

#define SNAKE_MAX_LENGTH 100
#define VERTICALFIELD 6
#define HORIZONTALFIELD 84
#define STARTPOSITION_Y 3
#define STARTPOSITION_X 42
#define STARTINGSIZE 14
#define FIELDSIZE 504

typedef enum{NMOVE=-1, STOP, MOVE}Motion;
typedef enum{BEGIN, DSTART}Conditionals;
typedef enum{DEAD, ALIVE}GameOver;

typedef struct{

	uint8 snakePositionX;
	uint8 snakePositionY;
	uint8 modifyPositionX;
	uint8 modifyPositionY;
	uint8 image;

}snakeType;

typedef struct{

	uint8 fruitPositionX;
	uint8 fruitPositionY;

}fruitPosition;

void initSnakeParameters(void);
void initMotionSnake(void);
void createField(void);
void introduceDataToField(void);
void drawField(void);
void gameLoop(void);
void input(uint8* life);
void update(void);
void introduceNewDataToField(void);

#endif /* SNAKE_H_ */

