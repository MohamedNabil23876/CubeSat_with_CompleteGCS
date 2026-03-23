/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  AX_25_C
 *       Module:  -
 *
 *  Description:   C Program File for the AX25 Functions    
 *  
 *********************************************************************************************************************/

#include "AX25_Feb.h"
//-------------------------------------- AX 25 -------------------------------//

u8 CubeSat_Add[6] ={0x42,0x24,0x3A,0xBC,0x52,0xA2};
u8 GCS_Add[6] ={0x59,0xA0,0x9E,0x42,0xAB,0x22};
#define MY_ADD   GCS_Add
#define Dest_ADD  CubeSat_Add
#define SRT_Default 0
#define AX_FLAG  0x7E
#define space 0x40 

 /*Global Received struct */
 
  AX_FRAME_Struct AX_Received={
		.AX_End_Flag=AX_FLAG,
	  .AX_Start_Flag=AX_FLAG,
};
	
 /*Global Send struct */
 
  AX_FRAME_Struct AX_Send={ 
		.AX_End_Flag=AX_FLAG,
	  .AX_Start_Flag=AX_FLAG,
	};

	//global config struct 
 AX_Config_t AX_SendConfig={
  .Error=Error_None,
	.Expedited=0,
  };
 AX_Config_t AX_ReceiveConfig={
	.Error=Error_None,
	.Expedited=0,
 };

	//global arrays to send and recive 
u8 AX_SendArray[256+24];  
u8 AX_ReceiveArray[256+24];

AX_ConnectionStatus_t AX_ConnectionStatus;

//--------------------------------------PH Layer Duplix-------------------------------//
	PH_Statet PH_StateTx;
	PH_Statet PH_StateRx;

	//------Flags and Timers-----//
	u8 Interrupted=0;
	u8 T105_Expired=0;
	u32 T105;
	u32 T107;
	u8 T107_Epired=0;

//--------------PH  interactions with RF---------------------//
	PH_RF_Primitivest PHtoRF_Primitives;
	PH_RF_Primitivest RFtoPH_Primitives;
	u8 Received=0;
	u8 PH_RxArray[300];
	u8 FrameReceivedFlag =0 ;
//---- PH Normal Queue ----//
	ST_queue_t PH_NormalQueue={
		.front= -1,
		.rear= -1 };
	
//--------------PH  interactions with LM---------------------//
	PH_Primitivest 	PHtoLM_Primitives;
	PH_Primitivest 	LMtoPH_Primitives;

		
/************************************   Link Multiplixer Layer  *****************************************************/

LM_states global_enLMStateControl;
LM_primitive global_enLMPrimitiveFlag;
PH_primitive global_enPHPrimitiveFlag;

u8 global_u8CurrentDL;
u8 global_u8RequestingDL;  // set in data link
u8 global_u8NumberOfPrimitive;   // set in data link
u8 global_u8ArrServingList[SERVING_LIST_CAPACITY];
u8 global_u8servingListIndex;
ST_queue_t current_queue={.front = -1,
                          .rear = -1};
ST_queue_t awaiting_queue={.front = -1,
                           .rear = -1};
ST_queue_t served_queue={.front = -1,
                         .rear = -1};

//--------------------------------------Data Link Layer-------------------------------//
	// sequence numbers 
	u8 V_S,V_A,V_R=0;    
	u8 N_S,N_R=0;
												 
	AXDL_State_t AXDL_State=Disconnected;  //DataLink Current state  of the State machine 
	I_Queue_struct I_Q_Send[8]; // the number of Buffers as window size 
	I_Queue_struct I_Q_Receive[8]; 												 
												 
 DL_Flagst DL_Flags;
 DL_Primitivest DLtoDLS_Primitives;
 DL_Primitivest DLStoDL_Primitives;
 
 LM_Primitivest DLtoLM_Primitives;
 LM_Primitivest LMtoDL_Primitives;
 
 DL_Errorst DL_Error;			
u8 Q_Send_Counter=0;
u8 Q_Received_Counter=0;
											 
												 
//------------------------------------ RF/USART Interfacing ---------------------------------------------//
												 
void AX_SendFrameUSART(void){
	if(PHtoRF_Primitives==Frame) {
	USART_voidTransmit( USART_1,&AX_SendArray);
	}
}
void AX_ReceiveFrameUSART(void) {
u8 Test ;
u8 i=0;
	Test=USART_u8ReceiveAX(USART_1);
	if(Received==1&&PH_StateRx==Receiver_Ready){
		RFtoPH_Primitives=Acquisition_of_Signal;
	}
	if(Test==0x7E){
		while(Received==1){
		PH_RxArray[i]=USART_u8ReceiveAX(USART_1);
		i++;
		if(i>16){
		FrameReceivedFlag=1;
		}
	}
		i=0;
}
if(PH_StateRx==Receiving){
	if(FrameReceivedFlag==1){
		RFtoPH_Primitives=Frame;
		FrameReceivedFlag=0;
	}
	else RFtoPH_Primitives=Loss_of_Signal;
}	
}
//--------- Init Function for Duplex Physical Layer State Machine -------//
	void AX_PH_InitDuplex(void) {
		
		switch (PH_StateRx) {
			case Receiver_Ready:AX_PH_ReceiverReadyState();break;
			case Receiving:AX_PH_ReceivingState();break;
		}
		switch (PH_StateTx){
			case Transmitter_Ready:AX_PH_Transmitter_ReadyState();break;
			case Transmitter_Start:AX_PH_Transmitter_StartState();break;
			case Transmitting:AX_PH_TransmittingState();  break;
		}
		if(PHtoLM_Primitives!=PH_None)
			global_enPHPrimitiveFlag=PHtoLM_Primitives;
	}
	
	//-----------------------------------------------------------------------------------//
	void AX_PH_ReceiverReadyState(void) {
		switch (RFtoPH_Primitives){
			case Acquisition_of_Signal :  //Stop Timers 
																	PHtoLM_Primitives=PH_BUSYIndication;
																	PH_StateRx=Receiving;RFtoPH_Primitives=RF_None;break;
			default 									 :RFtoPH_Primitives=RF_None;PH_StateRx=Receiver_Ready;break;
			
		}
		
	}
	//-----------------------------------------------------------------------------------//	
	void AX_PH_ReceivingState(void) {
		switch(RFtoPH_Primitives) {
			case Frame 					: PHtoLM_Primitives=PH_DATAIndication; 
														RFtoPH_Primitives=RF_None;
														PH_StateRx=Receiving ;break;
			case Loss_of_Signal : PHtoLM_Primitives=PH_QUIETIndication;
														RFtoPH_Primitives=RF_None;
														PH_StateRx=Receiver_Ready; break;
		}
	}
	//-----------------------------------------------------------------------------------//
	void AX_PH_Transmitter_ReadyState(void) {
		dequeuePH(&PH_NormalQueue,&LMtoPH_Primitives);
		switch (LMtoPH_Primitives){
			case PH_SEIZERequest: //start T103
														PHtoRF_Primitives=Turn_on_Transmitter;
														PH_StateTx=Transmitter_Start;
														//LMtoPH_Primitives=PH_None;
														break;
			case PH_RELEASERequest: PH_StateTx=Transmitter_Ready;
															//LMtoPH_Primitives=PH_None;
															break;
			default 							:  enqueuePH(&PH_NormalQueue,LMtoDL_Primitives);
															 //LMtoDL_Primitives=PH_None;
															 PH_StateTx=Transmitter_Ready;				
		}
		}
	//-----------------------------------------------------------------------------------//
	void AX_PH_Transmitter_StartState(void){
			dequeuePH(&PH_NormalQueue,&LMtoPH_Primitives);
			switch (LMtoPH_Primitives) {
				default : enqueuePH(&PH_NormalQueue,LMtoDL_Primitives); PH_StateTx=Transmitter_Start;break;
			}
			if(T105_Expired==1){
				if(Interrupted==1){
					PHtoLM_Primitives=PH_SEIZEConfirm;
				}
				PH_StateTx=Transmitting;
			} 
	}
	//-----------------------------------------------------------------------------------//
	void AX_PH_TransmittingState(void){
			dequeuePH(&PH_NormalQueue,&LMtoPH_Primitives);
		switch (LMtoPH_Primitives) {
			case PH_SEIZERequest 				 : PHtoLM_Primitives=PH_SEIZEConfirm;break;
			case PH_RELEASERequest			 : Interrupted=0; //stop T107 
																		 PHtoRF_Primitives=Turn_Off_Transmitter; 
																		 PH_StateTx=Transmitter_Ready ;break;
			case PH_DATARequest 				 : PHtoRF_Primitives=Frame;
																		 PH_StateTx=Transmitting;break;
			case PH_EXPEDITED_DATARequest: PHtoRF_Primitives=Frame;
																		 PH_StateTx=Transmitting;break;
			default											 : enqueuePH(&PH_NormalQueue,LMtoDL_Primitives); 
																		 PH_StateTx=Transmitting;break;
			}
		if(T107_Epired==1){
			Interrupted==1;
			PHtoRF_Primitives=Turn_Off_Transmitter;
			PH_StateTx=Transmitter_Ready;
		}
	}



