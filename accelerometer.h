/*
 * accelerometer.h
 *
 *  Created on: 27 Nov 2017
 *      Author: lrolo
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#define RESETMOTION 4

// ACCELEROMETER I2C (default) slave address
#define ACCEL_WR_SL_A 0x3A // with pins SA0=1, SA1=0
#define ACCEL_RD_SL_A 0x3B // with pins SA0=1, SA1=0

// FXOS8700CQ Registers

#define STATUS_REG 0x00  // STATUS Register

#define OUT_X_MSB_REG 0x01  // [7:0] are 8 MSBs of 14-bit acceleration data for X-axis
#define OUT_X_LSB_REG 0x02  // [7:2] are the 6 LSB of 14-bit acceleration data for X-axis
#define OUT_Y_MSB_REG 0x03  // [7:0] are 8 MSBs of 14-bit acceleration data for Y-axis
#define OUT_Y_LSB_REG 0x04  // [7:2] are the 6 LSB of 14-bit acceleration data for Y-axis
#define OUT_Z_MSB_REG 0x05  // [7:0] are 8 MSBs of 14-bit acceleration data for Z-axis
#define OUT_Z_LSB_REG 0x06  // [7:2] are the 6 LSB of 14-bit acceleration data for Z-axis

#define LSB_XYZ_MASK 0xFC
#define MSB_XYZ_MASK 0xFF

void configIIC_Acc(void);

void wr_Acc(void);

void xyz_Acc(void);

void setMotionAcc(void);

uint8 getMotionAcc(void);

#endif /* ACCELEROMETER_H_ */
