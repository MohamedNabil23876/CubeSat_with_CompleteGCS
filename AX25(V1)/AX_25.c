/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  AX_25_C
 *       Module:  -
 *
 *  Description:   C program for the AX25 Functions     
 *  
 *********************************************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "string.h"
#include "AX_25_interface.h"
#include "USART_interface.h"
const u8 CubeSat_Add[6] ={0x03,0x94,0x6A,0x7C};
const u8 GCS_Add[6] ={0x59,0xA0,0x9E};

#define MY_ADD   GCS_Add

/*Functions to copy and compare arrays */

void cpyArr(u8 *Arr1,u8 *Arr2,u8 size){
    for(u8 i=0;i<size;i++){
        Arr1[i]=Arr2[i];
    }
}
u8 cmpArr(u8 *Arr1,u8 *Arr2,u8 size){
    for(u8 i=0;i<size;i++){
       if( Arr1[i]!=Arr2[i]){
				 return 0;
    }
	}
			 return 1;
}
AX_ConnectionStatus_t AX_ConnectionStatus;
Receive_Mood_t Mood=Normal;
u8 I_resendN[4];
u8 Resend_index =0;
u8 I_SREJ[4];   //Array to save the N(R) of I Frame ro send SREJ 
u8 SREJ_Available = 3 ;  // Window/2 
seqn_Recovery_t Recov_Type=SREJ;
u8 CopySSP_Frame[256]; //Data of SSP 
u8 CopySSP_Length;    //The length of SSP Frame
u8 AX_NoIFrames;     // I Frames needs to be Send 
AX_State_t AX_State=Disconnected;  //DataLink Current state  of the State machine 
I_Queue_struct I_Q_Send[8]; // the number of Buffers as window size 
I_Queue_struct I_Q_Receive[8]; 
u8 W=7;

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
  .Error=OK,
  };
 AX_Config_t AX_ReceiveConfig={
	.Error=OK,
 };

	//global arrays to send and recive 
u8 AX_SendArray[256+24];  
u8 AX_ReceiveArray[256+24];

	// sequence numbers 
	u8 V_S,V_A,V_R=0;    
	u8 N_S,N_R=0;
	
	

/*************************************************************************
 *     Function @GCS  																									 *
 *		 Send U (SABM) 																										 *
 *		 wait for the respond to connect (UA) or diconnecte (DM) 		       *
 *     Calls the Receive function and start timer T1                     *
 *************************************************************************/
void AX_InitConncetion(){
		if(AX_State==Disconnected){
			cpyArr(&AX_Send.AX_Src_Add,&GCS_Add,6);
			cpyArr(&AX_Send.AX_Dest_Add,&CubeSat_Add,6);
			AX_SendConfig.SSID_C=Command;
			AX_Send.AX_UControl=SABM_1;
			AX_BuildFrame(&AX_SendConfig);
	}
	//wait for respond 
	//Set a timer  and resend SABM if no response  is recived 
	AX_ReceiveFrame(USART_1,&AX_ReceiveArray);
	//
	}

	
/********************************************************************************
 *		Function processing the Received  Frame @OBC/GCS                          *
 * 		Receive Frame Array and assign it to the frame struct and Config struct 	* 
 *		Calls The Error  Function                                              		*
 ********************************************************************************/
	
