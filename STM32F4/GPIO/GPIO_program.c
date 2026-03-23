/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPIO_program_c
 *       Module:  -
 *
 *  Description:  C program for GPIO functions   
 *  
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_private.h"
#include "GPIO_interface.h"

/**********************************************************************************************************************
 * GPIO PINS Functions
 *********************************************************************************************************************/

void GPIO_voidSetPinMode(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_MODE Copy_u8PinMode){
	switch(Copy_u8Port){
		case GPIO_PORT_A : MSK_2BIT(GPIO_A_MODER,2*Copy_u8Pin,Copy_u8PinMode);break;
		case GPIO_PORT_B : MSK_2BIT(GPIO_B_MODER,2*Copy_u8Pin,Copy_u8PinMode);break;
		case GPIO_PORT_C : MSK_2BIT(GPIO_C_MODER,2*Copy_u8Pin,Copy_u8PinMode);break;

	}
	
}
void GPIO_voidPinOPT(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_OPT Copy_u8PinOPT){
	switch(Copy_u8Port){
		case GPIO_PORT_A : MSK_1BIT(GPIO_A_OTYPER,Copy_u8Pin,Copy_u8PinOPT);break;
		case GPIO_PORT_B : MSK_1BIT(GPIO_B_OTYPER,Copy_u8Pin,Copy_u8PinOPT);break;
		case GPIO_PORT_C : MSK_1BIT(GPIO_C_OTYPER,Copy_u8Pin,Copy_u8PinOPT);break;

	}
}
void GPIO_voidPinPullType(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_PLT Copy_u8PinPLT){
	switch(Copy_u8Port){
		case GPIO_PORT_A : MSK_2BIT(GPIO_A_PUPDR,2*Copy_u8Pin,Copy_u8PinPLT);break;
		case GPIO_PORT_B : MSK_2BIT(GPIO_B_PUPDR,2*Copy_u8Pin,Copy_u8PinPLT);break;
		case GPIO_PORT_C : MSK_2BIT(GPIO_C_PUPDR,2*Copy_u8Pin,Copy_u8PinPLT);break;

	}
}
void GPIO_voidSetPinValue(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_VALUE Copy_u8PinValue){
	switch(Copy_u8Port){
		case GPIO_PORT_A : MSK_1BIT(GPIO_A_ODR,Copy_u8Pin,Copy_u8PinValue);break;
		case GPIO_PORT_B : MSK_1BIT(GPIO_B_ODR,Copy_u8Pin,Copy_u8PinValue);break;
		case GPIO_PORT_C : MSK_1BIT(GPIO_C_ODR,Copy_u8Pin,Copy_u8PinValue);break;

	}
}
GPIO_PIN_VALUE GPIO_voidReadPinValue(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin){
	GPIO_PIN_VALUE PIN_VALUE;
	switch(Copy_u8Port){
		case GPIO_PORT_A : PIN_VALUE=GET_BIT(GPIO_A_IDR,Copy_u8Pin);break;
		case GPIO_PORT_B : PIN_VALUE=GET_BIT(GPIO_B_IDR,Copy_u8Pin);break;
		case GPIO_PORT_C : PIN_VALUE=GET_BIT(GPIO_C_IDR,Copy_u8Pin);break;

	}
	return PIN_VALUE;
}

void GPIO_voidPinSpeed(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_SPEED_t Copy_u8PinST){
	switch(Copy_u8Port){
		case GPIO_PORT_A : MSK_2BIT(GPIO_A_OSPEEDR,2*Copy_u8Pin,Copy_u8PinST);break;
		case GPIO_PORT_B : MSK_2BIT(GPIO_B_OSPEEDR,2*Copy_u8Pin,Copy_u8PinST);break;
		case GPIO_PORT_C : MSK_2BIT(GPIO_C_OSPEEDR,2*Copy_u8Pin,Copy_u8PinST);break;

	}
}

/**********************************************************************************************************************
 * GPIO BYTES Functions
 *********************************************************************************************************************/
