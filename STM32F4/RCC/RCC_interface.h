/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  RCC_INTERFACE_H
 *       Module:  -
 *
 *  Description:   header for the RCC interface types     
 *  
 *********************************************************************************************************************/
#ifndef  RCC_INTERFACE_H
#define  RCC_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************
 
 /**********************************************************************************************************************
 *  GLOBAL  MACROS
 *********************************************************************************************************************/
 
 #define RCC_AHB1 	0
 #define RCC_AHB2 	1
 #define RCC_AHB3 	2 	
 #define RCC_APB1	3
 #define RCC_APB2 	4

 
 
typedef enum{
	RCC_AHB1_GPIOA,
	RCC_AHB1_GPIOB,
	RCC_AHB1_GPIOC,
	RCC_AHB1_GPIOD,
	RCC_AHB1_GPIOE,
	RCC_AHB1_GPIOF,
	RCC_AHB1_GPIOG,
	RCC_AHB1_GPIOI,
	RCC_AHB1_CRCEN=12,
	RCC_AHB1_BKPSRAMEN=18,
	RCC_AHB1_CCMDATARAMEN=20,
	RCC_AHB1_DMA1=21,
	RCC_AHB11_DMA1=22,
	/* PerID not defined yet AHB1 25-->30 + AHB2 + AHB3*/
}RCC_AHB1_PerID;

typedef enum {
	RCC_APB1_TIM2,
	RCC_APB1_TIM3,
	RCC_APB1_TIM4,
	RCC_APB1_TIM5,
	RCC_APB1_TIM6,
	RCC_APB1_TIM7,
	RCC_APB1_TIM12,
	RCC_APB1_TIM13,
	RCC_APB1_TIM14,
	RCC_APB1_WWDG=11,
	RCC_APB1_SPI2=14,
	RCC_APB1_SPI3=15,
	RCC_APB1_UART2=17,
	RCC_APB1_UART3=18,
}RCC_APB1_PerID;
 
/**********************************************************************************************************************
 * RCC Functions
 *********************************************************************************************************************/
 
 void RCC_voidInitSysClock(void);
 void RCC_voidEnableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);
 void RCC_voidDisableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);


 #endif /* RCC_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: RCC_INTERFACE_H
 *********************************************************************************************************************/
