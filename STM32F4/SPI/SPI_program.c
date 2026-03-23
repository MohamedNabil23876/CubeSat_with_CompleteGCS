/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SPI_PROGRAM_C
 *       Module:  -
 *
 *  Description:   c Program for SPI Functions
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#include"STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include"SPI_config.h"
void (*SPI1_CallBackFunc)(u8) ;

void SPI_voidMasterInit(SPI_MasterConfig_t CopyMasterConfig){
	/*Setting SPI1 Pins in the GPIO as alternative function mode*/
	GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_6,GPIO_ALT);
	GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_7,GPIO_ALT);
	GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_5,GPIO_ALT);
	/*Setting SPI1 as alternative function*/
	MSK_4BIT(GPIO_A_AFRL,20,5);
	MSK_4BIT(GPIO_A_AFRL,24,5);
	MSK_4BIT(GPIO_A_AFRL,28,5);
	/*Setting the CR as the Configuration*/
	MSKP_REG(SPI1->CR1,BIDIMODE,CopyMasterConfig.SPI_Mode);
	MSKP_REG(SPI1->CR1,CRCEN,CopyMasterConfig.SPI_CRC);
	MSKP_REG(SPI1->CR1,DFF,CopyMasterConfig.SPI_DataSize);
	MSKP_REG(SPI1->CR1,SSM,CopyMasterConfig.SPI_SSM);
	MSKP_REG(SPI1->CR1,LSBFIRST,CopyMasterConfig.SPI_FirstBit);
	MSKP_REG(SPI1->CR1,BR,CopyMasterConfig.SPI_BR);
	MSKP_REG(SPI1->CR1,CPOL,CopyMasterConfig.SPI_Polarity);
	MSKP_REG(SPI1->CR1,CPHA,CopyMasterConfig.SPI_Phase);
	MSKP_REG(SPI1->CR2,4,CopyMasterConfig.SPI_FrameFormate);
	/*Enabling Master Mode and the SPI*/
	SET_BIT(SPI1->CR1,MSTR);
	SET_BIT(SPI1->CR1,SPE);
	


}

void SPI_voidSlaveInit(SPI_SlaveConfig_t CopySlaveConfig){
	/*Setting SPI1 Pins in the GPIO*/
	GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_6,GPIO_ALT);
	GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_7,GPIO_ALT);
	GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_5,GPIO_ALT);
	GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_4,GPIO_ALT);
	/*Setting SPI1 as alternative function*/
	MSK_4BIT(GPIO_A_AFRL,20,5);
	MSK_4BIT(GPIO_A_AFRL,24,5);
	MSK_4BIT(GPIO_A_AFRL,28,5);
	MSK_4BIT(GPIO_A_AFRL,16,5);
	/*Setting the CR as the Configuration*/
	MSKP_REG(SPI1->CR1,BIDIMODE,CopySlaveConfig.SPI_Mode);
	MSKP_REG(SPI1->CR1,CRCEN,CopySlaveConfig.SPI_CRC);
	MSKP_REG(SPI1->CR1,DFF,CopySlaveConfig.SPI_DataSize);
	MSKP_REG(SPI1->CR1,RXONLY,CopySlaveConfig.SPI_RX_Only);
	MSKP_REG(SPI1->CR1,LSBFIRST,CopySlaveConfig.SPI_FirstBit);
	MSKP_REG(SPI1->CR1,BR,CopySlaveConfig.SPI_BR);
	MSKP_REG(SPI1->CR1,CPOL,CopySlaveConfig.SPI_Polarity);
	MSKP_REG(SPI1->CR1,CPHA,CopySlaveConfig.SPI_Phase);
	MSKP_REG(SPI1->CR2,4,CopySlaveConfig.SPI_FrameFormate);
	/*Enabling Slave Mode and the SPI*/
	CLR_BIT(SPI1->CR1,MSTR);
	SET_BIT(SPI1->CR1,SPE);
	

}

