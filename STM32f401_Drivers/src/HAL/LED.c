/*
 * LED.c
 *
 *  Created on: Mar 5, 2024
 *      Author: Nada
 */

#include "LED.h"
#include "GPIO.h"

extern const LED_cfg_t Leds [LEDs_Number];

u8 LED_Init(void)
{
    u8 ErrorStatus = Ok;

    GPIO_PinConfig_t Pin;
    Pin.Configuration = GPO_PP;
    Pin.Speed = GPIO_HIGH_SPEED;

    for (u32 i = 0; i < LEDs_Number; i++)
    {
        Pin.Port = Leds[i].Port;
        Pin.Pin = Leds[i].Pin;
        ErrorStatus = GPIO_InitPinConfig(&Pin);
        ErrorStatus = GPIO_SetPinStatus(Leds[i].Port,Leds[i].Pin,(Leds[i].Connection)^(Leds[i].Default_Status));
    }

    return ErrorStatus;
}

u8 LED_SetStatus(u8 Led, u8 status)
{
    u8 ErrorStatus = Ok;

    ErrorStatus = GPIO_SetPinStatus(Leds[Led].Port,Leds[Led].Pin,(Leds[Led].Connection)^status);

    return ErrorStatus;
}