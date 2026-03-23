/*********************************************************************************************************************
  *   FILE DESCRIPTION
  *  -------------------------------------------------------------------------------------------------------------------
  *         File:  SPI_INTERFACE_H
  *       Module:  -
  *
  *  Description:   header for the SPI   interfacing
  *
  *********************************************************************************************************************/
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

#include "STD_TYPES.h"
#include "GPIO_interface.h"
typedef enum{
	UNI, /*FULL*/
	BI,  /*HALF*/
}SPI_Dir_t;

typedef enum{
	RX_TX,   /*Full*/
	RX_ONLY, /*Broadcasting*/
}RX_Only_t;

 typedef enum {
	  D8BITS,
	  D16BITS
  }SPI_DataSize_t;

typedef enum {
  	Sample_SetUp,
  	SetUp_Sample,
  }SPI_CPHASE_t;

typedef enum {
  	Rising_Faling,
  	Faling_Rising,
  }SPI_CPOL_t;

  typedef enum {
	  CRC_ENABLE,
	  CRC_DISABLE,
  }SPI_CRC_Mode_t;

  typedef enum{
	  SSM_DISABLE,
	  SSM_ENABLE,
  }SPI_SSM_t;

  typedef enum {
	  MSB,
	  LSB,
  }SPI_FirstBit_t;

  typedef enum {
	  f_2,
	  f_4,
	  f_8,
	  f_16,
	  f_32,
	  f_64,
	  f_128,
	  f_256,
  }SPI_BR_t;

typedef enum {
  	Motorola,
  	TI,
  }SPI_FRF_t;

typedef struct {
	SPI_Dir_t	   	 SPI_Mode;
	SPI_DataSize_t	 SPI_DataSize;
	SPI_CPHASE_t	 SPI_Phase;
	SPI_CPOL_t 		 SPI_Polarity;
	SPI_BR_t 		 SPI_BR;
	SPI_FirstBit_t   SPI_FirstBit;
	SPI_SSM_t        SPI_SSM;
	SPI_CRC_Mode_t       SPI_CRC;
	SPI_FRF_t		 SPI_FrameFormate;
}SPI_MasterConfig_t;

typedef struct {
	SPI_Dir_t	   	 SPI_Mode;
	SPI_DataSize_t	 SPI_DataSize;
	SPI_CPHASE_t	 SPI_Phase;
	SPI_CPOL_t 		 SPI_Polarity;
	SPI_BR_t 		 SPI_BR;
	SPI_FirstBit_t   SPI_FirstBit;
	SPI_CRC_Mode_t       SPI_CRC;
	RX_Only_t		 SPI_RX_Only;
	SPI_FRF_t		 SPI_FrameFormate;

}SPI_SlaveConfig_t;



/*Function Description :Master Initialization Function
 * 						Set the Master Configuration
 * 						Set the GPIO Pin Directions as Alternative function mode PA6,PA5,PA7
 *						Set The SPI in the AFR
 *						Enables The SPI
 */
void SPI_voidMasterInit(SPI_MasterConfig_t CopyMasterConfig);


/*Function Description :Slave Initialization Function
 * 						Set the Slave Configuration
 * 						Set the GPIO Pin Directions as Alternative function mode PA6,PA5,PA7,PA4
 *						Enables The SPI
 */
void SPI_voidSlaveInit(SPI_SlaveConfig_t CopySlaveConfig);

/*Function Description :Master mode Function used to Connect Slave 
 * 						Set the Slave Select Pin in GPIO Directions as OUTPUT
 * 						Set the GPIO Pin Value as HIGH to disable the Communication
 */
void SPI_voidMasterConectSlave(GPIO_PORT_ID Copy_u8SlavePort,GPIO_PIN_ID Copy_u8SlavePin);




/*Function Description : Sending and Receiving array of bytes using Polling */
void SPI_voidSendReceiveSync(u8 *Copy_u8DataToTransmit,u8 *Copy_DataToReceive[],u8 Copy_SlaveSelect);

/*Function Description : Sending and Receiving byte using Interrupt IRQ */
void SPI_voidSendReceiveASync(u8 Copy_u8DataToTransmit,void (*CallBackFunc)(u8),u8 Copy_SlaveSelect);

#endif
