/*
 * SWITCH_cfg.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Nada
 */

#include "SWITCH_cfg.h"
#include "SWITCH.h"
#include "GPIO.h"

const SWITCH_PinConfig_t Switches[Switches_Number]=
{
    [Switch_One]={
        .Port = GPIO_A,
        .Pin = GPIO_Pin0,
        .Connection = SWITCH_IP_PD,
    }
};