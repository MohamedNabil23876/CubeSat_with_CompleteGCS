/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  AX_25_H
 *       Module:  -
 *
 *  Description:   header for the AX25 types     
 *  
 *********************************************************************************************************************/
#ifndef  AX_25_H
#define  AX_25_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "string.h"
#include "USART_interface.h"
/* Sequence for calling function in The main @ GCS 
	AX_InitConncetion();
	
	
	*/

/*Sequence for calling Function in the main @ OBC

*/



#define AX_FLAG  0x7E
#define space 0x40 
typedef enum{
	SREJ,
	REJ
}seqn_Recovery_t;

typedef enum {
	FLAG_ERROR,
	ADD_ERROR,
	SSID_ERROR,
	LENGTH_ERROR,
	SEQ_ERROR,
	OK
	}FRAME_TYPE_ERROR ;


typedef enum {
	AVAILABLE,
	NOT_AVAILABLE
}AX_ConnectionStatus_t;

typedef enum {
	I_Frame,
	U_Frame,
	S_Frame
}AX_FrameType_t;

/*For Command (Dest=1 ,Src=0)   Respond (Dest=0, Src=1)*/
typedef enum {
	SSID_C_0=0x60,
	SSID_C_1=0xE0
}SSID_Type;

typedef enum {
	Normal,
	Recovery
}Receive_Mood_t;
/* P/F is in Bit 4 */
/*N(R) 3Bits starts from bit5*/
typedef enum{
	RR_0   = 0x01,
	RR_1   = 0x11,
	RNR_0  = 0x05,
	RNR_1  = 0x15,
	REJ_0  = 0x09,
	REJ_1  = 0x19,
	SREJ_0 = 0x0D,
	SREJ_1 = 0x1D
}S_Ctrl_t;

/*P for Commands  F for Response p/f for either*/
typedef enum{
		SABME_1= 0x7F, //P=1
		SABME_0= 0x6F, //P=0
		SABM_1 = 0x3F, //p=1
		SABM_0 = 0x2F, //P=0
		DISC_1 = 0x53, //P=1
		DISC_0 = 0x43,  //P=0
		DM_1   = 0x1F, //F=1
		DM_0   = 0x0F, //F=0
		UA_1	 = 0x73, //F
		UA_0	 = 0x63, //F
		FRMR_1 = 0x97, //F
		FRMR_0 = 0x87, //F
		UI_1   = 0x13, //P/F
		UI_0 	 = 0x03, //P/F
		XID_1  = 0xBF, //P/F
		XID_0  = 0xAF, //P/F
		TEST_1 = 0xF3,  //P/F
		TEST_0 = 0xE3  //P/F
}U_Ctrl_t;
//global array 
//or rearange 


typedef struct {
	u8					 U_Start_Flag;
	u8					 U_Dest_Add[6];
	SSID_Type 	 U_Dest_SSID;
	u8 					 U_Src_Add[6];
	SSID_Type	   U_Src_SSID;
	U_Ctrl_t 		 U_Control;
	u8 					 U_Length;
	u8 	 				 U_Data[256];
	u8 					 U_FCS[2];
	u8 					 U_End_Flag;
}U_FRAME_Struct;
typedef struct {
	u8					 S_Start_Flag;
	u8					 S_Dest_Add[6];
	SSID_Type 	 S_Dest_SSID;
	u8 					 S_Src_Add[6];
	SSID_Type	   S_Src_SSID;
	S_Ctrl_t 		 S_Control;
	u16 				 S_FCS;
	u8 					 S_End_Flag;
}S_FRAME_Struct;

typedef enum {
	Disconnected,
	Awaiting_Connection,
	Awaiting_Release,
	Connected,
	Timer_Recovery,
	Awaiting_Connection_v2
}AX_State_t;

typedef enum {
	Command,
	Resp
}SSID_C_t;

typedef enum {
	Non,
	PF
}PF_Bit_t;

typedef struct {	
	u16 				 AX_FCS;
	u8	 				 AX_IControl;
	U_Ctrl_t		 AX_UControl;
	S_Ctrl_t 		 AX_SControl;
	u8					 AX_Start_Flag;
	u8					 AX_Dest_Add[6];
	SSID_Type 	 AX_Dest_SSID;
	u8 					 AX_Src_Add[6];
	SSID_Type	   AX_Src_SSID;
	u8  				 AX_PID;  //Next layer protocol in I and UI Frame
	u8 					 AX_Length;
	u8 	 				 AX_Data[256];
	u8 					 AX_End_Flag;
}AX_FRAME_Struct;

typedef struct {
		SSID_C_t SSID_C;
		AX_FrameType_t Frame_Type;
		PF_Bit_t PF_Bit;
		FRAME_TYPE_ERROR Error;
}AX_Config_t;

typedef struct {
	u8  Seq;
	u8  Data[256];
}I_Queue_struct;




void AX_SendFrame(USART_No_t AX_USART);
void AX_ReceiveFrame(USART_No_t AX_USART,u8 *Copy_RecievedData);
u16 AX_CRC(void);
void AX_BuildFrame(AX_Config_t *Copy_AXConfig);

/*void AX_SendSFrame(USART_No_t AX_USART);
void AX_SendUFrame(USART_No_t AX_USART);
*/


void AX_DisconnectedStateOBC(void);
void AX_ConnectedStateOBC(void);
void AX_DisconnectedStateGCS(void);
void AX_ConnectedStateGCS(void);

//function for each state 
void AX_InitConncetion(void);
void  AX_ReceiveFrameGA(void);

void AX_DLStateMachine(void);
	
u8 cmpArr(u8 *Arr1,u8 *Arr2,u8 size);
void cpyArr(u8 *Arr1,u8 *Arr2,u8 size);


#endif
