/*
 * button.c
 *
 *  Created on: 19 Oct 2017
 *      Author: lrolo
 */

#include "MK64F12.h"
#include "GPIO.h"
#include "button.h"
#include "NVIC.h"
#include "PIT.h"

const button_ConfigType button_Config = {GPIO_INPUT,
										pinControlRegisterPORTBSW,
										{GPIO_B,BIT18,BIT19,BIT20,BIT11},
										PIT_CH0_IRQ,
										PORTB_IRQ,
										PRIORITY_7,
										PRIORITY_8,
										PRIORITY_12
										};



void buttonsReady(void)
{
	button_init(&button_Config); /*! Configuration function  */
}


void button_init(const button_ConfigType* button_Config)
/**This function contains all the initialisation of the button organised as an structure*/
{
	GPIO_clockGating(button_Config->GPIOForButton.GPIO_portName);
	PIT_clockGating();
	GPIO_pinControlRegister(button_Config->GPIOForButton.GPIO_portName, button_Config->GPIOForButton.button0, & (button_Config->pinControlRegisterPORTB));
	GPIO_pinControlRegister(button_Config->GPIOForButton.GPIO_portName, button_Config->GPIOForButton.button1, & (button_Config->pinControlRegisterPORTB));
	GPIO_pinControlRegister(button_Config->GPIOForButton.GPIO_portName, button_Config->GPIOForButton.button2, & (button_Config->pinControlRegisterPORTB));
	GPIO_pinControlRegister(button_Config->GPIOForButton.GPIO_portName, button_Config->GPIOForButton.button3, & (button_Config->pinControlRegisterPORTB));
	GPIO_clearIRQStatus(button_Config->GPIOForButton.GPIO_portName);
	GPIO_dataDirectionPIN(button_Config->GPIOForButton.GPIO_portName,button_Config->GPIO_DataDirectionPin,button_Config->GPIOForButton.button0);
	GPIO_dataDirectionPIN(button_Config->GPIOForButton.GPIO_portName,button_Config->GPIO_DataDirectionPin,button_Config->GPIOForButton.button1);
	GPIO_dataDirectionPIN(button_Config->GPIOForButton.GPIO_portName,button_Config->GPIO_DataDirectionPin,button_Config->GPIOForButton.button2);
	GPIO_dataDirectionPIN(button_Config->GPIOForButton.GPIO_portName,button_Config->GPIO_DataDirectionPin,button_Config->GPIOForButton.button3);
	NVIC_setBASEPRI_threshold(button_Config->GlobalPriority);
	NVIC_enableInterruptAndPriority(button_Config->GPIO_ISR, button_Config->GPIO_Priority);
	NVIC_enableInterruptAndPriority(button_Config->PIT_ISR, button_Config->PIT_Priority);
	EnableInterrupts;
}




