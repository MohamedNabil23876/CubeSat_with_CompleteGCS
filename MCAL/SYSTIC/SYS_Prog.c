/*
 * SYS_Prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */
// LIB

// LIB
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

// MACL Drivers
// SYSTIC
#include "SYS_Interface.h"
#include "SYS_Pri.h"
#include "SYS_cfg.h"

static  void (*GS_SET_CallBack)(void);
static volatile u8 G_u8Sinle_flag;
void MSTK_VoidInit(void)
{
	// Set CLK Source
#if STK_CLKSOURCE==SYSCLK
	SET_BIT(SYSTICK->STK_CTRL,CLKSOURCE);
#elif  STK_CLKSOURCE==AHB_BY_8_
	CLR_BIT(SYSTICK->STK_CTRL,CLKSOURCE);
#endif
	// INT or polling
#if  STK_TICKINT==NO_INT
	CLR_BIT(SYSTICK->STK_CTRL,TICKINT);
#elif STK_TICKINT==INT
	SET_BIT(SYSTICK->STK_CTRL,TICKINT);
#endif
}
void MSTK_VoidStartTimer(void)
{
	SET_BIT(SYSTICK->STK_CTRL,ENABLE);


}
void MSTK_VoidStopTimer(void)
{
	CLR_BIT(SYSTICK->STK_CTRL,ENABLE);
}
void MSTK_VoidSETBusywait(u32 Copy_u32Ticks)
{
	// reset timer value
	SYSTICK->STK_VAL=0;
	// load timer value
	SYSTICK->STK_LOAD=Copy_u32Ticks;
	// start timer
	MSTK_VoidStartTimer();
	//wait flag
	while((GET_BIT(SYSTICK->STK_CTRL,COUNT_FLAG))!=1);
	// Stop timer
	MSTK_VoidStopTimer();


}
void MSTK_VoidSETInterval_Single(u32 Copy_u32Ticks ,void (*CallBackfun)(void))
{
	G_u8Sinle_flag=1;
     // SET Call Back
	if ((CallBackfun)!=NULL)
	{
		GS_SET_CallBack=CallBackfun;
	}
	else
	{
		// nothing
	}
	// reset timer value
	SYSTICK->STK_VAL=0;
	// load timer value
	SYSTICK->STK_LOAD=Copy_u32Ticks;
	// start timer
	MSTK_VoidStartTimer();



}
void MSTK_VoidSETInterval_Periodic(u32 Copy_u32Ticks ,void (*CallBackfun)(void))
{
	G_u8Sinle_flag=0;
	// SET Call Back
		if ((CallBackfun)!=NULL)
		{
			GS_SET_CallBack=CallBackfun;
		}
		else
		{
			// nothing
		}
		// reset timer value
		SYSTICK->STK_VAL=0;
		// load timer value
		SYSTICK->STK_LOAD=Copy_u32Ticks;
		// start timer
		MSTK_VoidStartTimer();

}
u32 MSTK_VoidGETElapedTime(void)
{
	u32 Local_ElapedTime;
	Local_ElapedTime =((SYSTICK->STK_LOAD)-(SYSTICK->STK_VAL));
	return Local_ElapedTime;

}
u32 MSTK_VoidGETRemainigTime(void)
{
	u32 Local_RemainigTime;
	Local_RemainigTime =(SYSTICK->STK_VAL);
		return Local_RemainigTime;

}

void Systick_Handler(void)
{
	if ((GS_SET_CallBack)!=NULL)
	{
		GS_SET_CallBack();
	}
	else
	{
		// nothing
	}
	if (G_u8Sinle_flag==1)
	{
		G_u8Sinle_flag=0;
	CLR_BIT(SYSTICK->STK_CTRL,ENABLE);
	}
}
