/*
 * IIC.c
 *
 *  Created on: 8 Nov 2017
 *      Author: lrolo
 */

#include "IIC.h"

/**Configures the Channel of IIC to be used and also the GPIO PORTS AND PINS*/
void IIC_init(I2C_ChannelType channel, uint32 systemClock, uint8 baudRate, I2C_mult mult)
{
	uint8 ICR;

	/* Scheduler supports I2C communications up to 410 kHz. */
		if (21000000 == systemClock && 400 == baudRate && mul_1 == mult) {
			ICR = SCL_26; /* SCL = 26.25 */
		} else if (21000000 == systemClock && 100 == baudRate && mul_1 == mult) {
			ICR = SCL_104; /* SCL = 105 */
		} else if (21000000 == systemClock && 100 == baudRate && mul_2 == mult) {
			ICR = SCL_56; /* SCL = 52.5 */
		} else if (21000000 == systemClock && 400 == baudRate && mul_4 == mult) {
			ICR = SCL_26; /* SCL = 26.25 */
		} else if (60000000 == systemClock && 100 == baudRate && mul_1 == mult) {
			ICR = SCL_288; /* SCL = 300 */
		} else if (60000000 == systemClock && 100 == baudRate && mul_2 == mult) {
			ICR = SCL_144; /* SCL = 150 */
		} else if (60000000 == systemClock && 100 == baudRate && mul_4 == mult) { /* Este */
			ICR = SCL_72; /* SCL = 75 */
		} else if (60000000 == systemClock && 400 == baudRate && mul_1 == mult) {
			ICR = SCL_72; /* SCL = 75 */
		} else if (60000000 == systemClock && 400 == baudRate && mul_2 == mult) {
			ICR = SCL_36; /* SCL = 37.5 */
		} else if (60000000 == systemClock && 400 == baudRate && mul_4 == mult) {
			ICR = SCL_20; /* SCL = 18.75 */
		}

	switch(channel)
	{

		case I2C_0:
			SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;			//Clock Gating for I2C0
			SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;			//Clock Gating for PORTB
			PORTB->PCR[2] =  PORT_PCR_MUX(2);			//PORTB USED AS I2C SCL
			PORTB->PCR[3] =  PORT_PCR_MUX(2);			//PORTB USED AS I2C SDA

			I2C0->C1 |= I2C_C1_IICEN_MASK;				//Enabling I2C module
			I2C0->F |= I2C_F_MULT(mult);					//Configures the divider multiplies by 1
			I2C0->F |= I2C_F_ICR(ICR);					//Configures ICR number to approach the baud rate
			break;

		case I2C_1:
			SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;			//Clock Gating for I2C1
			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;			//Clock Gating for PORTB
			PORTC->PCR[10] =  PORT_PCR_MUX(2);			//PORTB USED AS I2C SCL
			PORTC->PCR[11] =  PORT_PCR_MUX(2);			//PORTB USED AS I2C SDA

			I2C1->C1 |= I2C_C1_IICEN_MASK;				//Enabling I2C module
			I2C1->F |= I2C_F_MULT(mult);	//Configures the divider multiplies by 1
			I2C1->F |= I2C_F_ICR(ICR);		//Configures ICR number to approach the baud rate
			break;

		default:
			SIM->SCGC1 |= SIM_SCGC1_I2C2_MASK;			//Clock Gating for I2C2
			SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;			//Clock Gating for PORTB
			PORTA->PCR[11] =  PORT_PCR_MUX(2);			//PORTB USED AS I2C SCL
			PORTA->PCR[12] =  PORT_PCR_MUX(2);			//PORTB USED AS I2C SDA

			I2C2->C1 |= I2C_C1_IICEN_MASK;				//Enabling I2C module
			I2C2->F |= I2C_F_MULT(mult);	//Configures the divider multiplies by 1
			I2C2->F |= I2C_F_ICR(ICR);		//Configures ICR number to approach the baud rate
			break;
	}

}

 /**It selects between master or slave mode*/
 void IIC_MST_Or_SLV_Mode(I2C_ChannelType channel, uint8 MoS)
 {

		switch(channel)
		{

			case I2C_0:
				if(MoS)
					I2C0->C1 |= I2C_C1_MST_MASK;		//Master mode is selected start signal send
				else
					I2C0->C1 &= ~(I2C_C1_MST_MASK);		//Slave mode is selected stop signal send
				break;

			case I2C_1:
				if(MoS)
					I2C1->C1 |= I2C_C1_MST_MASK;		//Master mode is selected start signal send
				else
					I2C1->C1 &= ~(I2C_C1_MST_MASK);		//Slave mode is selected stop signal send
				break;

			default:
				if(MoS)
					I2C2->C1 |= I2C_C1_MST_MASK;		//Master mode is selected start signal send
				else
					I2C2->C1 &= ~(I2C_C1_MST_MASK);		//Slave mode is selected stop signal send
				break;
		}

 }

 /**It selects between transmitter mode or receiver mode*/
 void IIC_TX_RX_Mode(I2C_ChannelType channel, uint8 mode)
 {

	 	 switch(channel)
	 	 {

			case I2C_0:
				if(mode)
					I2C0->C1 |= I2C_C1_TX_MASK;			//Master transmitter mode selected
				else
					I2C0->C1 &= ~(I2C_C1_TX_MASK);		//Master receiver mode selected
				break;

			case I2C_1:
				if(mode)
					I2C1->C1 |= I2C_C1_TX_MASK;			//Master transmitter mode selected
				else
					I2C1->C1 &= ~(I2C_C1_TX_MASK);		//Master receiver mode selected
				break;

			default:
				if(mode)
					I2C2->C1 |= I2C_C1_TX_MASK;			//Master transmitter mode selected
				else
					I2C2->C1 &= ~(I2C_C1_TX_MASK);		//Master receiver mode selected
				break;
		}

 }

 /**It generates the Not ACKnowledge that is needed when the master reads data*/
 void IIC_NACK(I2C_ChannelType channel)
 {
 	 switch(channel)
 	 {

		case I2C_0:
			I2C0->C1 |= I2C_C1_TXAK_MASK;
			break;

		case I2C_1:
			I2C1->C1 |= I2C_C1_TXAK_MASK;
			break;

		default:
			I2C2->C1 |= I2C_C1_TXAK_MASK;
			break;
	}
 }

 /**It generates a repeated start that is needed when master reads data*/
 void IIC_repeated_Start(I2C_ChannelType channel)
 {
 	 switch(channel)
 	 {

		case I2C_0:
			I2C0->C1 |= I2C_C1_RSTA_MASK;
			break;

		case I2C_1:
			I2C1->C1 |= I2C_C1_RSTA_MASK;
			break;

		default:
			I2C2->C1 |= I2C_C1_RSTA_MASK;
			break;
	}
 }

 /**It writes the data to be transmitted into the transmission buffer*/
