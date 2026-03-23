/*
 * SYS_Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef MCAL_SYSTIC_SYS_INTERFACE_H_
#define MCAL_SYSTIC_SYS_INTERFACE_H_

void MSTK_VoidInit(void);
void MSTK_VoidStartTimer(void);
void MSTK_VoidStopTimer(void);
void MSTK_VoidSETBusywait(u32 Copy_u32Ticks);
void MSTK_VoidSETInterval_Single(u32 Copy_u32Ticks ,void (*CallBackfun)(void));
void MSTK_VoidSETInterval_Periodic(u32 Copy_u32Ticks ,void (*CallBackfun)(void));
u32 MSTK_VoidGETElapedTime(void);
u32 MSTK_VoidGETRemainigTime(void);

#endif /* MCAL_SYSTIC_SYS_INTERFACE_H_ */