void  AX_ReceiveFrameGA(void){
	u8 NS_Check;
	if(AX_ReceiveArray[0]==AX_FLAG){
		//Put the src and dest Adresses to the global struct
		  cpyArr(&AX_Received.AX_Dest_Add,&AX_ReceiveArray[1],6);
			cpyArr(&AX_Received.AX_Src_Add,&AX_ReceiveArray[8],6);
		if (!cmpArr(&AX_Received.AX_Dest_Add,&MY_ADD,6)){
			AX_ReceiveConfig.Error=ADD_ERROR;//Drop the Frame 
		 //Sending Error Frame Wrong Address 	
		 //goto ErrorRecovery Function 
		}else{
			 u8 x= GET_BIT(AX_ReceiveArray[15],0); //Get the first bit of Control 
		if(x==0){ 
			if(Mood==Normal){
			//Update the global struct config 
			AX_ReceiveConfig.Frame_Type=I_Frame;
			AX_Received.AX_IControl=AX_ReceiveArray[15];
			//Check if its I command or  Respond 
			if((GET_BYTE(AX_ReceiveArray[7],0)==SSID_C_0)&&(GET_BYTE(AX_ReceiveArray[14],0)==SSID_C_1)){
					AX_ReceiveConfig.SSID_C=Resp;}
			else if((GET_BYTE(AX_ReceiveArray[7],0)==SSID_C_1)&&(GET_BYTE(AX_ReceiveArray[14],0)==SSID_C_0)){
					AX_ReceiveConfig.SSID_C=Command;}
			else {
				AX_ReceiveConfig.Error=SSID_ERROR; //DRop the Frame
				//Send Error Frame if its not command or respond (means they're Using seconed repeater which is yet not supported in this driver)
			/*if(MAX_SREJ<=3){
				NS_Check=GET_3BIT(AX_Received.AX_IControl,1);
				I_SREJ[MAX_SREJ]=NS_Check;
				MAX_SREJ++;
				//goto ErrorFunc_Calling;*/
				}
			//I Frame
			AX_Received.AX_Length=AX_ReceiveArray[16]; //Get the length of the data
			//Check if there is flag at the end of the frame
			if(AX_ReceiveArray[17+AX_Received.AX_Length+2]!=AX_FLAG){
				AX_ReceiveConfig.Error=FLAG_ERROR;   //Drop the Frame
				/*
			//Send error Frame (REJ or SREJ)?? 
				if(MAX_SREJ<=3){
				NS_Check=GET_3BIT(AX_Received.AX_IControl,1);
				I_SREJ[MAX_SREJ]=NS_Check;
				MAX_SREJ++;
			 //goto ErrorFunc_Calling;
			}*/
			}
			//Check CRC Here !!!!!! 
			//Copy the Data(SSP) to the global struct Data Feild 
			cpyArr(&AX_Received.AX_Data,&AX_ReceiveArray[17],AX_Received.AX_Length); //USED Length Byte as only the Data size
			//Check the if V(R) = NS and send error Frame if not 
			if(V_R!=(GET_3BIT(AX_ReceiveArray[15],1))){
				AX_ReceiveConfig.Error=SEQ_ERROR;
				u8 Frame_NS=GET_3BIT(AX_Received.AX_IControl,1);
			//Sending Error Frame with N_R
				if((Frame_NS-V_R)<SREJ_Available){
					for(u8 i=V_R;i<Frame_NS;i++){
						I_SREJ[3-SREJ_Available]=i;
						SREJ_Available--;
					}
				}else {
					Recov_Type=REJ;
			}}
			//Check if its POLL OR FINAL is set 
			if(GET_BIT(AX_Received.AX_IControl,4)==1){
					AX_ReceiveConfig.PF_Bit=PF;
			}
			V_R++; 
		}
		}		
		else if (x==1){ 
			//Check if there is flag at the end of the frame
			if(AX_ReceiveArray[18]!=AX_FLAG){
				AX_ReceiveConfig.Error=FLAG_ERROR;//Drop the frame 
			//Send error Frame (REJ or SREJ)?? 
			}
			x= GET_BIT(AX_ReceiveArray[15],1);
			if(x==1){ //U Frame
				AX_ReceiveConfig.Frame_Type=U_Frame;
				//U Frame
				switch (AX_ReceiveArray[15]){
					case 0x3F:AX_Received.AX_UControl=SABM_1;AX_ReceiveConfig.SSID_C=Command;break;
					case 0x73:AX_Received.AX_UControl=UA_1;AX_ReceiveConfig.SSID_C=Resp;break;
					case 0x1F:AX_Received.AX_UControl=DM_1;AX_ReceiveConfig.SSID_C=Resp;break;
					case 0x53:AX_Received.AX_UControl=DISC_1;AX_ReceiveConfig.SSID_C=Command;break;
				}
				
			}
			else if(x==0){
				AX_ReceiveConfig.Frame_Type=S_Frame;
			//S Frame //Updating The Acknowledegd  frames
				switch (GET_BYTE(AX_ReceiveArray[15],0)){
					case 0x11:AX_Received.AX_SControl=RR_1;V_A=GET_BYTE(AX_ReceiveArray[15],5);break;
					case 0x15:AX_Received.AX_SControl=RNR_1;V_A=GET_BYTE(AX_ReceiveArray[15],5);break;
					case 0x19:AX_Received.AX_SControl=REJ_1;V_A=GET_BYTE(AX_ReceiveArray[15],5)-1;break;
					case 0x1D:AX_Received.AX_SControl=SREJ_1;break;
					case 0x0D:AX_Received.AX_SControl=SREJ_0;break;
				} 
				if(AX_Received.AX_SControl==SREJ_0){
					I_resendN[Resend_index]=GET_BYTE(AX_ReceiveArray[15],5);
					Resend_index++;
					AX_ReceiveConfig.PF_Bit=Non;
				}else if(AX_Received.AX_SControl==SREJ_1){
					I_resendN[Resend_index]=GET_BYTE(AX_ReceiveArray[15],5);
					Resend_index=0;
					AX_ReceiveConfig.PF_Bit=PF;
				}
				
				
				}
			
				}
			AX_DLStateMachine();	
			}
		}
	}
	
