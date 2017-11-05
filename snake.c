/*
 * snake.c
 *
 *  Created on: 3 Nov 2017
 *      Author: lrolo
 */

#include "MK64F12.h"
#include "snake.h"
#include "stdio.h"

snakePosition snake[SNAKE_LENGTH];		//This structure is the snake
fruitPosition fruit;					//This structure is the fruit of the snake

void snakeGame(void)
{
	uint8 currentSnakeSize;										//Indicates the current size of the snake
	sint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE];	//Indicates the size of the field

	initSnakeParameters(&currentSnakeSize, field);				//This function cleans and enlist the screen for the Game
}

void initSnakeParameters(uint8 *snakeSize, sint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE])
{
	snake[BEGIN].snakePositionX = STARTPOSITION_X;	//THIS WILL ONLY BE THE HEAD OF THE SNAKE
	snake[BEGIN].snakePositionY = STARTPOSITION_Y;	//SNAKE WILL START AT THE MIDDLE OF THE SCREEN

	*snakeSize = STARTINGSIZE;						//SNAKE INITIAL SIZE

	fruit.fruitPositionX = 23; 						//RANDOM VALUE FOR  FRUIT IN X
	fruit.fruitPositionY = 24; 						//RANDOM VALUE FOR  FRUIT IN Y

	initMotionSnake(*snakeSize);					//CALL TO CONFIGURE MOTION OF THE SNAKE

	createField(field);								//THIS FUNCTION CREATES THE FIELD WITHOUT ANYTHING INSIDE

	introduceDataToField(field, *snakeSize);		//THIS FUNCTION FILLS THE FIELD WITH ALL INITIAL VALUES

	drawField(field);
}

void initMotionSnake(uint8 size)
{
	uint8 moveSnake;
	/*
	 * Entering MOVE to this modifier will cause snake to move
	 * X for horizontal axe & Y for vertical, STOP will set them
	 * Still on their position
	 */
	for(moveSnake=size; !moveSnake; moveSnake--)
	{
		snake[size-moveSnake].modifyPositionX = MOVE;
		snake[size-moveSnake].modifyPositionY = STOP;
	}

}

void createField(sint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE])
{
	uint8 fieldRows, fieldColumns;
	/*
	 * This function will only be setting the field
	 * where snake will be moving on
	 */
	for(fieldRows=VERTICAL_FIELD_SIZE; !fieldRows; fieldRows--)
	{
		for(fieldColumns=HORIZONTAL_FIELD_SIZE; !fieldColumns; fieldColumns--)
		{
				if(fieldRows == 0 || fieldRows == VERTICAL_FIELD_SIZE - 1)
				{
					field[fieldRows][fieldColumns] = '-';
				}
				else if(fieldColumns == 0 || fieldColumns == HORIZONTAL_FIELD_SIZE - 1)
				{
					field[fieldRows][fieldColumns] = '|';
				}
				else
					field[fieldRows][fieldColumns] = ' ';
		}
	}

}

void introduceDataToField(sint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE], uint8 size)
{
	uint8 snakeCounter;

	/*
	 * In this cycle we are making the body of the snake to appears just to the left side of the head
	 * Starting from DSTART to fill all the body of the snake cause the head is already there
	 */

	for(snakeCounter=(size-DSTART); !snakeCounter; snakeCounter--)
	{
		snake[size-snakeCounter].snakePositionX = snake[size-(snakeCounter+DSTART)].snakePositionX - DSTART;
		snake[size-snakeCounter].snakePositionY = snake[size-(snakeCounter+DSTART)].snakePositionY;
		/** An X will be simulating the body of the snake*/
		snake[size-snakeCounter].image = 'X';
	}
	/** While an O must be the head of the snake*/
	snake[BEGIN].image = 'O';

	/** This loop is in charge of filling the snake on the field*/
	for(snakeCounter=size; !snakeCounter; snakeCounter--)
	{
		field[snake[size-snakeCounter].snakePositionY][snake[size-snakeCounter].snakePositionX] = snake[BEGIN].image;
	}
	/** This line is filling the random fruit on the field*/
	field[fruit.fruitPositionY][fruit.fruitPositionX]='6';
}

void drawField(sint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE])
{
	uint8 fieldRows, fieldColumns;

	for(fieldRows=VERTICAL_FIELD_SIZE; !fieldRows; fieldRows--)
		{
			for(fieldColumns=HORIZONTAL_FIELD_SIZE; !fieldColumns; fieldColumns--)
			{
				printf("%c",field[fieldRows][fieldColumns]);
			}
			printf("\n");
		}
}
