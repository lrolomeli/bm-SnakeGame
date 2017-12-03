/*
 * snake.c
 *
 *  Created on: 3 Nov 2017
 *      Author: lrolo
 */

#include "MK64F12.h"
#include "snake.h"
#include "LCDNokia5110.h"
#include "PIT.h"
#include "GPIO.h"
#include "accelerometer.h"
#include "menu.h"

static snakeType snake[SNAKE_MAX_LENGTH];							//This structure is the snake
static fruitPosition fruit;											//This structure is the fruit of the snake
static uint8 fruity = 0;
static uint8 currentSnakeSize;										//Indicates the current size of the snake
static uint8 field[VERTICALFIELD][HORIZONTALFIELD] = {0};			//Indicates the size of the field
static uint8 life = ALIVE;											//Indicates whether snake is alive
static uint8 eatenFruit = FALSE;									//flag for eaten fruit
static uint8 lastTailPositionX, lastTailPositionY, lastTailImage;						//Tail image and position previous run
static uint8 endGame[] = "GAME OVER"; 								//String to be printed in the LCD
static uint8 selectCtrl;
static uint8 score = FALSE;

void initSnakeParameters(void)
{

	snake[BEGIN].snakePositionX = STARTPOSITION_X;			//THIS WILL ONLY BE THE HEAD OF THE SNAKE
	snake[BEGIN].snakePositionY = STARTPOSITION_Y;			//SNAKE WILL START AT THE MIDDLE OF THE SCREEN

	currentSnakeSize = STARTINGSIZE;						//SNAKE INITIAL SIZE

	fruit.fruitPositionX = 67; 								//RANDOM VALUE FOR  FRUIT IN X
	fruit.fruitPositionY = 3; 								//RANDOM VALUE FOR  FRUIT IN Y

	initMotionSnake();										//CALL TO CONFIGURE MOTION OF THE SNAKE

	createField();											//THIS FUNCTION CREATES THE FIELD WITHOUT ANYTHING INSIDE

	introduceDataToField();									//THIS FUNCTION FILLS THE FIELD WITH ALL INITIAL VALUES

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
		snake[moveSnake].modifyPositionX = STOP;
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
	for(snakeCounter = BEGIN; snakeCounter < currentSnakeSize; snakeCounter++)
	{
		field[snake[snakeCounter].snakePositionY][snake[snakeCounter].snakePositionX] = snake[snakeCounter].image;
	}
	/** This lines is filling the random fruit on the field*/
	fruit.image = 0x01;

	field[fruit.fruitPositionY][fruit.fruitPositionX] = fruit.image;
}

void drawField(void)
{

	/**WE ARE GOING TO CREATE A BIT MAP FROM A BIDIMENSIONAL MATRIX */

	// This function receives a vector of 504 elements
	// and we are going to convert it from a 6 x 84 matrix

	uint8 fieldRows, fieldColumns;
	static uint8 lcdImage[FIELDSIZE];

	for(fieldRows = BEGIN; fieldRows < VERTICALFIELD; fieldRows++)
	{
		for(fieldColumns = BEGIN; fieldColumns < HORIZONTALFIELD; fieldColumns++)
		{
			lcdImage[fieldRows*HORIZONTALFIELD+fieldColumns] = field[fieldRows][fieldColumns];
		}
	}

	LCDNokia_bitmap(lcdImage);

}

void gameLoop(void)
{
	setlocal();
	LCDNokia_clear();
	PIT_delay(PIT_0, SYSTEMCLOCK, 0.0001);

	/**Continue the game while we are alive and back have not been pressed*/
	while(ALIVE == life && !(GBACK == getButton()))
	{

		xyz_Acc();

		if(FALSE != PIT_getIntrStatus())
		{
			drawField();
			input();
			update();
			PIT_delay(PIT_0, SYSTEMCLOCK, 0.3);
		}

		if(DEAD == life)
		{
			setDirection();
		}

	}


	if(ALIVE != life)
	{

		LCDNokia_gotoXY(10,2);
		LCDNokia_sendString(endGame); 	/*! It prints a GAME OVER stored in an array*/



		if(GBACK == getButton())
		{
			LCDNokia_clear();
			initSnakeParameters();		/*!Reinitialises the parameters of snake game*/
			life = ALIVE;
			setRecord(score);			/*!Stores scores*/
			score = FALSE;

		}
		else
			keepPlaying();
	}



}

