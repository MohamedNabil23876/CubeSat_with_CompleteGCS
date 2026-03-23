/*
 * SSP.c
 *
 *  Created on: May 10, 2023
 *      Author:
 */

#include "SSP.h"
#include "MPU.h"
#include "stm32f4xx_hal.h"
#include "BIT_MATH.h"

//#include<stdint.h>
//#include "UART_interface.h"
//#include "UART_configuration.h"
//#include "UART_private.h"
//#include "DHT.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

void cpyArr(uint8_t *Arr1,uint8_t *Arr2,uint8_t size){
    for(uint8_t i=0;i<size;i++){
        Arr1[i]=Arr2[i];
    }
}
uint8_t cmpArr(uint8_t *Arr1,uint8_t *Arr2,uint8_t size){
    for(uint8_t i=0;i<size;i++){
       if( Arr1[i]!=Arr2[i]){
				 return 0;
    }
	}
			 return 1;
}
uint8_t SSP_Arr[300];
SSP_Struct_t SSP_Send={
		.Src_Add=My_SSP_Add,
		.Dest_Add=Dest_SSP_Add,
};
uint8_t SSP_Arr_Rx[300];
SSP_Struct_t SSP_Rx;
uint8_t SSP_L;
//extern DHT_DataTypedef DHT_Data;

extern uint8_t T,H;
extern float Gx,Gy,Gz,Ax,Ay,Az;

//extern DHT_DataTypedef DHT22_Data;
//extern uint8_t FrameASCII[300];
#define CRC16 0x8005
#define POLY 0x8408

//void HextoASCII(uint8_t *Arr1,uint8_t *Arr2,uint16_t size);

uint16_t gen_crc16(const uint8_t *data, uint16_t length)
{
	{
	unsigned short crc = 0xffff;
	unsigned char *bufp = data;
	int len;
	int i;
	for (len = length; len > 0; len--) {
	unsigned char ch = *bufp++;
	for (i = 0; i < 8; i++) {
	crc = (crc >> 1) ^ ( ((ch ^ crc) & 0x01) ? POLY : 0 );
	ch >>= 1;
	}
	}
	return crc;
	}

	//uint16_t out = 0;
    //int bits_read = 0, bit_flag;
    //
    ///* Sanity check: */
    //if(data == NULL)
    //    return 0;
    //
    //while(size > 0)
    //{
    //    bit_flag = out >> 15;
    //
    //    /* Get next bit: */
    //    out <<= 1;
    //    out |= (*data >> bits_read) & 1; // item a) work from the least significant bits
    //
    //    /* Increment bit counter: */
    //    bits_read++;
    //    if(bits_read > 7){
    //               bits_read = 0;
    //               data++;
    //               size--;
    //           }
    //
    //           /* Cycle check: */
    //           if(bit_flag)
    //               out ^= CRC16;
    //
    //       }
    //
    //       // item b) "push out" the last 16 bits
    //       int i;
    //       for (i = 0; i < 16; ++i) {
    //           bit_flag = out >> 15;
    //           out <<= 1;
    //           if(bit_flag)
    //               out ^= CRC16;
    //       }
    //       // item c) reverse the bits
    //       uint16_t crc = 0;
    //           i = 0x8000;
    //           int j = 0x0001;
    //           for (; i != 0; i >>=1, j <<= 1) {
    //               if (i & out) crc |= j;
    //           }
    //
    //           return crc;
           }





