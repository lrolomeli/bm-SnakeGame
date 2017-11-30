/*
 * GPIO.c
 *
 *  Created on: 19 Oct 2017
 *      Author: lrolo
 */

#include "MK64F12.h"
#include "GPIO.h"
#include "snake.h"

GPIO_interruptFlags_t GPIO_intrStatusFlag = {0};

uint8 motion = NOBUTTONPRESSED;


void setMotion(void)
{

	motion = NOBUTTONPRESSED;

}


uint8 getMotion(void)
{

	return motion;

}

void PORTB_IRQHandler()
{
	GPIO_clearInterrupt(GPIO_B);
	if(!GPIO_readPIN(GPIO_B, BIT18))
		motion = GDOWN;
	else if(!GPIO_readPIN(GPIO_B, BIT19))
		motion = GUP;
	else if(!GPIO_readPIN(GPIO_B, BIT20))
		motion = GLEFT;
	else if(!GPIO_readPIN(GPIO_B, BIT11))
		motion = GRIGHT;

}

uint8 GPIO_getIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			return(GPIO_intrStatusFlag.flagPortA);
			break;
		case GPIO_B:
			return(GPIO_intrStatusFlag.flagPortB);
			break;
		case GPIO_C:
			return(GPIO_intrStatusFlag.flagPortC);
			break;
		case GPIO_D:
			return(GPIO_intrStatusFlag.flagPortD);
			break;
		case GPIO_E:
			return(GPIO_intrStatusFlag.flagPortE);
			break;
		default:
			return(ERROR);
			break;
	}

}

uint8 GPIO_clearIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			GPIO_intrStatusFlag.flagPortA = FALSE;
			break;
		case GPIO_B:
			GPIO_intrStatusFlag.flagPortB = FALSE;
			break;
		case GPIO_C:
			GPIO_intrStatusFlag.flagPortC = FALSE;
			break;
		case GPIO_D:
			GPIO_intrStatusFlag.flagPortD = FALSE;
			break;
		case GPIO_E:
			GPIO_intrStatusFlag.flagPortE = FALSE;
			break;
		default:
			return(ERROR);
			break;
	}

	return(TRUE);

}

void GPIO_clearInterrupt(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			PORTA->ISFR=0xFFFFFFFF;
			break;
		case GPIO_B: /** GPIO B is selected*/
			PORTB->ISFR=0xFFFFFFFF;
			break;
		case GPIO_C: /** GPIO C is selected*/
			PORTC->ISFR = 0xFFFFFFFF;
			break;
		case GPIO_D: /** GPIO D is selected*/
			PORTD->ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE->ISFR=0xFFFFFFFF;
			break;

	}// end switch
}

uint8 GPIO_clockGating(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIO_B: /** GPIO B is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIO_C: /** GPIO C is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIO_D: /** GPIO D is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
					break;
				default: /**If doesn't exist the option*/
					return(FALSE);
			}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8 GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister)
{

	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin] = *pinControlRegister;	/**Arguments to configure the port*/
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin] = *pinControlRegister;	/**Arguments to configure the port*/
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin] = *pinControlRegister;	/**Arguments to configure the port*/
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin] = *pinControlRegister;	/**Arguments to configure the port*/
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin]= *pinControlRegister;	/**Arguments to configure the port*/
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);
}

void GPIO_writePORT(GPIO_portNameType portName, uint32 Data){

	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDOR = Data;	/**Constant to configure register PDOR*/
			break;

		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDOR = Data;	/**Constant to configure register PDOR*/
			break;

		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDOR = Data;	/**Constant to configure register PDOR*/
			break;

		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDOR = Data;	/**Constant to configure register PDOR*/
			break;

		default :/** GPIO E is selected*/
			GPIOE->PDOR = Data;	/**Constant to configure register PDOR*/
			break;
	}

}

