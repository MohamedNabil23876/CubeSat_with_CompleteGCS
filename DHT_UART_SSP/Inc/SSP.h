/*
 * SSP.h
 *
 *  Created on: May 10, 2023
 *      Author: HP
 */

#ifndef INC_SSP_H_
#define INC_SSP_H_

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/

#include "BIT_MATH.h"
#include "stm32f4xx_hal.h"

#define FEND 0xC0
#define FESC 0xDB

#define My_SSP_Add 0x42
#define Dest_SSP_Add 0x35


typedef enum {
	PING,
	INIT,
	ACK,
	NAK,
	GET,
	PUT,
	READ,
	WRITE,
	ID,
	TEMP_Req,
	TEMP_Res,
	HUMID_Req,
	HUMID_Res,
	T_H_Req,
	T_H_Res,
	//Custom 10-52
	ADDRT=54,
	DELRT,
	GETRT
}SSP_Type_t;

typedef struct {
	uint8_t Dest_Add;
	uint8_t Src_Add;
	SSP_Type_t SSP_Type;
	uint8_t Length;
	uint16_t SSP_CRC;
	uint8_t SSP_Data[256];
}SSP_Struct_t;

void   SSP_Process(void);
void SSP_BuildFrame(SSP_Struct_t SSP_Struct);
uint16_t gen_crc16(const uint8_t *data, uint16_t size);


void SSP_DataDecode(void);
uint16_t CRC_SSPCalc(void);

#endif /* INC_SSP_H_ */
