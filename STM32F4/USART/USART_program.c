/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  USART_program_c
 *       Module:  -
 *
 *  Description:  C program for USART functions   
 *  
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_private.h"
#include "USART_interface.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

void (*USART1_CallBackFunc)(u8) ;
u8 USART_Buffer[];


volatile USART_t* USART;
void  USART_voidInit(USART_Config_t USART_Config){
	switch (USART_Config.USART_No){
		case USART_1: USART=USART1;USART1_PinsConfig();break;
		case USART_2: USART=USART2;USART2_PinsConfig();break;
		case USART_3: USART=USART3;USART3_PinsConfig();break;
	}

/*setting baudrate*/
MSK_2BYTE(USART->BRR,0,USART_Config.USART_BR);
/*Setting the Configuration before enabling the USART*/
USART_voidSetOverSamplingMode(USART_Config.USART_OverSampling);
if(USART_Config.USART_ParityEnable==Parity_DISABLE){
	CLR_BIT(USART->CR1,10);
}
else if (USART_Config.USART_ParityEnable==Parity_ENABLE){
	USART_voidEnableParity(USART_Config.USART_Parity);
}
USART_voidSetWordLength(USART_Config.USART_WorlLength);
USART_voidSetStopBits(USART_Config.USART_StopBits);
USART_voidSetPolarity(USART_Config.USART_Pol);
USART_voidSetPhase(USART_Config.USART_Phase);
/*Enabling Tx,Rx, and USART*/
SET_BIT(USART->CR1,2);
SET_BIT(USART->CR1,3);
SET_BIT(USART->CR1,13);
/*Clearing the SR Flags*/
USART-> SR =0;
	
}

void USART_voidTransmit(USART_No_t Copy_USART_No,u8 *arr){
	switch (Copy_USART_No){
		case USART_1: USART=USART1;break;
		case USART_2: USART=USART2;break;
		case USART_3: USART=USART3;break;
	}
	u8 i=0;
	while(arr[i]!='\0'){	
		STK_VoidDelayMs(1000);

		while((GET_BIT(USART->SR,7))==0);
			/*Waiting for the data to transfer to the shift reg*/
			STK_VoidDelayMs(1000);

		USART->DR=arr[i];
		STK_VoidDelayMs(1000);
		i++;

	while((GET_BIT(USART->SR,6))==0);
		STK_VoidDelayMs(1000);
		/*wait Transmision complete flag is set*/

	}
	arr=0;
}
u8 USART_u8Receive(USART_No_t Copy_USART_No){
	switch (Copy_USART_No){
		case USART_1: USART=USART1;break;
		case USART_2: USART=USART2;break;
		case USART_3: USART=USART3;break;
	}
	while(GET_BIT(USART->SR,5)==0){
	}
	return (0xFF&(USART->DR));
}

void USART_voidEnableCLK(USART_No_t Copy_USART_No){
	switch (Copy_USART_No){
		case USART_1: GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_8,GPIO_ALT); //Clk
									MSK_4BIT(GPIO_A_AFRH,0,7);
									SET_BIT(USART1->CR2,11);
									break;
		case USART_2: GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_4,GPIO_ALT); //Clk
									MSK_4BIT(GPIO_A_AFRL,16,7);
									SET_BIT(USART2->CR2,11);break;
		case USART_3: GPIO_voidSetPinMode(GPIO_PORT_B,GPIO_PIN_12,GPIO_ALT); //Clk
									MSK_4BIT(GPIO_B_AFRH,16,7);
									SET_BIT(USART3->CR2,11);break;
	}
	
}


void USART1_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (GET_BIT(USART1->SR,5)) {
			USART1_CallBackFunc(USART1->DR) ;

		#ifdef TM_USART1_USE_CUSTOM_IRQ
			/* Call user function */
			TM_USART1_ReceiveHandler(USART1->DR);
		#else
			/* Put received data into internal buffer */
			TM_USART_INT_InsertToBuffer(&TM_USART1, USART1->DR);
		#endif
	}
}
void USART_voidTCInteruptEnable(void){
		SET_BIT(USART->CR1,6);

}
void USART_voidTXEInteruptEnable(void){
		SET_BIT(USART->CR1,7);

}

void USART_voidSetOverSamplingMode(USART_OVER_SAMPLING_MODE_t Copyu8Mode){
		MSK_1BIT(USART->CR1,15,Copyu8Mode);

}

void USART_voidEnableParity(USART_PARITY_t Copyu8PT){
	SET_BIT(USART->CR1,10);
	MSK_1BIT(USART->CR1,9,Copyu8PT);
}

void USART_voidSetPolarity(USART_CPOL_t Copyu8P){
	MSK_1BIT(USART->CR2,10,Copyu8P);
}
void USART_voidSetPhase(USART_CPHASE_t Copyu8P){
	MSK_1BIT(USART->CR2,9,Copyu8P);
}
void USART_voidSetStopBits(USART_STOP_BITS_t Copyu8B){
	MSK_2BIT(USART->CR2,12,Copyu8B);
}
void USART_voidSetWordLength(USART_WORD_L_t Copyu8L){
		MSK_1BIT(USART->CR1,12,Copyu8L);
}
void USART1_PinsConfig(void){
	/*Setting GPIO PINS for alternative functions*/
GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_9,GPIO_ALT); //Tx
GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_10,GPIO_ALT);//Rx
/*Setting the usart as the Alternative function*/
MSK_4BIT(GPIO_A_AFRH,8,7);
MSK_4BIT(GPIO_A_AFRH,4,7);
}
void USART2_PinsConfig(void){
	/*Setting GPIO PINS for alternative functions*/
GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_2,GPIO_ALT); //Tx
GPIO_voidSetPinMode(GPIO_PORT_A,GPIO_PIN_3,GPIO_ALT);//Rx
/*Setting the usart as the Alternative function*/
MSK_4BIT(GPIO_A_AFRL,8,7);
MSK_4BIT(GPIO_A_AFRL,12,7);
}
void USART3_PinsConfig(void){
	/*Setting GPIO PINS for alternative functions*/
GPIO_voidSetPinMode(GPIO_PORT_B,GPIO_PIN_10,GPIO_ALT); //Tx
GPIO_voidSetPinMode(GPIO_PORT_B,GPIO_PIN_11,GPIO_ALT);//Rx
/*Setting the usart as the Alternative function*/
MSK_4BIT(GPIO_B_AFRH,8,7);
MSK_4BIT(GPIO_B_AFRH,12,7);
}