/*
 * snake.h
 *
 *  Created on: 3 Nov 2017
 *      Author: lrolo
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include "DataTypeDefinitions.h"

#define SNAKE_LENGTH 100
#define VERTICAL_FIELD_SIZE 21
#define HORIZONTAL_FIELD_SIZE 65
#define STARTPOSITION_Y 10
#define STARTPOSITION_X 32
#define STARTINGSIZE 4

typedef enum{STOP, MOVE}Motion;
typedef enum{BEGIN, DSTART}Conditionals;

typedef struct{

	uint8 snakePositionX;
	uint8 snakePositionY;
	uint8 modifyPositionX;
	uint8 modifyPositionY;
	sint8 image;

}snakePosition;

typedef struct{

	uint8 fruitPositionX;
	uint8 fruitPositionY;

}fruitPosition;

void snakeGame(void);
void initSnakeParameters(uint8 *size, sint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE]);
void initMotionSnake(uint8 size);
void createField(sint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE]);
void introduceDataToField(sint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE], uint8 size);
void drawField(sint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE]);

#endif /* SNAKE_H_ */
