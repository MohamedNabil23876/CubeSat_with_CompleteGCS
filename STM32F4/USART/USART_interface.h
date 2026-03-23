/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  USART_INTERFACE_H
 *       Module:  -
 *
 *  Description:   header for the USART interface types     
 *  
 *********************************************************************************************************************/
#ifndef  USART_INTERFACE_H
#define  USART_INTERFACE_H

#include"STD_TYPES.h"
typedef enum {
	USART_1,
	USART_2,
	USART_3,
}USART_No_t;

typedef enum {
	BR9600_OS16_f8 = 0x341, /*Over sampling 16 , f=8MHz*/
	BR9600_OS16_f12 =0x4E2,
	
}USART_BR_t;
typedef enum {
	OVER_16,
	OVER_8
}USART_OVER_SAMPLING_MODE_t;

typedef enum {
	USART_8B,
	USART_9B,
}USART_WORD_L_t;

typedef enum {
	USART_Sample_SetUp,
	USART_SetUp_Sample,
}USART_CPHASE_t;

typedef enum {
	USART_Rising_Faling,
	USART_Faling_Rising,
}USART_CPOL_t;

typedef enum {
		STOP_1,
		STOP_05,
		STOP_2,
		STOP_15,
}USART_STOP_BITS_t;

typedef enum {
	Parity_ENABLE,
	Parity_DISABLE,
}USART_ParityEnable_t;

typedef enum {
	EVEN_P,
	ODD_P,
}USART_PARITY_t;

typedef enum{
	USART_Poll,
	USART_Interrupt,
}USART_Methode_t;

typedef struct {
	USART_No_t						 USART_No;
	USART_ParityEnable_t	 USART_ParityEnable;
	USART_PARITY_t 				 USART_Parity;
	USART_CPOL_t    			 USART_Pol;
	USART_CPHASE_t  			 USART_Phase;
	USART_OVER_SAMPLING_MODE_t  USART_OverSampling;
	USART_BR_t  					 USART_BR;
	USART_STOP_BITS_t			 USART_StopBits;
	USART_WORD_L_t				 USART_WorlLength;
	USART_Methode_t				 USART_Methode;
	u8									  *Buffer_DataReceived;
	void (*CallBackFunc)(u8);
}USART_Config_t;


/*USART Functions*/

/* Function 	: USART_voidInitUSART_Config_t USART_Config);
   DESCRIPTION  : Set the PA9 Tx ,PA10 Rx in alternative Function mode
				  Set the usart in AFR 
				  Set the USART Baudrate
				  Enable The Rx and the Tx in the USART 
				  Enable The USART and clear the statues register	  
*/
void  USART_voidInit(USART_Config_t USART_Config);


/* Function 	: USART_voidTransmit(USART_No_t Copy_USART_No,u8 arr[])
   DESCRIPTION  : Send Array of Bytes 
				  Transmit the Data and Wait for the Flag to be Set 			  
*/
void USART_voidTransmit(USART_No_t Copy_USART_No,u8 *arr);


/* Function 	: USART_u8Receive(USART_No_t Copy_USART_No)
   DESCRIPTION  : Receive 1 Byte of Data		  
*/
u8 USART_u8Receive(USART_No_t Copy_USART_No);



/* Function 	: USART_voidEnableCLK(USART_No_t Copy_USART_No)
   DESCRIPTION  : Enables the Clock in the USART 
				  Set PA8 as the  USART Clock in the GPIO		  
*/
void USART_voidEnableCLK(USART_No_t Copy_USART_No);


/*Functions for USART Configurations */

void USART_voidSetOverSamplingMode(USART_OVER_SAMPLING_MODE_t Copyu8Mode);

void USART_voidEnableParity(USART_PARITY_t Copyu8PT);

void USART_voidSetWordLength(USART_WORD_L_t Copyu8L);
void USART_voidSetStopBits(USART_STOP_BITS_t Copyu8B);

void USART_voidSetPolarity(USART_CPOL_t Copyu8P);
void USART_voidSetPhase(USART_CPHASE_t Copyu8P);

void USART1_PinsConfig(void);
void USART2_PinsConfig(void);
void USART3_PinsConfig(void);

/*INTERUPTS ENABLING FOR USART*/ 
void USART_voidTCInteruptEnable(void);
void USART_voidTXEInteruptEnable(void);

#endif 


