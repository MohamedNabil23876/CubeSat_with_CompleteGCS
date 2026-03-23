
// LIB
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_Intrface.h"
#include "GPIO_Interface.h"
#include "DHT_Interface.h"

int main (void)
{
	u8 Temp_1=0;
	u8 Temp_2=0;
	u8 Rh_1=0;
	u8 Rh_2=0;
	u8 Sum=0;
	u16 Temp=0;
	u16 Rh=0;
	MRCC_VoidInit();
	RCC_VoidEnableCLK(AHB1,GPIOA_PERIPHERAL);

	while (1)
	{
		DHT_VoidInit();
		DHT_u8CheckResponce();
		Temp_1=DHT_u8ReadData();
		Temp_2=DHT_u8ReadData();
		Rh_1=DHT_u8ReadData();
		Rh_2=DHT_u8ReadData();
		Sum=DHT_u8ReadData();
		Temp=((Temp_1<<8)|Temp_2);
		Rh=((Rh_1<<8)|Rh_2);


	}
}

