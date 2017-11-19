/*
 * snake.c
 *
 *  Created on: 3 Nov 2017
 *      Author: lrolo
 */

#include "MK64F12.h"
#include "snake.h"
#include "LCDNokia5110.h"
#include "LCDNokia5110Images.h"
#include "PIT.h"
#include "GPIO.h"

static snakeType snake[SNAKE_MAX_LENGTH];							//This structure is the snake
static fruitPosition fruit;											//This structure is the fruit of the snake
static uint8 currentSnakeSize;										//Indicates the current size of the snake
static uint8 field[VERTICALFIELD][HORIZONTALFIELD] = {0};			//Indicates the size of the field

void initSnakeParameters(void)
{
	snake[BEGIN].snakePositionX = STARTPOSITION_X;			//THIS WILL ONLY BE THE HEAD OF THE SNAKE
	snake[BEGIN].snakePositionY = STARTPOSITION_Y;			//SNAKE WILL START AT THE MIDDLE OF THE SCREEN

	currentSnakeSize = STARTINGSIZE;						//SNAKE INITIAL SIZE

	fruit.fruitPositionX = 12; 								//RANDOM VALUE FOR  FRUIT IN X
	fruit.fruitPositionY = 5; 								//RANDOM VALUE FOR  FRUIT IN Y

	initMotionSnake();										//CALL TO CONFIGURE MOTION OF THE SNAKE

	createField();											//THIS FUNCTION CREATES THE FIELD WITHOUT ANYTHING INSIDE

	introduceDataToField();									//THIS FUNCTION FILLS THE FIELD WITH ALL INITIAL VALUES

	gameLoop();

	//drawField();											//THIS FUNCTION DRAWS ALL INTIAL DATA ON THE FIELD
}

void initMotionSnake(void)
{
	uint8 moveSnake;
	/*
	 * Entering MOVE to this modifier will cause snake to move
	 * X for horizontal axe & Y for vertical, STOP will set them
	 * Still on their position
	 */
	for(moveSnake=BEGIN; moveSnake<currentSnakeSize; moveSnake++)
	{
		snake[moveSnake].modifyPositionX = MOVE;
		snake[moveSnake].modifyPositionY = STOP;
	}

}

