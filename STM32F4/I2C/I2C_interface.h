/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  I2C_INTERFACE_H
 *       Module:  -
 *
 *  Description:   header for the I2C INTERFACING
 *
 *********************************************************************************************************************/
#ifndef  I2C_INTERFACE_H
#define  I2C_INTERFACE_H

#include"BIT_MATH.h"
#include"STD_TYPES.h"
typedef enum{
	SM,		/*Standard Mode*/
	FM,		/*Fast Mode*/
}I2C_Mode_t;

typedef enum{
	Duty_2,
	Duty_16O9,
}I2C_FM_Duty_t;

/*CCR */

typedef enum {
	I2C_TRANSMITTER_MODE,
	I2C_RECEIVER_MODE
}I2C_Dir_t;

typedef enum {
	ACK_DISABLE,
	ACK_ENABLE,
}I2C_ACK_t;

typedef struct {
	u16				 I2C_Freq; /*From   2MHz to 50MHz*/
	I2C_Mode_t 		 I2C_Mode;
	I2C_FM_Duty_t	 I2C_FM_DC; /*Place Duty_2 in Standard mode*/
	u16				 I2C_SCL;  /*in ...*/
	u16 			 I2C_TRISE;  /* in ns*/
}I2C_ClockConfig_t;


/* Function 	: I2C_voidMasterInitTx(u16 Copy_SlaveAdd,u8 *Copy_Data[])
   DESCRIPTION  : Set the PB6  ,PB9  in alternative Function mode and open drain
				  Set the I2C in AFR 
				  Enabling I2C
				  Sending the Starting Bit the Address , The Data , The Stop Bit
*/
void I2C_voidMasterInitTx(u16 Copy_SlaveAdd,u8 *Copy_Data);

/* Function 	: I2C_u8MasterRx(u16 Copy_SlaveAdd,u8 *Copy_DataToReceive[],I2C_ACK_t Copy_ACK)
   DESCRIPTION  : Set the PB6  ,PB9  in alternative Function mode and open drain
				  Set the I2C in AFR 
				  Enabling I2C
				  Sending the Starting Bit the Address ,
				  Setting tha Ack 
				  Recive The Data ,
				  Sending The Stop Bit When BTF flag is send from the Slave
*/
void I2C_u8MasterRx(u16 Copy_SlaveAdd,u8 *Copy_DataToReceive[],I2C_ACK_t Copy_ACK,u8 Copy_DataReq);
/*Setting the Slave 1st Address*/
void I2C_voidSetSlaveAdd1(u16 Copy_Address);
/*Setting the Slave 2nd Address*/
void I2C_voidSetSlaveAdd2(u16 Copy_Address);

/* Function 	: I2C_voidClockConfig(I2C_ClockConfig_t Copy_ClockConfig)
   DESCRIPTION  : Set the Peripheral Freq 
				  Choose Between Standad and Fast mode
				  Set The Duty Cycle for the FM 
				  Calculate and Set The Clock Control Reg
				  Calculate and Set The Trise Reg 
				  The Freq used is in MHz  and time in ns
*/
void I2C_voidClockConfig(I2C_ClockConfig_t Copy_ClockConfig);



/////////////////////////////
void I2C_Start( u8 address, I2C_Dir_t direction, I2C_ACK_t ack) ;
u8 I2C_ReadNack(void) ;
u8 I2C_ReadAck(void) ;
void I2C_WriteNoRegister( u8 address, u8 data,I2C_ACK_t Ack) ;
void I2C_Write( u8 address, u8 reg, u8 data) ;
void I2C_Stop(void) ;
u8 I2C_ReadNoRegister( u8 address);
u8 I2C_Read(u8 address, u8 reg,I2C_ACK_t Ack);
void I2C_WriteData(u8 data) ;
u8 I2C_Read(u8 address, u8 reg,I2C_ACK_t Ack);
#endif