/************************************   Link Multiplixer Layer  *****************************************************/


/* main function */
void linkMultiplexerMainFunction(void)
{
   switch (global_enLMStateControl)
   {
     case Idle :
    	  /* call idle state function */
    	  linkMultiplexerIdleState();
	      break;
     case Seize_Pending :
    	  /* call seize_pending function */
    	  linkMultiplexerSeizePendingState();
    	  break;
     case Seized :
    	  /* call seized function */
    	  linkMultiplexerSeizedState();
    	  break;
   }
}

/* state functions */

void linkMultiplexerIdleState(void)
{
	u8 local_u8CopyPrimitive=0;
	u8 local_u8copyRequestingNo=0;
  dequeue(&awaiting_queue,&global_enLMPrimitiveFlag,&global_u8RequestingDL);
    switch(global_enLMPrimitiveFlag)
    {
       case LM_EXPEDITED_DATA_Request : /* enqueue PH_EXPEDITE_DATA_Request onto Physical queue*/
																						enqueuePH(&PH_NormalQueue,PH_EXPEDITED_DATARequest);
                                        break;
       case LM_DATA_Request :           /*enqueue PH_SEIZE_Request onto Physical queue*/
																				enqueuePH(&PH_NormalQueue,PH_SEIZERequest);
    	                                /* current DL = requesting DL*/
    	                                global_u8CurrentDL = global_u8RequestingDL;
    	                                /* move all event submitted by current data link to current queue*/
    	                                for(u8 i=0;i<global_u8NumberOfPrimitive;i++)
    	                                {
    	                                	dequeue(&awaiting_queue,&local_u8CopyPrimitive,&local_u8copyRequestingNo);
    	                                	enqueue(&current_queue,local_u8CopyPrimitive,local_u8copyRequestingNo);
    	                                }
    	                                /* change state */
    	                                global_enLMStateControl = Seize_Pending;
    	                                break;
       case LM_SEIZE_Request :          /*enqueue PH_SEIZE_Request onto Physical queue*/
																				enqueuePH(&PH_NormalQueue,PH_SEIZERequest);
                                        /* current DL = requesting DL*/
                                        global_u8CurrentDL = global_u8RequestingDL;
                                        /* move all event submitted by current data link to current queue*/
                                        for(u8 i=0;i<global_u8NumberOfPrimitive;i++)
                                        {
                                            dequeue(&awaiting_queue,&local_u8CopyPrimitive,&local_u8copyRequestingNo);
           	                                enqueue(&current_queue,local_u8CopyPrimitive,local_u8copyRequestingNo);
                                        }
                                        /* change state */
                                        global_enLMStateControl = Seize_Pending;
                                        break;
       case LM_RELEASE_Request :        /* stay in idle state */
    	                                break;
       case queue_empty :               /* move events from served list to awaiting list */
    	                                copyQueue(&served_queue,&awaiting_queue);
    	                                /* clear served list */
                                        makeQueueEmpty(&served_queue);
    	                                break;
       case LM_SEIZE_Confirm :          /* queue event subroutine */
                                        queueEvent();
    	                                break;
       case LM_DATA_Indication :        /* queue event subroutine */
    	                                queueEvent();
    	                                break;
    }
    switch(global_enPHPrimitiveFlag)
    {
      case PH_SEIZE_Confirm :           /*enqueue PH_RELEASE_Request onto Physical queue */
																			enqueuePH(&PH_NormalQueue,PH_RELEASERequest);
    	                                break;
      case PH_DATA_Indication :         /* frame received subroutine */
    	                                break;
      case PH_BUSY_Indication :         /* suspend all link layer timing */
    	                                break;
      case PH_QUIET_Indication :        /* resume all link layer timing */
    	                                break;
    }
}

