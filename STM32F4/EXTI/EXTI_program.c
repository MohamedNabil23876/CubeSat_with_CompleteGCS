/*********************************************************************************************************************
  *   FILE DESCRIPTION
  *  -------------------------------------------------------------------------------------------------------------------
  *         File:  EXTI_PROGRAM_C
  *       Module:  -
  *
  *  Description:   c source for the EXTI Functions  
  *  
  *********************************************************************************************************************/

  
 /**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"

void (*EXTI_CallBackFunc_LINE[23]) (void) ;


/**********************************************************************************************************************
 * Enable External interupt Line
 *********************************************************************************************************************/

 void EXTI_voidInteruptInit(EXTI_LINE Copyu8ID,EXTI_PORT Copyu8Port,EXTI_TRIG Copyu8Trig,EXTI_TYPE Copyu8Type,void (*CallBackFun) (void)){
	/*unmasking the interupt or the event*/
	switch(Copyu8Type){
		 case EXTI_INTERUPT :	 SET_BIT(EXTI_IMR,Copyu8ID);break;
		 case EXTI_EVENT 	:	 SET_BIT(EXTI_EMR,Copyu8ID);break;
		} 
	/*choosing the event trigger type */
	switch (Copyu8Trig){
		case EXTI_RISING 	 : SET_BIT(EXTI_RTSR,Copyu8ID);CLR_BIT(EXTI_FTSR,Copyu8ID);break;
		case EXTI_FALLING    : CLR_BIT(EXTI_RTSR,Copyu8ID);SET_BIT(EXTI_FTSR,Copyu8ID);break;
		case EXTI_ON_CHANGE  : SET_BIT(EXTI_RTSR,Copyu8ID);SET_BIT(EXTI_FTSR,Copyu8ID);break;
	}
	/*Selecting the port for the  the choosed interupt  line */
	 MSKP_REG(EXTICR->SYSCFG_EXTICR[Copyu8ID/4],4*Copyu8ID-(16*(Copyu8ID/4)),Copyu8Port);
	
	/*Assign ISR function for the interupt*/
	EXTI_CallBackFunc_LINE[Copyu8ID]=CallBackFun;
 }
 
  void EXTI_voidDisableInt(EXTI_LINE Copyu8ID){
	  /*masking the interupt or the event*/
	  CLR_BIT(EXTI_IMR,Copyu8ID);
	  CLR_BIT(EXTI_EMR,Copyu8ID);
  }
  
  void EXTI_SWInterupt(EXTI_LINE Copyu8ID){
	  /*enabling the interupt and trigering the SWIER*/
	  SET_BIT(EXTI_IMR,Copyu8ID);
	  SET_BIT(EXTI_SWIER,Copyu8ID);
  }
  
  EXTIPendFlag_state EXTI_u8GetPendingFlag(EXTI_LINE Copyu8ID){
	  EXTIPendFlag_state LINE_Flag = GET_BIT(EXTI_PR,Copyu8ID);
	  return LINE_Flag;
  }
  
 /*IRQ Handlers :
 Process the ISR function 
 clear the pending flag 
 */
 
void EXTI0_IRQHandler(void)
{
	EXTI_CallBackFunc_LINE[0]() ;
	SET_BIT(EXTI_PR,EXTI0) ; 
}

void EXTI1_IRQHandler(void)
{
	EXTI_CallBackFunc_LINE[1]() ;
	SET_BIT(EXTI_PR,EXTI1) ; 
}

void EXTI2_IRQHandler(void)
{
	EXTI_CallBackFunc_LINE[2]() ;
	SET_BIT(EXTI_PR,EXTI2) ; 
}

void EXTI3_IRQHandler(void)
{
	EXTI_CallBackFunc_LINE[3]() ;
	SET_BIT(EXTI_PR,EXTI3) ; 
}
void EXTI4_IRQHandler(void)
{
	EXTI_CallBackFunc_LINE[4]() ;
	SET_BIT(EXTI_PR,EXTI4) ; 
}

void EXTI9_5_IRQn(void)	{
	 

if (EXTI_u8GetPendingFlag(EXTI5) == PENDING){
	EXTI_CallBackFunc_LINE[5]() ;
	SET_BIT(EXTI_PR,EXTI5) ; 
}

if (EXTI_u8GetPendingFlag(EXTI6) == PENDING){
	EXTI_CallBackFunc_LINE[6]() ;
	SET_BIT(EXTI_PR,EXTI6) ; 
} 

if (EXTI_u8GetPendingFlag(EXTI7) == PENDING){
	EXTI_CallBackFunc_LINE[7]() ;
	SET_BIT(EXTI_PR,EXTI7) ; 
}

if (EXTI_u8GetPendingFlag(EXTI8) == PENDING){
	EXTI_CallBackFunc_LINE[8]() ;
	SET_BIT(EXTI_PR,EXTI8) ; 
}

if (EXTI_u8GetPendingFlag(EXTI9) == PENDING){
	EXTI_CallBackFunc_LINE[9]() ;
	SET_BIT(EXTI_PR,EXTI9) ; 
}
}
void EXTI15_10_IRQHandler(void){
	
if (EXTI_u8GetPendingFlag(EXTI10) == PENDING){
	EXTI_CallBackFunc_LINE[10]() ;
	SET_BIT(EXTI_PR,EXTI10) ; 
}

if (EXTI_u8GetPendingFlag(EXTI11) == PENDING){
	EXTI_CallBackFunc_LINE[11]() ;
	SET_BIT(EXTI_PR,EXTI11) ; 
} 

if (EXTI_u8GetPendingFlag(EXTI12) == PENDING){
	EXTI_CallBackFunc_LINE[12]() ;
	SET_BIT(EXTI_PR,EXTI12) ; 
}

if (EXTI_u8GetPendingFlag(EXTI13) == PENDING){
	EXTI_CallBackFunc_LINE[13]() ;
	SET_BIT(EXTI_PR,EXTI13) ; 
}

if (EXTI_u8GetPendingFlag(EXTI14) == PENDING){
	EXTI_CallBackFunc_LINE[14]() ;
	SET_BIT(EXTI_PR,EXTI14) ; 
}

if (EXTI_u8GetPendingFlag(EXTI15) == PENDING){
	EXTI_CallBackFunc_LINE[15]() ;
	SET_BIT(EXTI_PR,EXTI15) ; 
}
}
 

