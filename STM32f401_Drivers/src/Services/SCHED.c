/*
 * SCHED.c
 *
 *  Created on: Mar 26, 2024
 *      Author: Nada
 */

#include "SCHED.h"
#include "STK.h"
#include "Runnables.h"

typedef struct
{
    const RunnableInfo_t *Runnable;
    u32 RemainingTime;
}RunnableData_t;


static volatile u32 PendingTicks = 0;

extern const RunnableInfo_t Runnables[Runnables_Numbers];

RunnableData_t Sched_Runnables[Runnables_Numbers];

static void SCHED (void)
{
    for (u8 iterator = 0; iterator < Runnables_Numbers; iterator++)
    {
        if(Sched_Runnables[iterator].Runnable->CBF && Sched_Runnables[iterator].RemainingTime == 0)
        {
            Sched_Runnables[iterator].Runnable->CBF();
            Sched_Runnables[iterator].RemainingTime = Sched_Runnables[iterator].Runnable->Periodicity_Ms;
        }
        Sched_Runnables[iterator].RemainingTime -= SCHED_TICK_TIME;
    }
}

static void IncPendingTicks (void)
{
    PendingTicks++;
}

void SCHED_Init(void)
{
    STK_SetTimeMs(SCHED_TICK_TIME);
    STK_SetCallBack(IncPendingTicks,0);

    for (u8 iterator = 0; iterator < Runnables_Numbers; iterator++)
    {
        Sched_Runnables[iterator].Runnable = &Runnables[iterator];
        Sched_Runnables[iterator].RemainingTime = Sched_Runnables[iterator].Runnable->Delay_Ms;
    }
}

void SCHED_Start(void)
{
    STK_Start();

    while(1)
    {
        if(PendingTicks)
        {
            PendingTicks--;
            SCHED();
        }
    }
}