/*
 * menu.c
 *
 *  Created on: 27 Nov 2017
 *      Author: lrolo
 */

#include "DataTypeDefinitions.h"
#include "LCDNokia5110.h"
#include "menu.h"

void screenMenu(void)
{

	uint8 string1[]="1) SNAKE GAME"; /*! String to be printed in the LCD*/
	uint8 string2[]="2) SCORES"; /*! String to be printed in the LCD*/
	uint8 string3[]="3) MANUAL"; /*! String to be printed in the LCD*/
	uint8 string4[]="4) ACCEL"; /*! String to be printed in the LCD*/

	LCDNokia_clear();/*! It clears the information printed in the LCD*/
	LCDNokia_gotoXY(0,0); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
    LCDNokia_gotoXY(0,1);
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
    LCDNokia_gotoXY(0,2);
	LCDNokia_sendString(string3); /*! It print a string stored in an array*/
    LCDNokia_gotoXY(0,3);
	LCDNokia_sendString(string4); /*! It print a string stored in an array*/

}
