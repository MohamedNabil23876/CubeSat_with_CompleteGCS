/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  AX_25_H
 *       Module:  -
 *
 *  Description:   header for the AX25 Driver    
 *  
 *********************************************************************************************************************/
 
#ifndef  AX_25_H
#define  AX_25_H


#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#include "BIT_MATH.h"
#include "queueAX.h"

/***************** AX25 *******************/

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

typedef enum {
	Command,
	Resp
}SSID_C_t;

typedef enum {
	None,
	PF
}PF_Bit_t;

typedef enum {
A, 
B, 
C,
D,
E,
F ,
I, 
J ,
L ,
M ,
N ,
O ,
P ,
Q ,
R,
S,
Tt,
U, 
V,
K,
Error_None
}DL_Errorst;

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
		DL_Errorst Error;
		u8 Expedited;
		u8 NR;
		u8 NS;
}AX_Config_t;

typedef struct {
	u8  Seq;
	u8  Data[256];
	u8  Data_Length;
	u8  Empty;
}I_Queue_struct;


/***************** Data Link Layer *******************/

typedef enum {
	Disconnected,
	Awaiting_Connection,
	Awaiting_Release,
	Connected,
	Timer_Recovery,
	Awaiting_Connection_v2
}AXDL_State_t;


typedef enum {
	DL_CONNECTConfirm,
	DL_CONNECTIndicate,
	DL_DISCONNECTConfirm,
	DL_DISCONNECTIndicate,
	DL_DATAIndicate,
	DL_UNITDATAIndicate,
	DL_ERRORIndicate,
	DL_CONNECTRequest,
	DL_DISCONNECTRequest,
	DL_DATARequest,
	DL_DATAIConfirm,
	DL_UNITDATARequest,
	DL_FLOWOFFRequest,
	DL_FLOWONRequest,
	DL_None
}DL_Primitivest;


typedef struct {
 u8 Layer3Init;
 u8 PRB;
 u8 ORB;
 u8 RejExc;
 u8 SREJExc;
 u8 AckPend;
	u8 SRT;
	u8 T1V;
	u8 N1;
	u8 N2;
}DL_Flagst;

typedef enum {
	LM_SEIZERequest,
	LM_RELEASERequest,
	LM_DATARequest,
	LM_EXPEDITEDDATARequest,
	LM_SEIZEConfirm,
	LM_DATAIndicate,
	LM_None
}LM_Primitivest;

u8 cmpArr(u8 *Arr1,u8 *Arr2,u8 size);
void cpyArr(u8 *Arr1,u8 *Arr2,u8 size);
u16 AX_CRC(void);
void AX_BuildFrame(AX_Config_t *Copy_AXConfig);
void AX_DisconnectedState(void);
void AX_ConnectedState(void);
void AX_SetV20(void);
void AX_AwaitingConnectionState(void);
void AX_FrameProcess(void);
void AX_ClearExceptionConditions (void);
void AX_EstablishDataLink(void);
void AX_DisconnectHandler(void);
void AX_AwaitingConnectionHandler(void);
void AX_SelectT1(void);
void AX_AwaitingReleaseState(void);
void AX_AwaitingReleaseHandler(void);
void AX_ConnectedHandler(void);
void AX_EnquiryResponse(void);
void AX_ChechIAcked(void);
void AX_NR_ErrorRecovery(void);
void AX_InvokeRetransmission(void);
void AX_DL_ConnectRequest(void);
void AX_TimerRecoveryState(void);
void AX_InitVariables (void);
void AX_ChechIAcked(void);

void AX_DLInit(void);

/***************** Duplex Physical Layer *******************/
typedef enum {
	Ready,
	Receiver_Ready,
	Receiving,
	Transmitter_Ready,
	Transmitter_Start,
	Transmitting
}PH_Statet;

typedef enum {	
	PH_SEIZERequest,
	PH_SEIZEConfirm,
	PH_DATARequest,
	PH_RELEASERequest,	
	PH_DATAIndication,
	PH_EXPEDITED_DATARequest,
	PH_BUSYIndication,
	PH_QUIETIndication,
	PH_None
}PH_Primitivest;

typedef enum {
	Acquisition_of_Signal,
	Loss_of_Signal,
	Frame,
	Turn_on_Transmitter,
	Turn_Off_Transmitter,
	RF_None
}PH_RF_Primitivest;

/* main function */
void AX_PH_InitDuplex(void) ;

/* Rceiving States Functions*/
void AX_PH_ReceiverReadyState(void);		
void AX_PH_ReceivingState(void) ;

/*Transmitting States Functions*/
void AX_PH_Transmitter_ReadyState(void) ;
void AX_PH_Transmitter_StartState(void);
void AX_PH_TransmittingState(void);


/***************** Link Multiplexer Layer *******************/
/* queue event subroutine */
#define SERVING_LIST_CAPACITY 10
#define NOT_SERVED 0
#define ON_SERVED 1
#define NULL 0

typedef enum LM_primitive
{
	queue_empty,LM_SEIZE_Request,LM_SEIZE_Confirm,
	LM_RELEASE_Request,LM_EXPEDITED_DATA_Request,
	LM_DATA_Request,LM_DATA_Indication
}LM_primitive;

typedef enum PH_primitive
{
	PH_SEIZE_Request,PH_SEIZE_Confirm,
	PH_DATA_Request,PH_RELEASE_Request,
	PH_DATA_Indication,PH_EXPEDITE_DATA_Request,
	PH_BUSY_Indication, PH_QUIET_Indication
}PH_primitive;

typedef enum LM_states
{
    Idle,
    Seize_Pending,
	Seized
}LM_states;


/* main function */
void linkMultiplexerMainFunction(void);

/* state functions */
void linkMultiplexerIdleState(void);
void linkMultiplexerSeizePendingState(void);
void linkMultiplexerSeizedState(void);

/* subroutine function */
void queueEvent(void);
void finishCurrentTransmission(void);
void frameRecieved(void);


#endif
