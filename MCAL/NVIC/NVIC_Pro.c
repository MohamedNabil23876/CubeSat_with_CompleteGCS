/*
 * NVIC_Pro.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */
//LIB
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

// MACL Drivers Files
// NVIC
#include "NVIC_Pri.h"
#include "NVIC_Cfg.h"
#include "NVIC_Interface.h"

static u32   volatile Global_u32SetPriority;
/******************************************************************************
 * Function Name:  MNVIC_VoidEnablePeripheral
 * Description:	this enable INT of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id
 * Return:	ErrorState , Type:u8
 *
 ******************************************************************************/
void MNVIC_VoidEnablePeripheral (u8 Copy_u8PriId )
{
	// Atomic access to enable INT in NVIC
	NVIC->ISER[Copy_u8PriId/32]=1<<(Copy_u8PriId%32);
}
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVIC_VoidEnablePeripheral
 * Description:	this enable INT of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id
 * Return:	ErrorState , Type:u8
 *
 ******************************************************************************/
void MNVIC_VoidDisablePeripheral (u8 Copy_u8PriId )
{
	// Atomic access to disable INT in NVIC
		NVIC->ICER[Copy_u8PriId/32]=1<<(Copy_u8PriId%32);
}
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVIC_VoidSetPending
 * Description:	this set INT  pending flag of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id
 * Return:	void
 *
 ******************************************************************************/
void MNVIC_VoidSetPending (u8 Copy_u8PriId )
{
	// Atomic access to Set pending flag  INT in NVIC
	NVIC->ISPR[Copy_u8PriId/32]=1<<(Copy_u8PriId%32);
}
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVIC_VoidClearPending
 * Description:	this Clear INT Pending flag  of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id
 * Return:	void
 *
 ******************************************************************************/
void MNVIC_VoidClearPending(u8 Copy_u8PriId )
{

	// Atomic access to Clear pending flag  INT in NVIC
	NVIC->ICPR[Copy_u8PriId/32]=1<<(Copy_u8PriId%32);

}
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVICGetActiveFlag
 * Description:	this enable GET Active flag  of the peripheral in NVIC
 * Parameters: 1- Copy_u8PriId: INT id  , *Copy_u8Flag
 * Return:	 void
 *
 ******************************************************************************/
void MNVICGetActiveFlag(u8 Copy_u8PriId , u8 *Copy_u8Flag)
{

	*Copy_u8Flag= ((NVIC->IABR[Copy_u8PriId/32] & (1<<Copy_u8PriId%32))>>Copy_u8PriId%32);

}
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
void MNVICSetPriorityCfg(u8 Copy_u8PriorityOption )
{
	// save  the option of priority in static GLO VAR
	Global_u32SetPriority = VECT_KEY_PASS|(Copy_u8PriorityOption<<8);
	SCB_AIRCR=Global_u32SetPriority;// set priority option in SCB
}
/*============================================================================*/

/******************************************************************************
 * Function Name:  MNVICSetPriority
 * Description: the function Set the interrupt  Priority Field
 *              number of groups and number of SUB
 * Parameters: 1- Copy_u8IntID ,Copy_u8GruopPriority ,Copy_u8SubPriority
 * Return:	 void
 *
 ******************************************************************************/
void MNVICSetPriority(s8 Copy_u8IntID ,u8 Copy_u8GruopPriority ,u8 Copy_u8SubPriority )
{
	u8 Local_Priority =Copy_u8SubPriority |Copy_u8GruopPriority<<((Global_u32SetPriority-0x5FA300)/256);

    // SCB core peripheral
	// core peripheral A negative number so that I know it
	if (Copy_u8IntID < 0)
	{
		if (Copy_u8IntID == MEM_MANGE || Copy_u8IntID ==BUS_FAULT || Copy_u8IntID==USEGE_FAULT )
		{
			Copy_u8IntID +=3;
			SCB_SHPR1= Local_Priority <<((8*Copy_u8IntID)+4);
		}
		else if (Copy_u8IntID == SV_CALL)
		{
			Copy_u8IntID +=7;
			SCB_SHPR2= Local_Priority <<((8*Copy_u8IntID)+4);
		}
		else
		{

		}


	}
	else if (Copy_u8IntID>=0) // NVIC INT
	{
		NVIC->IPR[Copy_u8IntID]=((Local_Priority)+4);

	}
	else
	{

	}




}
/*============================================================================*/




