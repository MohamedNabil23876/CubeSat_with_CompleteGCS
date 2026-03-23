/*
 * SYS_Pri.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef MCAL_SYSTIC_SYS_PRI_H_
#define MCAL_SYSTIC_SYS_PRI_H_


#define SYSTICK_BASE_ADD 0xE000ED00UL

typedef struct
{
	u32 STK_CTRL ;
	u32 STK_LOAD ;
	u32 STK_VAL ;
	u32 STK_CALIB ;


} SYSTICK_Reg_Cfg;


#define SYSTICK ((volatile SYSTICK_Reg_Cfg * )(SYSTICK_BASE_ADD))

#define SYSCLK 1
#define AHB_BY_8_  0

#define INT 1
#define NO_INT 0


#define CLKSOURCE   2
#define TICKINT     1
#define ENABLE      0
#define COUNT_FLAG 16
#endif /* MCAL_SYSTIC_SYS_PRI_H_ */

