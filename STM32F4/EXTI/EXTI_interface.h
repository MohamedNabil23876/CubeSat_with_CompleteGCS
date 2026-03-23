/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  EXTI_INTERFACE_H
 *       Module:  -
 *
 *  Description:   header for the EXTI interface types     
 *  
 *********************************************************************************************************************/
#ifndef  EXTI_INTERFACE_H
#define  EXTI_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
typedef enum {
	EXTI0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	EXTI5,
	EXTI6,
	EXTI7,
	EXTI8,
	EXTI9,
	EXTI10,
	EXTI11,
	EXTI12,
	EXTI13,
	EXTI14,
	EXTI15,
	EXTI16,
	EXTI17,
	EXTI18,
	EXTI20,
	EXTI21,
	EXTI22,
}EXTI_LINE;
 
 typedef enum {
	 PORT_A,
	 PORT_B,
	 PORT_C,
	 PORT_D,
	 PORT_E,
	 PORT_F,
	 PORT_G,
	 PORT_H,
	 PORT_I,
	 }EXTI_PORT;
	 
 typedef enum {
	 EXTI_RISING,
	 EXTI_FALLING,
	 EXTI_ON_CHANGE,
 }EXTI_TRIG;
 
 typedef enum {
	 NOT_PENDING,
	 PENDING, 
 }EXTIPendFlag_state;
 
 typedef enum {
	 EXTI_INTERUPT,
	 EXTI_EVENT,
 }EXTI_TYPE;
 
 
 void EXTI_voidInteruptInit(EXTI_LINE Copyu8ID,EXTI_PORT Copyu8Port ,EXTI_TRIG Copyu8Trig,EXTI_TYPE Copyu8Type,void (*CallBackFun) (void));
 void EXTI_voidDisableInt(EXTI_LINE Copyu8ID);
 void EXTI_SWInterupt(EXTI_LINE Copyu8ID);
 EXTIPendFlag_state EXTI_u8GetPendingFlag(EXTI_LINE Copyu8ID);

 #endif //  __EXTI_interface_H__
