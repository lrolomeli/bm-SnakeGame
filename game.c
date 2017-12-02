/*
 * game.c
 *
 *  Created on: 30 Nov 2017
 *      Author: lrolo
 */

#include "MK64F12.h"

#include "GPIO.h"
#include "SPI.h"
#include "IIC.h"

#include "LCDNokia5110.h"
#include "LCDNokia5110Images.h"
#include "button.h"
#include "accelerometer.h"
#include "menu.h"
#include "game.h"
#include "snake.h"

static const SnakeStateType FSM_Moore[5] =
		{
				{ &mainScreen,	{ MAINSCREEN, 	MAINSCREEN,	MAINSCREEN, MAINSCREEN,	MAINMENU }	}, 	/**MAINSCREEN*/
				{ &screenMenu,	{ MAINMENU, 	GAME, 		CONTROLS, 	SCORES, 	MAINMENU }	}, 	/**MAINMENU*/
				{ &gameLoop,	{ MAINMENU, 	GAME, 		GAME, 		GAME, 		GAME 	 }	}, 	/**GAME*/
				{ &ctrlScreen,	{ MAINMENU, 	CONTROLS, 	CONTROLS, 	CONTROLS, 	CONTROLS }	}, 	/**CONTROLS*/
				{ &scoreScreen,	{ MAINMENU, 	SCORES, 	SCORES, 	SCORES, 	SCORES 	 }	} 	/**SCORES*/
		};

static uint8 currentState = MAINSCREEN;

void initGame(void)
{

	buttonsReady(); 	/*! Configuration for input buttons needed*/
	initSPI();		 	/*! Configuration function for the LCD port*/

	IIC_init(I2C_0, busClock, BR_100, mul_4); /*! Configuration for I2C Communication*/

	loadScores();			/*! Reading scores from EEPROM **************/
	configIIC_Acc();		/*! Preparing the ambient for accelerometer */
	wr_Acc();				/*! Configuring the accelerometer on I2C ****/

	LCDNokia_init(); 		/*! Configuration LCD ***********************/
	LCDNokia_clear();		/*! Cleaning LCD display ********************/
	initSnakeParameters();	/*! Configuration function for the LCD ******/

}

void mainScreen(void)
{

	LCDNokia_bitmap(getImage());	/**Snake presentation image Introduction*/

}

void mainMenu(void)
{
	//Will receive which button is pressed to change the current state
	currentState = FSM_Moore[currentState].next[getButton()];

	//So then the menu change according to the FSM_Moore structure
	FSM_Moore[currentState].fptrPort();

	//this going to be happen only on this menu
	//after a function completes the control come back to this function
}
