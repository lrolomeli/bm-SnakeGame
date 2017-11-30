/*
 * devicesIIC.h
 *
 *  Created on: 12 Nov 2017
 *      Author: lrolo
 */

#ifndef DEVICESIIC_H_
#define DEVICESIIC_H_

#include "IIC.h"

typedef enum {RTC_SC1, RTC_SC2, RTC_SEC, RTC_MIN, RTC_HOURS, RTC_DAY, RTC_WEEKDAY, RTC_MONTH, RTC_YEAR} RTC_Register_Types;

//CONSTANTS FOR EEPROM
#define WREEPROM 0xA0
#define RDEEPROM 0xA1
#define DATA 0x36

//CONSTANTS FOR THE RTC
#define WRRTC 0xA2
#define RDRTC 0xA3

//MASKS FOR RTC REGISTERS
#define RTC_SEC_MASK		0x7F		//initial values to write the date to the RTC STOP MODE
#define RTC_MIN_MASK		0x7F		//initial values to write the date to the RTC START MODE
#define RTC_HOURS_MASK		0x3F		//register for status & control 2
#define RTC_DAY_MASK		0x3F		//register for seconds
#define RTC_WEEKDAY_MASK	0x07		//register for minutes
#define RTC_MONTH_MASK		0x1F		//register for hours and format PM or AM
#define RTC_YEAR_MASK		0xFF		//register for days 0 - 31

//START CONDITIONS FOR REGISTER 00H TO 0FH
#define RTC_CTRLSTOP  		0x08		//initial values to write the date to the RTC STOP MODE
#define RTC_CTRLSTART		0x00		//initial values to write the date to the RTC START MODE
#define RTC_REGISTER1 		0x00		//register for status & control 2
#define RTC_REGISTER2 		0x00		//register for seconds
#define RTC_REGISTER3		0x00		//register for minutes
#define RTC_REGISTER4 		0x12		//register for hours and format PM or AM
#define RTC_REGISTER5 		0x01		//register for days 0 - 31
#define RTC_REGISTER6 		0x00		//register for weekdays
#define RTC_REGISTER7 		0x00		//register for months
#define RTC_REGISTER8 		0x11		//register for years
#define RTC_TIMERCTRL 		0X82		//register for enabling the timer for 1 Hz
#define RTC_TIMERCNT  		0X3C		//register for timer counting to 60

void wrByte(I2C_ChannelType channel, uint8 slaveAddress, uint8 hAddress, uint8 lAddress, uint8 data);

uint8 rdByte(I2C_ChannelType channel, uint8 writeAddr, uint8 readAddr, uint8 hAddress, uint8 lAddress);

void wrIIC_Device(I2C_ChannelType channel, uint8 slaveAddress, uint8 address, uint8 data);

uint8 rdIIC_Device(I2C_ChannelType channel, uint8 writeAddr, uint8 readAddr, uint8 regAddress, uint8 mask);

void setDateAndTime(void);

#endif /* DEVICESIIC_H_ */
