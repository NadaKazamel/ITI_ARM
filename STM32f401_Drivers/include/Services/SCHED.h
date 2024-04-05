/*
 * SCHED.h
 *
 *  Created on: Mar 26, 2024
 *      Author: Nada
 */


#ifndef SERVICES_SCHED_H_
#define SERVICES_SCHED_H_

#include "std_types.h"

#define SCHED_TICK_TIME     500

typedef void (*Runnable_CBF) (void);

typedef struct{
	char* name;
	u32 Periodicity_Ms;
	Runnable_CBF CBF;
    u32 Delay_Ms;
}RunnableInfo_t;


void SCHED_Init(void);
void SCHED_Start(void);

#endif /* SERVICES_SCHED_H_ */