/*
 * STM32f411XX.h
 *
 *  Created on: Jul 12, 2022
 *      Author: nabil
 */

#ifndef STM32F411XX_H_
#define STM32F411XX_H_
/********************		core base addresses		******************************/

/********************		SYSTIC Timer  base  addresses		******************************/
#define SYS_CTRL *((volatile u32 *)(0xE000E010+0x00))
#define SYS_LOAD *((volatile u32 *)(0xE000E010+0x04))
#define SYS_VAL  *((volatile u32 *)(0xE000E010+0x08))


/********************* Memories Base Address************************/

/*Write FLASH_BASE_ADDRESS Because it is divided from within To region */
#define FLASH_BASE_ADDRESS 0x08000000UL
/*Write SRAM Because it is Not divided from within To region */
#define SRAM 0x20000000UL
#define ROM  0x1FFF0000Ul


/********************* AHB1 PeripheraL Base Address************************/
#define GPIOA_BASE_ADDRES 0x40020000UL
#define GPIOB_BASE_ADDRES 0x40020400UL
#define GPIOC_BASE_ADDRES 0x40020800UL
#define GPIOD_BASE_ADDRES 0x40020C00UL
#define GPIOE_BASE_ADDRES 0x40021000UL
#define GPIOH_BASE_ADDRES 0x40021C00UL

/********************* APB1 PeripheraL Base Address************************/

#define I2C1_BASE_ADDRES  0x40005400UL
#define I2C2_BASE_ADDRES  0x40005800UL
#define I2C3_BASE_ADDRES  0x40005C00UL
#define SPI2_BASE_ADDRES  0x40003800UL
#define SPI3_BASE_ADDRES  0x40003C00UL
#define USART2_BASE_ADDRES 0x40004400UL

/********************* APB2 PeripheraL Base Address************************/
#define USART1_BASE_ADDRES 0x40011000UL
#define USART6_BASE_ADDRES 0x40011400UL
#define EXTI_BASE_ADDRES 0x40013C00UL
#define SPI1_BASE_ADDRES 0x40013000UL
#define SPI4_BASE_ADDRES 0x40013400UL
#define SYSCFG_BASE_ADDRES 0x40013800UL

/********************* GPIO Register definition ************************/


typedef struct
{
	volatile u32  MODER;		    /*GPIO port mode register*/
	volatile u32  OTYPER;		/*GPIO port output type register*/
	volatile u32  OSPEEDR;		/*GPIO port output speed register*/
	volatile u32  PUPDR;			/*GPIO port pull-up/pull-down register*/
	volatile u32  IDR;			/*GPIO port input data register*/
	volatile u32  ODR;			/*GPIO port output data register*/
	volatile u32  BSRR;			/*GPIO port bit set/reset register */
	volatile u32  LCKR;			/*GPIO port configuration lock register */
	volatile u32  AFR[2];		/*GPIO_AFR[0] GPIO alternate function low register
	                           	   	  GPIO_AFR[1] GPIO alternate function high register   */

}GPIO_RegDef_t;

/********************* Pointer to port BASE addresses  ************************/

#define GPIO_PORTA_PTR     ((GPIO_RegDef_t *)GPIOA_BASE_ADDRES)
#define GPIO_PORTB_PTR     ((GPIO_RegDef_t *)GPIOB_BASE_ADDRES)
#define GPIO_PORTC_PTR     ((GPIO_RegDef_t *)GPIOC_BASE_ADDRES)
#define GPIO_PORTD_PTR     ((GPIO_RegDef_t *)GPIOD_BASE_ADDRES)
#define GPIO_PORTE_PTR     ((GPIO_RegDef_t *)GPIOE_BASE_ADDRES)
#define GPIO_PORTH_PTR     ((GPIO_RegDef_t *)GPIOH_BASE_ADDRES)


#endif /* STM32F411XX_H_ */

