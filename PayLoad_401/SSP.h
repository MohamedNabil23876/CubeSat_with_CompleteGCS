/*
 * SSP.h
 *
 *  Created on: May 10, 2023
 *      Author:
 */

#ifndef INC_SSP_H_
#define INC_SSP_H_

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/

#include "stm32f4xx_hal.h"


#define FEND 0xC0
#define FESC 0xDB

#define My_SSP_Add 0x3
#define Dest_SSP_Add 0x15


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
	MPUGy_Req=10,
	MPUGy_Res=11,
	MPUGz_Req=12,
	MPUGz_Res=13,
	TEMP_Req=0x26,
	TEMP_Res=0x31,
	HUMID_Req=14,
	HUMID_Res=17,
	T_H_Req=18,
	T_H_Res=19,
	MPUGx_Req=0x15,
	MPUGx_Res=0x16,
	IMG_Req=0x20,
	IMG_Res=0x32,
    MPUAx_Req=22,
    MPUAx_Res=21,
    MPUAy_Req=23,
    MPUAy_Res=24,
	MPUAz_Req=30,
	MPUAz_Res=33,
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