/***************************/
void linkMultiplexerSeizePendingState(void)
{
	dequeue(&current_queue,&global_enLMPrimitiveFlag,&global_u8RequestingDL);
	switch(global_enLMPrimitiveFlag)
	{
	  case LM_EXPEDITED_DATA_Request : /* enqueue PH_EXPEDITE_DATA_Request onto Physical queue*/
																			enqueuePH(&PH_NormalQueue,PH_EXPEDITED_DATARequest);
		                               /* change state */
		                               global_enLMStateControl = Idle;
                                       break;
	  case LM_DATA_Request :           /* replace on current queue */
		                               /* halt processing of the current queue until a new state is reached */
		                               break;
	  case LM_SEIZE_Request :          /* stay in seized pending state */
		                               break;
	  case LM_RELEASE_Request :        /* finish current transmission subroutine  */
		                               finishCurrentTransmission();
		                               /* change state */
		  		                       global_enLMStateControl = Idle;
		                               break;
	  case queue_empty :               /* stay in seized pending state */
		                               break;
	  case LM_SEIZE_Confirm :          /* queue event subroutine */
	                                   queueEvent();
	      	                           break;
	  case LM_DATA_Indication :        /* queue event subroutine */
	      	                           queueEvent();
	      	                           break;
	}
	switch(global_enPHPrimitiveFlag)
    {
	  case PH_SEIZE_Confirm :          /*enqueue LM_SEIZE_CONFIRM on data link queue */
																		LMtoDL_Primitives=LM_SEIZEConfirm;
		                               /* change state */
		                               global_enLMStateControl = Seized;
	    	                           break;
      case PH_DATA_Indication :        /* frame received subroutine */
    	                               frameRecieved();
	    	                           break;
	  case PH_BUSY_Indication :        /* suspend all link layer timing */
	    	                           break;
      case PH_QUIET_Indication :       /* resume all link layer timing */
	    	                           break;
    }
}

/***************************/
void linkMultiplexerSeizedState(void)
{
	dequeue(&current_queue,&global_enLMPrimitiveFlag,&global_u8RequestingDL);
		switch(global_enLMPrimitiveFlag)
		{
		  case LM_EXPEDITED_DATA_Request : enqueuePH(&PH_NormalQueue,PH_EXPEDITED_DATARequest);
																			/* enqueue PH_EXPEDITE_DATA_Request onto Physical queue*/
			                               /* change state */
			                               global_enLMStateControl = Idle;
	                                       break;

		  case LM_DATA_Request :           /* enqueue PH_DATA_Request onto Physical queue */
																		enqueuePH(&PH_NormalQueue,PH_DATARequest);
			                               break;

		  case LM_SEIZE_Request :          /* enqueue LM_SEIZE_CONFIRM on data link queue*/
																		LMtoDL_Primitives=LM_SEIZEConfirm;
			                               break;

		  case LM_RELEASE_Request :        /* finish current transmission subroutine  */
			                               finishCurrentTransmission();
			                               /* change state */
			  		                       global_enLMStateControl = Idle;
			                               break;

		  case queue_empty :               /* finish current transmission subroutine  */
                                           finishCurrentTransmission();
                                           /* change state */
                                           global_enLMStateControl = Idle;
                                           break;

		  case LM_SEIZE_Confirm :          /* queue event subroutine */
		                                   queueEvent();
		      	                           break;

		  case LM_DATA_Indication :        /* queue event subroutine */
		      	                           queueEvent();
		      	                           break;
		}
		switch(global_enPHPrimitiveFlag)
	    {
		  case PH_SEIZE_Confirm :          /* stay in seized state */
		    	                           break;

	      case PH_DATA_Indication :        /* frame received subroutine */
	    	                               frameRecieved();
		    	                           break;

		  case PH_BUSY_Indication :        /* suspend all link layer timing */
		    	                           break;

	      case PH_QUIET_Indication :       /* resume all link layer timing */
		    	                           break;
	    }
}

/* subroutine functions */
void queueEvent(void)
{
	u8 local_u8flag=NOT_SERVED;
	if(global_u8RequestingDL == global_u8CurrentDL)
	{
		enqueue(&current_queue,global_enLMPrimitiveFlag,global_u8RequestingDL);
	}
	else
	{
		for (u8 i=0;i<SERVING_LIST_CAPACITY;i++)
		{
          if (global_u8RequestingDL == global_u8ArrServingList[i])
          {
        	  local_u8flag=ON_SERVED;
          }
          else
          {}
		}
	}
	if(local_u8flag == NOT_SERVED)
	{
		enqueue(&served_queue,global_enLMPrimitiveFlag,global_u8RequestingDL);
	}
	else
	{
		enqueue(&awaiting_queue,global_enLMPrimitiveFlag,global_u8RequestingDL);
	}
}

/**************************/
void finishCurrentTransmission(void)
{
	u8 local_copyPrimitive=0;
	u8 local_copyRequestingNo=0;
	/* enqueue PH_EXPEDITE_DATA_Request onto Physical queue*/
	/* pop all frames of current queue and push in served queue */
	for(u8 i=0;i<QUEUE_SIZE;i++)
	{
		dequeue(&current_queue,&local_copyPrimitive,&local_copyRequestingNo);
		if(local_copyPrimitive == 0)
		{
			i = QUEUE_SIZE;      // to stop loop
		}
		else
		{
		enqueue(&served_queue,local_copyPrimitive,local_copyRequestingNo);
		}
	}
	/* place current DL on served list */
	global_u8ArrServingList[global_u8servingListIndex]=global_u8CurrentDL;
	global_u8servingListIndex++;
	/* current DL <= Null  */
	global_u8CurrentDL =NULL;
}
/****************************/ 
void frameRecieved(void)
{

}

//------------------------------------------Data Link Layer --------------------------------------------//
u32 T1,T2,T3;
u32 T1_Remaining;
u8 T1_Expired=0;
u8 T3_Expired=0;
u8 k;
u8 RC=0;
u8 DataLink_Id=0;

void AX_DLInit(void) {
		
		switch (AXDL_State) {
			case Disconnected				 :AX_DisconnectedState();break;
			case Awaiting_Connection :AX_AwaitingConnectionState();break;
			case Awaiting_Release		 :AX_AwaitingReleaseState();break;
			case Connected           :AX_ConnectedState();break;
			case Timer_Recovery			 :AX_TimerRecoveryState();break;
		}
		
	}
	

//--------------------------------------------------------//
void AX_EstablishDataLink(void){
    
			AX_ClearExceptionConditions();
      AX_SendConfig.Frame_Type=U_Frame;
			AX_SendConfig.SSID_C=Command;
			AX_Send.AX_UControl=SABM_1;
			AX_BuildFrame(&AX_SendConfig);
			RC=0;
           //restart T1 
	        // Stop T3

	}

