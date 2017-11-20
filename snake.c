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
static uint8 life = ALIVE;											//Indicates whether snake is alive
static uint8 pixel;													//Moves snake vertically
static uint8 eatenFruit = FALSE;									//flag for eaten fruit
static uint8 lastTailPosition, lastTailImage;						//Tail image and position previous run
static uint8 string1[] = "GAME OVER"; 								//String to be printed in the LCD

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

	do{
		LCDNokia_clear();
		drawField();
		input();
		update();
		PIT_delay(PIT_0, SYSTEMCLOCK, 0.9);
		while(!PIT_getIntrStatus());	//secure count to 10ms after reseting LCD
	}while(ALIVE==life);

	LCDNokia_gotoXY(10,2);
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/

}


void input(void)
{

	uint8 snakeCounter;

	//si estamos en alguno de los bordes de la pantalla life debe ser igual a 0
	if(snake[BEGIN].snakePositionX == BEGIN || snake[BEGIN].snakePositionX == HORIZONTALFIELD - DSTART || snake[BEGIN].snakePositionY == BEGIN || snake[BEGIN].snakePositionY == VERTICALFIELD - DSTART)
		life = DEAD;

	for(snakeCounter = DSTART; snakeCounter < currentSnakeSize && ALIVE == life; snakeCounter++)
	{
		if(snake[BEGIN].snakePositionX == snake[snakeCounter].snakePositionX && snake[BEGIN].image == snake[snakeCounter].image)
			life = DEAD;
	}

	//Comprobar si nos hemos comido la fruta

	//si el gusano se ha comido la fruta debe entonces crecer su cuerpo en uno
	//se debera copiar la imagen de la cola y agregarla en el siguiente refresco de la pantalla es decir
	//ya que la cabeza se haya desplazado en uno
	//por lo tanto al comprobar que se ha comido la fruta debemos guardar la imagen y la posicion de la cola
	//y en la siguiente impresion agregarle un elemento a la serpiente con la imagen y posicion anterior de la cola.

	if(eatenFruit)
	{
		currentSnakeSize++;

		snake[currentSnakeSize - 1].modifyPositionX = lastTailPosition;
		snake[currentSnakeSize - 1].image = lastTailImage;

		fruit.fruitPositionX = 13; 								//RANDOM VALUE FOR  FRUIT IN X
		fruit.fruitPositionY = 4; 								//RANDOM VALUE FOR  FRUIT IN Y

		eatenFruit = FALSE;

	}

	if(snake[BEGIN].snakePositionX == fruit.fruitPositionX && snake[BEGIN].snakePositionY == fruit.fruitPositionY)
	{
		//encender una bandera
		eatenFruit = TRUE;

		//guardar la posicion en X, la imagen de la cola
		lastTailPosition = snake[currentSnakeSize - 1].modifyPositionX;
		lastTailImage = snake[currentSnakeSize - 1].image;
	}

	if(4 != getMotion()){

		if(ALIVE == life)
		{

			if(0 == getMotion() && snake[BEGIN].modifyPositionY != UP)		//DOWN
			{
				snake[BEGIN].modifyPositionX=STOP;
				snake[BEGIN].modifyPositionY=DOWN;

			}

			if(1 == getMotion() && snake[BEGIN].modifyPositionY != DOWN)	//UP
			{
				snake[BEGIN].modifyPositionX=STOP;
				snake[BEGIN].modifyPositionY=UP;
			}

			if(2 == getMotion() && snake[BEGIN].modifyPositionX != MOVE)	//LEFT
			{
				snake[BEGIN].modifyPositionX=NMOVE;
				snake[BEGIN].modifyPositionY=STOP;
			}

			if(3 == getMotion() && snake[BEGIN].modifyPositionX != NMOVE)	//RIGHT
			{
				snake[BEGIN].modifyPositionX=MOVE;
				snake[BEGIN].modifyPositionY=STOP;
			}
		}

		for(snakeCounter = currentSnakeSize-DSTART; snakeCounter > BEGIN; snakeCounter--)
		{
			snake[snakeCounter].snakePositionX = snake[snakeCounter-DSTART].snakePositionX;
			//snake[snakeCounter].snakePositionY = snake[snakeCounter-DSTART].snakePositionY;/**Only we are copying positions in AXIS X and pixels in AXIS Y*/
			snake[snakeCounter].image = snake[snakeCounter-DSTART].image;
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

	pixel = snake[BEGIN].image;

	snake[BEGIN].snakePositionX += snake[BEGIN].modifyPositionX;

	//snake[BEGIN].snakePositionY += snake[BEGIN].modifyPositionY;/**The position in Y will not be modify unless we raised the end of the row*/

	moveSnakeAxisY();

	//At this point we have the positions in axis X and images of all the body of the snake

	for(snakeCounter = BEGIN; snakeCounter < currentSnakeSize; snakeCounter++)
	{
		field[snake[snakeCounter].snakePositionY][snake[snakeCounter].snakePositionX] = snake[snakeCounter].image;
	}

	field[fruit.fruitPositionX][fruit.fruitPositionY] = 0x01;

}

void moveSnakeAxisY(void)
{

	if(UP == snake[BEGIN].modifyPositionY)		//This means they need to change snake position going up 1 but only one pixel
	{
		if(HIGHEST==pixel)						//Only if the pixel has the final pixel value
		{
			snake[BEGIN].snakePositionY += snake[BEGIN].modifyPositionY;	//We are going to increment the position of the snake
			pixel = LOWEST;													//And set the first pixel of the other column
		}

		else	pixel /= TWICE;					//Otherwise pixel will receive the next top pixel

		snake[BEGIN].image = pixel;				//So we are only redrawing the head of the snake so the body can replaced it later
		/**The head already has the position in AXIS Y*/
	}

	else if(DOWN == snake[BEGIN].modifyPositionY)		//This means they need to change snake position going down 1 but only one pixel
	{
		if(LOWEST==pixel)						//Only if the pixel has the final pixel value
		{
			snake[BEGIN].snakePositionY += snake[BEGIN].modifyPositionY;	//We are going to decrement the position of the snake
			pixel = HIGHEST;													//And set the last pixel of the other column
		}

		else	pixel *= TWICE;					//Otherwise pixel will receive the next bottom pixel

		snake[BEGIN].image = pixel;				//So we are only redrawing the head of the snake so the body can replaced it later
		/**The head already has the position in AXIS Y*/
	}

}
