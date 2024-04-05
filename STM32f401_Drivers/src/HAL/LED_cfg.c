/*
 * LED_cfg.c
 *
 *  Created on: Mar 5, 2024
 *      Author: Nada
 */

#include "GPIO.h"
#include "LED.h"

const LED_cfg_t Leds [LEDs_Number] =    {   [LED_1] =   {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin0,
                                                            .Connection = LED_Conn_FW,
                                                            .Default_Status = LED_Status_Off
                                                        },
                                            [LED_2] =   {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin1,
                                                            .Connection = LED_Conn_FW,
                                                            .Default_Status = LED_Status_Off
                                                        },
                                            [LED_3] =   {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin2,
                                                            .Connection = LED_Conn_FW,
                                                            .Default_Status = LED_Status_Off
                                                        }
                                        };