//-------------------------------------------------//
void AX_ClearExceptionConditions (void) {
			DL_Flags.PRB =0;
			DL_Flags.ORB =0;
			DL_Flags.RejExc =0;
			DL_Flags.SREJExc=0;
			DL_Flags.AckPend=0;
}
//------------------------------------------------//
void AX_DisconnectedState(void){
	switch (DLStoDL_Primitives) {
		case DL_CONNECTRequest		:	DL_Flags.SRT=SRT_Default;
																DL_Flags.T1V=2*DL_Flags.SRT;
																AX_DL_ConncectRequest(); 
																DL_Flags.Layer3Init=1;
																DLtoLM_Primitives=LM_DATARequest;
																enqueue(&awaiting_queue,DLtoLM_Primitives,DataLink_Id);
																AXDL_State=Awaiting_Connection; 
																DLStoDL_Primitives=DL_None; break;
		case DL_DISCONNECTRequest : DLtoDLS_Primitives=DL_DISCONNECTConfirm;DLStoDL_Primitives=DL_None; AXDL_State=Disconnected ; break;
		default 									: AXDL_State=Disconnected;DLStoDL_Primitives=DL_None;break;
	}
	switch (LMtoDL_Primitives) {
		case LM_DATAIndicate : AX_FrameProcess(); AX_DisconnectHandler();LMtoDL_Primitives=LM_None;break ;
		default 						 : AXDL_State=Disconnected ;LMtoDL_Primitives=LM_None;break;
 }
}
//-------------------------------------------------------//
void AX_AwaitingConnectionState(void) {
		switch (LMtoDL_Primitives) {
					case LM_DATAIndicate : AX_FrameProcess(); AX_AwaitingConnectionHandler(); LMtoDL_Primitives=LM_None;break ;
					default 						 : AXDL_State=Awaiting_Connection ;LMtoDL_Primitives=LM_None;break;
 }
		switch (DLStoDL_Primitives) {
		case DL_CONNECTRequest		:	//Discard The Queue ?? Setting Empty Flag to 1 ?
																DL_Flags.Layer3Init=1;
																AXDL_State=Awaiting_Connection; 
																DLStoDL_Primitives=DL_None; break;
		case DL_DATARequest 			:  //Push to Queue ?
																 break;
		default 									: AXDL_State=Awaiting_Connection;DLStoDL_Primitives=DL_None;break;
	}
	if(T1_Expired==1){
		if(RC==DL_Flags.N2){
		//	discard I framequeue Setting Empty Flag to 1 ?
    //DL-ERRORindication(g)
		DLtoDLS_Primitives=DL_DISCONNECTIndicate;
		AXDL_State=Disconnected;
		}else{
		RC++;
		AX_SendConfig.Frame_Type=U_Frame;
		AX_SendConfig.SSID_C=Command;
		AX_Send.AX_UControl=SABM_1;
		AX_BuildFrame(&AX_SendConfig);
		AX_SelectT1();
		//start T1
			}
	}		
}
//-------------------------------------------------------//
 void AX_AwaitingConnectionHandler(void){
	 if(AX_ReceiveConfig.Frame_Type==U_Frame){
			switch (AX_Received.AX_UControl) {
				case    DM_1  : 	DLtoDLS_Primitives=DL_DISCONNECTIndicate;
													//stop T1
													//Discard Frame Queue  Setting Empty Flag to 1 ?
													AXDL_State=Disconnected;break;
													
				case 		UA_1  :   if(DL_Flags.Layer3Init==1){
													DLtoDLS_Primitives=DL_CONNECTConfirm;
													}else{
														if(V_S!=V_A){
															//discard Queue Setting Empty Flag to 1 ?
															DLtoDLS_Primitives=DL_CONNECTIndicate;
														}
													}
													//stop T1 T3
													AX_SelectT1();
													V_S=0;V_A=0;V_R=0;
													AXDL_State=Connected;break;

				default  			:   AXDL_State=Awaiting_Connection;
													break;			
			}
		}
	else{
		AXDL_State=Awaiting_Connection;
	}
 }
//-------------------------------------------------------//
 void AX_SelectT1(void){
	 if(RC==0){
	  DL_Flags.SRT=DL_Flags.SRT*(7/8)+(1/8)*T1-(1/8)*T1_Remaining;
		T1=DL_Flags.SRT*2;
	 } else {
		 	 if(T1_Expired==0){
				T1=2*(RC+1)*DL_Flags.SRT;
			 }
 }
}	 
//-------------------------------------------------------//

/*
 Parameters
 Maximum Number of Octets in an I Field (N1)
The default maximum number of octets allowed in the I field is 256. This variable is negotiable between end
stations. The I field is an integral number of octets.
 Maximum Number of Retries (N2)
The maximum number of retries is used in conjunction with the T1 timer.
 Maximum Number of I Frames Outstanding (k)
The maximum number of I frames outstanding at a time is seven (modulo 8) or 127 (modulo 128
*/
void AX_SetV20(void){
	/*
			Modulo <-- 8
N1R <-- 2048??
kR <-- 4 ??
	*/
		k=7;
		DL_Flags.N1=256;
		T2= 3000;
		DL_Flags.N2=10;
}
//-------------------------------------------------------//
void AX_DisconnectHandler(void) {
		if(AX_ReceiveConfig.Frame_Type==U_Frame){
			switch (AX_Received.AX_UControl) {
				case 		SABM_1 :  AX_SendConfig.SSID_C=Resp;
													AX_SendConfig.Frame_Type=U_Frame;
													if(AX_ConnectionStatus==AVAILABLE){
													AX_SetV20();
													AX_Send.AX_UControl=UA_1;
													AX_ClearExceptionConditions();
													V_S=0;V_A=0;V_R=0;
													DLtoDLS_Primitives=DL_CONNECTIndicate;
													DL_Flags.SRT=SRT_Default;
													DL_Flags.T1V=2*DL_Flags.SRT;
													//start T3 
													AXDL_State=Connected;
													}else {
														AX_Send.AX_UControl=DM_1;
														AXDL_State=Disconnected;
													}
													AX_BuildFrame(&AX_SendConfig);
													break;
				case    DM_1  : 	AXDL_State=Disconnected;break;
				case 		UA_1  :   AXDL_State=Disconnected;break; //DL Error C,D
				case 		UI_0  :		AXDL_State=Disconnected;break;
				default  			:   AX_SendConfig.SSID_C=Resp;
													AX_SendConfig.Frame_Type=U_Frame;
													AX_Send.AX_UControl=DM_1;
													AXDL_State=Disconnected; 
													AX_BuildFrame(&AX_SendConfig);
													break;			
			}
		}
		else {
			if(AX_ReceiveConfig.PF_Bit==PF) {
			AX_SendConfig.SSID_C=Resp;
			AX_SendConfig.Frame_Type=U_Frame;
			AX_Send.AX_UControl=DM_1;
			AX_BuildFrame(&AX_SendConfig);
			}
		}
		
}
//-------------------------------------------------------//
void AX_AwaitingReleaseState(void) {
	switch (LMtoDL_Primitives) {
					case LM_DATAIndicate : AX_FrameProcess(); AX_AwaitingReleaseHandler(); LMtoDL_Primitives=LM_None;break ;
					default 						 : AXDL_State=Awaiting_Release ;LMtoDL_Primitives=LM_None;break;
 }
		switch (DLStoDL_Primitives) {
				case DL_DISCONNECTRequest:AX_SendConfig.SSID_C=Resp;
																	AX_SendConfig.Frame_Type=U_Frame;
																	AX_Send.AX_UControl=DM_1;
																	AX_SendConfig.Expedited=1;
																	AXDL_State=Disconnected; 
																	AX_BuildFrame(&AX_SendConfig);
																	//stop T1
																	DLStoDL_Primitives=DL_None; break;

					default 							: AXDL_State=Awaiting_Release;DLStoDL_Primitives=DL_None;break;
	}
		if(T1_Expired==1){
		if(RC==DL_Flags.N2){
		//	discard I framequeue  Setting Empty Flag to 1 ?
    //DL-ERRORindication(g)
		DLtoDLS_Primitives=DL_DISCONNECTConfirm;
		AXDL_State=Disconnected;
		}else{
		RC++;
		AX_SendConfig.Frame_Type=U_Frame;
		AX_SendConfig.SSID_C=Command;
		AX_Send.AX_UControl=DISC_1;
		AX_BuildFrame(&AX_SendConfig);
		AX_SelectT1();
		//start T1
			}
}
}

