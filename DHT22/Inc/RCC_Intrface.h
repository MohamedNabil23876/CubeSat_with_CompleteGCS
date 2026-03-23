/*
 * RCC_Intrface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef MCAL_RCC_RCC_INTRFACE_H_
#define MCAL_RCC_RCC_INTRFACE_H_


/*Peripherals Connected to AHB1 Bus*/
#define GPIOA_PERIPHERAL                     							 0
#define GPIOB_PERIPHERAL                    							 1
#define GPIOC_PERIPHERAL                     							 2
#define GPIOD_PERIPHERAL                    							 3
#define GPIOE_PERIPHERAL                    							 4
#define GPIOH_PERIPHERAL                     							 7
#define CRC_PERIPHERAL                       							 12
#define DMA1_PERIPHERAL                    								 21
#define DMA2_PERIPHERAL                    								 22

/*Peripherals Connected to AHB2 Bus*/
#define USB_OTGFS_PERIPHERAL                    						 7

/*Peripherals Connected to APB1 Bus*/
#define TIM2_PERIPHERAL           	 0
#define TIM3_PERIPHERAL           	 1
#define TIM4_PERIPHERAL           	 2
#define TIM5_PERIPHERAL           	 3
#define SPI2_I2S2_PERIPHERAL      	 14
#define SPI3_I2S3_PERIPHERAL      	 15
#define USART2_PERIPHERAL         	 17
#define I2C1_PERIPHERAL           	 21
#define I2C2_PERIPHERAL           	 22
#define I2C3_PERIPHERAL           	 23
#define PWR_PERIPHERAL            	 28

/*Peripherals Connected to APB2 Bus*/
#define TIM1_PERIPHERAL         	 0
#define USART1_PERIPHERAL       	 4
#define USART6_PERIPHERAL       	 5
#define ADC1_PERIPHERAL         	 8
#define SDIO_PERIPHERAL         	 11
#define SPI1_PERIPHERAL         	 12
#define SPI4_I2S4_PERIPHERAL    	 13
#define   SYSCFGEN                   14
#define TIM9_PERIPHERAL         	 16
#define TIM10_PERIPHERAL        	 17
#define TIM11_PERIPHERAL        	 18

//-------------Buses--------------------

#define AHB1 0
#define AHB2 1
#define APB1 2
#define APB2 3


/******************************************************************************
 * Function Name:  MRCC_VoidInit
 *
 * Description:	the function initialize the RCC from where type of CLK and
 *              and Enable CLK Source
 *
 * Parameters: void
 * Return:	void
 *
 ******************************************************************************/
void MRCC_VoidInit(void);
//-----------------------------------------------------------------------------

/******************************************************************************
 * Function Name:  RCC_VoidEnableCLK
 *
 * Description:	the function select bus and enable Peripheral
 *
 * Parameters: Copy_u8BusName  : select Bus
 *             Copy_u8Peripheral : select peripheral to enable
 * Return:	void
 *
 ******************************************************************************/
void RCC_VoidEnableCLK(u8 Copy_u8BusName , u8 Copy_u8Peripheral );

//-----------------------------------------------------------------------------

/******************************************************************************
 * Function Name:  RCC_VoidDisableCLK
 *
 * Description:	the function select bus and Disable Peripheral
 *
 * Parameters: Copy_u8BusName  : select Bus  AHB1 |AHB2 |APB1 |APB2
 *             Copy_u8Peripheral : select peripheral to enable
 * Return:	void
 *
 ******************************************************************************/
void RCC_VoidDisableCLK(u8 Copy_u8BusName , u8 Copy_u8Peripheral );
//-----------------------------------------------------------------------------




#endif /* MCAL_RCC_RCC_INTRFACE_H_ */
