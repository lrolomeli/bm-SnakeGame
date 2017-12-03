/*
 * menu.c
 *
 *  Created on: 27 Nov 2017
 *      Author: lrolo
 */

#include "DataTypeDefinitions.h"
#include "LCDNokia5110.h"
#include "menu.h"
#include "GPIO.h"
#include "snake.h"
#include "devicesIIC.h"
#include "GlobalFunctions.h"

uint8 local=0;
uint8 a, b, c, d, e;
uint8 scores[5] = {0};

void screenMenu(void)
{

	if(1!=local)
	{
		uint8 string1[]="!) PLAY"; /*! String to be printed in the LCD*/
		uint8 string2[]="^) CONTROLS"; /*! String to be printed in the LCD*/
		uint8 string3[]="<) SCORES"; /*! String to be printed in the LCD*/

		LCDNokia_clear();/*! It clears the information printed in the LCD*/
		LCDNokia_gotoXY(0,0); /*! It establishes the position to print the messages in the LCD*/
		LCDNokia_sendString(string1); /*! It print a string stored in an array*/
		LCDNokia_gotoXY(0,1);
		LCDNokia_sendString(string2); /*! It print a string stored in an array*/
		LCDNokia_gotoXY(0,2);
		LCDNokia_sendString(string3); /*! It print a string stored in an array*/
		local=1;
	}


}
/**
 * This function stores 5 elements in 5 different directions in EEPROM
 */
void storeScores(void)
{

	wrByte(I2C_0, WREEPROM, 0x0F, 0xF0, scores[4]);
	delay(800);
	wrByte(I2C_0, WREEPROM, 0x0F, 0xF1, scores[3]);
	delay(800);
	wrByte(I2C_0, WREEPROM, 0x0F, 0xF2, scores[2]);
	delay(800);
	wrByte(I2C_0, WREEPROM, 0x0F, 0xF3, scores[1]);
	delay(800);
	wrByte(I2C_0, WREEPROM, 0x0F, 0xF4, scores[0]);
	delay(800);
}

/**
 * This function reads 5 elements in 5 directions in EEPROM
 */
void loadScores(void)
{
	scores[4] = rdByte(I2C_0, WREEPROM, RDEEPROM, 0x0F, 0xF0);
	scores[3] = rdByte(I2C_0, WREEPROM, RDEEPROM, 0x0F, 0xF1);
	scores[2] = rdByte(I2C_0, WREEPROM, RDEEPROM, 0x0F, 0xF2);
	scores[1] = rdByte(I2C_0, WREEPROM, RDEEPROM, 0x0F, 0xF3);
	scores[0] = rdByte(I2C_0, WREEPROM, RDEEPROM, 0x0F, 0xF4);
}

/**
 * This function applies a sort method called bubble sort
 *  which classify and sort the numbers from highest to lowest
 *  but first check if the current score is actually higher than previous scores
 */
void setRecord(uint8 score)
{
	uint8 sort2, sort1, aux_score;

	if(score > scores[4])
		scores[4] = score;

	for(sort1=0;sort1<5;sort1++)
	{

		for(sort2=0;sort2<5;sort2++)
		{

			if(scores[sort2]<scores[sort2+DSTART])
			{
				aux_score = scores[sort2+DSTART];
				scores[sort2+DSTART] = scores[sort2];
				scores[sort2] = aux_score;
			}


		}
	}
	storeScores();
}


