/*
 * snake.h
 *
 *  Created on: 3 Nov 2017
 *      Author: lrolo
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include "DataTypeDefinitions.h"

#define SNAKE_MAX_LENGTH 100	/*!< Maximum length of the snake*/
#define VERTICALFIELD 6			/*!< 6 Y positions*/
#define HORIZONTALFIELD 84		/*!< 84 X positions*/
#define STARTPOSITION_Y 3		/*!< snake X start position*/
#define STARTPOSITION_X 42		/*!< snake Y start position*/
#define STARTINGSIZE 8			/*!< starting size of the snake*/
#define FIELDSIZE 504			/*!< array constant of the field*/
#define TWICE 2					/*!< Duplicate*/

/**
 *	NMOVE DECREMENT POSITION
 *	MOVE INCREMENT POSITION
 *	STOP STUCKS POSITION
 */
typedef enum{NMOVE = -1, STOP, MOVE}Motion;
/**
 *	MOVES RIGHT & LEFT
 */
typedef enum{RIGHT = 1, LEFT}MotionX;
/**
 *	MOVES UP AND DOWN
 */
typedef enum{DOWN = 1, UP}MotionY;
/**
 *	PIXELS HAVE MASKS SO THESE ARE THE BOTTOM AND TOP PIXELS
 */
typedef enum{HIGHEST = 1, LOWEST = 128}Pixels;
/**
 *	START POSITIONS OF ALL (FOR) LOOPS
 */
typedef enum{BEGIN, DSTART}Conditionals;
/**
 *	SNAKE KNOW IF IS ALIVE
 */
typedef enum{DEAD, ALIVE}GameOver;
/**
 *	CONSTANTS FOR EACH BUTTON PRESSED
 */
typedef enum{GBACK, GDOWN, GUP, GLEFT, GRIGHT}Moving;

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
	uint8 image;

}fruitPosition;



/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function begins the things needed for snake game as
 	 \		 position of snake and fruit and the initial motion

 	 \param[in]  void
 	 \return void
 */

void initSnakeParameters(void);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function start the snake with its size and position going to the left

 	 \param[in]  void
 	 \return void
 */
void initMotionSnake(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function makes the field to play and the limits of that field

 	 \param[in]  void
 	 \return void
 */
void createField(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function stores each picture of the field and snake and fruit in an array

 	 \param[in]  void
 	 \return void
 */
void introduceDataToField(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function sends the array created to a bitmap recognised by LCDNokia

 	 \param[in]  void
 	 \return void
 */
void drawField(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function begin the game asking first if the snake is alive and it prints
 	 \		 all the values of the snake after a count of 0.3 ms

 	 \param[in]  void
 	 \return void
 */
void gameLoop(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function detects each input of the buttons or accelerometer and checks
 	 \		 the border limits comparing with the snake, also compares if the fruit has been eaten

 	 \param[in]  void
 	 \return void
 */
void input(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function updates all the values and parameters for the next move of the snake

 	 \param[in]  void
 	 \return void
 */
void update(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is basically for the movement in Y axis pixel by pixel

 	 \param[in]  void
 	 \return void
 */
void moveSnakeAxisY(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function do the same as IntroduceDataToField but with new parameters

 	 \param[in]  void
 	 \return void
 */
void introduceNewDataToField(void);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function clears the value in accelerometer to re-initialise the movement

 	 \param[in]  void
 	 \return void
 */
void setAccel(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function clears the value in buttons to re-initialise the movement

 	 \param[in]  void
 	 \return void
 */
void setManual(void);


#endif /* SNAKE_H_ */