void createField(void)
{
	uint8 fieldRows, fieldColumns;
	/*
	 * This function will only be setting the field
	 * where snake will be moving on
	 */
	for(fieldRows = BEGIN; fieldRows < VERTICALFIELD; fieldRows++)
	{
		for(fieldColumns = BEGIN; fieldColumns < HORIZONTALFIELD; fieldColumns++)
		{

			//FIRST ROW
			if(fieldRows == BEGIN)
				field[fieldRows][fieldColumns] = 0x01;

			//LAST ROW
			else if(fieldRows == VERTICALFIELD-DSTART)
				field[fieldRows][fieldColumns] = 0x80;

			//FIRST OR LAST COLUMN
			else if(fieldColumns == BEGIN || fieldColumns == HORIZONTALFIELD-DSTART)
				field[fieldRows][fieldColumns] = 0xFF;

			//NON OF THIS
			else
				field[fieldRows][fieldColumns] = 0x00;

			//FIRST ROW BUT IN ADDITION FIRST COLUMN OR LAST COLUMN
			if(fieldRows == BEGIN && (fieldColumns == BEGIN || fieldColumns == HORIZONTALFIELD-DSTART))
				field[fieldRows][fieldColumns] = 0xFF;

			//LAST ROW BUT IN ADDITION FIRST COLUMN OR LAST COLUMN
			if(fieldRows == VERTICALFIELD-DSTART && (fieldColumns == BEGIN || fieldColumns == HORIZONTALFIELD-DSTART))
				field[fieldRows][fieldColumns] = 0xFF;

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

	for(snakeCounter=DSTART; snakeCounter<currentSnakeSize; snakeCounter++)
	{
		snake[snakeCounter].snakePositionX = snake[snakeCounter-DSTART].snakePositionX - DSTART;
		snake[snakeCounter].snakePositionY = snake[snakeCounter-DSTART].snakePositionY;
		/** An X will be simulating the body of the snake*/
		snake[snakeCounter].image = 0x01;
	}
	/** While an O must be the head of the snake*/
	snake[BEGIN].image = 0x01;

	/** This loop is in charge of filling the snake on the field*/
	for(snakeCounter=BEGIN; snakeCounter<currentSnakeSize; snakeCounter++)
	{
		field[snake[snakeCounter].snakePositionY][snake[snakeCounter].snakePositionX] = snake[snakeCounter].image;
	}
	/** This line is filling the random fruit on the field*/
	field[fruit.fruitPositionY][fruit.fruitPositionX] = 0x01;
}

void drawField(void)
{

	/**WE ARE GOING TO CREATE A BIT MAP FROM A BIDIMENSIONAL MATRIX */

	// This function receives a vector of 504 elements
	// and we are going to convert it from a 6 x 84 matrix

	uint8 fieldRows,fieldColumns;
	static uint8 lcdImage[FIELDSIZE];

	for(fieldRows = BEGIN; fieldRows < VERTICALFIELD; fieldRows++)
	{
		for(fieldColumns = BEGIN; fieldColumns < HORIZONTALFIELD; fieldColumns++)
		{
			lcdImage[fieldRows*HORIZONTALFIELD+fieldColumns] = field[fieldRows][fieldColumns];
		}
	}

	//LCDNokia_bitmap(getImage());
	//lcdImage[502]=0xFF;
	//lcdImage[503]=0xFF;
	LCDNokia_bitmap(lcdImage);

}


void gameLoop(void)
{

	uint8 life = ALIVE;
	uint8 string1[]="GAME OVER"; /*! String to be printed in the LCD*/

	do{
		LCDNokia_clear();
		drawField();
		input(&life);
		update();
		PIT_delay(PIT_0, SYSTEMCLOCK, 0.15);
		while(!PIT_getIntrStatus());	//secure count to 10ms after reseting LCD
	}while(ALIVE==life);

	LCDNokia_gotoXY(10,2);
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/

}


void input(uint8* life)
{

	uint8 snakeCounter;

	//si estamos en alguno de los bordes de la pantalla life debe ser igual a 0
	if(snake[BEGIN].snakePositionX == BEGIN || snake[BEGIN].snakePositionX == HORIZONTALFIELD - DSTART || snake[BEGIN].snakePositionY == BEGIN || snake[BEGIN].snakePositionY == VERTICALFIELD - DSTART)
		*life = DEAD;

	for(snakeCounter = DSTART; snakeCounter < currentSnakeSize && ALIVE == *life; snakeCounter++)
	{
		if(snake[BEGIN].snakePositionX == snake[snakeCounter].snakePositionX && snake[BEGIN].snakePositionY == snake[snakeCounter].snakePositionY)
			*life = DEAD;
	}

	//Comprobar si nos hemos comido la fruta

	if(snake[BEGIN].snakePositionX == fruit.fruitPositionX && snake[BEGIN].snakePositionY == fruit.fruitPositionY)
	{
		currentSnakeSize++;

		snake[currentSnakeSize - 1].image = 0x01;

		fruit.fruitPositionX = 13; 								//RANDOM VALUE FOR  FRUIT IN X
		fruit.fruitPositionY = 4; 								//RANDOM VALUE FOR  FRUIT IN Y
	}

	if(ALIVE == *life && 4 != getMotion())
	{

		if(0 == getMotion() && snake[BEGIN].modifyPositionY != NMOVE)		//UP
		{
			snake[BEGIN].modifyPositionX=STOP;
			snake[BEGIN].modifyPositionY=MOVE;

		}

		if(1 == getMotion() && snake[BEGIN].modifyPositionY != MOVE)	//DOWN
		{
			snake[BEGIN].modifyPositionX=STOP;
			snake[BEGIN].modifyPositionY=NMOVE;
		}

		if(2 == getMotion() && snake[BEGIN].modifyPositionX != MOVE)	//LEFT
		{
			snake[BEGIN].modifyPositionX=NMOVE;
			snake[BEGIN].modifyPositionY=STOP;
		}

		if(6 == getMotion() && snake[BEGIN].modifyPositionX != NMOVE)	//RIGHT
		{
			snake[BEGIN].modifyPositionX=MOVE;
			snake[BEGIN].modifyPositionY=STOP;
		}
	}

}

void update(void)
{
	//CLEAR ALL DATA ON FIELD
	createField();

	introduceNewDataToField();

}

void introduceNewDataToField(void)
{

	uint8 snakeCounter;
	uint8 variable = 1;

	for(snakeCounter = currentSnakeSize-DSTART; snakeCounter > BEGIN; snakeCounter--)
	{
		snake[snakeCounter].snakePositionX = snake[snakeCounter-DSTART].snakePositionX;
		snake[snakeCounter].snakePositionY = snake[snakeCounter-DSTART].snakePositionY;
	}

	//queremos que solamente se copie la direccion en x porque

	snake[BEGIN].snakePositionX += snake[BEGIN].modifyPositionX;

	//hacer una funcion que solamente incremente la posicion en Y cuando se presenta el pixel mas alto para subir o mas bajo para bajar

	if(snake[BEGIN].modifyPositionY == MOVE){
		if(1 == variable){
			variable = 128;
			snake[BEGIN].snakePositionY += NMOVE;
		}

		else
		{
			for(snakeCounter = BEGIN; snakeCounter < currentSnakeSize; snakeCounter++)
			{
				field[snake[snakeCounter].snakePositionY][snake[snakeCounter].snakePositionX] = variable*2;
			}
		}
	}

	else if(snake[BEGIN].modifyPositionY == NMOVE)
	{
		if(128 == variable){
			variable = 1;
			snake[BEGIN].snakePositionY += MOVE;
		}

		else
		{
			for(snakeCounter = BEGIN; snakeCounter < currentSnakeSize; snakeCounter++)
			{
				if(BEGIN)
					field[snake[snakeCounter].snakePositionY][snake[snakeCounter].snakePositionX] = variable/2;
				else
					field[snake[snakeCounter].snakePositionY][snake[snakeCounter].snakePositionX] = variable/2;
			}
		}
	}

	else
	{
		for(snakeCounter = BEGIN; snakeCounter < currentSnakeSize; snakeCounter++)
		{
			field[snake[snakeCounter].snakePositionY][snake[snakeCounter].snakePositionX] = snake[snakeCounter].image;
		}
	}


	field[fruit.fruitPositionX][fruit.fruitPositionY] = 0x01;

}
//prueba para que ambos modifiquemos