void SSP_BuildFrame(SSP_Struct_t SSP_Struct){
	SSP_Arr[0]=FEND;
	SSP_Arr[1]=SSP_Struct.Dest_Add;
	SSP_Arr[2]=SSP_Struct.Src_Add;
	SSP_Arr[3]=SSP_Struct.SSP_Type;

	switch(SSP_Struct.SSP_Type){
	case TEMP_Req :  SSP_Arr[0]=FEND;
					 SSP_Arr[1]=My_SSP_Add;
					 SSP_Arr[2]=Dest_SSP_Add;
					 SSP_Arr[3]=SSP_Struct.SSP_Type;
					 SSP_Arr[4]=0x00;
					 SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],4);
					 SSP_Arr[5]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					 SSP_Arr[6]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					 SSP_Arr[7]=FEND;
					 SSP_L=8;
						//MUSART_voidTransmitString(USART1, SSP_Arr);
					 break;

	case TEMP_Res : SSP_Arr[4]=0x01;SSP_Arr[5]=T;
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],5);
					SSP_Arr[6]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					SSP_Arr[7]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					SSP_Arr[8]=FEND;
					SSP_L=9;

					HAL_UART_Transmit(&huart2, SSP_Arr, SSP_L, 10);

					//HAL_UART_Transmit(&huart2, "The SSP Frame Sent :  \n",24, 1000);
					  //HextoASCII(SSP_Arr,FrameASCII,SSP_L);
					  //HAL_UART_Transmit(&huart2, FrameASCII,(SSP_L*3 + 1), 1000);
					  //HAL_UART_Transmit(&huart2,"\n",2, 1000);
					//char x[]={"The Data : \nTemperature = "};
					//HAL_UART_Transmit(&huart2, x,sizeof(x), 1000);
					//uint8_t TASCII[3];
					//uint8_t Temp[1] ={((SSP_Arr[5]/10)*16+(SSP_Arr[5]%10))};
					//HextoASCII(Temp,TASCII, 1);
					//HAL_UART_Transmit(&huart2,TASCII ,2, 1000);
					break;


	case HUMID_Req: break;
	case HUMID_Res: SSP_Arr[4]=0x01;SSP_Arr[5]=H;
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],5);
					SSP_Arr[6]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					SSP_Arr[7]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					SSP_Arr[8]=FEND;
					SSP_L=9;
					HAL_UART_Transmit(&huart2, SSP_Arr, SSP_L, 10);
					break;
	case T_H_Req  : break;
	case T_H_Res  : SSP_Arr[4]=0x02;SSP_Arr[5]=T;SSP_Arr[6]=H;
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],6);
					SSP_Arr[7]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					SSP_Arr[8]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					SSP_Arr[9]=FEND;
					SSP_L=10;
					HAL_UART_Transmit(&huart2, SSP_Arr, SSP_L, 10);
					break;
	case MPUAx_Res: SSP_Arr[4]=0x04;
					cpyArr(&SSP_Arr[5], (uint8_t*) &Ax, sizeof(float));
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],8);
	    			SSP_Arr[9]=GET_BYTE(SSP_Struct.SSP_CRC,0);
	    			SSP_Arr[10]=GET_BYTE(SSP_Struct.SSP_CRC,8);
	    			SSP_Arr[11]=FEND;
	    			SSP_L=12;
	    			HAL_UART_Transmit(&huart2, SSP_Arr, SSP_L, 10);
	    			break;
	case MPUAy_Res: SSP_Arr[4]=0x04;
					cpyArr(&SSP_Arr[5], (uint8_t*) &Ay, sizeof(float));
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],8);
					SSP_Arr[9]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					SSP_Arr[10]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					SSP_Arr[11]=FEND;
					SSP_L=12;
					HAL_UART_Transmit(&huart2, SSP_Arr, SSP_L, 10);
		    			break;
	case MPUAz_Res: SSP_Arr[4]=0x04;
					cpyArr(&SSP_Arr[5], (uint8_t*) &Az, sizeof(float));
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],8);
					SSP_Arr[9]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					SSP_Arr[10]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					SSP_Arr[11]=FEND;
					SSP_L=12;
					HAL_UART_Transmit(&huart2, SSP_Arr, SSP_L, 10);
		    			break;
	case MPUGx_Res: SSP_Arr[4]=0x04;
					cpyArr(&SSP_Arr[5], (uint8_t*) &Gx, sizeof(float));
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],8);
					SSP_Arr[9]=GET_BYTE(SSP_Struct.SSP_CRC,0);
					SSP_Arr[10]=GET_BYTE(SSP_Struct.SSP_CRC,8);
					SSP_Arr[11]=FEND;
					SSP_L=12;
					HAL_UART_Transmit(&huart2, SSP_Arr, SSP_L, 10);
					break;

	case MPUGz_Res: SSP_Arr[4]=0x04;
					cpyArr(&SSP_Arr[5], (uint8_t*) &Gz, sizeof(float));
					SSP_Struct.SSP_CRC=gen_crc16(SSP_Arr[1],8);
		  			SSP_Arr[9]=GET_BYTE(SSP_Struct.SSP_CRC,0);
		  			SSP_Arr[10]=GET_BYTE(SSP_Struct.SSP_CRC,8);
		  			SSP_Arr[11]=FEND;
		  			SSP_L=12;
		  			HAL_UART_Transmit(&huart2, SSP_Arr, SSP_L, 10);
		  			break;
	case MPUGy_Res :break;

	default  : break;
	}

}

void SSP_Process(void){
	if (SSP_Arr_Rx[0]==FEND){
		if(SSP_Arr_Rx[1]==My_SSP_Add){
			if(SSP_Arr_Rx[2]==Dest_SSP_Add){
				SSP_Rx.SSP_Type=SSP_Arr_Rx[3];
				switch (SSP_Arr_Rx[3]){
				case TEMP_Req :	//DHT_GetData(&DHT_Data);
								//T=DHT_Data.Temperature/10;
								//H=DHT_Data.Humidity/10;
								SSP_Send.SSP_Type=TEMP_Res;
								SSP_BuildFrame(SSP_Send);
								break;
				case HUMID_Req: // DHT_GetData(&DHT_Data);
								//T=DHT_Data.Temperature/10;
								//H=DHT_Data.Humidity/10;
								SSP_Send.SSP_Type=HUMID_Res;
								SSP_BuildFrame(SSP_Send);
								break;
				case T_H_Req  : // DHT_GetData(&DHT_Data);
								// T=DHT_Data.Temperature/10;
								// H=DHT_Data.Humidity/10;
								SSP_Send.SSP_Type=T_H_Res;
								SSP_BuildFrame(SSP_Send);
								break;
				case MPUAx_Req :MPU6050_Read_Accel();
								SSP_Send.SSP_Type=MPUAx_Res;
								SSP_BuildFrame(SSP_Send);break;
				case MPUAy_Req :MPU6050_Read_Accel();
								SSP_Send.SSP_Type=MPUAy_Res;
								SSP_BuildFrame(SSP_Send);break;
				case MPUAz_Req :MPU6050_Read_Accel();
								SSP_Send.SSP_Type=MPUAz_Res;
								SSP_BuildFrame(SSP_Send);break;
				case MPUGx_Req :MPU6050_Read_Gyro();
								SSP_Send.SSP_Type=MPUGx_Res;
								SSP_BuildFrame(SSP_Send);break;
				case MPUGy_Req :MPU6050_Read_Gyro();
								SSP_Send.SSP_Type=MPUGy_Res;
								SSP_BuildFrame(SSP_Send);break;
				case MPUGz_Req :MPU6050_Read_Gyro();
								SSP_Send.SSP_Type=MPUGz_Res;
								SSP_BuildFrame(SSP_Send);break;
				default       :break;

				}
			}
		}
	}
}
