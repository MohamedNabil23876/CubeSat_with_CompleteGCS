/*********************************************************************************************************************
  *   FILE DESCRIPTION
  *  -------------------------------------------------------------------------------------------------------------------
  *         File:  EXTI_PRIVATE_H
  *       Module:  -
  *
  *  Description:   header for the EXTI registers and their bits    
  *  
  *********************************************************************************************************************/
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H
 
 
 /**********************************************************************************************************************
 * EXTI REGISTERS DEFINITIONS
 *********************************************************************************************************************/
 
 #define EXTI_IMR			*((volatile u32*)0x40013C00)
 #define EXTI_EMR			*((volatile u32*)0x40013C04)
 #define EXTI_RTSR			*((volatile u32*)0x40013C08)
 #define EXTI_FTSR			*((volatile u32*)0x40013C0C)
 #define EXTI_SWIER			*((volatile u32*)0x40013C10)
 #define EXTI_PR			*((volatile u32*)0x40013C14)
 
 /**********************************************************************************************************************
 * System config REGISTERS For EXTI DEFINITIONS
 *********************************************************************************************************************/
  typedef struct {
	volatile u32 SYSCFG_EXTICR[4];	
}SYSCFG_EXTICR_t;

#define EXTICR ((volatile SYSCFG_EXTICR_t *)(0xE000E100+0x100))
#endif //  __EXTI_PRIVATE_H__