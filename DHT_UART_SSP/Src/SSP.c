/*
 * SSP.c
 *
 *  Created on: May 10, 2023
 *      Author: HP
 */
#include "stm32f4xx_hal.h"
#include "SSP.h"
#include "DHT.h"
uint8_t SSP_Arr[300];
SSP_Struct_t SSP_Send={
		.Src_Add=My_SSP_Add,
		.Dest_Add=Dest_SSP_Add,
};
uint8_t SSP_Arr_Rx[300];
SSP_Struct_t SSP_Rx;
extern uint8_t T,H;
extern DHT_DataTypedef DHT22_Data;
extern float Temperature, Humidity;
#define CRC16 0x8005

uint16_t gen_crc16(const uint8_t *data, uint16_t size)
{
	uint16_t out = 0;
    int bits_read = 0, bit_flag;

    /* Sanity check: */
    if(data == NULL)
        return 0;

    while(size > 0)
    {
        bit_flag = out >> 15;

        /* Get next bit: */
        out <<= 1;
        out |= (*data >> bits_read) & 1; // item a) work from the least significant bits

        /* Increment bit counter: */
        bits_read++;
        if(bits_read > 7){
                   bits_read = 0;
                   data++;
                   size--;
               }

               /* Cycle check: */
               if(bit_flag)
                   out ^= CRC16;

           }

           // item b) "push out" the last 16 bits
           int i;
           for (i = 0; i < 16; ++i) {
               bit_flag = out >> 15;
               out <<= 1;
               if(bit_flag)
                   out ^= CRC16;
           }
           // item c) reverse the bits
           uint16_t crc = 0;
               i = 0x8000;
               int j = 0x0001;
               for (; i != 0; i >>=1, j <<= 1) {
                   if (i & out) crc |= j;
               }

               return crc;
           }





void SSP_BuildFrame(SSP_Struct_t SSP_Struct){
	SSP_Arr[0]=FEND;
	SSP_Arr[1]=SSP_Struct.Dest_Add;
	SSP_Arr[2]=SSP_Struct.Src_Add;
	SSP_Arr[3]=SSP_Struct.SSP_Type;

	switch(SSP_Struct.SSP_Type){
	case TEMP_Req :  break;
	case TEMP_Res : SSP_Arr[4]=0x01;SSP_Arr[5]=T;
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],5);
					SSP_Arr[6]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					SSP_Arr[7]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					SSP_Arr[8]=FEND;break;


	case HUMID_Req: break;
	case HUMID_Res: SSP_Arr[4]=0x01;SSP_Arr[5]=H;
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],5);
					SSP_Arr[6]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					SSP_Arr[7]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					SSP_Arr[8]=FEND;break;
	case T_H_Req  : break;
	case T_H_Res  : SSP_Arr[4]=0x02;SSP_Arr[5]=T;SSP_Arr[6]=H;
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],6);
					SSP_Arr[7]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					SSP_Arr[8]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					SSP_Arr[9]=FEND; break;
	default  : break;
	}

}

void SSP_Process(void){
	if (SSP_Arr_Rx[0]==FEND){
		if(SSP_Arr_Rx[1]==My_SSP_Add){
			if(SSP_Arr_Rx[2]==Dest_SSP_Add){
				SSP_Rx.SSP_Type=SSP_Arr_Rx[3];
				switch (SSP_Arr_Rx[3]){
				case TEMP_Req :	/*DHT_GetData(&DHT22_Data);
								Temperature = DHT22_Data.Temperature;
								Humidity = DHT22_Data.Humidity;*/
								T=Temperature/10;
								H=Humidity/10;
								SSP_Send.SSP_Type=TEMP_Res;
								SSP_BuildFrame(SSP_Send);
								break;
				case HUMID_Req: DHT_GetData(&DHT22_Data);
								Temperature = DHT22_Data.Temperature;
								Humidity = DHT22_Data.Humidity;
								T=Temperature/10;
								H=Humidity/10;
								SSP_Send.SSP_Type=HUMID_Res;
								SSP_BuildFrame(SSP_Send);
								break;
				case T_H_Req  : DHT_GetData(&DHT22_Data);
								Temperature = DHT22_Data.Temperature;
								Humidity = DHT22_Data.Humidity;
								T=Temperature/10;
								H=Humidity/10;
								SSP_Send.SSP_Type=T_H_Res;
								SSP_BuildFrame(SSP_Send);
								break;
				default       :break;

				}
			}
		}
	}
}
