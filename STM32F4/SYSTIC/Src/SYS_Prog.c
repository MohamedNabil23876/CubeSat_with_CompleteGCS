/*
 * SYS_Prog.c
 *
 *  Created on: Jul 15, 2022
 *      Author: nabil
 */

#include "SYS_Interface.h"
#include "STM32f411XX.h"
void STK_VoidDelayMs(u32 Copy_u8DelayMs)
{

	u32 Local_u32Value;
	/*Select ClK Source*/
	/*1.Program reload value.*/
	Local_u32Value=Copy_u8DelayMs*2000;
	SYS_LOAD = Local_u32Value;
	/*2. Clear current value.*/
	SYS_VAL=0;
	/*3. Program Control and Status register*/
	SYS_CTRL |= (1<<0);
	SYS_CTRL &= ~(1<<2);


	while((((SYS_CTRL)>>16)&1)==0);
	SYS_CTRL &= ~(1<<0);




}
