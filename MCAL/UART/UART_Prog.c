/*
 * UART_Prog.c
 *
 *  Created on: Mar 3, 2023
 *      Author: hp
 */

// LIB
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_Interface.h"
#include  "USART_Pri.h"
#include "UART_Cfg.h"


void (*MUSART1_CallBack)(void);
void (*MUSART2_CallBack)(void);
void (*MUSART6_CallBack)(void);

USART_Reg_Cfg *G_Ptr_SR=NULL;

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
void MUSART_void_Init (USART_Cfg * A_Init , USART_CLK_Inti * A_Clk_Init , USART_Reg_Cfg * A_USARTx)
{
	switch (A_Init->USART_OverSampling)
	{
	// SET BaudRate
	case  OVER_SAMPLING_16 : (A_USARTx->USART_BRR)=(UART_DIV_SAMPLING16(__PCLK__,A_USARTx->USART_BRR));break;
	case  OVER_SAMPLING_8  : (A_USARTx->USART_BRR)=(UART_DIV_SAMPLING8(__PCLK__,A_USARTx->USART_BRR));break;
	}
	// SER CR1 By  A_Init values
	A_USARTx->USART_CR1 = (A_Init->USART_OverSampling <<MUSART_CR1_OVER8_BIT)|
			              (A_Init->USART_DataLenth<<MUSART_CR1_M_BIT)        |
			              (A_Init->USART_ParityEn<<MUSART_CR1_PCE_BIT)       |
			              (A_Init->USART_ParitySelection<<MUSART_CR1_PS_BIT) ;
    // Select UART Transmit only or Receive  only or both
	switch (A_Init->USART_TransferDirction)
	{
	case  TX_ONLY : SET_BIT(A_USARTx->USART_CR1,MUSART_CR1_TE_BIT);break;
	case  RX_ONLY : SET_BIT(A_USARTx->USART_CR1,MUSART_CR1_RE_BIT);break;
	case  TX_RX   : SET_BIT(A_USARTx->USART_CR1,MUSART_CR1_TE_BIT);
		            SET_BIT(A_USARTx->USART_CR1,MUSART_CR1_RE_BIT);break;
	}
    // SET CLK and Stop Bit in CR2
	A_USARTx->USART_CR2 =   (A_Init->USART_NumStopBits<<MUSART_CR2_STOP_BIT)       |
			                (A_Clk_Init->USART_CLK_Output <<MUSART_CR2_CLKEN_BIT)  |
							(A_Clk_Init->USART_CLK_Phase <<MUSART_CR2_CPHA_BIT)    |
							(A_Clk_Init->USART_CLK_Polarity <<MUSART_CR2_CPOL_BIT) |
							(A_Clk_Init->USART_CLK_Pulse <<MUSART_CR2_LBCL_BIT);

	A_USARTx->USART_SR=0;


}
/********************************************************************************************/

void MUSART_VoidEnable(USART_Reg_Cfg * A_USARTx)
{
	SET_BIT(A_USARTx->USART_CR1,MUSART_CR1_UE_BIT);
}
/********************************************************************************************/

void MUSART_VoidDisable(USART_Reg_Cfg * A_USARTx)
{
	CLR_BIT(A_USARTx->USART_CR1,MUSART_CR1_UE_BIT);
}
/********************************************************************************************/
void MUSART_VoidSendByte(USART_Reg_Cfg * A_USARTx, u8 A_Byte)
{
	// check if USART Data Register Empty or not
	while(GET_BIT(A_USARTx->USART_SR,MUSART_SR_TXE_BIT)==0);
	A_USARTx->USART_DR=A_Byte; // Send data
	while(GET_BIT(A_USARTx->USART_SR,MUSART_SR_TC_BIT)==0); // check if Data is transferred
	CLR_BIT(A_USARTx->USART_SR,MUSART_SR_TC_BIT);// Clear flag



}
/********************************************************************************************/
void MUSART_VoidSendString(USART_Reg_Cfg * A_USARTx, char const  * A_PtrStr)
{

	 u16 Local_Counter=0;
	 while(A_PtrStr[Local_Counter] != '\0')
	 {
		 MUSART_VoidSendByte(A_USARTx,A_PtrStr[Local_Counter]);
		 Local_Counter++;
	 }


}
/********************************************************************************************/
u8   MUSART_u8ReceiveByteSynchNonBlocking(USART_Reg_Cfg * A_USARTx)
{
	u32 Local_TimeOut=0;
	u8 Local_Data=0;
	while((GET_BIT(A_USARTx->USART_SR,MUSART_SR_RXNE_BIT)==0) && (Local_TimeOut<THRESHOLD_VALUE))
	{
		Local_TimeOut++;
	};
	if(Local_TimeOut==THRESHOLD_VALUE)
	{
		Local_Data=255;
	}
	else
	{
		Local_Data=A_USARTx->USART_DR;
	}
	return Local_Data;


}
/********************************************************************************************/
u8   MUSART_u8ReceiveByteAsynch(USART_Reg_Cfg * A_USARTx)
{
	return A_USARTx->USART_DR;
}


void MUSART1_voidSetCallBack( void (*ptr) (void) )
{
	if (ptr!=NULL)
	{
	MUSART1_CallBack = ptr ;
	}
	else
	{

	}
}

void MUSART2_voidSetCallBack( void (*ptr) (void) )
{

	if (ptr!=NULL)
	{
	MUSART2_CallBack = ptr ;
	}
	else
	{

	}
}

void MUSART6_voidSetCallBack( void (*ptr) (void) )
{
	if (ptr!=NULL)
	{
	MUSART6_CallBack = ptr ;
	}
	else
	{

	}
}

void USART1_IRQHandler(void)
{
	if (MUSART1_CallBack!=NULL)
	{
		MUSART1_CallBack();
		G_Ptr_SR= (USART_Reg_Cfg *)(0x40011000);
		G_Ptr_SR->USART_SR=0;

	}
	else
	{

	}

}

void USART2_IRQHandler(void)
{
	if (MUSART2_CallBack!=NULL)
	{
		MUSART2_CallBack();
		G_Ptr_SR= (USART_Reg_Cfg *)(0x40014400);
		G_Ptr_SR->USART_SR=0;

	}
	else
	{

	}
}

void USART6_IRQHandler(void)
{
	if (MUSART6_CallBack!=NULL)
	{
		MUSART6_CallBack();
		G_Ptr_SR= (USART_Reg_Cfg *)(0x40011400);
		G_Ptr_SR->USART_SR=0;

	}
	else
	{

	}
}
