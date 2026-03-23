/*
 * UART_Interface.h
 *
 *  Created on: Mar 3, 2023
 *      Author: hp
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#include  "USART_Pri.h"


//
#define USART1_BASE_ADD 0x40011000UL
#define USART2_BASE_ADD 0x40004400UL
#define USART6_BASE_ADD 0x40011400UL
// USART Registers

typedef struct
{
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;

}USART_Reg_Cfg;



//Pointer to sTruct point to USART Registers
#define USART1   (( USART_Reg_Cfg * )0x40011000)
#define USART2   (( USART_Reg_Cfg * )0x40014400)
#define USART6   (( USART_Reg_Cfg * )0x40011400)


// structure to define USART
typedef struct
{
	u32 USART_Baudrate;
	u8 USART_DataLenth; // 8 or 9
	u8 USART_NumStopBits; // 1 or 2
	u8 USART_ParityEn;
	u8 USART_ParitySelection; // even or odd
	u8 USART_TransferDirction;  // TX or RX or TX&RX
	u8 USART_HardwareFlowControl;
	u8 USART_OverSampling;// 8 or 16


}USART_Cfg;

// structure  to handle USART CLK
typedef struct
{
	u8 USART_CLK_Output;
	u8 USART_CLK_Polarity;
	u8 USART_CLK_Phase;
	u8 USART_CLK_Pulse;

}USART_CLK_Inti;

// OverSamplig Configuration

#define OVER_SAMPLING_16 0
#define OVER_SAMPLING_8  1

// TX & RX Configuration

#define TX_ONLY 0
#define RX_ONLY 1
#define TX_RX   2

/*******************************************************************************************
                   These values ​​are set forth in USART_Cfg
*******************************************************************************************/
// Parity Configuration
#define EVEN_PARITY         0
#define ODD_PARITY          1

//date Length  Configuration
#define MODE_8BIT			0
#define MODE_9BIT			1

// Stop bit  Configuration
#define STOP_BIT_1			0
#define STOP_BIT_0_5		1
#define STOP_BIT_2			2
#define STOP_BIT_1_5		3

// uArt  Configuration
#define ENABLE				1
#define DISABLE				0
/********************************************************************************************/

/************************************************************************************************************
 * Function Name:  MUSART_void_Init
 *
 * Description:	the function initialize the required USART configuration  options
 *
 * Parameters: 1- A_Init : pointer to USART_Cfg structure which holds the USART configurations
 *             2- A_Init : pointer to USART_CLK_Inti structure which holds the USART  clock configurations
 *             3- A_Init : pointer to USART_Reg_Cfg structure Specifies the USART number
 *
 * Return:	void
 ***********************************************************************************************************/
void MUSART_void_Init (USART_Cfg * A_Init , USART_CLK_Inti * A_Clk_Init , USART_Reg_Cfg * A_USARTx);

void MUSART_VoidEnable(USART_Reg_Cfg * A_USARTx);

void MUSART_VoidDisable(USART_Reg_Cfg * A_USARTx);

void MUSART_VoidSendByte(USART_Reg_Cfg * A_USARTx, u8 A_Byte);

void MUSART_VoidSendString(USART_Reg_Cfg * A_USARTx, char const  * A_PtrStr);

u8   MUSART_u8ReceiveBytesynchNonBlocking(USART_Reg_Cfg * A_USARTx);

u8   MUSART_u8ReceiveByteAsynch(USART_Reg_Cfg * A_USARTx);

void MUSART1_voidSetCallBack( void (*ptr) (void) );
void MUSART2_voidSetCallBack( void (*ptr) (void) );
void MUSART6_voidSetCallBack( void (*ptr) (void) );



#endif /* MCAL_UART_UART_INTERFACE_H_ */
