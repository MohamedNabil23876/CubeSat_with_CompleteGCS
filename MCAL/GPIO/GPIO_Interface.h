/*
 * GPIO_Interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */

#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_


typedef struct
{
	u8 GPIO_u8Port;
	u8 GPIO_u8PinNumber;
	u8 GPIO_u8Mode;
	u8 GPIO_u8OutputSpeed;
	u8 GPIO_u8OutputType;
	u8 GPIO_u8PullUpDown;
	u8 GPIO_u8AltFuncOption;
}PinConfig_t;



/****************************	GPIO_u8Port	*****************************************/

#define	GPIO_u8_GPIOA					0
#define	GPIO_u8_GPIOB					1
#define	GPIO_u8_GPIOC					2
/****************************	GPIO_u8PinNumber	********************************/

#define	GPIO_u8_PIN0					0
#define	GPIO_u8_PIN1					1
#define	GPIO_u8_PIN2					2
#define	GPIO_u8_PIN3					3
#define	GPIO_u8_PIN4					4
#define	GPIO_u8_PIN5					5
#define	GPIO_u8_PIN6					6
#define	GPIO_u8_PIN7					7
#define	GPIO_u8_PIN8					8
#define	GPIO_u8_PIN9					9
#define	GPIO_u8_PIN10					10
#define	GPIO_u8_PIN11					11
#define	GPIO_u8_PIN12					12
#define	GPIO_u8_PIN13					13
#define	GPIO_u8_PIN14					14
#define	GPIO_u8_PIN15					15

/*********************************	Pin_State	***********************************/

#define	GPIO_u8_PIN_LOW					0
#define	GPIO_u8_PIN_HIGH				1

/*********************************	PORT_State	***********************************/

#define	GPIO_u8_PORT_LOW					0xFFFF
#define	GPIO_u8_PORT_HIGH				    0

/******************************	  GPIO_u8Mode	 *********************************/

#define	GPIO_INPUT						0b00
#define	GPIO_OUTPUT						0b01
#define	GPIO_ALTFUNC   					0b10
#define GPIO_ANALOG						0b11

/****************************	GPIO_u8OutputSpeed	********************************/
#define	GPIO_OUTPUT_LOW_SPEED						0b00
#define	GPIO_OUTPUT_MEDIUM_SPEED					0b01
#define	GPIO_OUTPUT_HIGH_SPEED   					0b10
#define GPIO_OUTPUT_VERY_HIGH_SPEED					0b11

/****************************	GPIO_u8OutputType	********************************/
#define	GPIO_OUTPUT_PUSH_PULL						0b0
#define	GPIO_OUTPUT_OPEN_DRAIN						0b1

/****************************	GPIO_u8PullUpDown	********************************/
#define	GPIO_PORT_NO_PULL_UP_DOWN				    0b00
#define	GPIO_PORT_PULL_UP					        0b01
#define	GPIO_PORT_PULL_DOWN   					    0b10

/****************************	GPIO_u8AltFuncOption	****************************/
#define	GPIO_AF0						            0b0000
#define	GPIO_AF1						            0b0001
#define	GPIO_AF2						            0b0010
#define	GPIO_AF3						            0b0011
#define	GPIO_AF4						            0b0100
#define	GPIO_AF5						            0b0101
#define	GPIO_AF6						            0b0110
#define	GPIO_AF7						            0b0111
#define	GPIO_AF8						            0b1000
#define	GPIO_AF9						            0b1001
#define	GPIO_AF10						            0b1010
#define	GPIO_AF11						            0b1011
#define	GPIO_AF12						            0b1100
#define	GPIO_AF13						            0b1101
#define	GPIO_AF14						            0b1110
#define	GPIO_AF15						            0b1111


/****************************** function prototype ***************************/


/******************************************************************************
 * Function Name:  GPIO_voidPinInit
 *
 * Description:	the function initialize the required pin configuration  options
 *
 * Parameters: 1- AS_Pin_Cfg: const pointer to GPIO_PinConfig_t structure which holds the configurations
 *
 * Return:	ErrorState , Type:u8
 *
 ******************************************************************************/
u8 MGPIO_VoidSetPinConfg( const PinConfig_t * AS_Pin_Cfg );


/******************************************************************************
 * Function Name:  GPIO_voidSetPinValue
 *
 * Description:	the function sets an output values on the output pin
 *
 * Parameters: 1- Copy_u8Port : the port of the required output pin, refer to port possible options
 * 			   2- Copy_u8pin  : the pin number of the required output pin, refer to pin number possible options
 * 			   3- Copy_u8value: the required pin state, refer to pin value possible options
 *
 * Return:	ErrorState , Type:u8
 *
 ******************************************************************************/
u8 GPIO_voidSetPinValue(u8 Copy_u8Port,u8 Copy_u8pin,u8 Copy_u8value);
/********************************************************************************/


u8 GPIO_voidSetPortValue(u8 Copy_u8Port, u16 Copy_u16value);

u8 GPIO_voidReadPinValue(u8 Copy_u8Port,u8 Copy_u8pin,u8* Copy_pu8value);

u8 GPIO_TogglePinValue(u8 Copy_u8Port,u8 Copy_u8pin);
void MGPIO_voidSetAF(u8 copy_u8PORT, u8 copy_u8PIN, u8 copy_u8AlternateFunctionNo);




#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */
