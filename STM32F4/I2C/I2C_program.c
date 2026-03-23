/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  I2C_PROGRAM_C
 *       Module:  -
 *
 *  Description:   C program for I2C
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "I2C_private.h"
#include "I2C_interface.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"

void I2C_voidMasterInitTx(u16 Copy_SlaveAdd,u8 *Copy_Data){
	/*Setting GPIO MODER to alternative function*/
	GPIO_voidSetPinMode(GPIO_PORT_B,GPIO_PIN_6,GPIO_ALT);
	GPIO_voidSetPinMode(GPIO_PORT_B,GPIO_PIN_9,GPIO_ALT);
	/*Setting I2C as Alternative function*/
	MSK_4BIT(GPIO_B_AFRL,24,4);
	MSK_4BIT(GPIO_B_AFRH,4,4);
	/*Setting PA6,PA9 as open drain*/
	GPIO_voidPinOPT(GPIO_PORT_B,GPIO_PIN_9,GPIO_OPEN_DRAIN);
	GPIO_voidPinOPT(GPIO_PORT_B,GPIO_PIN_6,GPIO_OPEN_DRAIN);
	/*Enabling I2C*/
	SET_BIT(I2C1->CR1,0);
	SET_BIT(I2C1->CR1,8);
	/*Start bit */
	I2C1->CR1 |= 1<<8;                		//I2C Start
	while (!(I2C1->SR1 & 0x0001));   //waiting for the start bit 
	/*Sending the Address of the slave*/
	STK_VoidDelayMs(100);
	MSK_2BYTE(I2C1->DR,0,Copy_SlaveAdd);
	STK_VoidDelayMs(1000);
	/*Waiting for the address to be sent*/
	while (!(I2C1->SR1 & 0x0002));
	u32 SR2_V = (I2C1->SR2); /*to clear SR1*/
	u8 i=0;
	/*Sending the Data*/
	while(Copy_Data[i]!='\0'){
	I2C1->DR = Copy_Data[i];
	/*Waiting for Ack*/
		STK_VoidDelayMs(1000);
	while (GET_BIT(I2C1->SR1,7)==0);
	i++;
	}
	/*Sending the Stop Bit*/
	SET_BIT(I2C1->CR1,9);
	while (I2C1->SR2 & 0x0002);

}
/*****************************************************************************************************************/
u8 I2C_Read(u8 address, u8 reg,I2C_ACK_t Ack) {
	u8 received_data;
	I2C_Start( address, I2C_TRANSMITTER_MODE, Ack );
	I2C_WriteData(reg);
	I2C_Stop();
	I2C_Start( address, I2C_RECEIVER_MODE,Ack);
	received_data = I2C_ReadNack();
	return received_data;
}
u8 I2C_ReadNoRegister( u8 address) {
	u8 data;
	I2C_Start( address, I2C_RECEIVER_MODE, ACK_ENABLE);
	/* Also stop condition happens */
	data = I2C_ReadNack();
	return data;
}
void I2C_Write( u8 address, u8 reg, u8 data) {
	I2C_Start( address, I2C_TRANSMITTER_MODE, ACK_DISABLE);
	I2C_WriteData( reg);
	I2C_WriteData( data);
	I2C_Stop();
}
void I2C_WriteNoRegister( u8 address, u8 data,I2C_ACK_t Ack) {
	I2C_Start(address, I2C_TRANSMITTER_MODE,Ack);
	I2C_WriteData(data);
	I2C_Stop();
}

/* Private functions */
///////////////////////
void I2C_Start( u8 address, I2C_Dir_t direction, I2C_ACK_t ack) {
	/* Generate I2C start pulse */
	//I2C1->CR1 |= I2C1_CR1_START;
	SET_BIT(I2C1->CR1,8);
	/* Wait till I2C is busy */
	while (!GET_BIT(I2C1->SR1,0));
	/* Enable ack if we select it */
		MSK_1BIT(I2C1->CR1,10,ack);
	/* Send write/read bit */
	if (direction == I2C_TRANSMITTER_MODE) {
		/* Send address with zero last bit */	
		I2C1->DR =( (address<<1) & ~(0x001));
		/* Wait till finished */
		while (!(GET_BIT(I2C1->SR1,1)));
	}	
	if (direction == I2C_RECEIVER_MODE) {
		/* Send address with 1 last bit */
		I2C1->DR =( (address<<1)|(0x001));	
		/* Wait till finished */
		while (!(GET_BIT(I2C1->SR1,1)));
		}	
	/* Read status register to clear ADDR flag */
	u32 SR2_V = I2C1->SR2;
	/* Return 0, everything ok */
}
////////////////////////
void I2C_WriteData(u8 data) {
	/* Wait till I2C is not busy anymore */	
	while (!GET_BIT(I2C1->SR1,7));	
	/* Send I2C data */
	I2C1->DR = data;
}
//////////////////////////
u8 I2C_ReadAck(void) {
	u8 data;
	/* Enable ACK */
	SET_BIT(I2C1->CR1,10);
	/* Wait till not received */
	while (!GET_BIT(I2C1->SR1,2));
	/* Read data */
	data = I2C1->DR;
	/* Return data */
	return data;
}
///////////////////////////
u8 I2C_ReadNack(void) {
	u8 data;
	/* Disable ACK */
	CLR_BIT(I2C1->CR1,10);
	/* Generate stop */
	SET_BIT(I2C1->CR1,9);
	/* Wait till received */	
	while (!GET_BIT(I2C1->SR1,6));
	/* Read data */
	data = I2C1->DR;	
	/* Return data */
	return data;
}

