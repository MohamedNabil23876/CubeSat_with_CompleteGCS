/*
 * GPIO_Pri.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef MCAL_GPIO_GPIO_PRI_H_
#define MCAL_GPIO_GPIO_PRI_H_

#define GPIOA_BASE_ADDRESS  0x40020000UL
#define GPIOB_BASE_ADDRESS  0x40020400UL
#define GPIOC_BASE_ADDRESS  0x40020800UL

typedef struct
{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFR[2];


}GPIO_Reg_Cfg;


#define GPIOA ((GPIO_Reg_Cfg *)(GPIOA_BASE_ADDRESS))
#define GPIOB ((GPIO_Reg_Cfg *)(GPIOB_BASE_ADDRESS))
#define GPIOC ((GPIO_Reg_Cfg *)(GPIOC_BASE_ADDRESS))

#define GPIOA_A ((volatile GPIO_t *)0x40020000)
#define GPIOB_A ((volatile GPIO_t *)0x40020400)
#define GPIOC_A ((volatile GPIO_t *)0x40020800)

typedef struct
{
	volatile u32 MODER2;
	volatile u32 OTYPER2;
	volatile u32 OSPEEDR2;
	volatile u32 PUPDR2;
	volatile u32 IDR2;
	volatile u32 ODR2;
	volatile u32 BSRR2;
	volatile u32 LCKR2;
	volatile u32 AFRL;
	volatile u32 AFRH;
}GPIO_t;


#define MAX_PORT_NUM 3

#endif /* MCAL_GPIO_GPIO_PRI_H_ */
