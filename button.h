/*
 * button.h
 *
 *  Created on: 19 Oct 2017
 *      Author: lrolo
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "NVIC.h"
#include "GPIO.h"
#include "DataTypeDefinitions.h"

/*! Constant to manage INT on falling edge and MUX with GPIO function*/
#define pinControlRegisterPORTBSW GPIO_MUX1 | INTR_FALLING_EDGE

typedef struct{

	GPIO_portNameType GPIO_portName;
	uint8 button0;
	uint8 button1;
	uint8 button2;
	uint8 button3;
	uint8 button4;

}GPIOForButtonType;

/*Type that is used for buttons configuration, It contains all the information needed for a button module*/
typedef struct
{
	GPIO_PIN_CONFIG GPIO_DataDirectionPin;
	GPIO_pinControlRegisterType pinControlRegisterPORTB;
	GPIOForButtonType GPIOForButton;
	InterruptType PIT_ISR;
	InterruptType GPIO_ISR;
	PriorityLevelType PIT_Priority;
	PriorityLevelType GPIO_Priority;
	PriorityLevelType GlobalPriority;

}button_ConfigType;


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function calls button init to configure all buttons needed on PORTB GPIO.

 	 \param[in]  void.
 	 \return void
 */
void buttonsReady(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function clears all interrupts that were sensed by the GPIO.

 	 \param[in]  button_ConfigType structure type which contains all constants to initialise all buttons
 	 \return void
 */
void button_init(const button_ConfigType* button_Config);

#endif /* BUTTON_H_ */



