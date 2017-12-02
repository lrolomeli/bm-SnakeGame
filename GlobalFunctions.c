/*
 * GlobalFunctions.c
 *
 *  Created on: 16/08/2017
 *      Author: jlpe
 */


#include "GlobalFunctions.h"
/**
 * DELAY USED ONLY TO WAIT A COMPLETE OPERATION OF
 * WRITING ON EEPROM NON VOLATILE MEMORY
 */
void delay(uint16 delay)
{
	volatile int counter, counter2;

	for(counter2=16; counter2 > 0; counter2--)
	{
		for(counter=delay; counter > 0; counter--);

	}
}
