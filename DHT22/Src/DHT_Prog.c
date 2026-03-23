/*
 * DHT_Prog.c
 *
 *  Created on: Mar 9, 2023
 *      Author: hp
 */

// LIB
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL

#include "GPIO_Interface.h"
#include "RCC_Intrface.h"

//HAL DHT Files
#include "DHT_Interface.h"
#include "DHT_Cfg.h"
#include "DHT_Pri.h"

void DHT_VoidInit(void)
{
	// SET DHT Pin Output
	// pin Make DHT CLK
	/*                20-40MS
	 * ----          ---------------
	 *    \       /                 \
	 *      ------                    --------
	 *      18ms
	 * */
	PinConfig_t DHT_Pin={DHT22_PORT,DHT22_PIN,
			GPIO_OUTPUT,GPIO_OUTPUT_LOW_SPEED,
			GPIO_OUTPUT_PUSH_PULL,0,0};
	MGPIO_VoidSetPinConfg(&DHT_Pin);
	GPIO_voidSetPinValue(DHT22_PORT,DHT22_PIN, GPIO_u8_PIN_LOW);
	// delay 18 mS
	GPIO_voidSetPinValue(DHT22_PORT,DHT22_PIN, GPIO_u8_PIN_HIGH);
	// delay 20-40 Ms

	// SET pin input to Get response
	(DHT_Pin.GPIO_u8Mode)=	GPIO_INPUT;
	MGPIO_VoidSetPinConfg(&DHT_Pin);

}

u8 DHT_u8CheckResponce(void)
{
	u8 Local_Responce=0;
	// delay 40 MS
	if (GET_BIT(DHT22_PORT,DHT22_PIN)==0) // if Pin low
	{
		/*                  80M
		 *  if low    _____________
		 *  at 40 MS |             |  start transmit data
		 *_____|_____|             |__________
		 *      80Ms
		 * */
		// delay 80 MS
		if (GET_BIT(DHT22_PORT,DHT22_PIN)==1) // if high
		{
			Local_Responce=1;    // start trans
		}
		else Local_Responce=0;

		while (GET_BIT(DHT22_PORT,DHT22_PIN)); // pin become low

		return Local_Responce;

	}
}

u8 DHT_u8ReadData(void)
{

	/*     high-voltage-level is around 26-28 us, the bit is “0”
	 *     __________
	 *    |          |
	 * ___|          |___
	 *
	 * */

	/*     high-voltage-level is around 70 us u, the bit is “1”
	 *     ___________________
	 *    |                   |
	 * ___|                   |___
	 *
	 * */

	u8 local_8bitData=0;// to save data
	 u8 local_couter;  // to pickup 8 bit
	for(local_couter=0;local_couter<8;local_couter++)
	{
		// wait bin to be high
		while(!(GET_BIT(DHT22_PORT,DHT22_PIN)));
		// delay 40 MS
		// if pin low data = zero
		if(GET_BIT(DHT22_PORT,DHT22_PIN)==0)
		{
			// write zero
			local_8bitData&=~(1<<(7-local_couter));
		}
		else local_8bitData|=(1<<(7-local_couter)); // write one

		// wait bin to be low
		while((GET_BIT(DHT22_PORT,DHT22_PIN))==0);

	}
	return local_8bitData;

}
