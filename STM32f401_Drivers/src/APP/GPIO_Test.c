/*
 * GPIO_Test.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Nada
 */

/*

#include "RCC.h"
#include "GPIO.h"

int main(void)
{

	RCC_EnableAHB1Peri(AHB1ENR_GPIOAEN);

	GPIO_PinConfig_t PinA0;
	PinA0.Port = GPIO_A;
	PinA0.Pin = GPIO_Pin0;
	PinA0.Configuration = GPO_PP;
	PinA0.Speed = GPIO_HIGH_SPEED;

	GPIO_InitPinConfig(&PinA0);

	GPIO_SetPinStatus(GPIO_A,GPIO_Pin0,GPIO_HIGH);

	u8 x=10;

	GPIO_GetPinStatus(GPIO_A,GPIO_Pin0,&x);

	while(x==1)
	{
		//if we reached here then the GetPinStatus works perfectly
	}

	return 0;
}
*/