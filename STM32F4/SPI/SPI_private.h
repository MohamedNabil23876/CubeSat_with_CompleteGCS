/*********************************************************************************************************************
  *   FILE DESCRIPTION
  *  -------------------------------------------------------------------------------------------------------------------
  *         File:  SPI_PRIVATE_H
  *       Module:  -
  *
  *  Description:   header for the SPI registers and their bits
  *
  *********************************************************************************************************************/
#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H


 /**********************************************************************************************************************
 * REGISTERS DEFINITIONS
 *********************************************************************************************************************/
 typedef struct
{
   volatile  u32 CR1     ;
   volatile  u32 CR2     ;
   volatile  u32 SR      ;
   volatile  u32 DR      ;
   volatile  u32 CRCPR   ;
   volatile  u32 RXCRCR  ;
   volatile  u32 TXCRCR  ;
   volatile  u32 I2SCFGR ;
   volatile  u32 I2SPR   ;
}SPI_Register;

#define SPI1 ((volatile SPI_Register *) 0x40013000)


/*CR1 Register Bits*/

#define BIDIMODE   	15
#define BIDIOE		14
#define CRCEN		13
#define CRCNEXT		12
#define DFF			11
#define RXONLY		10
#define SSM			9
#define SSI			8
#define LSBFIRST	7
#define SPE			6
#define BR			3
#define MSTR		2
#define CPOL		1
#define CPHA        0

#endif