void input(void)
{

	uint8 snakeCounter;

	//We must check if the head of the snake is in any border of the field
	if(snake[BEGIN].snakePositionX == BEGIN || snake[BEGIN].snakePositionX == HORIZONTALFIELD - DSTART || (snake[BEGIN].snakePositionY == BEGIN && snake[BEGIN].image & 0x01) || (snake[BEGIN].snakePositionY == VERTICALFIELD - DSTART && snake[BEGIN].image & 0x80))
		life = DEAD;
	//And of course check if the head has eaten its body
	for(snakeCounter = DSTART; snakeCounter < currentSnakeSize && ALIVE == life; snakeCounter++)
	{
		if(snake[BEGIN].snakePositionX == snake[snakeCounter].snakePositionX && snake[BEGIN].snakePositionY == snake[snakeCounter].snakePositionY && snake[BEGIN].image == snake[snakeCounter].image)
			life = DEAD;
	}

	//If the head is in the same position as fruit and with the exactly same image then fruit was eaten

	if(eatenFruit)
	{
		currentSnakeSize++;												//adding one element to the body of the snake

		snake[currentSnakeSize - 1].snakePositionX = lastTailPositionX;	//Saving x position of tail of the snake
		snake[currentSnakeSize - 1].snakePositionY = lastTailPositionY;	//Saving y position of tail of the snake
		snake[currentSnakeSize - 1].image = lastTailImage;				//Saving image of tail of the snake
		fruity++;
		switch(fruity)
		{
		case 0:
			fruit.fruitPositionX = 13; 								//RANDOM VALUE FOR  FRUIT IN X
			fruit.fruitPositionY = 4; 								//RANDOM VALUE FOR  FRUIT IN Y
			fruit.image = 0x01;
			break;
		case 1:
			fruit.fruitPositionX = 13; 								//RANDOM VALUE FOR  FRUIT IN X
			fruit.fruitPositionY = 4; 								//RANDOM VALUE FOR  FRUIT IN Y
			fruit.image = 0x80;
			break;
		case 2:
			fruit.fruitPositionX = 76; 								//RANDOM VALUE FOR  FRUIT IN X
			fruit.fruitPositionY = 4; 								//RANDOM VALUE FOR  FRUIT IN Y
			fruit.image = 0x02;
			break;
		case 3:
			fruit.fruitPositionX = 53; 								//RANDOM VALUE FOR  FRUIT IN X
			fruit.fruitPositionY = 3; 								//RANDOM VALUE FOR  FRUIT IN Y
			fruit.image = 0x80;
			break;
		case 4:
			fruit.fruitPositionX = 60; 								//RANDOM VALUE FOR  FRUIT IN X
			fruit.fruitPositionY = 2; 								//RANDOM VALUE FOR  FRUIT IN Y
			fruit.image = 0x08;
			break;
		default:
			fruity = 0;
			fruit.fruitPositionX = 10; 								//RANDOM VALUE FOR  FRUIT IN X
			fruit.fruitPositionY = 5; 								//RANDOM VALUE FOR  FRUIT IN Y
			fruit.image = 0x04;
			break;
		}


		eatenFruit = FALSE;

	}

	if(snake[BEGIN].snakePositionX == fruit.fruitPositionX && snake[BEGIN].snakePositionY == fruit.fruitPositionY && snake[BEGIN].image & fruit.image)
	{
		//This flag indicates that fruit was eaten so the last position will be copied
		//And will be send on the next move of the snake
		eatenFruit = TRUE;
		score++;
		//This part saves the position and image of the current tail so the next tail will be incremented
		lastTailPositionX = snake[currentSnakeSize - 1].snakePositionX;
		lastTailPositionY = snake[currentSnakeSize - 1].snakePositionY;
		lastTailImage = snake[currentSnakeSize - 1].image;
	}
	//If button 3 is pressed then snake will start moving right
	if(NOBUTTONPRESSED != getDirection()){

		if(ALIVE == life) //of course while we are alive
		{

			if(selectCtrl)
			{
				if(GDOWN == getButton()/**getMotion()*/ && UP != snake[BEGIN].modifyPositionY)			//DOWN	/**cannot go down while moving up*/
				{
					snake[BEGIN].modifyPositionX = STOP;
					snake[BEGIN].modifyPositionY = DOWN;
				}

				if(GUP == getButton()/**getMotion()*/ && DOWN != snake[BEGIN].modifyPositionY)			//UP	/**cannot go up while moving down*/
				{
					snake[BEGIN].modifyPositionX = STOP;
					snake[BEGIN].modifyPositionY = UP;
				}

				if(GLEFT == getButton()/**getMotion()*/ && RIGHT != snake[BEGIN].modifyPositionX)		//LEFT	/**cannot go left while moving right*/
				{
					snake[BEGIN].modifyPositionX = LEFT;
					snake[BEGIN].modifyPositionY = STOP;
				}

				if(GRIGHT == getButton()/**getMotion()*/ && LEFT != snake[BEGIN].modifyPositionX)		//RIGHT	/**cannot go right while moving left*/
				{
					snake[BEGIN].modifyPositionX = RIGHT;
					snake[BEGIN].modifyPositionY = STOP;
				}
			}

			else
			{
				if(GDOWN == getDirection()/**getMotion()*/ && UP != snake[BEGIN].modifyPositionY)		//DOWN	/**cannot go down while moving up*/
				{
					snake[BEGIN].modifyPositionX = STOP;
					snake[BEGIN].modifyPositionY = DOWN;
				}

				if(GUP == getDirection()/**getMotion()*/ && DOWN != snake[BEGIN].modifyPositionY)		//UP	/**cannot go up while moving down*/
				{
					snake[BEGIN].modifyPositionX = STOP;
					snake[BEGIN].modifyPositionY = UP;
				}

				if(GLEFT == getDirection()/**getMotion()*/ && RIGHT != snake[BEGIN].modifyPositionX)	//LEFT	/**cannot go left while moving right*/
				{
					snake[BEGIN].modifyPositionX = LEFT;
					snake[BEGIN].modifyPositionY = STOP;
				}

				if(GRIGHT == getDirection()/**getMotion()*/ && LEFT != snake[BEGIN].modifyPositionX)	//RIGHT	/**cannot go right while moving left*/
				{
					snake[BEGIN].modifyPositionX = RIGHT;
					snake[BEGIN].modifyPositionY = STOP;
				}
			}

		}

		/*
		 * On this loop we are making that last element of the snake follows the next one in line
		 */
		for(snakeCounter = currentSnakeSize-DSTART; snakeCounter > BEGIN; snakeCounter--)
		{
			snake[snakeCounter].snakePositionX = snake[snakeCounter-DSTART].snakePositionX;		//Copying next X position in line
			snake[snakeCounter].image = snake[snakeCounter-DSTART].image;						//otherwise we will just copy next image in line
			snake[snakeCounter].snakePositionY = snake[snakeCounter-DSTART].snakePositionY;		//Copying next Y position in line
		}

	}


}

