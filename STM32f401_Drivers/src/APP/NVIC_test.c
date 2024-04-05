/*
 * NVIC_Test.c
 *
 *  Created on: Apr 4, 2024
 *      Author: Nada
 */

/*

#include "RCC.h"
#include "NVIC.h"
#include "LED.h"

int main (void)
{
    u8 y = 5;
    u8 *x = &y;
    
    NVIC_EnableIRQ(EXTI0);
    NVIC_SetPendingIRQ(EXTI0);
    NVIC_GetPendingIRQ(EXTI0,x);
    NVIC_ClearPendingIRQ(EXTI0);
    NVIC_GetActive(EXTI0,x);
    NVIC_SetPriority(EXTI0, PRIGROUP0, 8, 0);
    NVIC_GetPriority(EXTI0,x);
    NVIC_GenerateSWInt(EXTI0);
    NVIC_DisableIRQ(EXTI0);

    while(x==8)
    {
        //if we reached here then the NVIC_GetPriority works perfectly
    }
    return 0   ;
}

*/