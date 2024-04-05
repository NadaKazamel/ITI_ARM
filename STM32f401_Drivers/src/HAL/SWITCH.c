/*
 * SWITCH.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Nada
 */

#include "GPIO.h"
#include "SWITCH.h"

#define ONE                         1
#define MASK_SHIFT_THREE            3

extern const SWITCH_PinConfig_t Switches[Switches_Number];
u8 SWITCH_AllSwitchStatus[Switches_Number];

void SWITCH_Init(void)
{
    GPIO_PinConfig_t Switch;

    for (u8 iterator = 0; iterator < Switches_Number; iterator++)
    {
        Switch.Port = Switches[iterator].Port;
        Switch.Pin = Switches[iterator].Pin;
        Switch.Configuration = Switches[iterator].Connection;

        GPIO_InitPinConfig(&Switch);
    }
}

u8 SWITCH_getStatus(u8 Switch_Name, u8* Status)
{
    u8 ErrorStatus = Ok;

    if (Switch_Name < Switch_One || Switch_Name > Switches_Number)
    {
        ErrorStatus = WrongChoice;
    }   

    else if (Status == NULL)
    {
        ErrorStatus = NullPointer;
    }

    else
    {
        *Status = SWITCH_AllSwitchStatus[Switch_Name];
    }

    return ErrorStatus;
}

void SWITCH_Runnable (void)
{
    u8 current;

    static u8 prev_state[Switches_Number];
    
    static u32 counter[Switches_Number];

    for (u8 iterator = 0; iterator < Switches_Number; iterator++)
    {
        GPIO_GetPinStatus(Switches[iterator].Port, Switches[iterator].Pin, &current);
        
        if (current == prev_state[iterator])
        {
            counter[iterator]++;
        }

        else
        {
             counter[iterator] = 0 ;
        }

        if (counter[iterator] % 5 == 0)
        {
            SWITCH_AllSwitchStatus[iterator] = current ^ (((Switches[iterator].Connection) >> MASK_SHIFT_THREE) & ONE);
        }
        
        prev_state[iterator] = current;
    }
}