void update(void)
{
	//CLEAR ALL DATA ON FIELD
	createField();
	//Recalculating values for the snake
	introduceNewDataToField();

}

void moveSnakeAxisY(void)
{


	if(DOWN == snake[BEGIN].modifyPositionY)		//This means they need to change snake position going down 1 but only one pixel
	{
		if(LOWEST == snake[BEGIN].image)						//Only if the pixel has the final pixel value
		{
			snake[BEGIN].snakePositionY += MOVE;	//We are going to decrement the position of the snake
			snake[BEGIN].image = HIGHEST;
		}

		else{
			snake[BEGIN].image *= TWICE;		//So we are only redrawing the head of the snake so the body can replaced it later
			/**The head already has the position in AXIS Y*/
		}


	}

	else if(UP == snake[BEGIN].modifyPositionY)		//This means they need to change snake position going up 1 but only one pixel
	{
		if(HIGHEST == snake[BEGIN].image)									//Only if the pixel has the final pixel value
		{
			snake[BEGIN].snakePositionY += NMOVE;	//We are going to increment the position of the snake
			snake[BEGIN].image = LOWEST;
		}

		else{
			snake[BEGIN].image /= TWICE;		//So we are only redrawing the head of the snake so the body can replaced it later
			/**The head already has the position in AXIS Y*/
		}
	}

}

void introduceNewDataToField(void)
{

	uint8 snakeCounter;

	if(LEFT == snake[BEGIN].modifyPositionX)
		snake[BEGIN].snakePositionX += NMOVE;

	else
		snake[BEGIN].snakePositionX += snake[BEGIN].modifyPositionX;

	moveSnakeAxisY();

	//At this point we have the positions in axis X and images of all the body of the snake

	//Una vez que tenemos todas las imagenes de la serpiente posiciones y lo demas
	//vamos a checar todos los elementos de la serpiente y vamos a agrupar los que se encuentren en la misma posicion

	for(snakeCounter = BEGIN; snakeCounter < currentSnakeSize-DSTART; snakeCounter++)
	{
		//checamos si el primer elemento tiene la misma posicion que el segundo
		//y si es asi el segundo elemento tendra la imagen del primero concatenada con la suya
		//si el segundo elemento tiene la misma posicion que el tercero entonces
		//el tercer elemento tendra la imagen del segundo concatenada con el tercero

		if(snake[snakeCounter].snakePositionY == snake[snakeCounter+DSTART].snakePositionY)
			snake[snakeCounter+DSTART].image |= snake[snakeCounter].image;
	}

	for(snakeCounter = BEGIN; snakeCounter < currentSnakeSize; snakeCounter++)
	{
		field[snake[snakeCounter].snakePositionY][snake[snakeCounter].snakePositionX] = snake[snakeCounter].image;
	}

	field[fruit.fruitPositionY][fruit.fruitPositionX] = fruit.image;
}

void setManual(void)
{
	selectCtrl = TRUE;
}

void setAccel(void)
{
	selectCtrl = FALSE;
}
