#include <MK64F12.h>
#include "SPI.h"

void SPI_enable(SPI_ChannelType channel)/***/
{
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);		//Enables the module clocks of SPI0
			break;
		case SPI_1:
			SPI1->MCR &= ~(SPI_MCR_MDIS_MASK);		//Enables the module clocks of SPI1
			break;
		default:
			SPI2->MCR &= ~(SPI_MCR_MDIS_MASK);		//Enables the module clocks of SPI2
			break;
	}
}
void SPI_clk(SPI_ChannelType channel)
{
	switch(channel)
	{
		case SPI_0:
			SIM->SCGC6 |= SPI0_CLOCK_GATING;		//Configuring Clock Gating 6 for SPI0
			break;
		case SPI_1:
			SIM->SCGC6 |= SPI1_CLOCK_GATING;		//Configuring Clock Gating 6 for SPI1
			break;
		default:
			SIM->SCGC3 |= SPI2_CLOCK_GATING;		//Configuring Clock Gating 3 for SPI2
			break;
	}
}
void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave)
{

	switch(channel)
	{

		case SPI_0:
			if(masterOrSlave)
				SPI0->MCR |= SPI_MCR_MSTR_MASK;			//Enables Master operation mode for SPI0
			else
				SPI0->MCR &= ~(SPI_MCR_MSTR_MASK);		//Enables Slave operation mode for SPI0
			break;
		case SPI_1:
			if(masterOrSlave)
				SPI1->MCR |= SPI_MCR_MSTR_MASK;			//Enables Master operation mode for SPI1
			else
				SPI1->MCR &= ~(SPI_MCR_MSTR_MASK);		//Enables Slave operation mode for SPI1
			break;
		default:
			if(masterOrSlave)
				SPI2->MCR |= SPI_MCR_MSTR_MASK;			//Enables Master operation mode for SPI2
			else
				SPI2->MCR &= ~(SPI_MCR_MSTR_MASK);		//Enables Slave operation mode for SPI2
			break;
	}

}