/********************************************************************************
 *		Function Calls the state machine function @ OBC/GCS                 	    *
 * 		when An error free frame is received                                 		  * 
 ********************************************************************************/	
void AX_DLStateMachine(void){

//separate  state machine functions from the R/S functions 
		//Calling the state function that will build the correct response to the Frame
		if(cmpArr(&AX_Received.AX_Dest_Add,&CubeSat_Add,6)){  
					switch(AX_State){
						case Disconnected :AX_DisconnectedStateOBC();break;
						case Connected    :AX_ConnectedStateOBC(); break;
					}
				}else if(cmpArr(&AX_Received.AX_Dest_Add,&GCS_Add,6)){
					switch (AX_State){
						case Disconnected :AX_DisconnectedStateGCS();break;
						case Connected    :AX_ConnectedStateGCS();break;
					}
				}
}

	
/********************************************************************************
 *	  	Function 	@OBC / GCS 																										*
 *		That Build I Frame and complete the rest of U,S Frame      					 			* 
 ********************************************************************************/	
void AX_BuildFrame(AX_Config_t *Copy_AXConfig){
		//Setting  Address for source and distenation 
		  cpyArr(&AX_Send.AX_Src_Add,&AX_Received.AX_Dest_Add,6);
			cpyArr(&AX_Send.AX_Dest_Add,&AX_Received.AX_Src_Add,6);
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
	//Setting Control Fields 
	switch (Copy_AXConfig->Frame_Type){
		case I_Frame: CLR_BIT(AX_Send.AX_IControl,0);  //start with 0
									if(V_S!=N_S){ //checking 
										N_S++;      // inc the Sequence number Send
										MSK_3BIT(AX_Send.AX_IControl,1,N_S);
										}
									AX_Send.AX_Length= CopySSP_Length;  //Setting the Length Field
									cpyArr(AX_Send.AX_Data,CopySSP_Frame,AX_Send.AX_Length);  //Loading the Data (SSP Frame to the Info field)
									//CRC Function Call to calculate the CRC 
									//Sending the Frame using USART 1
									AX_SendFrame(USART_1);
									V_S++; //inc Variable Seq Num Send 
									break;
		case U_Frame:		*AX_Send.AX_Data=NULL;
									  AX_Send.AX_Length=0;
										//CRC Function
										AX_SendFrame(USART_1);
										break;
		case S_Frame:		*AX_Send.AX_Data=NULL;
									  AX_Send.AX_Length=0;
										//CRC Function
										AX_SendFrame(USART_1);
										break;			
	}
}

/********************************************************************************
 *	  	Data Link  State machine Functions 																	    * 
 ********************************************************************************/	
 
 /*Function : @OBC 
			 Process the First U (SABM)Frame  to initialise the connection 
			 Build the respond nd change the state of connection  ( UA Ack(connected) or the DM (Disconnected)*/
	void AX_DisconnectedStateOBC(void){ 
		if(AX_State==Disconnected){
		if(AX_ReceiveConfig.Frame_Type==U_Frame){
			if(AX_Received.AX_UControl==SABM_1){
				AX_SendConfig.SSID_C=Resp;
				AX_SendConfig.Frame_Type=U_Frame;
				if(AX_ConnectionStatus==AVAILABLE){
				AX_Send.AX_UControl=UA_1;
				V_S=0;
				V_A=0;
				V_R=0;
				AX_State=Connected;
			}
				else if (AX_ConnectionStatus==NOT_AVAILABLE){
				 AX_Send.AX_UControl=DM_1;
				AX_State=Disconnected;
			}
		
			AX_BuildFrame( &AX_SendConfig);
			}
		}
	}
		AX_ReceiveFrame(USART_1,&AX_ReceiveArray);
}
 
 
/* Function @GCS
			Changing The State To Connected if UA is Received
			clearing V_S V_A V_R in case of UA is Received
			and calling the connected Function
			recalling AX_ConnectedStateGCS incase of DM is recived*/