void IIC_write_Byte(I2C_ChannelType channel, uint8 address)
{
	 switch(channel)
	 {

		case I2C_0:
			I2C0->D = address;
			break;

		case I2C_1:
			I2C1->D = address;
			break;

		default:
			I2C2->D = address;
			break;
	}
}

/**It reads data from the receiving buffer*/
uint8  IIC_read_Byte(I2C_ChannelType channel)
{
	 switch(channel)
	 {

		case I2C_0:
			return I2C0->D;
			break;

		case I2C_1:
			return I2C0->D;
			break;

		default:
			return I2C0->D;
			break;
	}
}

/**Indicates the status of the bus regardless of slave or master mode. Internally checks the busy bit in the I2Cx_S register*/
/*			if(I2C2->S & I2C_S_BUSY_MASK)
				return (I2C2->S & I2C_S_TCF_MASK);
			else
				return FALSE;
			break;*/
void IIC_wait(I2C_ChannelType channel)
{
	 switch(channel)
	 {

		case I2C_0:
			while(FALSE == (I2C0->S & I2C_S_IICIF_MASK));
				I2C0->S |= I2C_S_IICIF_MASK;
			break;

		case I2C_1:
			while(FALSE == (I2C1->S & I2C_S_IICIF_MASK));
				I2C1->S |= I2C_S_IICIF_MASK;
			break;

		default:
			while(FALSE == (I2C2->S & I2C_S_IICIF_MASK));
				I2C2->S |= I2C_S_IICIF_MASK;
			break;

	}
}

/**Indicates if the acknowledge was received*/
uint8 IIC_get_ACK(I2C_ChannelType channel)
{
	 switch(channel)
	 {

		case I2C_0:
			if(FALSE == (I2C0->S & I2C_S_RXAK_MASK))
				return TRUE;
			else
				return FALSE;
			break;
		case I2C_1:
			if(FALSE == (I2C1->S & I2C_S_RXAK_MASK))
				return TRUE;
			else
				return FALSE;
			break;
		default:
			if(FALSE == (I2C2->S & I2C_S_RXAK_MASK))
				return TRUE;
			else
				return FALSE;
			break;
	}
}

/**Configures the I2C in transmitting mode and generates the start signal*/
void IIC_start(I2C_ChannelType channel)
{
	 switch(channel)
	 {

		case I2C_0:
			IIC_MST_Or_SLV_Mode(channel, MASTER);
			IIC_TX_RX_Mode(channel, TRANSMITTER);
			break;

		case I2C_1:
			IIC_MST_Or_SLV_Mode(channel, MASTER);
			IIC_TX_RX_Mode(channel, TRANSMITTER);
			break;

		default:
			IIC_MST_Or_SLV_Mode(channel, MASTER);
			IIC_TX_RX_Mode(channel, TRANSMITTER);
			break;
	}
}

/**Configures the I2C in receiving mode and generates the stop signal*/
void IIC_stop(I2C_ChannelType channel)
{
	 switch(channel)
	 {

		case I2C_0:
			IIC_MST_Or_SLV_Mode(channel, SLAVE);
			IIC_TX_RX_Mode(channel, RECEIVER);
			break;

		case I2C_1:
			IIC_MST_Or_SLV_Mode(channel, SLAVE);
			IIC_TX_RX_Mode(channel, RECEIVER);
			break;

		default:
			IIC_MST_Or_SLV_Mode(channel, SLAVE);
			IIC_TX_RX_Mode(channel, RECEIVER);
			break;
	}
}