//------------------------------------------------------//
void AX_AwaitingReleaseHandler(void) {
	if(AX_ReceiveConfig.Frame_Type==U_Frame){
			switch (AX_Received.AX_UControl) {
				case 		SABM_1 :  AX_SendConfig.SSID_C=Resp;
													AX_SendConfig.Frame_Type=U_Frame;
													AX_Send.AX_UControl=DM_1;
													AX_SendConfig.Expedited=1;
													AX_BuildFrame(&AX_SendConfig);
													AXDL_State=Awaiting_Release;
													break;
				case    DISC_1: 	AX_SendConfig.SSID_C=Resp;
													AX_SendConfig.Frame_Type=U_Frame;
													AX_Send.AX_UControl=UA_1;
													AX_SendConfig.Expedited=1;
													AX_BuildFrame(&AX_SendConfig);
													AXDL_State=Disconnected;break;
				case    DM_1	:		DLtoDLS_Primitives=DL_DISCONNECTConfirm;
													//stop T1
													AXDL_State=Disconnected;break;
				case 		UA_1  :   DLtoDLS_Primitives=DL_DISCONNECTConfirm;
													//stop T1
													AXDL_State=Disconnected;break;
				case 		UI_1  :		AX_SendConfig.SSID_C=Resp;
													AX_SendConfig.Frame_Type=U_Frame;
													AX_Send.AX_UControl=DM_1;
													AX_BuildFrame(&AX_SendConfig);
													AXDL_State=Awaiting_Release;break;
				default  			: 	AXDL_State=Awaiting_Release; 
													break;			
			}
		}
		else {
			if(AX_ReceiveConfig.PF_Bit==PF) {
			AX_SendConfig.SSID_C=Resp;
			AX_SendConfig.Frame_Type=U_Frame;
			AX_Send.AX_UControl=DM_1;
			AX_BuildFrame(&AX_SendConfig);
			}
		}
}

//------------------------------------------------------//
void AX_ConnectedState(void) {
	switch (LMtoDL_Primitives) {
					case LM_DATAIndicate : AX_FrameProcess(); AX_ConnectedHandler(); LMtoDL_Primitives=LM_None;break ;
					default 						 : AXDL_State=Awaiting_Release ;LMtoDL_Primitives=LM_None;break;
 }
		switch (DLStoDL_Primitives) {
				case DL_CONNECTRequest	:		//Discard Frame Queue  Setting Empty Flag to 1 ?
																	AX_EstablishDataLink();
																	DL_Flags.Layer3Init=1;
																	AXDL_State=Awaiting_Connection;
																	DLStoDL_Primitives=DL_None;break;
				case DL_DISCONNECTRequest:		//Discard Frame Queue   Setting Empty Flag to 1 ?
																	RC=0;
																	AX_SendConfig.Frame_Type=U_Frame;
																	AX_SendConfig.SSID_C=Command;
																	AX_Send.AX_UControl=DISC_1;
																	AX_BuildFrame(&AX_SendConfig);
																	//STOP T3  START T1 
																	AXDL_State=Awaiting_Release;
																	DLStoDL_Primitives=DL_None;break;
				case DL_DATARequest			: //Push on I Frames Queue  I_Receive_Queue
																	DLtoDLS_Primitives=DL_DATAIndicate;
																	AXDL_State=Connected;
																	DLStoDL_Primitives=DL_None;break;
	}
		while(I_Q_Send[Q_Send_Counter].Empty==0){
			if(DL_Flags.PRB==0){
				if(V_S!=V_A+k){
					N_S=V_S;
					N_R=V_R;
					if(I_Q_Send[Q_Send_Counter+1].Empty==0)
					{AX_SendConfig.PF_Bit=None;}
					else 
					{AX_SendConfig.PF_Bit=PF;}
					AX_SendConfig.Frame_Type=I_Frame;
					AX_SendConfig.SSID_C=Command;
					AX_BuildFrame(&AX_SendConfig);
					V_S++;
					Q_Send_Counter++;
					DL_Flags.AckPend=0;
					//T1 runining ? T1 run / stop T3 
			}else{//Push I Frames on Queue
			}
		}else {//Push I Frames on Queue
			}
		AXDL_State=Connected;
	}	
		
}