void AX_DisconnectedStateGCS(void){
	if(AX_State==Disconnected){
		if(AX_ReceiveConfig.Frame_Type==U_Frame){
			if(AX_Received.AX_UControl==UA_1){
				if((AX_SendConfig.Frame_Type==U_Frame)&&(AX_Send.AX_UControl==SABM_1)){
				AX_State=Connected;
				V_S=0;
				V_A=0;
				V_R=0;
				AX_ConnectedStateGCS();
				}
			}
			else if (AX_Received.AX_UControl==DM_1){
			AX_InitConncetion();
			}
			}
	}
}

/* Function @GCS 
			Sending I Commands Frame Then S (RR) 
			Receveing I Respond Frames and S(RR) 
			Sending DISC Frame
*/
 void AX_ConnectedStateGCS(){
	 if(AX_ReceiveConfig.Frame_Type==U_Frame){
		if (AX_Received.AX_UControl==UA_1){
			if((AX_SendConfig.Frame_Type==U_Frame)&&(AX_Send.AX_UControl==SABM_1)){
				for(u8 i=0;i<AX_NoIFrames;i++){
				AX_SendConfig.SSID_C=Command; 
				//Set P=0 and set it only when i=AX_NoIFrames
				if(i<(AX_NoIFrames-1)){
					CLR_BIT(AX_Send.AX_IControl,4);
					AX_SendConfig.PF_Bit=Non;
				}else if (i==(AX_NoIFrames-1)){
					SET_BIT(AX_Send.AX_IControl,4);
					AX_SendConfig.PF_Bit=PF;
					//start Timer T2
				} // in the USART Function check if P=1 to poll for the receive 
				AX_SendConfig.Frame_Type=I_Frame;
				AX_BuildFrame( &AX_SendConfig);
				}
			AX_ReceiveFrame(USART_1,&AX_ReceiveArray);
	 }else if ((AX_SendConfig.Frame_Type==U_Frame)&&(AX_Send.AX_UControl==DISC_1)){
		 	AX_State=Disconnected;
	 }
	 }
	 }
     if (AX_ReceiveConfig.Frame_Type==I_Frame){
		 I_Q_Receive[7-W].Seq=GET_3BIT(AX_Received.AX_IControl,1);
		 cpyArr(&I_Q_Receive[7-W].Data,AX_Received.AX_Data,AX_Received.AX_Length);
		 if (AX_ReceiveConfig.PF_Bit==Non){
			W--;
			AX_ReceiveFrame(USART_1,&AX_ReceiveArray);
			goto x;
		 }else if(AX_ReceiveConfig.PF_Bit==PF){
			 if(AX_ReceiveConfig.Error==SEQ_ERROR){
				 //Seq Receive Recovery Function
			 }else if (AX_ReceiveConfig.Error==OK){
				 W=0;
			 }
		 }
			}	 
	 //again 
	 else if(AX_ReceiveConfig.Frame_Type==S_Frame){
	  if(AX_Received.AX_SControl==REJ_1){ //Check NR 
			V_S=V_A;
			Mood=Recovery;
			//SeqN send Recovery Function 
			}else if (AX_Received.AX_SControl==SREJ_0){
				AX_ReceiveFrame(USART_1,&AX_ReceiveArray);
				goto x;
			}else if ((AX_Received.AX_SControl==SREJ_1)){
			Mood=Recovery;
				//SeqN send  Recovery Function
			}
	 }   if (Mood==Normal){			
		  AX_SendConfig.SSID_C=Command;
		  AX_SendConfig.Frame_Type=U_Frame;
		  AX_Send.AX_UControl=DISC_1;  //needs to be ack with ua before changing to the disconnected state 
		  AX_BuildFrame( &AX_SendConfig);  
		  AX_ReceiveFrame(USART_1,&AX_ReceiveArray);
		  goto x;
		  }
		  x:;
	  }

/* Function @OBC 

*/ 

void AX_ConnectedOBC(void){
	

}	
/*************************************************************************
 *     Function @GCS/OBC 																								 *
 *		 USART Interfacing Functions 															         *
 *************************************************************************/
		
void AX_SendFrame(USART_No_t AX_USART){
cpyArr(&AX_SendArray,&AX_Send.AX_Start_Flag,1);
cpyArr(&AX_SendArray[1],&AX_Send.AX_Dest_Add,6);
}
void AX_ReceiveFrame(USART_No_t AX_USART,u8 *Copy_RecievedData);