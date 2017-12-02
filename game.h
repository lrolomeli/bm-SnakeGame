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

void initGame(void);

void mainScreen(void);

void mainMenu(void);

#endif /* GAME_H_ */
