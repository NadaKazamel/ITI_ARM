/*
 * TrafficLights_Test.c
 *
 *  Created on: Apr 4, 2024
 *      Author: Nada
 */

/* This is to test the following drivers:
    -GPIO
    -RCC
    -LED
    -STK
    -SCHED
*/

#include "RCC.h"
#include "LED.h"
#include "SCHED.h"
#include "Runnables.h"

int main ()
{
    RCC_EnableAHB1Peri(AHB1ENR_GPIOAEN);
    LED_Init();
    SCHED_Init();
    SCHED_Start();
}