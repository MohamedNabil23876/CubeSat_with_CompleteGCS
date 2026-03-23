/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  RCC_program_c
 *       Module:  -
 *
 *  Description:  C program for RCC functions   
 *  
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_private.h"
#include "RCC_interface.h"
#include "RCC_config.h"

/**********************************************************************************************************************
 * Functions
 *********************************************************************************************************************/
 void RCC_voidInitSysClock(void){
	 #if RCC_CLOCK_TYPE==RCC_HSE_CRYSTAL
		CLR_REG(RCC_CR);
		SET_BIT(RCC_CR,RCC_CR_HSEON_PIN);
		CLR_REG(RCC_CFGR);
		SET_BIT(RCC_CFGR,RCC_CFGR_SW0);
	 #elif RCC_CLOCK_TYPE==RCC_HSE_RC
		CLR_REG(RCC_CR);
		SET_BIT(RCC_CR,RCC_CR_HSEON_PIN);
		SET_BIT(RCC_CR,RCC_CR_HSEBPY_PIN);
		CLR_REG(RCC_CFGR);
		SET_BIT(RCC_CFGR,RCC_CFGR_SW0);
	 #elif RCC_CLOCK_TYPE==RCC_HSI
		CLR_REG(RCC_CR);
		SET_BIT(RCC_CR,RCC_CR_HSION_PIN);
		SET_BIT(RCC_CR,RCC_CR_HSITRIM_END_PIN);
		CLR_REG(RCC_CFGR);
 	 #elif RCC_CLOCK_TYPE==RCC_PLL
	 /*SET up PLL Factors before enabling the PLL*/
		CLR_REG(RCC_PLLCFGR);
		MSK_6BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLM,RCC_PLLM_VALUE);
		MSK_9BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLN,RCC_PLLN_VALUE);
		switch(RCC_PLLP_VALUE){
			case 2:MSK_2BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLP,0x0);break;
			case 4:MSK_2BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLP,0x1);break;
			case 6:MSK_2BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLP,0x2);break;
			case 8:MSK_2BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLP,0x3);break;
		};
		MSK_4BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLQ,RCC_PLLQ_VALUE);
		#if RCC_PLL_SRC==PLL_SRC_HSE
		SET_BIT(RCC_PLLCFGR,RCC_PLLCFGR_SRC);
		#endif
		CLR_REG(RCC_CR);
		SET_BIT(RCC_CR,RCC_CR_PLLON_PIN);		
	 #elif #error("wrong Clck type")
	 
	 #endif

 }
 
 void RCC_voidEnableClock(u8 Copy_u8BusId,u8 Copy_u8PerId){
	 if(Copy_u8PerId<=31){
		 
		 switch(Copy_u8BusId){
			 case RCC_AHB1  : SET_BIT(RCC_AHB1ENR,Copy_u8PerId);break;
			 case RCC_AHB2  : SET_BIT(RCC_AHB2ENR,Copy_u8PerId);break;
			 case RCC_AHB3  : SET_BIT(RCC_AHB3ENR,Copy_u8PerId);break;
			 case RCC_APB1  : SET_BIT(RCC_APB1ENR,Copy_u8PerId);break;
			 case RCC_APB2  : SET_BIT(RCC_APB2ENR,Copy_u8PerId);break;
			 default : /*send error*/ break; 
		 }
	 }
	 else{
		 /*send error*/
	 }
 }
 
 void RCC_voidDisableClock(u8 Copy_u8BusId,u8 Copy_u8PerId){
	 if(Copy_u8PerId<=31){
		 
		 switch(Copy_u8BusId){
			 case RCC_AHB1  : CLR_BIT(RCC_AHB1ENR,Copy_u8PerId);break;
			 case RCC_AHB2  : CLR_BIT(RCC_AHB2ENR,Copy_u8PerId);break;
			 case RCC_AHB3  : CLR_BIT(RCC_AHB3ENR,Copy_u8PerId);break;
			 case RCC_APB1  : CLR_BIT(RCC_APB1ENR,Copy_u8PerId);break;
			 case RCC_APB2  : CLR_BIT(RCC_APB2ENR,Copy_u8PerId);break;
			 default : /*send error*/ break; 
		 }
	 }
	 else{
		 /*send error*/
	 }
 }
 