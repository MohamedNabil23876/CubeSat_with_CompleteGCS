/*
 * EXTI_Pri.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef MCAL_EXTI_EXTI_PRI_H_
#define MCAL_EXTI_EXTI_PRI_H_

#define ENABLE  1
#define DISABLE 0

#define RISING  1
#define FALLING 2
#define ON_CANGE 3


#define EXTI_BASE_ADDRESS 0x40013C00UL

typedef struct
{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;

}EXTI_REG_Cfg;


#define EXTI ((volatile EXTI_REG_Cfg *) (EXTI_BASE_ADDRESS))


#endif /* MCAL_EXTI_EXTI_PRI_H_ */
