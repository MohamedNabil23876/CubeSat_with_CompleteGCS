/*
 * EXTI_Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_


#define EXTI_RISING   1
#define EXTI_FALLING  2
#define EXTI_ON_CANGE 3

#define EXTI_LINE0        0
#define EXTI_LINE1        1
#define EXTI_LINE2        2
#define EXTI_LINE3        3
#define EXTI_LINE4        4
#define EXTI_LINE5        5
#define EXTI_LINE6        6
#define EXTI_LINE7        7
#define EXTI_LINE8        8
#define EXTI_LINE9        9
#define EXTI_LINE10       10
#define EXTI_LINE11       11
#define EXTI_LINE12       12
#define EXTI_LINE13       13
#define EXTI_LINE14       14
#define EXTI_LINE15       15
#define EXTI_LINE16       16

void MEXTI_voidInit(void);
void MEXTI_voidEnabilLine(u8 copy_u8treger , u8 Copy_u8LineNum);
void MEXTI_voidDisableLine(u8 Copy_u8LineNum);
void MEXTI_VoidS_WINT(u8 Copy_u8LineNum);
void MEXTI_VoidSetEdeg(u8 copy_u8treger , u8 Copy_u8LineNum );
void MEXTI_VoidSETCAllBAck (u8 Copy_u8LineNum , void (*Ptr_CBack)(void));



#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
