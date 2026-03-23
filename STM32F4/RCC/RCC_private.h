 /*********************************************************************************************************************
  *   FILE DESCRIPTION
  *  -------------------------------------------------------------------------------------------------------------------
  *         File:  RCC_PRIVATE_H
  *       Module:  -
  *
  *  Description:   header for the RCC registers and their bits    
  *  
  *********************************************************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H
 
 
 /**********************************************************************************************************************
 * REGISTERS DEFINITIONS
 *********************************************************************************************************************/
 
 #define  RCC_CR			*((volatile u32*)0x40023800)
 #define  RCC_PLLCFGR		*((volatile u32*)0x40023804)
 #define  RCC_CFGR			*((volatile u32*)0x40023808)
 #define  RCC_CIR			*((volatile u32*)0x4002380C)
 #define  RCC_AHB1RSTR		*((volatile u32*)0x40023810)
 #define  RCC_AHB2RSTR		*((volatile u32*)0x40023814)
 #define  RCC_AHB3RSTR		*((volatile u32*)0x40023818)
 #define  RCC_APB1RSTR 		*((volatile u32*)0x40023820)
 #define  RCC_APB2RSTR		*((volatile u32*)0x40023824)
 #define  RCC_AHB1ENR		*((volatile u32*)0x40023830)
 #define  RCC_AHB2ENR		*((volatile u32*)0x40023834)
 #define  RCC_AHB3ENR		*((volatile u32*)0x40023838)
 #define  RCC_APB1ENR		*((volatile u32*)0x40023840)
 #define  RCC_APB2ENR		*((volatile u32*)0x40023844)
 #define  RCC_AHB1LPENR		*((volatile u32*)0x40023850)
 #define  RCC_AHB2LPENR		*((volatile u32*)0x40023854)
 #define  RCC_AHB3LPENR		*((volatile u32*)0x40023858)
 #define  RCC_APB1LPENR		*((volatile u32*)0x40023860)
 #define  RCC_APB2LPENR		*((volatile u32*)0x40023864)
 #define  RCC_BDCR			*((volatile u32*)0x40023870)
 #define  RCC_CSR			*((volatile u32*)0x40023874)
 #define  RCC_SSCGR			*((volatile u32*)0x40023880)
 #define  RCC_PLLI2SCFGR	*((volatile u32*)0x40023884)
 
 
 
 /**********************************************************************************************************************
 * RCC_CR Bits
 *********************************************************************************************************************/
#define RCC_CR_PLLI2SON_PIN          26
#define RCC_CR_PLLI2S_RDY_PIN        27 
#define RCC_CR_PLLON_PIN             24
#define RCC_CR_PLL_RDY_PIN           25 
#define RCC_CR_CSS_ON_PIN            19
#define RCC_CR_HSEBPY_PIN            18
#define RCC_CR_HSERDY_PIN            17
#define RCC_CR_HSEON_PIN             16
#define RCC_CR_HSICAL_START_PIN      8 
#define RCC_CR_HSITRIM_START_PIN     3
#define RCC_CR_HSITRIM_END_PIN       7
#define RCC_CR_HSIRDY_PIN            1
#define RCC_CR_HSION_PIN             0
 
 /**********************************************************************************************************************
 * RCC_CFGR Bits
 *********************************************************************************************************************/
#define RCC_CFGR_SW0          		 0
#define RCC_CFGR_SW1       		     1

/**********************************************************************************************************************
 * RCC_PLLCFGR Bits
 *********************************************************************************************************************/
#define RCC_PLLCFGR_SRC   	     22
#define RCC_PLLCFGR_PLLM		 0
#define RCC_PLLCFGR_PLLN		 6
#define RCC_PLLCFGR_PLLP		 16
#define RCC_PLLCFGR_PLLQ		 24


 /**********************************************************************************************************************
 * CLOCK TYPES
 *********************************************************************************************************************/
#define RCC_HSE_CRYSTAL  0
#define RCC_HSE_RC		 1
#define RCC_HSI			 2
#define RCC_PLL          3
#define RCC_PLLI2C       4

#define PLL_SRC_HSI      0
#define PLL_SRC_HSE      1

#define ON 				 1
#define OFF				 0


#endif  /* RCC_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: RCC_PRIVATE_H
 *********************************************************************************************************************/