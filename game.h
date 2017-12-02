/*
 * game.h
 *
 *  Created on: 30 Nov 2017
 *      Author: lrolo
 */

#ifndef GAME_H_
#define GAME_H_

#include "DataTypeDefinitions.h"

typedef enum{MAINSCREEN, MAINMENU, GAME, CONTROLS, SCORES}StatesSnakeGame;

typedef struct
{
	void(*fptrPort)(void);
	uint8 next[5];

}SnakeStateType;


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function writes on EEPROM by I2C

 	 \param[in]  channel , slaveAddress, high address, low address, data
 	 \return void
 */
void initGame(void);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function writes on EEPROM by I2C

 	 \param[in]  channel , slaveAddress, high address, low address, data
 	 \return void
 */
void mainScreen(void);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function writes on EEPROM by I2C

 	 \param[in]  channel , slaveAddress, high address, low address, data
 	 \return void
 */
void mainMenu(void);

#endif /* GAME_H_ */
