/*
 * menu.h
 *
 *  Created on: 27 Nov 2017
 *      Author: lrolo
 */

#ifndef MENU_H_
#define MENU_H_

void setRecord(uint8 score);
void screenMenu(void);
void scoreScreen(void);
void ctrlScreen(void);
void setlocal(void);
void digiToAscii(uint8 var);
void loadScores(void);
void storeScores(void);

#endif /* MENU_H_ */