void SPI_voidMasterConectSlave(GPIO_PORT_ID Copy_u8SlavePort,GPIO_PIN_ID Copy_u8SlavePin){
	GPIO_voidSetPinMode(Copy_u8SlavePort,Copy_u8SlavePin,GPIO_OUTPUT);
	GPIO_voidSetPinValue(Copy_u8SlavePort,Copy_u8SlavePin,GPIO_PIN_HIGH);

}


void SPI_voidSendReceiveSync(u8 *Copy_u8DataToTransmit,u8 *Copy_DataToReceive[],u8 Copy_SlaveSelect){
	/*Checking if 1M1S mode has SSM enabled*/
	u8 Check_SSM=GET_BIT(SPI1->CR1,SSM);
	if(Check_SSM== 0 ){
			switch(Copy_SlaveSelect){
			/*Enabling the Slave Select Pin*/
			case 1:GPIO_voidSetPinValue(Slave_1,GPIO_PIN_LOW);break;
			case 2:GPIO_voidSetPinValue(Slave_2,GPIO_PIN_LOW);break;
			case 3:GPIO_voidSetPinValue(Slave_3,GPIO_PIN_LOW);break;
		}
		}
	u8 i=0;
	while(Copy_u8DataToTransmit[i]!='\0'){
		/*Sending the Data*/
		SPI1->DR=Copy_u8DataToTransmit[i];
		i++;
		/*Waiting for the flag*/
		
		while(!(SPI1->SR & 0x0002));
		/*Receiving the Data*/
	
		while(!(SPI1->SR & 0x0001));

		*Copy_DataToReceive[i]=SPI1->DR;
		

	}
		if(Check_SSM==0){
				switch(Copy_SlaveSelect){
				/*Disabling the Slave Select pin*/
				case 1:GPIO_voidSetPinValue(Slave_1,GPIO_PIN_HIGH);break;
				case 2:GPIO_voidSetPinValue(Slave_2,GPIO_PIN_HIGH);break;
				case 3:GPIO_voidSetPinValue(Slave_3,GPIO_PIN_HIGH);break;
			}
			}

}

void SPI_voidSendReceiveASync(u8 Copy_u8DataToTransmit,void (*CallBackFunc)(u8),u8 Copy_SlaveSelect){
	/*Enabling the Interrupt for the SPI*/
		SET_BIT(SPI1->CR2,7);
		SPI1_CallBackFunc = CallBackFunc ;
	u8 Check_SSM=GET_BIT(SPI1->CR1,SSM);
	      if(Check_SSM==0){
	      		switch(Copy_SlaveSelect){
				/*Enabling the Slave Select Pin*/
	      		case 1:GPIO_voidSetPinValue(Slave_1,GPIO_PIN_LOW);break;
	      		case 2:GPIO_voidSetPinValue(Slave_2,GPIO_PIN_LOW);break;
	      		case 3:GPIO_voidSetPinValue(Slave_3,GPIO_PIN_LOW);break;
	      	}
	      	}
	    while(!(SPI1->SR & 0x0002)) ;
	    SPI1 -> DR = Copy_u8DataToTransmit ;
}

void SPI1_IRQHandler(u8 Copy_SlaveSelect)
{
	u8 Check_SSM=GET_BIT(SPI1->CR1,SSM);
	if(Check_SSM==0){
					switch(Copy_SlaveSelect){
					/*Disabling the Slave Select pin*/
					case 1:GPIO_voidSetPinValue(Slave_1,GPIO_PIN_HIGH);break;
					case 2:GPIO_voidSetPinValue(Slave_2,GPIO_PIN_HIGH);break;
					case 3:GPIO_voidSetPinValue(Slave_3,GPIO_PIN_HIGH);break;
				}
				}
	SPI1_CallBackFunc(SPI1 -> DR ) ;
	/*Disabling the Interrupt*/
    CLR_BIT(SPI1->CR2,7);
}