//------------------------------------------------------//
void AX_ConnectedHandler(void){
	if(AX_ReceiveConfig.Frame_Type==U_Frame){
			switch (AX_Received.AX_UControl) {
				case 		SABM_1 :  AX_SendConfig.SSID_C=Resp;
													AX_SendConfig.Frame_Type=U_Frame;
													AX_Send.AX_UControl=UA_1;
													AX_BuildFrame(&AX_SendConfig);
													AX_ClearExceptionConditions();
													DLtoDLS_Primitives=DL_ERRORIndicate;
													DL_Error=F;
													if(V_S!=V_A){
														//Discard Queue 
														DLtoDLS_Primitives=DL_CONNECTIndicate;
													}
													V_S=0;V_A=0;V_R=0;
													//stop T1 start T3
													AXDL_State=Connected;
													break;
				case    DISC_1: 	AX_SendConfig.SSID_C=Resp;
													AX_SendConfig.Frame_Type=U_Frame;
													AX_Send.AX_UControl=UA_1;
													AX_BuildFrame(&AX_SendConfig);
													DLtoDLS_Primitives=DL_DISCONNECTIndicate;
													//stop T1 T3
													AXDL_State=Disconnected;break;
				case    DM_1	:		DLtoDLS_Primitives=DL_ERRORIndicate;
													DL_Error=E;
													DLtoDLS_Primitives=DL_DISCONNECTIndicate;
													//stop T1 T3
													AXDL_State=Disconnected;break;
				case 		UA_1  :   DLtoDLS_Primitives=DL_ERRORIndicate;
													DL_Error=C;
													AX_EstablishDataLink();
													DL_Flags.Layer3Init=0;
													AXDL_State=Awaiting_Connection;break;
				case 		FRMR_1 :  DLtoDLS_Primitives=DL_ERRORIndicate;
													DL_Error=K;
													AX_EstablishDataLink();
													DL_Flags.Layer3Init=0;
													AXDL_State=Awaiting_Connection;break;	
			}
		}
		else if(AX_ReceiveConfig.Frame_Type==S_Frame){
			switch (AX_Received.AX_SControl){
				case RR_1 : DL_Flags.PRB=0;
										AX_EnquiryResponse(); 
										V_A=AX_ReceiveConfig.NR; 
										if (V_A==V_S) {
											AX_ChechIAcked();
											AXDL_State=Connected;
										}else{
											AX_NR_ErrorRecovery();
											AXDL_State=Awaiting_Connection;
										}
										break;
				case RR_0 : DL_Flags.PRB=0;
										DLtoDLS_Primitives=DL_ERRORIndicate;
										DL_Error=A;
										V_A=AX_ReceiveConfig.NR; 
										if (V_A==V_S) {
											AX_ChechIAcked();
											AXDL_State=Connected;
										}else{
											AX_NR_ErrorRecovery();
											AXDL_State=Awaiting_Connection;
										}
										break;
				case RNR_1 : DL_Flags.PRB=1;
										AX_EnquiryResponse(); 
										V_A=AX_ReceiveConfig.NR; 
										if (V_A==V_S) {
											AX_ChechIAcked();
											AXDL_State=Connected;
										}else{
											AX_NR_ErrorRecovery();
											AXDL_State=Awaiting_Connection;
										}
										break;
				case RNR_0 : DL_Flags.PRB=1;
										DLtoDLS_Primitives=DL_ERRORIndicate;
										DL_Error=A;
										V_A=AX_ReceiveConfig.NR; 
										if (V_A==V_S) {
											AX_ChechIAcked();
											AXDL_State=Connected;
										}else{
											AX_NR_ErrorRecovery();
											AXDL_State=Awaiting_Connection;
										}
										break;
				case SREJ_0: DL_Flags.PRB=0;
										DLtoDLS_Primitives=DL_ERRORIndicate;
										DL_Error=A;
										V_A=AX_ReceiveConfig.NR; 
										if (V_A==V_S) {
										}else{
											AX_NR_ErrorRecovery();
											AXDL_State=Awaiting_Connection;
										}break;
				case SREJ_1: DL_Flags.PRB=0;
										AX_EnquiryResponse(); 
										V_A=AX_ReceiveConfig.NR; 
										if (V_A==V_S) {
											if(AX_ReceiveConfig.PF_Bit==PF){
											V_A=AX_ReceiveConfig.NR;
											}
										}else{
											AX_NR_ErrorRecovery();
											AXDL_State=Awaiting_Connection;
										}break;
				case REJ_0 : DL_Flags.PRB=0;
										DLtoDLS_Primitives=DL_ERRORIndicate;
										DL_Error=A;
										V_A=AX_ReceiveConfig.NR; 
										if (V_A==V_S) {
											//stop T1,T3
											AX_SelectT1();
											AX_InvokeRetransmission();
											AXDL_State=Connected;
										}else {
											AX_NR_ErrorRecovery();
											AXDL_State=Awaiting_Connection;
										}
										break;
				case REJ_1 : DL_Flags.PRB=0;
										AX_EnquiryResponse(); 
										V_A=AX_ReceiveConfig.NR; 
										if (V_A==V_S) {
											//stop T1,T3
											AX_SelectT1();
											AX_InvokeRetransmission();
											AXDL_State=Connected;
										}else{
											AX_NR_ErrorRecovery();
											AXDL_State=Awaiting_Connection;
										}
										break;
			}
		}else if(AX_ReceiveConfig.Frame_Type==I_Frame){
			if(AX_ReceiveConfig.SSID_C==Command){
				if(AX_Received.AX_Length<=DL_Flags.N1){
						V_A=AX_ReceiveConfig.NS;
						if(V_A==V_S){
							//AX_CheckIAck();
							if(DL_Flags.ORB==1){
							//Discard content of I FRame
								if(AX_ReceiveConfig.PF_Bit==PF){
									AX_SendConfig.NR=V_R;
									AX_SendConfig.PF_Bit=PF;
									AX_SendConfig.Frame_Type=S_Frame;
									AX_Send.AX_SControl=RNR_1;
									AX_BuildFrame(&AX_SendConfig);
									DL_Flags.AckPend=0;
									AXDL_State=Connected;
								}else{
									AXDL_State=Connected;
								}
							}else{
								if(AX_ReceiveConfig.NR==V_S){
									DL_Flags.RejExc=0;
									if(DL_Flags.SREJExc>0){
									DL_Flags.SREJExc--;
									}
									DLtoDLS_Primitives=DL_DATAIndicate;
									while(I_Q_Receive[V_R].Empty==0){ // 1 ? 
									 if(I_Q_Receive[V_R].Seq==V_R){
										 //Copy Array Prefered 
									 *I_Q_Receive[V_R].Data=*AX_Send.AX_Data;
										 I_Q_Receive[V_R].Data_Length=AX_Send.AX_Length;
											//I_Q_R Empty =0;
										 DLtoDLS_Primitives=DL_DATAIndicate;
										V_R++;
									 }
									}
									if(AX_ReceiveConfig.PF_Bit==PF){
										goto P_1; 
										AXDL_State=Connected;
									}else{
										if(DL_Flags.AckPend==0){
											DLtoLM_Primitives=LM_SEIZERequest;
											DL_Flags.AckPend=1;
											AXDL_State=Connected;
									}else{
										
									}
									}
									}else{
										if(DL_Flags.RejExc==1){
											//Discard I Contents
											if(AX_ReceiveConfig.PF_Bit==PF){
										P_1:
												AX_SendConfig.NR=V_R;
									AX_SendConfig.PF_Bit=PF;
									AX_SendConfig.Frame_Type=S_Frame;
									AX_Send.AX_SControl=RR_1;
									AX_BuildFrame(&AX_SendConfig);
									DL_Flags.AckPend=0;
									}
								}else{
								//SREJ Disablled
									//discard I Fame
									DL_Flags.RejExc=1;
									AX_SendConfig.NR=V_R;
									AX_SendConfig.PF_Bit=PF;
									AX_SendConfig.Frame_Type=S_Frame;
									AX_Send.AX_SControl=REJ_1;
									AX_BuildFrame(&AX_SendConfig);
									DL_Flags.AckPend=0;
								}
							}
						}
					}else{
							AX_NR_ErrorRecovery();
						}
				}else{
					DL_Error=O;
					AX_EstablishDataLink();
					DL_Flags.Layer3Init=0;
					AXDL_State=Awaiting_Connection;
				}
				}else{
				DL_Error=S;
			//Discard I Frame
			}
			
		}			
		if((DL_Error==L)||(DL_Error==M)||(DL_Error==N)){
		//Discard Frame Queue  Setting Empty Flag to 1 ?
																	AX_EstablishDataLink();
																	DL_Flags.Layer3Init=1;
																	AXDL_State=Awaiting_Connection;
																	DLtoDLS_Primitives=DL_ERRORIndicate;
		}
		if(T1_Expired==1){
			
		}
		if(T3_Expired==1){
			
		}
	
}