uint32 GPIO_readPORT(GPIO_portNameType portName){
	//PDIR
	switch(portName){

	case GPIO_A :/** GPIO A is selected*/
		return GPIOA->PDIR;
	break;
	case GPIO_B :/** GPIO B is selected*/
		return GPIOB->PDIR;
	break;
	case GPIO_C :/** GPIO C is selected*/
		return GPIOC->PDIR;
	break;
	case GPIO_D :/** GPIO D is selected*/
		return GPIOD->PDIR;
	break;
	default:/** GPIO E is selected*/
		return GPIOE->PDIR;
	break;
	}
}

uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin){
	//PTOR

	uint32_t GPIO_readPIN_MASK = ((uint32_t)((uint32_t)(TRUE)) << pin);
	uint8 result;

	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			result = GPIOA->PDIR & GPIO_readPIN_MASK ? TRUE : FALSE;
			break;

		case GPIO_B:/** GPIO B is selected*/
			result = GPIOB->PDIR & GPIO_readPIN_MASK ? TRUE : FALSE;
			break;

		case GPIO_C:/** GPIO C is selected*/
			result = GPIOC->PDIR & GPIO_readPIN_MASK ? TRUE : FALSE;
			break;

		case GPIO_D:/** GPIO D is selected*/
			result = GPIOD->PDIR & GPIO_readPIN_MASK ? TRUE : FALSE;
			break;

		default :/** GPIO E is selected*/
			result = GPIOE->PDIR & GPIO_readPIN_MASK ? TRUE : FALSE;
			break;
	}
	return result;

}

void GPIO_setPIN(GPIO_portNameType portName, uint8 pin){

	uint32_t GPIO_setPIN_SHIFT = ((uint32_t)((uint32_t)(TRUE)) << pin);

	switch(portName){
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PSOR = GPIO_setPIN_SHIFT;
				break;

			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PSOR = GPIO_setPIN_SHIFT;
				break;

			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PSOR = GPIO_setPIN_SHIFT;
				break;

			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PSOR = GPIO_setPIN_SHIFT;
				break;

			default :/** GPIO E is selected*/
				GPIOE->PSOR = GPIO_setPIN_SHIFT;
				break;
		}
	//PSOR
}

void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin){

	uint32_t GPIO_clearPIN_SHIFT = ((uint32_t)((uint32_t)(1)) << pin);

	switch(portName){
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PCOR = GPIO_clearPIN_SHIFT;
				break;

			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PCOR = GPIO_clearPIN_SHIFT;
				break;

			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PCOR = GPIO_clearPIN_SHIFT;
				break;

			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PCOR = GPIO_clearPIN_SHIFT;
				break;

			default :/** GPIO E is selected*/
				GPIOE->PCOR = GPIO_clearPIN_SHIFT;
				break;
		}
}

void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin){

	uint32_t GPIO_tooglePIN_SHIFT = ((uint32_t)((uint32_t)(1)) << pin);

	switch(portName){
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PTOR = GPIO_tooglePIN_SHIFT;
				break;

			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PTOR = GPIO_tooglePIN_SHIFT;
				break;

			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PTOR = GPIO_tooglePIN_SHIFT;
				break;

			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PTOR = GPIO_tooglePIN_SHIFT;
				break;

			default :/** GPIO E is selected*/
				GPIOE->PTOR = GPIO_tooglePIN_SHIFT;
				break;
		}
}

void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction){
	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDDR |= direction;
			break;

		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDDR |= direction;
			break;

		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDDR |= direction;
			break;

		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDDR |= direction;
			break;

		default :/** GPIO E is selected*/
			GPIOE->PDDR |= direction;
			break;
	}

	//PDDR
}

void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin){

	uint32_t GPIO_dataDirectionPIN_x = (((uint32_t)(((uint32_t)(State)) << pin)) & ((uint32_t)((uint32_t)(1)) << pin));

	switch(portName)
	{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDDR |= GPIO_dataDirectionPIN_x;
			break;

		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDDR |= GPIO_dataDirectionPIN_x;
			break;

		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDDR |= GPIO_dataDirectionPIN_x;
			break;

		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDDR |= GPIO_dataDirectionPIN_x;
			break;

		default :/** GPIO E is selected*/
			GPIOE->PDDR |= GPIO_dataDirectionPIN_x;
			break;
	}

}
