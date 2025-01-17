/*
 * devicesIIC.c
 *
 *  Created on: 12 Nov 2017
 *      Author: lrolo
 */

#include "devicesIIC.h"

void wrByte(I2C_ChannelType channel, uint8 slaveAddress, uint8 hAddress, uint8 lAddress, uint8 data)
{
	///////////////////////////////////////////WRITE///////////////////////////////////////////////////
		IIC_start(channel);
		IIC_write_Byte(channel, slaveAddress);		//ADDRESS AND R/W BIT FOR LOCATING MEMORY
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_write_Byte(channel, hAddress);			//HIGH BYTE FOR ADDRESS IN MEMORY
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_write_Byte(channel, lAddress);			//LOW BYTE FOR ADDRESS IN MEMORY
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_write_Byte(channel, data);				//DATA TO STORE ON EEPROM
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_stop(channel);
	////////////////////////////////////////////////////////////////////////////////////////////////////
}

uint8 rdByte(I2C_ChannelType channel, uint8 writeAddr, uint8 readAddr, uint8 hAddress, uint8 lAddress)
{
	static uint8 memData;
	//////////////////////////////////////////////RANDOM READ///////////////////////////////////////////
		IIC_start(channel);

		IIC_write_Byte(channel, writeAddr);		//ADDRESS AND R/W BIT FOR LOCATING MEMORY
		IIC_wait(channel);
		IIC_get_ACK(channel);					//SLAVE RECOGNIZED BYTE TRANSFER COMPLETE

		IIC_write_Byte(channel, hAddress);		//HIGH BYTE FOR ADDRESS IN MEMORY
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_write_Byte(channel, lAddress);		//LOW BYTE FOR ADDRESS IN MEMORY
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_repeated_Start(channel);			//RESTART TO KNOW READ DATA
		IIC_write_Byte(channel, readAddr);		//ADDRESS AND R/W BIT FOR LOCATING MEMORY
		IIC_wait(channel);
		IIC_get_ACK(channel);					//SLAVE KNOWS ITS GOING TO BE READED

		IIC_TX_RX_Mode(channel, RECEIVER);		//MASTER RECEIVING CONFIGURING FOR READ DATA

		IIC_NACK(channel);						//NOT ACKNOWLEDGE GENERATED BY MASTER

		memData = IIC_read_Byte(channel);		//FALSE READ

		IIC_wait(channel);

		IIC_stop(channel);

		memData = IIC_read_Byte(channel);		//RETURNING VALUE
	////////////////////////////////////////////////////////////////////////////////////////////////////
		return memData;
}

void wrIIC_Device(I2C_ChannelType channel, uint8 slaveAddress, uint8 address, uint8 data)
{
	///////////////////////////////////////////WRITE///////////////////////////////////////////////////
		IIC_start(channel);
		IIC_write_Byte(channel, slaveAddress);		//ADDRESS AND R/W BIT FOR LOCATING RTC
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_write_Byte(channel, address);			//HIGH BYTE FOR ADDRESS IN RTC
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_write_Byte(channel, data);				//DATA RTC
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_stop(channel);
	////////////////////////////////////////////////////////////////////////////////////////////////////
}

uint8 rdIIC_Device(I2C_ChannelType channel, uint8 writeAddr, uint8 readAddr, uint8 regAddress, uint8 mask)
{
	static uint8 Data;
	//////////////////////////////////////////////RANDOM READ///////////////////////////////////////////
		IIC_start(channel);

		IIC_write_Byte(channel, writeAddr);	//ADDRESS AND R/W BIT FOR LOCATING MEMORY
		IIC_wait(channel);
		IIC_get_ACK(channel);				//SLAVE RECOGNIZED BYTE TRANSFER COMPLETE

		IIC_write_Byte(channel, regAddress);//REGISTER OF MODULE
		IIC_wait(channel);
		IIC_get_ACK(channel);

		IIC_repeated_Start(channel);		//RESTART TO KNOW READ DATA
		IIC_write_Byte(channel, readAddr);	//ADDRESS AND R/W BIT FOR LOCATING MEMORY
		IIC_wait(channel);
		IIC_get_ACK(channel);				//SLAVE KNOWS ITS GOING TO BE READED

		IIC_TX_RX_Mode(channel, RECEIVER);	//MASTER RECEIVING CONFIGURING FOR READ DATA

		IIC_NACK(channel);					//NOT ACKNOWLEDGE GENERATED BY MASTER
		Data = IIC_read_Byte(channel);		//FALSE READ
		IIC_wait(channel);

		IIC_stop(channel);
		Data = IIC_read_Byte(channel);		//RETURNING VALUE
	////////////////////////////////////////////////////////////////////////////////////////////////////
		return Data & mask;
}

///*void setDateAndTime(void)
//{
//
//	wrIIC_Device(I2C_0, WRRTC, RTC_SEC, RTC_REGISTER2);		//DATA SECONDS
//	wrIIC_Device(I2C_0, WRRTC, RTC_MIN, RTC_REGISTER3);		//DATA MINUTES
//	wrIIC_Device(I2C_0, WRRTC, RTC_HOURS, RTC_REGISTER4);	//DATA HOURS
//	wrIIC_Device(I2C_0, WRRTC, RTC_DAY, RTC_REGISTER5);		//DATA DAYS
//	wrIIC_Device(I2C_0, WRRTC, RTC_WEEKDAY, RTC_REGISTER6);	//DATA WEEKDAYS
//	wrIIC_Device(I2C_0, WRRTC, RTC_MONTH, RTC_REGISTER7);	//DATA MONTHS
//	wrIIC_Device(I2C_0, WRRTC, RTC_YEAR, RTC_REGISTER8);	//DATA YEARS
//
//}*/
