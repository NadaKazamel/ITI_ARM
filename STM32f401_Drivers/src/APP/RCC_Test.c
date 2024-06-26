/*
 * RCC_Test.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Nada
 */

/*
#include "RCC.h"

int main(void)
{

	RCC_EnableClk(Clock_HSE);

	RCC_SetPLLSource(Clock_HSI);

	RCC_ConfigPLL(8, 192, 6, 8);

	RCC_EnableClk(Clock_PLL);

	RCC_SelectSysClk(Clock_HSE);

	RCC_DisableClk(Clock_PLL);

	RCC_EnableAHB1Peri(AHB1ENR_GPIOAEN);

	RCC_DisableAHB1Peri(AHB1ENR_GPIOAEN);

	RCC_EnableAHB2Peri(AHB2ENR_OTGFSEN);

	RCC_DisableAHB2Peri(AHB2ENR_OTGFSEN);

	RCC_EnableAPB1Peri(APB1ENR_I2C1EN);

	RCC_DisableAPB1Peri(APB1ENR_I2C1EN);

	RCC_EnableAPB2Peri(APB2ENR_TIM10EN);

	RCC_DisableAPB2Peri(APB2ENR_TIM10EN);

	u8 x = 10;

	RCC_CheckClkStatus(Clock_HSI, &x);

	while(x==1)
	{
		//if we reached here then the CheckClkStatus works perfectly
	}

	return 0;
}

*/