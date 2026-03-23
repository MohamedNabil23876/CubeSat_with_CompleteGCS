/*
 * RTOS_Pro.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */
// LIB
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

// MCAL

#include "../MCAL/SYSTIC/SYS_Interface.h"


// RTOS
#include "RTOS_Interface.h"
#include "RTOS_Cfg.h"
#include "RTOS_Pri.h"

Task System_Task[MAX_NUM_OF_TASK]={0};
Task Empty={0};
u8 TaskTiming[MAX_NUM_OF_TASK];
u8 G_Periodicity;


void RTOS_VoidStartOS(void)
{
	//MSTK_VoidInit();
	MSTK_VoidSETInterval_Periodic(5000,schduler);

}

u8 RTOS_u8CreatTasck(void (* Copy_Handler)(void),u8 Copy_u8Periodicity, u8 copy_u8Priority, u8 Copy_u8FriestD )
{

	u8 Local_Error_state=OK;

	// check task priority < Array range
	if (copy_u8Priority<MAX_NUM_OF_TASK)
	{
		if (System_Task[copy_u8Priority].TaskHandler==0)
		{
			( System_Task[copy_u8Priority].TaskHandler)=Copy_Handler;
			(System_Task[copy_u8Priority].Periodicity) =Copy_u8Periodicity;
			TaskTiming[copy_u8Priority]				   =Copy_u8FriestD;
			(System_Task[copy_u8Priority].Task_Run_State) =Runing;

			G_Periodicity=Copy_u8Periodicity;
		}
		else
		{
			Local_Error_state=RESERVED;
		}
	}
	else
	{
		Local_Error_state=RONG_PRIORITY;
	}

	return Local_Error_state;

}

void schduler (void)
{
	u8 Local_Counter=0;
	// loop for all task
	for(Local_Counter=0;Local_Counter<MAX_NUM_OF_TASK;Local_Counter++)

	{
		// check the content of task
		if (System_Task[Local_Counter].TaskHandler!=0)
		{
			if (System_Task[Local_Counter].Task_Run_State==Runing)
			{

			if(TaskTiming[Local_Counter]==0)
			{
				// run task
				System_Task[Local_Counter].TaskHandler();
				TaskTiming[Local_Counter]= G_Periodicity; //reload task time

			}
			else
			{
				(TaskTiming[Local_Counter])--;
			}
			}
		}

	}

}
void schduler_2 (void)
{
	static u32 Local_u32TickCounter=0;
	  u8 Local_Counter;
	// loop for all task
	  Local_u32TickCounter++;
	for(Local_Counter=0;Local_Counter<MAX_NUM_OF_TASK;Local_Counter++)

	{
		// check the content of task
		if ((Local_u32TickCounter % System_Task[Local_Counter].Periodicity )==0)
		{
			if (System_Task[Local_Counter].TaskHandler!=NULL)
			{

				// run task
				System_Task[Local_Counter].TaskHandler();
				// TaskTiming[Local_Counter]= G_Periodicity; //reload task time

			}
			else
			{

			}
			}
		}

	}




u8 RTOS_u8DeletTask (u8 copy_u8Priority)
{
	u8 Local_Error_state=OK;
	if (System_Task[copy_u8Priority].TaskHandler!=0)
	{
		//remove task
		System_Task[copy_u8Priority]=Empty;
	}
	else
	{
		Local_Error_state=RONG_PRIORITY;
	}
	return Local_Error_state;
}

u8 RTOS_u8SuspendTask (u8 copy_u8Priority)
{
	u8 Local_Error_state=OK;
	if (System_Task[copy_u8Priority].TaskHandler!=0)
	{
		//Suspended task
		(System_Task[copy_u8Priority].Task_Run_State) =Suspended;
	}
	else
	{
		Local_Error_state=RONG_PRIORITY;
	}
	return Local_Error_state;

}

u8 RTOS_u8ResumeTask (u8 copy_u8Priority)
{
	u8 Local_Error_state=OK;
	if (System_Task[copy_u8Priority].TaskHandler!=0)
	{
		//Resume task run
		(System_Task[copy_u8Priority].Task_Run_State) =Runing;
	}
	else
	{
		Local_Error_state=RONG_PRIORITY;
	}
	return Local_Error_state;

}

