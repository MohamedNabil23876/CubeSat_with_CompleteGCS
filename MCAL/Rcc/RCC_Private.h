/*
 * RCC_Private.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef MCAL_RCC_RCC_PRIVATE_H_
#define MCAL_RCC_RCC_PRIVATE_H_


#define RCC_BASE_ADDRESS  0x40023800UL
typedef struct
{
	u32 CR; //RCC clock control register
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Res1;
	u32 Res2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Res3;
	u32 Res4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Res5;
	u32 Res6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 Res7;
	u32 Res8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Res9;
	u32 Res10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Res11;
	u32 Res12;
	u32 BDCR;
	u32 CSR;
	u32 Res13;
	u32 Res14;
	u32 SSCGR;
	u32 PLLI2SCFGR;


} RCC_Reg_Cfg;


#define RCC ((RCC_Reg_Cfg*)(RCC_BASE_ADDRESS))


/************ CR Registers  ************/

#define CR_CSSON  19  // Clock security system enable
#define CR_HSEBYP 18 //HSE clock bypass
#define CR_HSERDY 17 // HSE clock ready flag
#define CR_HSEON  16 // HSE clock enable
#define CR_HSIRDY 1 //Internal high-speed clock ready flag
#define CR_HSION  0  //Internal high-speed clock enable

/***************RCC clock configuration register (RCC_CFGR)****************/

#define CFGR_SW

#define SW0 0
#define SW1 1


/*********************CSS state *********************/

#define CSS_ENABLE 1 // if enable CLK security SYS
#define CSS_DISABLE 0

/*********************HSEBYP state *********************/

#define HSEBYP_ENABLE 0
#define HSEBYP_DISABLE 1


/*********************CLK TYPE *********************/

#define	RCC_HSI			 0
#define	RCC_HSE  	     1
#define	RCC_PLL		     2


#endif /* MCAL_RCC_RCC_PRIVATE_H_ */
