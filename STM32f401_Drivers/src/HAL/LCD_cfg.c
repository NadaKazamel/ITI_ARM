/*
 * LCD.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Nada
 */

#include "GPIO.h"
#include "LCD_cfg.h"

const LCD_Config_t LCD_Pins_Cfg[LCD_Pins] = {   [RS] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin0
                                                        },
                                                [RW] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin1
                                                        },
                                                [EN] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin2
                                                        },
                                                [D0] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin3
                                                        },
                                                [D1] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin4
                                                        },
                                                [D2] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin5
                                                        },
                                                [D3] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin6,
                                                        },
                                                [D4] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin7
                                                        },
                                                [D5] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin8
                                                        },
                                                [D6] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin9
                                                        },
                                                [D7] =  {
                                                            .Port = GPIO_A,
                                                            .Pin = GPIO_Pin10
                                                        }
                                            };