//------------------------------------------------------//
//to be checked Again !!!
void AX_InvokeRetransmission(void){
	u8 x=V_S;
	AX_ReceiveConfig.NR=V_S;
	while (V_S != x) {
	AX_SendConfig.Frame_Type=I_Frame;
	// Push old I frame 
	 AX_BuildFrame(&AX_SendConfig);
	V_S++;
	}

}

//------------------------------------------------------//

void AX_NR_ErrorRecovery(void) {
	DLtoDLS_Primitives=DL_ERRORIndicate;
	DL_Error=J;
	AX_EstablishDataLink();
	DL_Flags.Layer3Init=0;
}

//------------------------------------------------------//
void AX_EnquiryResponse(void) {
	if(AX_ReceiveConfig.SSID_C==Command){
			N_R=V_R;
	AX_SendConfig.SSID_C=Command;
		AX_SendConfig.Frame_Type=S_Frame;
	if(DL_Flags.ORB==1){
		AX_Send.AX_SControl=RNR_1;
	}else {
				AX_Send.AX_SControl=RR_1;
	}
	DL_Flags.AckPend=0;
}
}

//-----------------------------------------------------//

void AX_TimerRecoveryState(void)	{
}
//-----------------------------------------------------//
void AX_BuildFrame(AX_Config_t *Copy_AXConfig){
	//Setting SSID Byte as command or respond 
		// in I Frames this needs to be set using the configuration 
		// S, U this can be set while building as each frame SSID is fixed
		if(Copy_AXConfig->SSID_C==Command){
			AX_Send.AX_Dest_SSID=SSID_C_1;
			AX_Send.AX_Src_SSID=SSID_C_0;
		}
		else if(Copy_AXConfig->SSID_C==Resp){
			AX_Send.AX_Dest_SSID=SSID_C_0;
			AX_Send.AX_Src_SSID=SSID_C_1;
	}
		
		//Setting  Address for source and distenation  SSID to the Send Array
			cpyArr(&AX_SendArray[0],&AX_Send.AX_Start_Flag,1);
		  cpyArr(&AX_SendArray[1],Dest_ADD,6);
			cpyArr(&AX_SendArray[7],&AX_Send.AX_Dest_SSID,1);
			cpyArr(&AX_SendArray[8],MY_ADD,6);
			cpyArr(&AX_SendArray[14],&AX_Send.AX_Src_SSID,1);


	//Setting Control Fields 
	switch (Copy_AXConfig->Frame_Type){
		case I_Frame: CLR_BIT(AX_Send.AX_IControl,0);  //start with 0
										MSK_3BIT(AX_Send.AX_IControl,1,AX_SendConfig.NS);
										MSK_1BIT(AX_Send.AX_IControl,4,AX_SendConfig.PF_Bit);
										MSK_3BIT(AX_Send.AX_IControl,5,AX_SendConfig.NR);
										cpyArr(&AX_SendArray[15],&AX_Send.AX_IControl,1);
									u8 i=0;
									while (AX_SendConfig.NS != I_Q_Send[i].Seq){
										i++;
									}
									//AX_Send.AX_Length= I_Q_Send[i].Data_Length;  //Setting the Length Field
									cpyArr(&AX_SendArray[16],&I_Q_Send[i].Data_Length,1);
									cpyArr(&AX_SendArray[17],I_Q_Send[i].Data,I_Q_Send[i].Data_Length);  //Loading the Data (SSP Frame to the Info field)
									//CRC Function Call to calculate the CRC 
									cpyArr(&AX_SendArray[17+I_Q_Send[i].Data_Length],&AX_Send.AX_FCS,2);
									cpyArr(&AX_SendArray[17+I_Q_Send[i].Data_Length+2],&AX_Send.AX_End_Flag,1);
									i=0;
									break;
		case U_Frame:		*AX_Send.AX_Data=NULL;
									  AX_Send.AX_Length=0; //No length or Data Field in U Frames used in the Driver ;
										cpyArr(&AX_SendArray[15],&AX_Send.AX_UControl,1);
										//CRC Function in 16,17 
										cpyArr(&AX_SendArray[18],&AX_Send.AX_End_Flag,1);								
										//AX_SendFrame(USART_1);
										break;
		case S_Frame:		*AX_Send.AX_Data=NULL;
									  AX_Send.AX_Length=0; //No length or Data Field in S Frames used in the Driver ;
										cpyArr(&AX_SendArray[15],&AX_Send.AX_SControl,1);
										//CRC Function in 16,17 
										cpyArr(&AX_SendArray[18],&AX_Send.AX_End_Flag,1);
										//AX_SendFrame(USART_1);
										break;			
	}
	if(AX_SendConfig.Expedited==0){
	DLtoLM_Primitives=LM_DATARequest;
	enqueue(&awaiting_queue,DLtoLM_Primitives,DataLink_Id);
	}
	else{
	DLtoLM_Primitives=LM_EXPEDITEDDATARequest;
	enqueue(&awaiting_queue,DLtoLM_Primitives,DataLink_Id);
	AX_SendConfig.Expedited=0;
	}
}
//---------------------------------------------------------------------------------------//

