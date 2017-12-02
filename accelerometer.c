/*
 * accelerometer.c
 *
 *  Created on: 27 Nov 2017
 *      Author: lrolo
 */

#include "DataTypeDefinitions.h"
#include "accelerometer.h"
#include "IIC.h"
#include "devicesIIC.h"
#include "snake.h"

static uint16 Acc_X = FALSE, Acc_Y = FALSE;		//Variables that stores position in axis X and Y
static uint8 direction = RESETMOTION;			//Variable for the motion


void configIIC_Acc(void)
{

	/**IIC_init(I2C_0, busClock, BR_100, mul_4);*///This is commented because we have already initialised I2C module
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;				//Clock Gating for PORTE
	PORTE->PCR[24] =  PORT_PCR_MUX(5);				//PORTB USED AS I2C SCL
	PORTE->PCR[25] =  PORT_PCR_MUX(5);				//PORTB USED AS I2C SDA

}

void wr_Acc(void)
{

	wrIIC_Device(I2C_0, ACCEL_WR_SL_A, 0x2A, 0x37);	//This as a matter of fact selects
													//the 2A register of FXOS8700CQ and write a 0x37
													//which turns the bits for the active mode fast read
													//reduced noise and a period of 160ms for system output data rate

}

void xyz_Acc(void)
{

	/*
	 * Those lines allow us to read the low and high registers of accelerometer in X and Y
	 * linking one with the other to make a single variable o X or Y position
	 */
	Acc_X = (rdIIC_Device(I2C_0, ACCEL_WR_SL_A, ACCEL_RD_SL_A, OUT_X_MSB_REG, MSB_XYZ_MASK)<<6);
	Acc_X |= (rdIIC_Device(I2C_0, ACCEL_WR_SL_A, ACCEL_RD_SL_A, OUT_X_LSB_REG, LSB_XYZ_MASK)>>2);
	Acc_Y = (rdIIC_Device(I2C_0, ACCEL_WR_SL_A, ACCEL_RD_SL_A, OUT_Y_MSB_REG, MSB_XYZ_MASK)<<6);
	Acc_Y |= (rdIIC_Device(I2C_0, ACCEL_WR_SL_A, ACCEL_RD_SL_A, OUT_Y_LSB_REG, LSB_XYZ_MASK)>>2);

	/*
	 * This is our manual calibration based on uncertain measures which
	 * permits a good performances on this project
	 */

	if(Acc_X >13000 && Acc_X < 16400 && (Acc_Y > 15600 || Acc_Y < 400))
		direction = GUP;

	else if(Acc_X > 700 && Acc_X < 10000 && (Acc_Y > 15000 || Acc_Y < 400))
		direction = GDOWN;

	else if(Acc_X < 1000 && Acc_Y > 12000 && Acc_Y < 15900)
		direction = GLEFT;

	else if(Acc_X > 100 && Acc_Y > 300 && Acc_Y < 3000)
		direction = GRIGHT;


}

/*
 * Function that returns the direction of K64 to implement the accelerometer game
 */
uint8 getDirection(void)
{
	return direction;
}

/*
 * This is only to reset the motion and stop the snake
 */
void setDirection(void)
{
	direction = RESETMOTION;
}


