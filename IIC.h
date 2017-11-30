/*
 * IIC.h
 *
 *  Created on: 8 Nov 2017
 *      Author: lrolo
 */

#ifndef IIC_H_
#define IIC_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"

#define busClock 10500000

typedef enum {
	mul_1, mul_2, mul_4
} I2C_mult;

typedef enum {
	SCL_20, /*!< Bit 0 */
	SCL_22, /*!< Bit 1 */
	SCL_24, /*!< Bit 2 */
	SCL_26, /*!< Bit 3 */
	SCL_28, /*!< Bit 4 */
	SCL_30, /*!< Bit 5 */
	SCL_34, /*!< Bit 6 */
	SCL_40, /*!< Bit 7 */
	SCL_29, /*!< Bit 8 */
	SCL_32, /*!< Bit 9 */
	SCL_36, /*!< Bit A */
	SCL_41, /*!< Bit B */
	SCL_44, /*!< Bit C */
	SCL_48, /*!< Bit D */
	SCL_56, /*!< Bit E */
	SCL_68, /*!< Bit F */
	SCL_49, /*!< Bit 10 */
	SCL_57, /*!< Bit 11 */
	SCL_64, /*!< Bit 12 */
	SCL_72, /*!< Bit 13 */
	SCL_80, /*!< Bit 14 */
	SCL_88, /*!< Bit 15 */
	SCL_104, /*!< Bit 16 */
	SCL_128, /*!< Bit 17 */
	SCL_81, /*!< Bit 18 */
	SCL_96, /*!< Bit 19 */
	SCL_112, /*!< Bit 1A */
	SCL_129, /*!< Bit 1B */
	SCL_144, /*!< Bit 1C */
	SCL_160, /*!< Bit 1D */
	SCL_192, /*!< Bit 1E */
	SCL_240, /*!< Bit 1F */
	SCL_161, /*!< Bit 20 */
	SCL_193, /*!< Bit 21 */
	SCL_224, /*!< Bit 22 */
	SCL_256, /*!< Bit 23 */
	SCL_288, /*!< Bit 24 */
	SCL_320, /*!< Bit 25 */
	SCL_384, /*!< Bit 26 */
	SCL_480, /*!< Bit 27 */
	SCL_321, /*!< Bit 28 */
	SCL_385, /*!< Bit 29 */
	SCL_448, /*!< Bit 2A */
	SCL_512, /*!< Bit 2B */
	SCL_576, /*!< Bit 2C */
	SCL_640, /*!< Bit 2D */
	SCL_768, /*!< Bit 2E */
	SCL_960, /*!< Bit 2F */
	SCL_641, /*!< Bit 30 */
	SCL_769, /*!< Bit 31 */
	SCL_896, /*!< Bit 32 */
	SCL_1024, /*!< Bit 33 */
	SCL_1152, /*!< Bit 34 */
	SCL_1280, /*!< Bit 35 */
	SCL_1536, /*!< Bit 36 */
	SCL_1920, /*!< Bit 37 */
	SCL_1281, /*!< Bit 38 */
	SCL_1537, /*!< Bit 39 */
	SCL_1792, /*!< Bit 3A */
	SCL_2048, /*!< Bit 3B */
	SCL_2304, /*!< Bit 3C */
	SCL_2560, /*!< Bit 3D */
	SCL_3072, /*!< Bit 3E */
	SCL_3480, /*!< Bit 3F */
} SCL_divider;

/**
 * \brief This enum define the IIC port to be used.
 */
typedef enum {I2C_0, I2C_1, I2C_2}I2C_ChannelType;

/**
 * \brief This enum define the BAUD RATE to be used.
 */
typedef enum {BR_100 = 100, BR_400 = 400}BaudRateIICType;

/**
 * \brief This enum define the MASTER OR SLAVE to be used.
 */
typedef enum {SLAVE, MASTER}MasterOrSlaveIICType;

/**
 * \brief This enum define the TX OR RX MODE to be used.
 */
typedef enum {RECEIVER, TRANSMITTER}TX_RX_MODE_IICType;
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Configures the I2C port based on the input parameters.
  	 	 Also, internally this function configures the GPIO, pin control register and clock gating, to be used as I2C.
  	 	 It is recommended to use pin 2 and 3 of GPIOB.
  	 \param[in] channel It is the channel to be used.
  	 \param[in] systemClock Frequency of the system.
  	 \param[in] baudRate baud rate between MCU and I2C device.
  	 \return void

  */
void IIC_init(I2C_ChannelType channel, uint32 systemClock, uint8 baudRate, I2C_mult mult);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It selects between master or slave mode.
  	 \param[in] masterOrSlave If == 1 master mode, if == 0 slave mode.
  	 \return void

  */
 void IIC_MST_Or_SLV_Mode(I2C_ChannelType channel, uint8 MoS);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It selects between transmitter mode or receiver mode.
  	 \param[in] txOrRx If == 1 transmitter mode, if == 0 slave mode.
  	 \return void

  */
 void IIC_TX_RX_Mode(I2C_ChannelType channel, uint8 mode);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It generates the Not ACKnowledge that is needed when the master reads data.
  	 \return void

  */
 void IIC_NACK(I2C_ChannelType channel);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It generates a repeated start that is needed when master reads data.
  	 \return void

  */
 void IIC_repeated_Start(I2C_ChannelType channel);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It writes the data to be transmitted into the transmission buffer. When you want to
  	 	 write a value into the buffer you need to use this sentence I2C0_D = data. Avoid to use
  	 	 masks like this I2C0_D |= data.
  	 \return void

  */
void IIC_write_Byte(I2C_ChannelType channel, uint8 address);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 It reads data from the receiving buffer.
 	 \return void

 */
uint8  IIC_read_Byte(I2C_ChannelType channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Indicates the status of the bus regardless of slave or master mode. Internally checks the busy bit int the
 	 	 I2Cx_S register. This bit is set when a START signal is detected and cleared when a STOP signal is detected.
 	 \return This function returns a 0 logic if the bus is idle and returns 1 logic if the bus is busy.

 */
void IIC_wait(I2C_ChannelType channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Indicates if the acknowledge was received.
 	 \return This function returns a 0 logic if the acknowledge was received and returns 1 logic if the acknowledge was not received.

 */
uint8 IIC_get_ACK(I2C_ChannelType channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Generates the start signal. When MST bit is changed from 0 to 1, a START signal is generated
 	 	 on the bus and master mode is selected. Also, inside the function the I2C is
 	 	 change to transmitter mode.
 	 \return void

 */
void IIC_start(I2C_ChannelType channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Generates the stop signal. When this bit changes from 1 to 0, a STOP signal is generated
 	 	 and the mode of operation changes from master to slave. Also, inside the function the I2C is
 	 	 change to receiver mode.
 	 \return void

 */
void IIC_stop(I2C_ChannelType channel);

#endif /* IIC_H_ */

