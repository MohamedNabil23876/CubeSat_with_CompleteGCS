/*
 * NVIC_Pri.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef NVIC_NVIC_PRI_H_
#define NVIC_NVIC_PRI_H_

#define NVIC_BASE_ADDRESS 0xE000E100UL
// SCB

#define SCB_BASE_ADDRESS 0xE000ED00UL

#define AIRCR_OFFSET 0x0CUL
#define SCB_AIRCR  *((volatile u32*)(SCB_BASE_ADDRESS+AIRCR_OFFSET))

#define SHPR1_OFFSET 0x18UL
#define SCB_SHPR1  *((volatile u32*)(SCB_BASE_ADDRESS+SHPR1_OFFSET))

#define SHPR2_OFFSET 0x1CUL
#define SCB_SHPR2  *((volatile u32*)(SCB_BASE_ADDRESS+SHPR2_OFFSET))

/*#define SHPR1_OFFSET 0x18UL
#define SCB_SHPR3  *((volatile u32*)(SCB_BASE_ADDRESS+SHPR1_OFFSET))*/


typedef struct {
	u32 ISER[32];
	u32 ICER[32];
	u32 ISPR[32];
	u32 ICPR[32];
	u32 IABR[32];
	u32 RESE[32];
	u8 IPR[128];

}NVIC_REG_Cfg;

#define NVIC ((NVIC_REG_Cfg*)(0xE000E100UL))


#define VECT_KEY_PASS				0x05FA0000

#endif /* NVIC_NVIC_PRI_H_ */