void GPIO_voidSetByteMode(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin,GPIO_PIN_MODE Copy_u8PinMode){
	switch(Copy_u8Port){
		u8 POS=0;
		case GPIO_PORT_A :  for( POS=0;POS<=14;POS=POS+2){
								if((2*Copy_u8StartPin+POS)>=31)
								break;
							MSKP_REG(GPIO_A_MODER,2*Copy_u8StartPin+POS,Copy_u8PinMode);
								}
							break;
		case GPIO_PORT_B : for( POS=0;POS<=14;POS=POS+2){
								if((2*Copy_u8StartPin+POS)>=31)
								break;
							MSKP_REG(GPIO_C_MODER,2*Copy_u8StartPin+POS,Copy_u8PinMode);
								}
							break;
		case GPIO_PORT_C : for( POS=0;POS<=14;POS=POS+2){
								if((2*Copy_u8StartPin+POS)>=31)
								break;
							MSKP_REG(GPIO_C_MODER,2*Copy_u8StartPin+POS,Copy_u8PinMode);
								}
							break;

	}
}

void GPIO_voidByteOPT(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin,GPIO_PIN_OPT Copy_u8PinOPT){
	u8 POS=0;
	switch(Copy_u8Port){
		case GPIO_PORT_A : for( POS=0;POS<=7;POS++){
							if(Copy_u8StartPin+POS>=31)
								break;
							MSKP_REG(GPIO_A_OTYPER,Copy_u8StartPin+POS,Copy_u8PinOPT);
							}
							break;
		
		case GPIO_PORT_B : for( POS=0;POS<=7;POS++){
							if(Copy_u8StartPin+POS>=31)
								break;
							MSKP_REG(GPIO_B_OTYPER,Copy_u8StartPin+POS,Copy_u8PinOPT);
							}
							break;
		case GPIO_PORT_C : for( POS=0;POS<=7;POS++){
							if(Copy_u8StartPin+POS>=31)
								break;
							MSKP_REG(GPIO_C_OTYPER,Copy_u8StartPin+POS,Copy_u8PinOPT);
							}
							break;

	}
}

void GPIO_voidBytePullType(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin,GPIO_PIN_PLT Copy_u8PinPLT){
	switch(Copy_u8Port){u8 POS =0;
		case GPIO_PORT_A :  for( POS=0;POS<=14;POS=POS+2){
								if((2*Copy_u8StartPin+POS)>=31)
								break;
							MSKP_REG(GPIO_A_PUPDR,2*Copy_u8StartPin+POS,Copy_u8PinPLT);
								}
							break;
		case GPIO_PORT_B : for( POS=0;POS<=14;POS=POS+2){
								if((2*Copy_u8StartPin+POS)>=31)
								break;
							MSKP_REG(GPIO_C_PUPDR,2*Copy_u8StartPin+POS,Copy_u8PinPLT);
								}
							break;
		case GPIO_PORT_C : for( POS=0;POS<=14;POS=POS+2){
								if((2*Copy_u8StartPin+POS)>=31)
								break;
							MSKP_REG(GPIO_C_PUPDR,2*Copy_u8StartPin+POS,Copy_u8PinPLT);
								}
							break;

	}
}
void GPIO_voidSetByteValue(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin,u8 Copy_u8ByteValue){
	switch(Copy_u8Port){
		case GPIO_PORT_A :	MSKP_REG(GPIO_A_ODR,Copy_u8StartPin,Copy_u8ByteValue);
							break;
		case GPIO_PORT_B : MSKP_REG(GPIO_B_ODR,Copy_u8StartPin,Copy_u8ByteValue);
							break;
		case GPIO_PORT_C : MSKP_REG(GPIO_C_ODR,Copy_u8StartPin,Copy_u8ByteValue);
							break;
	}
}

u8 GPIO_voidReadByteValue(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin){
	u8 BYTE_VALUE;
	switch(Copy_u8Port){
		case GPIO_PORT_A : BYTE_VALUE=GET_BYTE(GPIO_A_IDR,Copy_u8StartPin);break;
		case GPIO_PORT_B : BYTE_VALUE=GET_BYTE(GPIO_B_IDR,Copy_u8StartPin);break;
		case GPIO_PORT_C : BYTE_VALUE=GET_BYTE(GPIO_C_IDR,Copy_u8StartPin);break;

	}
	return BYTE_VALUE;
}