void  AX_FrameProcess(void){
	AX_FRAME_Struct AX_TempReceived;
	AX_Config_t AX_TempReceivedConfig;
	if(AX_ReceiveArray[0]==AX_FLAG){
		//Put the src and dest Adresses to the global struct
		  cpyArr(AX_TempReceived.AX_Dest_Add,&AX_ReceiveArray[1],6);
			cpyArr(AX_TempReceived.AX_Src_Add,&AX_ReceiveArray[8],6);
		if (cmpArr(&AX_ReceiveArray[1],&MY_ADD,6)){
						if((GET_BYTE(AX_ReceiveArray[7],0)==SSID_C_0)&&(GET_BYTE(AX_ReceiveArray[14],0)==SSID_C_1)){
					AX_TempReceivedConfig.SSID_C=Resp;}
			else if((GET_BYTE(AX_ReceiveArray[7],0)==SSID_C_1)&&(GET_BYTE(AX_ReceiveArray[14],0)==SSID_C_0)){
					AX_TempReceivedConfig.SSID_C=Command;}
			else {
				//means they're Using seconed repeater which is yet not supported in this driver
			}
			 u8 x= GET_BIT(AX_ReceiveArray[15],0);	//Get the first bit of Control 
			AX_TempReceivedConfig.PF_Bit=GET_3BIT(AX_ReceiveArray[15],4);
			
		if(x==0){ 
			//Update the global struct config 
			AX_TempReceivedConfig.Frame_Type=I_Frame;
			AX_TempReceived.AX_IControl=AX_ReceiveArray[15];
			//I Frame
			AX_TempReceived.AX_Length=AX_ReceiveArray[16]; //Get the length of the data
			//Check if there is flag at the end of the frame
			if(AX_ReceiveArray[17+AX_Received.AX_Length+2]!=AX_FLAG){
				AX_TempReceivedConfig.Error=N;  
				//Error in the length of the frame
			}
			//Check CRC Here !!!!!! 
		
			//Copy the Data(SSP) to the global struct Data Feild 
			cpyArr(&AX_TempReceived.AX_Data,&AX_ReceiveArray[17],AX_TempReceived.AX_Length); //USED Length Byte as only the Data size
			//Check the NR NS
				AX_TempReceivedConfig.NS=GET_3BIT(AX_ReceiveArray[15],1);
				AX_TempReceivedConfig.NR=GET_3BIT(AX_ReceiveArray[15],5);
			
		}		
		else if (x==1){ 
			//Check if there is flag at the end of the frame
			if(AX_ReceiveArray[18]!=AX_FLAG){
				AX_ReceiveConfig.Error=N;//Drop the frame 
			//Send error Frame (REJ or SREJ)?? 
			}
			x= GET_BIT(AX_ReceiveArray[15],1);
			if(x==1){ //U Frame
				AX_ReceiveConfig.Frame_Type=U_Frame;
				//U Frame 
				/*
				switch (AX_ReceiveArray[15]){
					case 0x3F:AX_Received.AX_UControl=SABM_1;AX_ReceiveConfig.SSID_C=Command;break;
					case 0x73:AX_Received.AX_UControl=UA_1;AX_ReceiveConfig.SSID_C=Resp;break;
					case 0x1F:AX_Received.AX_UControl=DM_1;AX_ReceiveConfig.SSID_C=Resp;break;
					case 0x53:AX_Received.AX_UControl=DISC_1;AX_ReceiveConfig.SSID_C=Command;break;
				}*/
				AX_TempReceived.AX_UControl=AX_ReceiveArray[15];
				
			}
			else if(x==0){
				AX_ReceiveConfig.Frame_Type=S_Frame;
			//S Frame 
				//SS bits in Control 
				/*
				switch (GET_5BIT(AX_ReceiveArray[15],0)){
					case 0x11:AX_Received.AX_SControl=RR_1;break;
					case 0x15:AX_Received.AX_SControl=RNR_1;break;
					case 0x19:AX_Received.AX_SControl=REJ_1;break;
					case 0x1D:AX_Received.AX_SControl=SREJ_1;break;
					case 0x0D:AX_Received.AX_SControl=SREJ_0;break;
				} 
				*/
				AX_TempReceived.AX_SControl=GET_5BIT(AX_ReceiveArray[15],0);
				AX_TempReceivedConfig.NR=GET_3BIT(AX_ReceiveArray[15],5);				
				}
			}
	  	}
		if(AX_TempReceivedConfig.Error==Error_None){
			if(AX_TempReceivedConfig.Frame_Type==I_Frame){
			AX_Received.AX_IControl=AX_TempReceived.AX_IControl;
			cpyArr(&AX_Received.AX_Data,&AX_TempReceived.AX_Data,AX_TempReceived.AX_Length); //USED Length Byte as only the Data size
			}
			AX_Received.AX_SControl=AX_TempReceived.AX_SControl;
			AX_Received.AX_UControl=AX_TempReceived.AX_UControl;
			AX_ReceiveConfig.Frame_Type=AX_TempReceivedConfig.Frame_Type;
			AX_ReceiveConfig.PF_Bit=AX_TempReceivedConfig.PF_Bit;
			AX_ReceiveConfig.SSID_C=AX_TempReceivedConfig.SSID_C;
			AX_ReceiveConfig.NR=AX_TempReceivedConfig.NR;
			AX_ReceiveConfig.NS=AX_TempReceivedConfig.NS;
		}
	}
}


//-------------//
u8 SSP_FrameS[256];
u8 SSP_FrameR[256];
void SSP_TaskGCS(void){
  
	//rx array
	//
	//Sending Connection request
	DLStoDL_Primitives=	DL_CONNECTIndicate;
	//waiting for the confirm
	if(DLtoDLS_Primitives==DL_CONNECTConfirm){
	// Sending The Data (requesting to send the data)
	DLStoDL_Primitives = DL_DATARequest;
		//Copy Arrays or pointers
	*I_Q_Send[0].Data=*SSP_FrameS;
		//Assigning SSP to I frame to be Send 
	}
	//Waiting for the received respond data
	if(DLtoDLS_Primitives==DL_DATAIndicate){
		//copy arrays or pointers 
		*SSP_FrameR=*I_Q_Receive[0].Data;
		//Sending to the GUI
		DLStoDL_Primitives=DL_DISCONNECTRequest;
	}
	

}

void SSP_TaskOBC(void){
	if(DLtoDLS_Primitives==DL_CONNECTIndicate){
	//Connection Established 
	}
	if(DLtoDLS_Primitives=DL_DATAIndicate){
	*SSP_FrameR=*I_Q_Receive[0].Data;
	//Function to Process The SSP Frame and call the Task e.g read the Temp
	// and build the SSP_FrameS
		//waiting for a Flag from this Function ?
		//Data_Ready==1?
		DLStoDL_Primitives=DL_DATARequest;
	}
	if(DLtoDLS_Primitives==DL_DISCONNECTIndicate){
		//Disconnected 
	}
}

void SSP_Process(void){
//Process the ssp
	
//lookup table for the task function 
	//array of Function pointers ?
	
}

void SSP_Task1(void) {
//The Task e.g reading the temp sensor 
	//building the SSP_FrameS
	//Setting Data_Ready Flag
}