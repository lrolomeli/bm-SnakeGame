/*
 * Copyright (c) 2016, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    snakeGame.c
 * @brief   Application entry point.
 */

#include "MK64F12.h"
#include "snake.h"
#include "SPI.h"
#include "LCDNokia5110.h"

/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const SPI_ConfigType SPI_Config={SPI_DISABLE_FIFO,
								 SPI_LOW_POLARITY,
								 SPI_LOW_PHASE,
								 SPI_MSB,
								 SPI_0,
								 SPI_MASTER,
								 GPIO_MUX2,
								 SPI_BAUD_RATE_2,
								 SPI_FSIZE_8,
								{GPIO_D,BIT1,BIT2}
								};


int main()
{
	SPI_init(&SPI_Config); /*! Configuration function for the LCD port*/
	LCDNokia_init(); /*! Configuration function for the LCD */
	LCDNokia_clear();
	initSnakeParameters();

	while(TRUE){
		//drawField();
	}

	return 0;
}
