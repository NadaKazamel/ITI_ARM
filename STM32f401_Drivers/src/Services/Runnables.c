/*
 * Runnables.h
 *
 *  Created on: Mar 28, 2024
 *      Author: Nada
 */

#include "Runnables.h"
#include "SCHED.h"

extern void Traffic_Runnable (void);

const RunnableInfo_t Runnables[Runnables_Numbers] =     {   [TrafficLights] =   {
                                                                            .name = "Traffic Lights",
                                                                            .Periodicity_Ms = 1000,
                                                                            .CBF = &Traffic_Runnable,
                                                                            .Delay_Ms = 0
                                                                        }
                                                        };