/////////
void I2C_Stop(void) {
	/* Wait till transmitter not empty */
	while (((!GET_BIT(I2C1->SR1,7)) || (!GET_BIT(I2C1->SR1,2)))) ;
	/* Generate stop */
	SET_BIT(I2C1->CR1,9);
	/* Return 0, everything ok */

}
/*****************************************************************************************************/
void I2C_u8MasterRx(u16 Copy_SlaveAdd,u8 *Copy_DataToReceive[],I2C_ACK_t Copy_ACK,u8 Copy_DataReq){
	/*Setting GPIO MODER to alternative function*/
		GPIO_voidSetPinMode(GPIO_PORT_B,GPIO_PIN_6,GPIO_ALT);
		GPIO_voidSetPinMode(GPIO_PORT_B,GPIO_PIN_9,GPIO_ALT);
		/*Setting I2C as Alternative function*/
		MSK_4BIT(GPIO_B_AFRL,24,4);
		MSK_4BIT(GPIO_B_AFRH,4,4);
		/*Enabling I2C*/
		SET_BIT(I2C1->CR1,0);
		SET_BIT(I2C1->CR1,8);
		/*Start bit */
		I2C1->CR1 |= 1<<8;                		//I2C Start
		while (!(I2C1->SR1 & 0x0001));   //waiting
		/*Sending the Address of the slave*/
		MSK_2BYTE(I2C1->DR,0,Copy_SlaveAdd);
		/*Waiting for the address to be sent*/
		while (!(I2C1->SR1 & 0x0002));
		u32 SR2_V = (I2C1->SR2); /*to clear SR1*/
		/*Sending the Data*/
		I2C1->DR = Copy_DataReq;
		/*Waiting for Ack*/
		while (GET_BIT(I2C1->SR1,7)==0);
		I2C1->CR1 |= 1<<8;                		//I2C reStart
		while (!(I2C1->SR1 & 0x0001));   //waiting
		/*Sending the Address of the slave +1 to Write */
		MSK_2BYTE(I2C1->DR,0,Copy_SlaveAdd+0x01);
		/*Waiting for the address to be sent*/
		while (!(I2C1->SR1 & 0x0002));
		SR2_V = (I2C1->SR2); /*to clear SR1*/
		u8 i=0;
		/*
		 * Setting tha Ack
		 * Receiving the Data
		 */
		MSK_1BIT(I2C1->CR1,10,Copy_ACK);
		while(GET_BIT(I2C1->SR1,2)==1){
		while (!(I2C1->SR1 & 0x00000040));
		*Copy_DataToReceive[i]=I2C1->DR;
		i++;
		}
		/*Sending the Stop Bit*/
			SET_BIT(I2C1->CR1,9);
			while (I2C1->SR2 & 0x0002);

}

void I2C_voidSetSlaveAdd1(u16 Copy_Address){
	I2C1->OAR1=Copy_Address;

}
void I2C_voidSetSlaveAdd2(u16 Copy_Address){
	I2C1->OAR2=Copy_Address;

}

void I2C_voidClockConfig(I2C_ClockConfig_t Copy_ClockConfig){

	MSK_6BIT(I2C1->CR2,0,Copy_ClockConfig.I2C_Freq);   /*Peripheral Freq*/
	MSK_1BIT(I2C1->CCR,15,Copy_ClockConfig.I2C_Mode);  /*Standard or fast*/
	MSK_1BIT(I2C1->CCR,14,Copy_ClockConfig.I2C_FM_DC); /*The duty cycle for FM*/
	u16 CCR_Value=((Copy_ClockConfig.I2C_Freq*1000)/(2*Copy_ClockConfig.I2C_SCL)); /*Calculating the Clock control*/
	MSK_12BIT(I2C1->CCR,0,CCR_Value);
	u16 TRISE_Value=(Copy_ClockConfig.I2C_TRISE*Copy_ClockConfig.I2C_Freq*0.001)+1;  /*TRISE in ns and I2C Freq in MHz*/
	MSK_6BIT(I2C1->TRISE,0,TRISE_Value);

}
