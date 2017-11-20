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
#define STARTINGSIZE 8
#define FIELDSIZE 504
#define TWICE 2

typedef enum{NMOVE = -1, STOP, MOVE}MotionX;
typedef enum{UP = -1, DOWN = 1}MotionY;
typedef enum{HIGHEST = 1, LOWEST = 128}Pixels;
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
void input(void);
void update(void);
void introduceNewDataToField(void);
void moveSnakeAxisY(void);

#endif /* SNAKE_H_ */

