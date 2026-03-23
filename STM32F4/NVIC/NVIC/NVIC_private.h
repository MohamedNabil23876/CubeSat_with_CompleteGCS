/*********************************************************************************************************************
  *   FILE DESCRIPTION
  *  -------------------------------------------------------------------------------------------------------------------
  *         File:  NVIC_PRIVATE_H
  *       Module:  -
  *
  *  Description:   header for the NVIC registers and their bits    
  *  
  *********************************************************************************************************************/
#ifndef __NVIC_PRIVATE_H__
#define __NVIC_PRIVATE_H__

typedef struct {
	volatile u32 ISER[8];	
}ISER;

#define NVIC_ISER ((volatile ISER *)(0xE000E100))

/*******************************************************************/

typedef struct {	
	volatile u32 ICER[8];	
}ICER;

#define NVIC_ICER ((volatile ICER *)(0xE000E100+0x180))

/********************************************************************/

typedef struct {	
	volatile u32 ISPR[8];	
}ISPR;
#define NVIC_ISPR ((volatile ISPR *)(0xE000E100+0x200))
/********************************************************************/

typedef struct {
	volatile u32 ICPR[8];	
}ICPR;

#define NVIC_ICPR ((volatile ICPR *)(0xE000E100+0x280))

/********************************************************************/
typedef struct {
	volatile u32 IABR[8];	
}IABR;
#define NVIC_IABR ((volatile IABR *)(0xE000E100+0x300))
/********************************************************************/

typedef struct {
	volatile u32 IPR[60];
}IPR;
#define NVIC_IPR ((volatile IPR *)(0xE000E100+0x400))
/********************************************************************/

#define NVIC_STIR_OFFSET          0xE00

#define NVIC_STIR           *(( volatile u32 *) ( 0xE000E100 +  NVIC_STIR_OFFSET  ))

/*********************************************************************************************************************
  *   
  *  SCB regigster used for NVIC     
  *  
  *********************************************************************************************************************/
#define SCB_AIRCR   *(( volatile u32 *) ( 0xE000E100 +  0x0C  ))

#define AIRCR_VECTKEY_Bit   16
#define AIRCR_PRIGROUP_Bit  8
#define VECTKEY 0x5FA0
#define AIRCR_test 0x5FA00400

#endif //  __NVIC_PRIVATE_H__