void SPI_fIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable)
{
	switch(channel)
	{
		case SPI_0:
			if(enableOrDisable)
			{
				SPI0->MCR |= SPI_MCR_DIS_RXF_MASK;			//Disables FIFO RX on SPI0
				SPI0->MCR |= SPI_MCR_DIS_TXF_MASK;			//Disables FIFO TX on SPI0
			}
			else
			{
				SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK);		//Enables FIFO RX on SPI0
				SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK);		//Enables FIFO TX on SPI0
			}
				break;
		case SPI_1:
			if(enableOrDisable)
			{
				SPI1->MCR |= SPI_MCR_DIS_RXF_MASK;			//Disables FIFO RX on SPI1
				SPI1->MCR |= SPI_MCR_DIS_TXF_MASK;			//Disables FIFO TX on SPI1
			}
			else
			{
				SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK);		//Enables FIFO RX on SPI1
				SPI1->MCR &= ~(SPI_MCR_DIS_TXF_MASK);		//Enables FIFO TX on SPI1
			}
			break;
		default:
			if(enableOrDisable)
			{
				SPI2->MCR |= SPI_MCR_DIS_RXF_MASK;			//Disables FIFO RX on SPI2
				SPI2->MCR |= SPI_MCR_DIS_TXF_MASK;			//Disables FIFO TX on SPI2
			}
			else
			{
				SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK);		//Enables FIFO RX on SPI2
				SPI2->MCR &= ~(SPI_MCR_DIS_TXF_MASK);		//Enables FIFO TX on SPI2
			}
			break;
	}
}
void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol)
/**In this function we use CTAR0 because we haven't added any FIFO configuration and we are using the bus slave mode*/
{
	switch(channel)
	{
		case SPI_0:
			if(cpol)
				SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK;	//Configures High Polarity on SPI0
			else
				SPI0->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);	//Configures Low Polarity on SPI0
			break;
		case SPI_1:
			if(cpol)
				SPI1->CTAR[0] |= SPI_CTAR_CPOL_MASK;	//Configures High Polarity on SPI1
			else
				SPI1->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);	//Configures Low Polarity on SPI1
			break;
		default:
			if(cpol)
				SPI2->CTAR[0] |= SPI_CTAR_CPOL_MASK;	//Configures High Polarity on SPI2
			else
				SPI2->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);	//Configures Low Polarity on SPI2
			break;
	}
}
void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize)
/**In this function we use CTAR0 because we haven't added any FIFO configuration and we are using the bus slave mode*/
{
	switch(channel)
	{
		case SPI_0:
			SPI0->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);			//Clears the field space of the frame size on CTAR register
			SPI0->CTAR[0] |= frameSize;						//Charges another frame size on SPI0
			break;
		case SPI_1:
			SPI1->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);			//Clears the field space of the frame size on CTAR register
			SPI1->CTAR[0] |= frameSize;						//Charges another frame size on SPI1
			break;
		default:
			SPI2->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);			//Clears the field space of the frame size on CTAR register
			SPI2->CTAR[0] |= frameSize;						//Charges another frame size on SPI2
			break;
	}
}
void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha)
{
	switch(channel)
	{
		case SPI_0:
			if(cpha)
				SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;	//Data will change on leading edge
			else
				SPI0->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);	//Data will be captured on leading edge
			break;
		case SPI_1:
			if(cpha)
				SPI1->CTAR[0] |= SPI_CTAR_CPHA_MASK;	//Data will change on leading edge
			else
				SPI1->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);	//Data will be captured on leading edge
			break;
		default:
			if(cpha)
				SPI2->CTAR[0] |= SPI_CTAR_CPHA_MASK;	//Data will change on leading edge
			else
				SPI2->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);	//Data will be captured on leading edge
			break;
	}
}
void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate)
/**In this function we use CTAR0 because we haven't added any FIFO configuration and we are using the bus slave mode*/
{
	switch(channel)
	{
		case SPI_0:
			SPI0->CTAR[0] &= ~(SPI_CTAR_BR_MASK);		//Clears the field space of the baud rate on CTAR register
			SPI0->CTAR[0] |= SPI_CTAR_BR(baudRate);		//Charges another baud rate on SPI0
			break;
		case SPI_1:
			SPI1->CTAR[0] &= ~(SPI_CTAR_BR_MASK);		//Clears the field space of the baud rate on CTAR register
			SPI1->CTAR[0] |= SPI_CTAR_BR(baudRate);		//Charges another baud rate on SPI1
			break;
		default:
			SPI2->CTAR[0] &= ~(SPI_CTAR_BR_MASK);		//Clears the field space of the baud rate on CTAR register
			SPI2->CTAR[0] |= SPI_CTAR_BR(baudRate);		//Charges another baud rate on SPI2
			break;
	}
}
void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb)
{
	switch(channel)
	{
		case SPI_0:
			if(msb)
				SPI0->CTAR[0] |= SPI_CTAR_LSBFE_MASK;		//Data will be transfer from the lsb to the msb
			else
				SPI0->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);	//Data will be transfer from the msb to the lsb
			break;
		case SPI_1:
			if(msb)
				SPI1->CTAR[0] |= SPI_CTAR_LSBFE_MASK;		//Data will be transfer from the lsb to the msb
			else
				SPI1->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);	//Data will be transfer from the msb to the lsb
			break;
		default:
			if(msb)
				SPI2->CTAR[0] |= SPI_CTAR_LSBFE_MASK;		//Data will be transfer from the lsb to the msb
			else
				SPI2->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);	//Data will be transfer from the msb to the lsb
			break;
	}
}
void SPI_startTranference(SPI_ChannelType channel)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= ~(SPI_MCR_HALT_MASK);				//Putting halt on 0 Transfer will start
			break;
		case SPI_1:
			SPI1->MCR &= ~(SPI_MCR_HALT_MASK);				//Putting halt on 0 Transfer will start
			break;
		default:
			SPI2->MCR &= ~(SPI_MCR_HALT_MASK);				//Putting halt on 0 Transfer will start
			break;
	}
}
void SPI_stopTranference(SPI_ChannelType channel)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR |= SPI_MCR_HALT_MASK;					//Putting halt on 1 Transfer must stop
			break;
		case SPI_1:
			SPI1->MCR |= SPI_MCR_HALT_MASK;					//Putting halt on 1 Transfer must stop
			break;
		default:
			SPI2->MCR |= SPI_MCR_HALT_MASK;					//Putting halt on 1 Transfer must stop
			break;
	}
}
void SPI_sendOneByte(uint8 Data)
/**This function allow us to transfer one byte*/
{
	SPI0->PUSHR = (Data);							//Specifies data to be transferred to the TX FIFO
	while(FALSE == (SPI0->SR & SPI_SR_TCF_MASK));	//This flag indicates when a transfer is complete //Esto es codigo bloqueante duda para el profesor
	SPI0->SR |= SPI_SR_TCF_MASK;					//So then this flag is cleared
}

void SPI_init(const SPI_ConfigType* SPI_Config)
/**This function contains all the initialisation of the SPI organised as an structure*/
{
	SPI_clk(SPI_Config->SPI_Channel);
	GPIO_clockGating(SPI_Config->GPIOForSPI.GPIO_portName);
	GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName, SPI_Config->GPIOForSPI.SPI_clk, & (SPI_Config->pinConttrolRegisterPORTD));
	GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName, SPI_Config->GPIOForSPI.SPI_Sout, & (SPI_Config->pinConttrolRegisterPORTD));
	SPI_setMaster(SPI_Config->SPI_Channel, SPI_Config->SPI_Master);
	SPI_fIFO(SPI_Config->SPI_Channel, SPI_Config->SPI_EnableFIFO);
	SPI_enable(SPI_Config->SPI_Channel);
	SPI_clockPolarity(SPI_Config->SPI_Channel, SPI_Config->SPI_Polarity);
	SPI_frameSize(SPI_Config->SPI_Channel,SPI_Config->frameSize);
	SPI_clockPhase(SPI_Config->SPI_Channel, SPI_Config->SPI_Phase);
	SPI_baudRate(SPI_Config->SPI_Channel, SPI_Config->baudrate);
	SPI_mSBFirst(SPI_Config->SPI_Channel,SPI_MSB);
}
