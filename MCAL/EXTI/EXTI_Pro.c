/*
 * EXTI_Pro.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */


/*
 * GPIO_Pro.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */
// LIB
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

// MACL Drivers
// EXTI
#include "EXTI_Pri.h"
#include "EXTI_cfg.h"
#include "EXTI_Interface.h"

static  void (*GlobalPtrCback)(void);
void MEXTI_voidInit(void)
{
  EXTI->PR=0xffffffff;
  EXTI->IMR=0;
  EXTI->IMR|=(EXTI_LINE_0_EN<<0);

}
void MEXTI_voidEnabilLine(u8 copy_u8treger , u8 Copy_u8LineNum)
{
	if (Copy_u8LineNum<16)
	{
		SET_BIT(EXTI->IMR,Copy_u8LineNum);

		switch (copy_u8treger)
		{
		case  EXTI_RISING  : SET_BIT(EXTI->RTSR,Copy_u8LineNum);
							 CLR_BIT(EXTI->FTSR,Copy_u8LineNum);
							 break;
		case EXTI_FALLING  : SET_BIT(EXTI->FTSR,Copy_u8LineNum);
		                     CLR_BIT(EXTI->RTSR,Copy_u8LineNum);
		                     break;
		case EXTI_ON_CANGE : SET_BIT(EXTI->RTSR,Copy_u8LineNum);
		 	 	 	 	 	 SET_BIT(EXTI->FTSR,Copy_u8LineNum);
		 	 	 	 	 	 break;

		}
	}

}
void MEXTI_voidDisableLine( u8 Copy_u8LineNum)
{
	if (Copy_u8LineNum<16)
		{
			CLR_BIT(EXTI->IMR,Copy_u8LineNum);
		}

}
void MEXTI_VoidS_WINT(u8 Copy_u8LineNum)
{
	if (Copy_u8LineNum<16)
			{
				SET_BIT(EXTI->SWIER,Copy_u8LineNum);
			}

}
void MEXTI_VoidSetEdeg(u8 copy_u8treger , u8 Copy_u8LineNum )
{
	if (Copy_u8LineNum<16)
		{


			switch (copy_u8treger)
			{
			case  EXTI_RISING  : SET_BIT(EXTI->RTSR,Copy_u8LineNum);
								 CLR_BIT(EXTI->FTSR,Copy_u8LineNum);
								 break;
			case EXTI_FALLING  : SET_BIT(EXTI->FTSR,Copy_u8LineNum);
			                     CLR_BIT(EXTI->RTSR,Copy_u8LineNum);
			                     break;
			case EXTI_ON_CANGE : SET_BIT(EXTI->RTSR,Copy_u8LineNum);
			 	 	 	 	 	 SET_BIT(EXTI->FTSR,Copy_u8LineNum);
			 	 	 	 	 	 break;

			}
		}

}
void MEXTI_VoidSETCAllBAck (u8 Copy_u8LineNum , void (*Ptr_CBack)(void))
{
	if (Copy_u8LineNum <= 16)
	{
		switch(Copy_u8LineNum)
		{
		case EXTI_LINE0 :GlobalPtrCback=Ptr_CBack;
			break;
		}
	}
}
void EXTI0_IRQHandler(void)
{
	if (GlobalPtrCback!=NULL)
	{
	GlobalPtrCback();
	}
	SET_BIT(EXTI-> PR,EXTI_LINE0);
}
