
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