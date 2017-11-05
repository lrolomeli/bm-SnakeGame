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
#define STARTINGSIZE 5

typedef enum{STOP, MOVE}Motion;
typedef enum{BEGIN, DSTART}Conditionals;

typedef struct{

	uint8 snakePositionX;
	uint8 snakePositionY;
	uint8 modifyPositionX;
	uint8 modifyPositionY;
	sint8 image;

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

#endif /* SNAKE_H_ */

