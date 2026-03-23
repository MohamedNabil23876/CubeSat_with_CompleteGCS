/*
 * Rcc_Pro.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

// LIB
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
// RCC_Header File
#include "RCC_Gfg.h"
#include "RCC_Intrface.h"
#include "RCC_Private.h"


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

void MRCC_VoidInit(void)
{
	// CLK SYS state
#if CSS_STATE==CSS_ENABLE
	SET_BIT(RCC->CR,CR_CSSON);
#elif CSS_STATE==CSS_DISABLE
	CLR_BIT(RCC->CR,CR_CSSON);
#endif

	// select SYSCLK switch  to HSE

	SET_BIT(RCC->CFGR,SW0);
	// select the system clock source
#if SYSTEM_CLOCK==RCC_HSI
	SET_BIT(RCC->CR,CR_HSION);
	while(GET_BIT(RCC->CR,CR_HSIRDY)==0);
#elif SYSTEM_CLOCK==RCC_HSE
    #if HSEBYP_STATE==HSEBYP_ENABLE
    	SET_BIT(RCC->CR,HSEBYP)
    #elif HSEBYP_STATE==HSEBYP_DISABLE
    	CLR_BIT(RCC->CR,HSEBYP);
    #endif
    	SET_BIT(RCC->CR,CR_HSEON);
	while(GET_BIT(RCC->CR,CR_HSERDY)==0);
#endif
	//  sat clock bypass

}

//-----------------------------------------------------------------------------

/******************************************************************************
 * Function Name:  RCC_VoidEnableCLK
 *
 * Description:	the function select bus and enable Peripheral
 *
 * Parameters: Copy_u8BusName  : select Bus  AHB1 |AHB2 |APB1 |APB2
 *             Copy_u8Peripheral : select peripheral to enable
 * Return:	void
 *
 ******************************************************************************/
void RCC_VoidEnableCLK(u8 Copy_u8BusName , u8 Copy_u8Peripheral )
{

	switch( Copy_u8BusName)
	{

	case AHB1 : SET_BIT(RCC->AHB1ENR,Copy_u8Peripheral );break;
	case AHB2 : SET_BIT(RCC->AHB2ENR,Copy_u8Peripheral );break;
	case APB1 : SET_BIT(RCC->APB1ENR,Copy_u8Peripheral );break;
	case APB2 : SET_BIT(RCC->APB2ENR,Copy_u8Peripheral );break;
	}

}
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
void RCC_VoidDisableCLK(u8 Copy_u8BusName , u8 Copy_u8Peripheral )
{

	switch( Copy_u8BusName)
	{

	case AHB1 : CLR_BIT(RCC->AHB1ENR,Copy_u8Peripheral );break;
	case AHB2 : CLR_BIT(RCC->AHB2ENR,Copy_u8Peripheral );break;
	case APB1 : CLR_BIT(RCC->APB1ENR,Copy_u8Peripheral );break;
	case APB2 : CLR_BIT(RCC->APB2ENR,Copy_u8Peripheral );break;
	}

}

//-----------------------------------------------------------------------------

