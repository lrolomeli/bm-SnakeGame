/*
 * snake.c
 *
 *  Created on: 3 Nov 2017
 *      Author: lrolo
 */

#include "MK64F12.h"
#include "snake.h"
#include "LCDNokia5110.h"

static snakeType snake[SNAKE_LENGTH];								//This structure is the snake
static fruitPosition fruit;										//This structure is the fruit of the snake
static uint8 currentSnakeSize;										//Indicates the current size of the snake
static uint8 field[VERTICAL_FIELD_SIZE][HORIZONTAL_FIELD_SIZE];	//Indicates the size of the field

void initSnakeParameters(void)
{
	snake[BEGIN].snakePositionX = STARTPOSITION_X;			//THIS WILL ONLY BE THE HEAD OF THE SNAKE
	snake[BEGIN].snakePositionY = STARTPOSITION_Y;			//SNAKE WILL START AT THE MIDDLE OF THE SCREEN

	currentSnakeSize = STARTINGSIZE;						//SNAKE INITIAL SIZE

	fruit.fruitPositionX = 5; 								//RANDOM VALUE FOR  FRUIT IN X
	fruit.fruitPositionY = 3; 								//RANDOM VALUE FOR  FRUIT IN Y

	initMotionSnake();										//CALL TO CONFIGURE MOTION OF THE SNAKE

	createField();											//THIS FUNCTION CREATES THE FIELD WITHOUT ANYTHING INSIDE

	introduceDataToField();									//THIS FUNCTION FILLS THE FIELD WITH ALL INITIAL VALUES

	drawField();											//THIS FUNCTION DRAWS ALL INTIAL DATA ON THE FIELD
}

void initMotionSnake(void)
{
	uint8 moveSnake;
	/*
	 * Entering MOVE to this modifier will cause snake to move
	 * X for horizontal axe & Y for vertical, STOP will set them
	 * Still on their position
	 */
	for(moveSnake=currentSnakeSize; moveSnake; moveSnake--)
	{
		snake[currentSnakeSize-moveSnake].modifyPositionX = MOVE;
		snake[currentSnakeSize-moveSnake].modifyPositionY = STOP;
	}

}

void createField(void)
{
	uint8 fieldRows, fieldColumns;
	/*
	 * This function will only be setting the field
	 * where snake will be moving on
	 */
	for(fieldRows=VERTICAL_FIELD_SIZE; fieldRows; fieldRows--)
	{
		for(fieldColumns=HORIZONTAL_FIELD_SIZE; fieldColumns; fieldColumns--)
		{
				if((VERTICAL_FIELD_SIZE-fieldRows) == BEGIN || (VERTICAL_FIELD_SIZE-fieldRows) == VERTICAL_FIELD_SIZE-DSTART)
					field[VERTICAL_FIELD_SIZE-fieldRows][HORIZONTAL_FIELD_SIZE-fieldColumns] = '-';

				else if((HORIZONTAL_FIELD_SIZE-fieldColumns) == BEGIN || (HORIZONTAL_FIELD_SIZE-fieldColumns) == HORIZONTAL_FIELD_SIZE-DSTART)
					field[VERTICAL_FIELD_SIZE-fieldRows][HORIZONTAL_FIELD_SIZE-fieldColumns] = '|';

				else
					field[VERTICAL_FIELD_SIZE-fieldRows][HORIZONTAL_FIELD_SIZE-fieldColumns] = ' ';
		}
	}

}

void introduceDataToField(void)
{
	uint8 snakeCounter;

	/*
	 * In this cycle we are making the body of the snake to appears just to the left side of the head
	 * Starting from DSTART to fill all the body of the snake cause the head is already there
	 */

	for(snakeCounter=(currentSnakeSize-DSTART); snakeCounter; snakeCounter--)
	{
		snake[currentSnakeSize-snakeCounter].snakePositionX = snake[currentSnakeSize-(snakeCounter+DSTART)].snakePositionX - DSTART;
		snake[currentSnakeSize-snakeCounter].snakePositionY = snake[currentSnakeSize-(snakeCounter+DSTART)].snakePositionY;
		/** An X will be simulating the body of the snake*/
		snake[currentSnakeSize-snakeCounter].image = 'o';
	}
	/** While an O must be the head of the snake*/
	snake[BEGIN].image = 'x';

	/** This loop is in charge of filling the snake on the field*/
	for(snakeCounter=currentSnakeSize; snakeCounter; snakeCounter--)
	{
		field[snake[currentSnakeSize-snakeCounter].snakePositionY][snake[currentSnakeSize-snakeCounter].snakePositionX] = snake[currentSnakeSize-snakeCounter].image;
	}
	/** This line is filling the random fruit on the field*/
	field[fruit.fruitPositionY][fruit.fruitPositionX]='6';
}

void drawField(void)
{

	/**Vamos a crear un bitmap apartir de ciertas modificaciones */

	// esta funcion de lcd nokia recibe un vector de 504 elementos
	//y lo que nosotros tenemos es una matriz 12x42 convertido a un vector
	uint8 fieldRows,fieldColumns;
	uint8 image[FIELDSIZE];
	for(fieldRows=BEGIN; fieldRows<VERTICAL_FIELD_SIZE; fieldRows++)
	{
		for(fieldColumns=BEGIN; fieldColumns<HORIZONTAL_FIELD_SIZE; fieldColumns++)
		{
			image[fieldRows*HORIZONTAL_FIELD_SIZE+fieldColumns] = field[fieldRows][fieldColumns];
		}
	}

	LCDNokia_bitmap(image);
}
//prueba para que ambos modifiquemos
