/*********************************************************************************************************************
  *   FILE DESCRIPTION
  *  -------------------------------------------------------------------------------------------------------------------
  *         File:  USART_H
  *       Module:  -
  *
  *  Description:   header for the USART registers and their bits    
  *  
  *********************************************************************************************************************/
#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H
 
 
 /**********************************************************************************************************************
 * REGISTERS DEFINITIONS
 *********************************************************************************************************************/
 
 typedef struct {
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;	
	volatile u32 CR1;	
	volatile u32 CR2;	
	volatile u32 CR3;
	volatile u32 GTPR;	
	
}USART_t;

#define USART1 ((volatile USART_t *)(0x40011000))

#define USART2 ((volatile USART_t *)(0x40004400))

#define USART3 ((volatile USART_t *)(0x40004800))

#define UART4 ((volatile USART_t *)(0x40004C00))

#define UART5 ((volatile USART_t *)(0x40004C00))

#define USART6 ((volatile USART_t *)(0x40011400))

#define UART7 ((volatile USART_t *)(0x40007800))

#define UART8 ((volatile USART_t *)(0x40007C00))

#endif

