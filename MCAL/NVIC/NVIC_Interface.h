/*
 * NVIC_Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef NVIC_NVIC_INTERFACE_H_
#define NVIC_NVIC_INTERFACE_H_

/*************************		priority Field options		*********************/
#define GRP_PRI_4_SUB_PRI_0           0b011
#define GRP_PRI_3_SUB_PRI_1           0b100
#define GRP_PRI_2_SUB_PRI_2           0b101
#define GRP_PRI_1_SUB_PRI_3           0b110
#define GRP_PRI_0_SUB_PRI_4           0b111

#define PEND_SV 		-6
#define SYSTICK 	    -5
#define SV_CALL   	    -4
#define MEM_MANGE 	    -3
#define BUS_FAULT 	    -2
#define USEGE_FAULT 	-1


/******************************	IRQ Options	********************************/
#define IRQ_WWDG					            		0
#define IRQ_EXTI16_PVD                          		1
#define IRQ_EXTI21_TAMP_STAMP                 		    2
#define IRQ_EXTI22_RTC_WKUP                   			3
#define IRQ_FLASH                   					4
#define IRQ_RCC                   						5
#define IRQ_EXTI0                   					6
#define IRQ_EXTI1                  					    7
#define IRQ_EXTI2                   					8
#define IRQ_EXTI3                   					9
#define IRQ_EXTI4                 					    10
#define IRQ_DMA1_Stream0                  				11
#define IRQ_DMA1_Stream1                 			    12
#define IRQ_DMA1_Stream2                  				13
#define IRQ_DMA1_Stream3                  				14
#define IRQ_DMA1_Stream4                  				15
#define IRQ_DMA1_Stream5                  				16
#define IRQ_DMA1_Stream6                  				17
#define IRQ_ADC                  						18
#define IRQ_19                  						19
#define IRQ_20                  						20
#define IRQ_21                  						21
#define IRQ_22                  						22
#define IRQ_EXTI9_5                  					23
#define IRQ_TIM1_BRK_TIM9                 				24
#define IRQ_TIM1_UP_TIM10                  				25
#define IRQ_TIM1_TRG_COM_TIM11                  		26
#define IRQ_TIM1_CC                  					27
#define IRQ_TIM2                  						28
#define IRQ_TIM3                  						29
#define IRQ_TIM4                  						30
#define IRQ_I2C1_EV                  					31
#define IRQ_I2C1_ER                  					32
#define IRQ_I2C2_EV                  					33
#define IRQ_I2C2_ER                  					34
#define IRQ_SPI1                 						35
#define IRQ_SPI2                  						36
#define IRQ_USART1                  					37
#define IRQ_USART2                  					38
#define IRQ_39                  						39
#define IRQ_EXTI15_10                  					40
#define IRQ_EXTI17_RTC_Alarm                  			41
#define IRQ_EXTI18_OTG_FS_WKUP                  		42
#define IRQ_43                  						43
#define IRQ_44                  						44
#define IRQ_45                  						45
#define IRQ_46                  						46
#define IRQ_DMA1_Stream7                  				47
#define IRQ_48                  						48
#define IRQ_SDIO                  						49
#define IRQ_TIM5                  						50
#define IRQ_SPI3                  						51
#define IRQ_52                  						52
#define IRQ_53                  						53
#define IRQ_54                  						54
#define IRQ_55                  						55
#define IRQ_DMA2_Stream0                  				56
#define IRQ_DMA2_Stream1                  				57
#define IRQ_DMA2_Stream2                  				58
#define IRQ_DMA2_Stream3                  				59
#define IRQ_DMA2_Stream4                  				60
#define IRQ_61                  						61
#define IRQ_62                  						62
#define IRQ_63                  						63
#define IRQ_64                  						64
#define IRQ_65                  						65
#define IRQ_66                  						66
#define IRQ_OTG_FS                  					67
#define IRQ_DMA2_Stream5                  				68
#define IRQ_DMA2_Stream6                  				69
#define IRQ_DMA2_Stream7                  				70
#define IRQ_USART6                  					71
#define IRQ_I2C3_EV                  					72
#define IRQ_I2C3_ER                  					73
#define IRQ_74                  						74
#define IRQ_75                  						75
#define IRQ_76                  						76
#define IRQ_77                  						77
#define IRQ_78                  						78
#define IRQ_79                  						79
#define IRQ_80                  						80
#define IRQ_FPU                  						81
#define IRQ_82                  						82
#define IRQ_83                  						83
#define IRQ_SPI4                  						84
/**************************************************************************************************************************/



/******************************************************************************
 * Function Name:  MNVIC_VoidEnablePeripheral
 * Description:	this enable INT of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id
 * Return:	ErrorState , Type:u8
 *
 ******************************************************************************/
void MNVIC_VoidEnablePeripheral (u8 Copy_u8PriId );
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVIC_VoidEnablePeripheral
 * Description:	this enable INT of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id
 * Return:	ErrorState , Type:u8
 *
 ******************************************************************************/
void MNVIC_VoidDisablePeripheral (u8 Copy_u8PriId );
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVIC_VoidSetPending
 * Description:	this set INT  pending flag of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id
 * Return:	void
 *
 ******************************************************************************/
void MNVIC_VoidSetPending (u8 Copy_u8PriId );
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVIC_VoidClearPending
 * Description:	this enable INT Pending flag  of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id
 * Return:	void
 *
 ******************************************************************************/
void MNVIC_VoidClearPending(u8 Copy_u8PriId );
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVICGetActiveFlag
 * Description:	this enable GET Active flag  of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id  , *Copy_u8Flag
 * Return:	 void
 *
 ******************************************************************************/
void MNVICGetActiveFlag(u8 Copy_u8PriId , u8 *Copy_u8Flag);
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVICSetPriorityCfg
 * Description: the function initialize the interrupt  Priority Field
 *              number of groups and number of SUB
 * Parameters: 1- Copy_u8PriorityOption
 *                   GRP_PRI_4_SUB_PRI_0
 *                   GRP_PRI_3_SUB_PRI_1
 *                   GRP_PRI_2_SUB_PRI_2
 *                   GRP_PRI_1_SUB_PRI_3
 *  			     GRP_PRI_0_SUB_PRI_4
 *  Return:	 void
 *
 ******************************************************************************/
void MNVICSetPriorityCfg(u8 Copy_u8PriorityOption );
/*============================================================================*/
/******************************************************************************
 * Function Name:  MNVICSetPriority
 * Description: the function Set the interrupt  Priority Field
 *              number of groups and number of SUB
 * Parameters: 1- Copy_u8IntID ,Copy_u8GruopPriority ,Copy_u8SubPriority
 * Return:	 void
 *
 ******************************************************************************/
void MNVICSetPriority(s8 Copy_u8IntID ,u8 Copy_u8GruopPriority ,u8 Copy_u8SubPriority );
/*============================================================================*/


#endif /* NVIC_NVIC_INTERFACE_H_ */
