/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPIO_INTERFACE_H
 *       Module:  -
 *
 *  Description:   header for the GPIO interface types     
 *  
 *********************************************************************************************************************/
#ifndef  GPIO_INTERFACE_H
#define  GPIO_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************
 
 /**********************************************************************************************************************
 * GPIO PORT ID
 *********************************************************************************************************************/
 typedef enum {
	 GPIO_PORT_A ,
	 GPIO_PORT_B ,
	 GPIO_PORT_C ,
 }GPIO_PORT_ID;
 
 
 /**********************************************************************************************************************
 * GPIO PIN ID
 *********************************************************************************************************************/

 typedef enum {
	 GPIO_PIN_0,
	 GPIO_PIN_1,
	 GPIO_PIN_2,
	 GPIO_PIN_3,
	 GPIO_PIN_4,
	 GPIO_PIN_5,
	 GPIO_PIN_6,
	 GPIO_PIN_7,
	 GPIO_PIN_8,
	 GPIO_PIN_9,
	 GPIO_PIN_10,
	 GPIO_PIN_11,
 	 GPIO_PIN_12,
	 GPIO_PIN_13,
	 GPIO_PIN_14,
	 GPIO_PIN_15,
 }GPIO_PIN_ID;
 
 /**********************************************************************************************************************
 * GPIO PIN MODE
 *********************************************************************************************************************/
typedef enum{
	GPIO_INPUT,
	GPIO_OUTPUT,
	GPIO_ALT,
	GPIO_ANALOG,
}GPIO_PIN_MODE;

/**********************************************************************************************************************
 * GPIO PIN OUTPUT TYPE
 *********************************************************************************************************************/
typedef enum{
	GPIO_PUSH_PULL,
	GPIO_OPEN_DRAIN,
}GPIO_PIN_OPT;


/**********************************************************************************************************************
 * GPIO PIN PULL Output TYPE
 *********************************************************************************************************************/
typedef enum{
	GPIO_PLT_NONE,
	GPIO_PLT_UP,
	GPIO_PLT_DOWN,
}GPIO_PIN_PLT;


/**********************************************************************************************************************
 * GPIO PIN  Output VALUE
 *********************************************************************************************************************/
typedef enum{
	GPIO_PIN_LOW,
	GPIO_PIN_HIGH,
}GPIO_PIN_VALUE;


typedef enum {
	GPIO_LOW,
	GPIO_MEDIUM,
	GPIO_HIGH,
	GPIO_VHIGH,
}GPIO_PIN_SPEED_t;
/**********************************************************************************************************************
 * GPIO Pin Functions
 *********************************************************************************************************************/

void GPIO_voidSetPinMode(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_MODE Copy_u8PinMode);
void GPIO_voidPinOPT(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_OPT Copy_u8PinOPT);
void GPIO_voidPinPullType(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_PLT Copy_u8PinPLT);
void GPIO_voidSetPinValue(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_VALUE Copy_u8PinValue);
GPIO_PIN_VALUE GPIO_voidReadPinValue(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin);
void GPIO_voidPinSpeed(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8Pin,GPIO_PIN_SPEED_t Copy_u8PinST);

/**********************************************************************************************************************
 * GPIO BYTES Functions
 *********************************************************************************************************************/
void GPIO_voidSetByteMode(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin,GPIO_PIN_MODE Copy_u8PinMode);
void GPIO_voidByteOPT(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin,GPIO_PIN_OPT Copy_u8PinOPT);
void GPIO_voidBytePullType(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin,GPIO_PIN_PLT Copy_u8PinPLT);
void GPIO_voidSetByteValue(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin,u8 Copy_u8ByteValue);
u8 GPIO_voidReadByteValue(GPIO_PORT_ID Copy_u8Port,GPIO_PIN_ID Copy_u8StartPin);

#endif
