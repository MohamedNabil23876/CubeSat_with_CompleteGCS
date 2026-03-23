/*
 * GPIO_Pro.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: nabil
 */
// LIB
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

// MACL Drivers
// GPIO
#include "GPIO_Pri.h"
#include "GPIO_Cfg.h"
#include "GPIO_Interface.h"


static  GPIO_Reg_Cfg* Port_Num[MAX_PORT_NUM]={GPIOA,GPIOB,GPIOC,};

u8 MGPIO_VoidSetPinConfg(const PinConfig_t * AS_Pin_Cfg )
{
	u8 Local_Erorr_state =OK;

	if (AS_Pin_Cfg == NULL)
	{
		Local_Erorr_state=NULL_POINTER;
	}
	else if (((AS_Pin_Cfg->GPIO_u8Port )<=GPIO_u8_GPIOC)&&
			((AS_Pin_Cfg->GPIO_u8PinNumber )<=GPIO_u8_PIN15))
	{
		// set Pin mode
		(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->MODER) &=~(0b11 <<AS_Pin_Cfg->GPIO_u8PinNumber*2);
		(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->MODER )|=((AS_Pin_Cfg->GPIO_u8Mode) <<(AS_Pin_Cfg->GPIO_u8PinNumber)*2);

		// set input type
		(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->PUPDR)&=~(0b11<<(AS_Pin_Cfg->GPIO_u8PinNumber)*2);
		(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->PUPDR)|=((AS_Pin_Cfg->GPIO_u8PullUpDown)<<(AS_Pin_Cfg->GPIO_u8PinNumber)*2);
		if (AS_Pin_Cfg->GPIO_u8Mode==GPIO_OUTPUT)
		{
			// Set output type
			(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->OTYPER )&=~(0b1<<AS_Pin_Cfg->GPIO_u8PinNumber);
			(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->OTYPER) |=(AS_Pin_Cfg->GPIO_u8Mode <<AS_Pin_Cfg->GPIO_u8PinNumber);

			// set Pin Speed
			(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->OSPEEDR) &=~(0b11 <<AS_Pin_Cfg->GPIO_u8PinNumber*2);
			(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->OSPEEDR) |=(AS_Pin_Cfg->GPIO_u8OutputSpeed <<AS_Pin_Cfg->GPIO_u8PinNumber*2);
		}
		else if(AS_Pin_Cfg->GPIO_u8Mode==GPIO_ALTFUNC)
		{
			// Swt AF function
			u8 Local_Reg_index=0;
			Local_Reg_index=(AS_Pin_Cfg->GPIO_u8PinNumber)/8;
			u8 local_pin_Num =(AS_Pin_Cfg->GPIO_u8PinNumber)%8;
			(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->AFR[Local_Reg_index])&=~(0b1111<<(local_pin_Num)*4);
			(Port_Num[AS_Pin_Cfg->GPIO_u8Port]->AFR[Local_Reg_index])|=((AS_Pin_Cfg->GPIO_u8AltFuncOption)<<(local_pin_Num)*4);
		}

	}
	else
	{
		Local_Erorr_state=NOK;
	}

	return Local_Erorr_state;

}
/******************************************************************************/
u8 GPIO_voidSetPinValue(u8 Copy_u8Port,u8 Copy_u8pin,u8 Copy_u8value)
{
	u8 Local_Erorr_state=OK;
	if (Copy_u8Port<=GPIO_u8_GPIOC && Copy_u8pin<=GPIO_u8_PIN15)
	{
		if (Copy_u8value==GPIO_u8_PIN_HIGH)
		{
			SET_BIT(Port_Num[Copy_u8Port]->ODR,Copy_u8pin);
		}
		else if (Copy_u8value==GPIO_u8_PIN_LOW)
		{
			CLR_BIT(Port_Num[Copy_u8Port]->ODR,Copy_u8pin);
		}
		else
		{
			Local_Erorr_state=NOK;
		}

	}
	else
	{
		Local_Erorr_state=NOK;
	}
	return Local_Erorr_state;
}
/********************************************************************************/


u8 GPIO_voidSetPortValue(u8 Copy_u8Port, u16 Copy_u16value)
{
	u8 Local_Erorr_state=OK;
	if (Copy_u8Port<=GPIO_u8_GPIOC &&Copy_u16value<=GPIO_u8_PORT_HIGH)
	{

		Port_Num[Copy_u8Port]->ODR=Copy_u16value;

	}
	else
	{
		Local_Erorr_state=NOK;
	}
	return Local_Erorr_state;

}

u8 GPIO_voidReadPinValue(u8 Copy_u8Port,u8 Copy_u8pin,u8* Copy_pu8value)
{
	u8 Local_Erorr_state=OK;
	if (Copy_u8Port<=GPIO_u8_GPIOC && Copy_u8pin<=GPIO_u8_PIN15 && Copy_pu8value!=NULL )
	{
		*Copy_pu8value =GET_BIT(Port_Num[Copy_u8Port]->IDR,Copy_u8pin);
	}
	else
	{
		Local_Erorr_state=NOK;
	}
	return Local_Erorr_state;
}

u8 GPIO_TogglePinValue(u8 Copy_u8Port,u8 Copy_u8pin)
{
	u8 Local_Erorr_state=OK;
		if (Copy_u8Port<=GPIO_u8_GPIOC && Copy_u8pin<=GPIO_u8_PIN15  )
		{
		TOGGLE_BIT(Port_Num[Copy_u8Port]->ODR,Copy_u8pin);
		}
		else
		{
			Local_Erorr_state=NOK;
		}
		return Local_Erorr_state;

}

void MGPIO_voidSetAF(u8 copy_u8PORT, u8 copy_u8PIN, u8 copy_u8AlternateFunctionNo)
{
	switch (copy_u8PORT)
	{
	case GPIO_u8_GPIOA:
		if (copy_u8PIN<8)
		{
			GPIOA_A->AFRL |= (copy_u8AlternateFunctionNo<<(copy_u8PIN*4));
		}
		else
		{
			GPIOA_A->AFRH |= (copy_u8AlternateFunctionNo<<((copy_u8PIN-8)*4));
		}
		break;
	case GPIO_u8_GPIOB:
		if (copy_u8PIN<8)
		{
			GPIOB_A->AFRL |= (copy_u8AlternateFunctionNo<<(copy_u8PIN*4));
		}
		else
		{
			GPIOB_A->AFRH |= (copy_u8AlternateFunctionNo<<((copy_u8PIN-8)*4));
		}
		break;
	case GPIO_u8_GPIOC:
		if (copy_u8PIN<8)
		{
			GPIOC_A->AFRL |= (copy_u8AlternateFunctionNo<<(copy_u8PIN*4));
		}
		else
		{
			GPIOC_A->AFRH |= (copy_u8AlternateFunctionNo<<((copy_u8PIN-8)*4));
		}
		break;
	}
}


