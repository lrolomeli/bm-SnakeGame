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

static int16_t Acc_X = FALSE, Acc_Y = FALSE;
static uint8 motion = RESETMOTION;



void configIIC_Acc(void)
{

	IIC_init(I2C_0, busClock, BR_100, mul_4);
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;			//Clock Gating for PORTE
	PORTE->PCR[24] =  PORT_PCR_MUX(5);			//PORTB USED AS I2C SCL
	PORTE->PCR[25] =  PORT_PCR_MUX(5);			//PORTB USED AS I2C SDA

}

void wr_Acc(void)
{

	wrIIC_Device(I2C_0, ACCEL_WR_SL_A, 0x2A, 0x37);

}

void xyz_Acc(void)
{

	Acc_X = (rdIIC_Device(I2C_0, ACCEL_WR_SL_A, ACCEL_RD_SL_A, OUT_X_MSB_REG, MSB_XYZ_MASK)<<6);
	Acc_X |= (rdIIC_Device(I2C_0, ACCEL_WR_SL_A, ACCEL_RD_SL_A, OUT_X_LSB_REG, LSB_XYZ_MASK)>>2);
	Acc_Y = (rdIIC_Device(I2C_0, ACCEL_WR_SL_A, ACCEL_RD_SL_A, OUT_Y_MSB_REG, MSB_XYZ_MASK)<<6);
	Acc_Y |= (rdIIC_Device(I2C_0, ACCEL_WR_SL_A, ACCEL_RD_SL_A, OUT_Y_LSB_REG, LSB_XYZ_MASK)>>2);

	if(Acc_X >13000 && Acc_X < 16400 && (Acc_Y > 15600 || Acc_Y < 400))
		motion = GUP;

	else if(Acc_X > 700 && Acc_X < 10000 && (Acc_Y > 15000 || Acc_Y < 400))
		motion = GDOWN;

	else if(Acc_X < 1000 && Acc_Y > 12000 && Acc_Y < 15900)
		motion = GLEFT;

	else if(Acc_X > 100 && Acc_Y > 300 && Acc_Y < 3000)
		motion = GRIGHT;


}

uint8 getMotionAcc(void)
{
	return motion;
}

void setMotionAcc(void)
{
	motion = RESETMOTION;
}


