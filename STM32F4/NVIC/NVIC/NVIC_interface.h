/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NVIC_INTERFACE_H
 *       Module:  -
 *
 *  Description:   header for the NVIC interface types     
 *  
 *********************************************************************************************************************/
#ifndef  NVIC_INTERFACE_H
#define  NVIC_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#include"STD_TYPES.h"

 typedef enum {
	 NVIC_WWDG         = 0    ,  
  NVIC_PVD      	   = 1    , 
  NVIC_TAMP_STAMP      = 2    ,  
  NVIC_RTC_WKUP        = 3    , 
  NVIC_FLASH           = 4    , 
  NVIC_RCC             = 5    ,  
  NVIC_EXTI0           = 6    , 
  NVIC_EXTI1   		   = 7    , 
  NVIC_EXTI2           = 8    , 
  NVIC_EXTI3           = 9    , 
  NVIC_EXTI4           = 10   ,
  NVIC_DMA1_Stream0    = 11   , 
  NVIC_DMA1_Stream1    = 12   , 
  NVIC_DMA1_Stream2    = 13   , 
  NVIC_DMA1_Stream3    = 14   , 
  NVIC_DMA1_Streaml4   = 15   ,  
  NVIC_DMA1_Streaml5   = 16   ,  
  NVIC_DMA1_Streaml6   = 17   ,  
  NVIC_ADC             = 18   ,  
  NVIC_CAN1_TX 		   = 19   ,  
  NVIC_CAN1_RX0  	   = 20   ,  
  NVIC_CAN_RX1         = 21   , 
  NVIC_CAN_SCE         = 22   , 
  NVIC_EXTI9_5         = 23   , 
  NVIC_TIM1_BRK_TIM9   = 24   ,  
  NVIC_TIM1_UP_TIM10   = 25   ,  
  NVIC_TIM1_TRG_COM_TIM11    = 26   ,  
  NVIC_TIM1_CC         = 27   ,  
  NVIC_TIM2            = 28   ,  
  NVIC_TIM3            = 29   ,  
  NVIC_TIM4            = 30   ,  
  NVIC_I2C1_EV         = 31   ,  
  NVIC_I2C1_ER         = 32   ,  
  NVIC_I2C2_EV         = 33   ,  
  NVIC_I2C2_ER         = 34   ,  
  NVIC_SPI1            = 35   ,  
  NVIC_SPI2            = 36   ,  
  NVIC_USART1          = 37   ,  
  NVIC_USART2          = 38   ,  
  NVIC_USART3          = 39   ,  
  NVIC_EXTI15_10       = 40   ,  
  NVIC_RTCAlarm        = 41   ,  
  NVIC_OTG_FS_WKUP     = 42   ,
  NVIC_TIM8_BRK_TIM12  = 43   ,
  NVIC_TIM8_UP_TIM13   = 44   ,
  NVIC_TIM8_TRG_COM_TIM14    = 45   ,
  NVIC_TIM8_CC         = 46   ,
  NVIC_DMA1_Stream7    = 47   ,
  NVIC_FSMC            = 48   ,
  NVIC_SDIO            = 49   ,
  NVIC_TIM5            = 50   ,
  NVIC_SPI3            = 51   ,
  NVIC_UART4           = 52   ,
  NVIC_UART5           = 53   ,
  NVIC_TIM6_DAC        = 54   ,
  NVIC_TIM7            = 55   ,
  NVIC_DMA2_Stream0    = 56   ,
  NVIC_DMA2_Stream1    = 57   ,
  NVIC_DMA2_Stream2    = 58   ,
  NVIC_DMA2_Stream3    = 59   ,
  NVIC_DMA2_Stream4    = 60   ,
  NVIC_ETH             = 61   ,
  NVIC_ETH_WKUP        = 62   ,
  NVIC_CAN2_TX         = 63   ,
  NVIC_CAN2_RX0 	   = 64   ,
  CAN2_RX1			   = 65   ,
  CAN2_SCE			   = 66   ,
  OTG_FS			   = 67   ,
  DMA2_Stream5		   = 68   ,
  DMA2_Stream6		   = 69   ,
  DMA2_Stream7		   = 70   ,
  USART6			   = 71   ,
  I2C3_EV		       = 72   ,
  I2C3_ER			   = 73   ,
  OTG_HS_EP1_OUT	   = 74   ,
  OTG_HS_EP1_IN		   = 75   ,
  OTG_HS_WKUP		   = 76   ,
  OTG_HS		       = 77   ,
  DCMI				   = 78   ,
  CRYP			       = 79   ,
  HASH_RNG			   = 80   ,
  FPU				   = 81   ,
 }NVIC_Per;
 
 
 typedef enum {
	 NVIC_NOT_ACTIVR,
	 NVIC_ACTIVE,
 }NVIC_Flag;
 
 typedef enum {
	 G16_S0,
	 G8_S2=0x4,
	 G4_S4=0x5,
	 G2_S8=0x6,
	 G0_S16=0x7,
 }Group_Sub_t;

 void NVIC_voidEnablePerInt (NVIC_Per Copyu8Per);
 void NVIC_voidDisablePerInt (NVIC_Per Copyu8Per);
 void NVIC_voidSetPerPendingReg (NVIC_Per Copyu8Per);
 void NVIC_voidClrPerPendingReg (NVIC_Per Copyu8Per);
 NVIC_Flag NVIC_u8ReadFlag(NVIC_Per Copyu8Per);
 void SCB_voidNVICPriorityConfig(Group_Sub_t  Copyu8GST);
 void NVIC_voidSetPriorityModeG0_S16(NVIC_Per Copyu8Per,u8 Copyu8Sub);
 void NVIC_voidSetPriorityModeG2_S8(NVIC_Per Copyu8Per,u8 Copyu8Group,u8 Copyu8Sub);
 void NVIC_voidSetPriorityModeG4_S4(NVIC_Per Copyu8Per,u8 Copyu8Group,u8 Copyu8Sub);
 void NVIC_voidSetPriorityModeG8_S2(NVIC_Per Copyu8Per,u8 Copyu8Group,u8 Copyu8Sub);
 void NVIC_voidSetPriorityModeG16_S0(NVIC_Per Copyu8Per,u8 Copyu8Group);
#endif