void scoreScreen(void)
{

	if(2!=local)
	{

		uint8 string1[]="1)"; /*! String to be printed in the LCD*/
		uint8 string2[]="2)"; /*! String to be printed in the LCD*/
		uint8 string3[]="3)"; /*! String to be printed in the LCD*/
		uint8 string4[]="4)"; /*! String to be printed in the LCD*/
		uint8 string5[]="5)"; /*! String to be printed in the LCD*/

		LCDNokia_clear();/*! It clears the information printed in the LCD*/
		LCDNokia_gotoXY(0,0); /*! It establishes the position to print the messages in the LCD*/
		LCDNokia_sendString(string1); /*! It print a string stored in an array*/
		LCDNokia_gotoXY(15,0); /*! It establishes the position to print the messages in the LCD*/
		digiToAscii(scores[0]);
		LCDNokia_sendChar(e);
		LCDNokia_sendChar(d);
		LCDNokia_sendChar(c);
		LCDNokia_sendChar(b);
		LCDNokia_sendChar(a);

		LCDNokia_gotoXY(0,1);
		LCDNokia_sendString(string2); /*! It print a string stored in an array*/
		LCDNokia_gotoXY(15,1); /*! It establishes the position to print the messages in the LCD*/
		digiToAscii(scores[1]);
		LCDNokia_sendChar(e);
		LCDNokia_sendChar(d);
		LCDNokia_sendChar(c);
		LCDNokia_sendChar(b);
		LCDNokia_sendChar(a);

		LCDNokia_gotoXY(0,2);
		LCDNokia_sendString(string3); /*! It print a string stored in an array*/
		LCDNokia_gotoXY(15,2); /*! It establishes the position to print the messages in the LCD*/
		digiToAscii(scores[2]);
		LCDNokia_sendChar(e);
		LCDNokia_sendChar(d);
		LCDNokia_sendChar(c);
		LCDNokia_sendChar(b);
		LCDNokia_sendChar(a);

		LCDNokia_gotoXY(0,3);
		LCDNokia_sendString(string4); /*! It print a string stored in an array*/
		LCDNokia_gotoXY(15,3); /*! It establishes the position to print the messages in the LCD*/
		digiToAscii(scores[3]);
		LCDNokia_sendChar(e);
		LCDNokia_sendChar(d);
		LCDNokia_sendChar(c);
		LCDNokia_sendChar(b);
		LCDNokia_sendChar(a);

		LCDNokia_gotoXY(0,4);
		LCDNokia_sendString(string5); /*! It print a string stored in an array*/
		LCDNokia_gotoXY(15,4); /*! It establishes the position to print the messages in the LCD*/
		digiToAscii(scores[4]);
		LCDNokia_sendChar(e);
		LCDNokia_sendChar(d);
		LCDNokia_sendChar(c);
		LCDNokia_sendChar(b);
		LCDNokia_sendChar(a);


		local = 2;
	}

}


void ctrlScreen(void)
{
	if(3!=local)
	{
		uint8 string1[]="!) MANUAL"; /*! String to be printed in the LCD*/
		uint8 string2[]="^) ACCEL"; /*! String to be printed in the LCD*/
		uint8 string3[]="B) Main Menu"; /*! String to be printed in the LCD*/

		LCDNokia_clear();/*! It clears the information printed in the LCD*/
		LCDNokia_gotoXY(0,0); /*! It establishes the position to print the messages in the LCD*/
		LCDNokia_sendString(string1); /*! It print a string stored in an array*/
		LCDNokia_gotoXY(0,1);
		LCDNokia_sendString(string2); /*! It print a string stored in an array*/
		LCDNokia_gotoXY(0,2);
		LCDNokia_sendString(string3); /*! It print a string stored in an array*/

		local = 3;
	}

	while(3==getButton());
	if(1==getButton())
		setManual();
	if(2==getButton())
		setAccel();
}

/**It help the lcd nokia to stop refreshing the lcd and prevent erasing images*/
void setlocal(void)
{
	local = 0;

}
/**This only converts a number to a character so then we can send it from an LCD function*/
void digiToAscii(uint8 var)
{

	if (var >= 100 && var <= 999)
	{
		e = ' ';
		d = ' ';
		c = (var / 100)+'0';
		b = ((var % 100) / 10)+'0';
		a = ((var % 100) % 10)+'0';
	}

	if (var >= 10 && var <= 99)
	{
		e = ' ';
		d = ' ';
		c = ' ';
		b = (var / 10)+'0';
		a = ((var % 10))+'0';
	}

	if(var >= 0 && var <= 9)
	{
		e = ' ';
		d = ' ';
		c = ' ';
		b = ' ';
		a = var + '0';
	}
}
